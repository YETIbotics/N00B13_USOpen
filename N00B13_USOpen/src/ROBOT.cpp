
#include "ROBOT.h"

ROBOT::ROBOT() :Xbox(&Usb), Drive(*this), Hat(*this), Lift(*this), Fork(*this), Auton(*this)
	, RightEnc(RightEncInt, RightEncDig)
	, LeftEnc(LeftEncInt, LeftEncDig)
	, LiftEnc(LiftEncInt, LiftEncDig)
	
{

}

void ROBOT::Setup()
{
	Usb.Init(); 

	bno.begin();
	bno.setExtCrystalUse(true);

	Drive.Setup(); 
	Hat.Setup();
	Lift.Setup();
	Fork.Setup();
	Auton.Setup();

	lastStateUpdate = millis();
}

void ROBOT::Loop()
{
	Usb.Task();
	OI();

	if (millis() - lastStateUpdate > State.LoopFrequency)
	{
		State.ResetSpeeds();

		//Update State Machine with Sensor Readings
		ReadRobot();

		State.PrintSensors();

		Auton.Task();
		Drive.Task();
		Hat.Task();
		Lift.Task();
		Fork.Task();

		State.PrintSetpoints();

		MapOI();

		//State.PrintSpeeds();

		//State.PrintLift();

		Auton.Write();
		Drive.Write(); 
		Hat.Write();
		Lift.Write();
		Fork.Write();

		Serial.println("");

		lastStateUpdate = millis();
	}

}

void ROBOT::ReadRobot()
{
	//Get data from Gyro
	imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
	State.UpdateHeading(euler.x());
	State.Temp = bno.getTemp() * 9 / 5 + 32;

	//Shift Rigth Encoder to Prev
	State.RightEncoderPrev = State.RightEncoder;
	State.RightEncoderPrevTime = State.RightEncoderTime;

	//Get data from DriveLeftEnc
	State.RightEncoderTime = millis();
	State.RightEncoder = RightEnc.read();
    State.LeftEncoder = LeftEnc.read();

	//Calculate Right Velocity clicks per second
	State.DriveRightVelocity = (State.RightEncoder - State.RightEncoderPrev) / (State.RightEncoderTime - State.RightEncoderPrevTime) * 1000;



	//if lift encoder is less than zero. set to zero.
	if(LiftEnc.read() < 0)
		LiftEnc.write(0);

    State.LiftEncoder = LiftEnc.read();
	

	State.FlexSensor = analogRead(FlexSensor);
	
}

void ROBOT::MapOI(){
	if(State.ForkSpeedCont != 0)
		State.ForkSpeed = State.ForkSpeedCont;
	if(State.LiftSpeedCont != 0)
		State.LiftSpeed = State.LiftSpeedCont;
	if(State.DriveLeftSpeedCont != 0)
		State.DriveLeftSpeed = State.DriveLeftSpeedCont;
	if(State.DriveRightSpeedCont != 0)
		State.DriveRightSpeed = State.DriveRightSpeedCont;
}

