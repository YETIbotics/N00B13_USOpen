
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

		OI();

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

	//Get data from DriveLeftEnc
	State.RightEncoder = RightEnc.read();
    State.LeftEncoder = LeftEnc.read();

	//if lift encoder is less than zero. set to zero.
	if(LiftEnc.read() < 0)
		LiftEnc.write(0);

    State.LiftEncoder = LiftEnc.read();
	

	State.FlexSensor = analogRead(FlexSensor);
	
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
					State.LiftSpeed = Xbox.getButtonPress(R2, i) * 1 * .5;
				}
				//R2 Trigger
				else if (Xbox.getButtonPress(L2, i))
				{
					State.LiftSpeed = Xbox.getButtonPress(L2, i) * -1 * .5;
				}

				//L1 Button
				if (Xbox.getButtonPress(R1, i))
				{
					State.ForkSpeed = 255.0;
				}
				//R1 Button
				else if (Xbox.getButtonPress(L1, i))
				{
					State.ForkSpeed = -255.0;
				}

				const int joyThresh = 5500;
				if (Xbox.getAnalogHat(LeftHatX, i) > joyThresh || Xbox.getAnalogHat(LeftHatX, i) < -joyThresh || Xbox.getAnalogHat(LeftHatY, i) > joyThresh || Xbox.getAnalogHat(LeftHatY, i) < -joyThresh || Xbox.getAnalogHat(RightHatX, i) > joyThresh || Xbox.getAnalogHat(RightHatX, i) < -joyThresh || Xbox.getAnalogHat(RightHatY, i) > joyThresh || Xbox.getAnalogHat(RightHatY, i) < -joyThresh)
				{
					

					if (Xbox.getAnalogHat(LeftHatY, i) > joyThresh)
					{
						//LeftJoystickY = 255.0 / 32767 * Xbox.getAnalogHat(LeftHatY, i);
						State.DriveLeftSpeed = map(Xbox.getAnalogHat(LeftHatY, i), 5500, 32767, 116, 255);
					}
					else if (Xbox.getAnalogHat(LeftHatY, i) < -joyThresh)
					{
						State.DriveLeftSpeed = map(Xbox.getAnalogHat(LeftHatY, i), -5500, -32767, -116, -255);
					}

				
					if (Xbox.getAnalogHat(RightHatY, i) > joyThresh)
					{
						//RightJoystickY = 255.0 / 32767 * Xbox.getAnalogHat(RightHatY, i);
						State.DriveRightSpeed = map(Xbox.getAnalogHat(RightHatY, i), 5500, 32767, 116, 255);
					}
					else if (Xbox.getAnalogHat(RightHatY, i) < -joyThresh)
					{
						State.DriveRightSpeed = map(Xbox.getAnalogHat(RightHatY, i), -5500, -32767, -116, -255);
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

						//Xbox.setLedOff(i);
				}
				else
				{
					Xbox.setLedOn(LED1, i);
					//Xbox.setLedOn(LED2, i);
					//Xbox.setLedBlink(ALL, i);
				}
				

				//Serial.println(Xbox.getAnalogHat(RightHatY, i));

				//if (Xbox.getButtonPress(X, i))
				//{
					//DOWN
				//	ArmSpeed = -80;
				//}
				//else if (Xbox.getButtonPress(Y, i))
				//{
					//UP
				//	ArmSpeed = 200;
				//}

				//if (Xbox.getButtonPress(L1, i))
				//{
					//OPEN
				//	ClawSpeed = 225;
				//}
				//else if (Xbox.getButtonPress(R1, i))
				//{
					//CLOSE
				//	ClawSpeed = -225;
				//}

				

				//if (Xbox.getButtonClick(START, i))
				//{
				//	isArcadeDrive = !isArcadeDrive;
				//}

				// if (Xbox.getButtonClick(BACK, i))
				// {// parking match

				// 	mc.setMotorSpeed(4, 255); //rt
				// 	mc.setMotorSpeed(5, 255); //lt
				// 	delay(100);

				// 	mc.setMotorSpeed(4, 0); //rt
				// 	mc.setMotorSpeed(5, 0); //lt
				// 	delay(2000);

				// 	mc.setMotorSpeed(4, 255); //rt
				// 	mc.setMotorSpeed(5, 255); //lt
				// 	delay(1000);
				// }

				

				// if (Xbox.getButtonClick(UP, i))
				// {// 20 pt scoring
				// 	//match park
				// 	(600);
				// 	MOGO(0);

				// 	Drive(0,0);
				// 	delay(500);
				
				// 	Drive(200,200);
				// 	delay(1400);
				// 	Drive(0,0);

					
					
				// 	//Drive(255,255);
				// 	//delay(700);
				// 	//Drive(0,0);
				

				// 	//Drive(-255,-255);
				// 	//delay(700);
				// 	//Drive(0,0);
				// }
			
			





				
			}
		}
	}
}