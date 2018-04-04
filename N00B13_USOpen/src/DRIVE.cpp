#include "DRIVE.h"
#include "ROBOT.h"

DRIVE::DRIVE(ROBOT &refRobot)
	: Robot(refRobot),
	  DrivePID(&Robot.State.DrivePIDInput, &Robot.State.DrivePIDOutput, &Robot.State.DrivePIDSetpoint, Kp, Ki, Kd, DIRECT),
	  TurnPID(&Robot.State.Heading, &Robot.State.HeadingSpeed, &Robot.State.HeadingSetpoint, tKp, tKi, tKd, DIRECT),
	  Left(Robot.DriveLeftPWM, Robot.DriveLeftDir, false, 50),
	  Right(Robot.DriveRightPWM, Robot.DriveRightDir, false, 50)
{
}

void DRIVE::Setup()
{
	DrivePID.SetSampleTime(Robot.State.PIDFrequency);
	TurnPID.SetSampleTime(Robot.State.PIDFrequency);

	DrivePID.SetOutputLimits(-100, 100);
	TurnPID.SetOutputLimits(-100, 100);
}

void DRIVE::CalcPID()
{
	DrivePID.Compute();
	TurnPID.Compute();
}

void DRIVE::Task()
{

	if (Robot.State.DriveIsRunningPID)
	{
		if (Robot.State.DrivePIDIsLeft)
		{
			Robot.State.DrivePIDInput = Robot.State.LeftEncoder;
		}
		else
		{
			Robot.State.DrivePIDInput = Robot.State.RightEncoder;
		}
	}

	if (Robot.State.DriveIsRunningPID)
	{

		if (Robot.State.TurnPIDIsHeadingLock)
		{
			//This is the To function
			Robot.State.DriveLeftSpeed = Robot.State.DrivePIDOutput + (Robot.State.HeadingSpeed * .25);
			Robot.State.DriveRightSpeed = Robot.State.DrivePIDOutput - (Robot.State.HeadingSpeed * .25);
		}
		else
		{
			if (DrivePID.GetMode() == MANUAL)
			{
				//is turn
				Robot.State.DriveLeftSpeed = Robot.State.HeadingSpeed;
				Robot.State.DriveRightSpeed = -Robot.State.HeadingSpeed;
			}
			else
			{
				if (Robot.State.DrivePIDIsLeft)
				{
					//Is Sweep with Left Held
					Robot.State.DriveLeftSpeed = Robot.State.DrivePIDOutput;
					Robot.State.DriveRightSpeed = -Robot.State.HeadingSpeed;
				}
				else
				{
					//Is Sweep with Right Held
					Robot.State.DriveLeftSpeed = Robot.State.HeadingSpeed;
					Robot.State.DriveRightSpeed = Robot.State.DrivePIDOutput;
				}
			}
		}

		double accelLimit = 8;

		if (Robot.State.DriveLeftSpeed > Robot.State.DriveLeftSpeedPrev && Robot.State.DriveLeftSpeed > 0)
		{
			//Accel
			if (Robot.State.DriveLeftSpeed - Robot.State.DriveLeftSpeedPrev > accelLimit)
			{
				Robot.State.DriveLeftSpeed = Robot.State.DriveLeftSpeedPrev + accelLimit;	
			}
		}
		else if (Robot.State.DriveLeftSpeed < Robot.State.DriveLeftSpeedPrev && Robot.State.DriveLeftSpeed < 0)
		{
			//Accel
			if (abs(Robot.State.DriveLeftSpeed - Robot.State.DriveLeftSpeedPrev) > accelLimit)
			{
				Robot.State.DriveLeftSpeed = Robot.State.DriveLeftSpeedPrev - accelLimit;
			}
		}
		Robot.State.DriveLeftSpeedPrev = Robot.State.DriveLeftSpeed;

		if (Robot.State.DriveRightSpeed > Robot.State.DriveRightSpeedPrev && Robot.State.DriveRightSpeed > 0)
		{
			//Accel
			if (Robot.State.DriveRightSpeed - Robot.State.DriveRightSpeedPrev > accelLimit)
			{
				Robot.State.DriveRightSpeed = Robot.State.DriveRightSpeedPrev + accelLimit;	 
			}
		}
		else if (Robot.State.DriveRightSpeed < Robot.State.DriveRightSpeedPrev && Robot.State.DriveRightSpeed < 0)
		{
			//Accel
			if (abs(Robot.State.DriveRightSpeed - Robot.State.DriveRightSpeedPrev) > accelLimit)
			{
				Robot.State.DriveRightSpeed = Robot.State.DriveRightSpeedPrev - accelLimit;
			}
		}
		Robot.State.DriveRightSpeedPrev = Robot.State.DriveRightSpeed;

		//Handle Timeout
		if (millis() > Robot.State.DriveIsRunningPIDExpiry)
		{
			Robot.State.DriveIsRunningPID = false;
			DrivePID.SetMode(MANUAL);
			TurnPID.SetMode(MANUAL);
			
		}
	}
}