void ROBOT::OI()
{
	if (Xbox.XboxReceiverConnected)
	{
		for (uint8_t i = 0; i < 4; i++)
		{
			if (Xbox.Xbox360Connected[i])
			{
				//L2 Trigger
				if (Xbox.getButtonPress(R2, i))
				{
					State.LiftSpeedCont = Xbox.getButtonPress(R2, i) * 1 * .5;
				}
				//R2 Trigger
				else if (Xbox.getButtonPress(L2, i))
				{
					State.LiftSpeedCont = Xbox.getButtonPress(L2, i) * -1 * .5;
				}
				else
				{
					State.LiftSpeedCont = 0;
				}

				//L1 Button
				if (Xbox.getButtonPress(R1, i))
				{
					State.ForkSpeedCont = 255.0;
				}
				//R1 Button
				else if (Xbox.getButtonPress(L1, i))
				{
					State.ForkSpeedCont = -255.0;
				}
				else
				{
					State.ForkSpeedCont = 0;
				}

				const int joyThresh = 5500;
				const int MCDeadZone = 0; //116
				if (Xbox.getAnalogHat(LeftHatX, i) > joyThresh || Xbox.getAnalogHat(LeftHatX, i) < -joyThresh || Xbox.getAnalogHat(LeftHatY, i) > joyThresh || Xbox.getAnalogHat(LeftHatY, i) < -joyThresh || Xbox.getAnalogHat(RightHatX, i) > joyThresh || Xbox.getAnalogHat(RightHatX, i) < -joyThresh || Xbox.getAnalogHat(RightHatY, i) > joyThresh || Xbox.getAnalogHat(RightHatY, i) < -joyThresh)
				{
					

					if (Xbox.getAnalogHat(LeftHatY, i) > joyThresh)
					{
						//LeftJoystickY = 255.0 / 32767 * Xbox.getAnalogHat(LeftHatY, i);
						State.DriveLeftSpeedCont = map(Xbox.getAnalogHat(LeftHatY, i), 5500, 32767, MCDeadZone, 255);
					}
					else if (Xbox.getAnalogHat(LeftHatY, i) < -joyThresh)
					{
						State.DriveLeftSpeedCont = map(Xbox.getAnalogHat(LeftHatY, i), -5500, -32767, -MCDeadZone, -255);
					}
					else
					{
						State.DriveLeftSpeedCont = 0;
					}

				
					if (Xbox.getAnalogHat(RightHatY, i) > joyThresh)
					{
						//RightJoystickY = 255.0 / 32767 * Xbox.getAnalogHat(RightHatY, i);
						State.DriveRightSpeedCont = map(Xbox.getAnalogHat(RightHatY, i), 5500, 32767, MCDeadZone, 255);
					}
					else if (Xbox.getAnalogHat(RightHatY, i) < -joyThresh)
					{
						State.DriveRightSpeedCont = map(Xbox.getAnalogHat(RightHatY, i), -5500, -32767, -MCDeadZone, -255);
					}
					else
					{
						State.DriveRightSpeedCont = 0;
					}
				}

				if (Xbox.getButtonClick(X, i))
				{
					Hat.Release();
				}

				if (Xbox.getButtonClick(Y, i))
				{
					Fork.Toggle();
				}

				if (Xbox.getButtonClick(UP, i))
				{
					Lift.ReleaseCone();
				}

				if (Xbox.getButtonClick(DOWN, i))
				{
					Lift.AquireCone();
				}

				if (Xbox.getButtonClick(LEFT, i))
				{
					Lift.Previous();
				}

				if (Xbox.getButtonClick(RIGHT, i))
				{
					Lift.Next();
				}

				if(Xbox.getButtonClick(START, i))
				{
					Auton.NextProgram(); 
				}

				if(Xbox.getButtonClick(SELECT, i))
				{
					Auton.PreviousProgram();
				}

				if(Xbox.getButtonClick(XBOX, i))
				{ 
					if(State.IsAutonomousRunning)
						Auton.StopAutonomous();
					else
						Auton.StartAutonomous();
				}


				if(State.IsAutonomousRunning)
				{
					Xbox.setLedMode(ALTERNATING, i);
				}
				else if(State.AutonomousProgramNumber > 0)
				{
					//Decode prog number
					int pn = State.AutonomousProgramNumber;
					Xbox.setLedOff(i);

					if(pn % 2 > 0)
						Xbox.setLedOn(LED1, i);
					
					if((pn / 2) % 2 > 0)
						Xbox.setLedOn(LED2, i);

					if((pn / 4) % 2 > 0)
						Xbox.setLedOn(LED3, i);

					if((pn / 8) % 2 > 0)
						Xbox.setLedOn(LED4, i);
				}
				else
				{
					Xbox.setLedOn(LED1, i);
				}
				
			}
		}
	}
}