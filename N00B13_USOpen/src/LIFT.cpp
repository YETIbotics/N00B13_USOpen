#include "LIFT.h"
#include "ROBOT.h"

LIFT::LIFT(ROBOT &refRobot)
	: Robot(refRobot), LiftPID(&Robot.State.LiftEncoder, &Robot.State.LiftSpeed, &Robot.State.LiftSetpoint, Kp, Ki, Kd, DIRECT), LiftMotor(Robot.LiftPWM, Robot.LiftDir, true)
{
}

void LIFT::Setup()
{
	LiftPID.SetSampleTime(Robot.State.LoopFrequency);
	LiftPID.SetOutputLimits(-250, 250);
}

void LIFT::Task()
{
	LiftPID.Compute();

	if (Robot.State.LiftIsAquiring)
	{
		LiftPID.SetTunings(3, 0, 0);
		switch (Robot.State.LiftIsAquiringTime)
		{
		case 0:
			UpdateSetpointFromState(-100);
			break;
		case 250:
			UpdateSetpointFromStatePartTwo(0);
			Robot.State.LiftIsAquiring = false;
			break;
		}

		if (Robot.State.LiftIsAquiring)
			Robot.State.LiftIsAquiringTime += Robot.State.LoopFrequency;
		else
			Robot.State.LiftIsAquiringTime = 0;
	}else if (Robot.State.LiftIsReleasing)
	{
		LiftPID.SetTunings(3, 0, 0);
		switch (Robot.State.LiftIsReleasingTime)
		{
		case 0:
			UpdateSetpointFromStatePartTwo(100);
			break;
		case 130:
			Robot.Hat.Release();
			break;
		case 250:
			UpdateSetpointFromState(0);
			Robot.State.LiftIsReleasing = false;
			break;
		}

		if (Robot.State.LiftIsReleasing)
			Robot.State.LiftIsReleasingTime += Robot.State.LoopFrequency;
		else
			Robot.State.LiftIsReleasingTime = 0;
	}
	else
	{
		LiftPID.SetTunings(Kp, Ki, Kd);
	}

	if (Robot.State.LiftIsRunningPID)
	{
		double accelLimit = 8;

		if (Robot.State.LiftSpeed > Robot.State.LiftSpeedPrev && Robot.State.LiftSpeed > 0)
		{
			//Accel
			if (Robot.State.LiftSpeed - Robot.State.LiftSpeedPrev > accelLimit)
			{
				Robot.State.LiftSpeed = Robot.State.LiftSpeedPrev + accelLimit;	
			}
		}
		else if (Robot.State.LiftSpeed < Robot.State.LiftSpeedPrev && Robot.State.LiftSpeed < 0)
		{
			//Accel
			if (abs(Robot.State.LiftSpeed - Robot.State.LiftSpeedPrev) > accelLimit)
			{
				Robot.State.LiftSpeed = Robot.State.LiftSpeedPrev - accelLimit;
			}
		}
		Robot.State.LiftSpeedPrev = Robot.State.LiftSpeed;

		//Handle Timeout
		if (millis() > Robot.State.LiftIsRunningPIDExpiry)
		{
			Robot.State.LiftIsRunningPID = false;
			LiftPID.SetMode(MANUAL);
		}
	}
}

void LIFT::Write()
{

	LiftMotor.SetMotorSpeed(Robot.State.LiftSpeed);
}

void LIFT::UpdateSetpointFromState(int bonusclicks)
{
	if (Robot.State.LiftState == STATE::LIFTSTATES::FromFloorToMogo)
	{
		UpdateSetpoint(SetpointFloor + bonusclicks);
	}
	else if (Robot.State.LiftState == STATE::LIFTSTATES::FromDclToMogo)
	{
		UpdateSetpoint(SetpointDcl + bonusclicks);
	}
	else if (Robot.State.LiftState == STATE::LIFTSTATES::FromStatToBack)
	{
		UpdateSetpoint(SetpointStat + bonusclicks);
	}
	else if (Robot.State.LiftState == STATE::LIFTSTATES::FromMogoToStat)
	{
		UpdateSetpoint(SetpointMogo - bonusclicks);
	}
}

void LIFT::UpdateSetpointFromStatePartTwo(int bonusclicks)
{
	if (Robot.State.LiftState == STATE::LIFTSTATES::FromFloorToMogo)
	{
		UpdateSetpoint(SetpointMogo + bonusclicks);
	}
	else if (Robot.State.LiftState == STATE::LIFTSTATES::FromDclToMogo)
	{
		UpdateSetpoint(SetpointMogo + bonusclicks);
	}
	else if (Robot.State.LiftState == STATE::LIFTSTATES::FromStatToBack)
	{
		UpdateSetpoint(SetpointBack + bonusclicks);
	}
	else if (Robot.State.LiftState == STATE::LIFTSTATES::FromMogoToStat)
	{
		UpdateSetpoint(SetpointStat - bonusclicks);
	}
}

void LIFT::UpdateSetpoint(int newSP)
{
	UpdateSetpoint(newSP, 1000);
}

void LIFT::UpdateSetpoint(int newSP, int timeout)
{
	Robot.State.LiftSetpoint = newSP;
	Robot.State.LiftIsRunningPID = true;
	Robot.State.LiftIsRunningPIDExpiry = millis() + timeout;

	LiftPID.SetMode(AUTOMATIC);
}

void LIFT::Next()
{
	if (Robot.State.LiftState == 3)
		Robot.State.LiftState = STATE::LIFTSTATES(0);
	else
		Robot.State.LiftState = STATE::LIFTSTATES(int(Robot.State.LiftState) + 1);

	UpdateSetpointFromState(0);
}
void LIFT::Previous()
{
	if (Robot.State.LiftState == 0)
		Robot.State.LiftState = STATE::LIFTSTATES(3);
	else
		Robot.State.LiftState = STATE::LIFTSTATES(int(Robot.State.LiftState) - 1);

	UpdateSetpointFromState(0);
}
void LIFT::AquireCone()
{
	Robot.State.LiftIsAquiring = true;
	Robot.State.LiftIsAquiringTime = 0;
}
void LIFT::ReleaseCone()
{
	Robot.State.LiftIsReleasing = true;
	Robot.State.LiftIsReleasingTime = 0;
}
void LIFT::To(int degrees)
{
	UpdateSetpoint(degrees);
}