void DRIVE::Write()
{
	Left.SetMotorSpeed(Robot.State.DriveLeftSpeed);
	Right.SetMotorSpeed(Robot.State.DriveRightSpeed);
}

void DRIVE::To(int setpoint, double speed, int timeout)
{
	To(setpoint, speed, timeout, Robot.State.Heading);
	//LeftPID on
	//TurnPid on
	//No RightPid
	//Write same values to left and right minus
}

void DRIVE::To(int setpoint, double speed, int timeout, int heading)
{
	TurnPID.SetTunings(6, 0, 0);
	Robot.State.DriveIsRunningPID = true;
	Robot.State.DriveIsRunningPIDExpiry = millis() + timeout;

	Robot.State.TurnPIDIsHeadingLock = true;
	Robot.State.HeadingSetpoint = heading;
	Robot.State.HeadingSpeed = 0;

	Robot.State.DrivePIDIsLeft = true;
	Robot.State.DrivePIDSetpoint = Robot.State.LeftEncoder + setpoint;
	Robot.State.DrivePIDOutput = 0;

	DrivePID.SetMode(AUTOMATIC);
	TurnPID.SetMode(AUTOMATIC);

	DrivePID.SetOutputLimits(-speed, speed);
	TurnPID.SetOutputLimits(-speed, speed);

	//LeftPID on
	//TurnPid on
	//No RightPid
	//Write same values to left and right minus
}

void DRIVE::TurnRelative(int deg, double speed, int timeout)
{
	TurnPID.SetTunings(tKp, tKi, tKd);
	// no rigthpid or leftpid
	//TurnPid on
	//write opposite values to left and right
	TurnAbsolute(Robot.State.Heading + deg, speed, timeout);
	
}
void DRIVE::TurnAbsolute(int deg, double speed, int timeout)
{
	TurnPID.SetTunings(tKp, tKi, tKd);
	// no rigthpid or leftpid
	//TurnPid on
	//write opposite values to left and right
	Robot.State.DriveIsRunningPID = true;
	Robot.State.DriveIsRunningPIDExpiry = millis() + timeout;

	Robot.State.TurnPIDIsHeadingLock = false;
	Robot.State.HeadingSetpoint = deg;
	Robot.State.HeadingSpeed = 0;

	Robot.State.DrivePIDIsLeft = true;
	Robot.State.DrivePIDSetpoint = 0;
	Robot.State.DrivePIDOutput = 0;

	DrivePID.SetMode(MANUAL);
	TurnPID.SetMode(AUTOMATIC);

	DrivePID.SetOutputLimits(-speed, speed);
	TurnPID.SetOutputLimits(-speed, speed);
}
void DRIVE::SweepRelative(int deg, double speed, int timeout, bool lockLeft)
{
	TurnPID.SetTunings(tKp, tKi, tKd);
	// right pid OR left pid with setpoint of zero
	//TurnPid on
	//if right is on, write speed to left
	SweepAbsolute(Robot.State.Heading + deg, speed, timeout, lockLeft);
}
void DRIVE::SweepAbsolute(int deg, double speed, int timeout, bool lockLeft)
{
	TurnPID.SetTunings(tKp, tKi, tKd);
	// right pid OR left pid with setpoint of zero
	//TurnPid on
	//if right is on, write speed to left
	Robot.State.DriveIsRunningPID = true;
	Robot.State.DriveIsRunningPIDExpiry = millis() + timeout;

	Robot.State.TurnPIDIsHeadingLock = false;
	Robot.State.HeadingSetpoint = deg;
	Robot.State.HeadingSpeed = 0;

	Robot.State.DrivePIDIsLeft = lockLeft;
	Robot.State.DrivePIDSetpoint = 0;
	Robot.State.DrivePIDOutput = 0;

	DrivePID.SetMode(AUTOMATIC);
	TurnPID.SetMode(AUTOMATIC);

	DrivePID.SetOutputLimits(-speed, speed);
	TurnPID.SetOutputLimits(-speed, speed);
}