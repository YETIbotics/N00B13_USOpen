#include "FORK.h"
#include "ROBOT.h"

FORK::FORK(ROBOT &refRobot)
	: Robot(refRobot),
	ForkPID(&Robot.State.FlexSensor, &Robot.State.ForkSpeedPID, &Robot.State.ForkPIDSetpoint, Kp, Ki, Kd, DIRECT),
	ForkMotor(Robot.ForkPWM, Robot.ForkDir, true, 0)
{ 
 
}

void FORK::Setup(){ 
 
	ForkPID.SetSampleTime(Robot.State.PIDFrequency);
	
	ForkPID.SetOutputLimits(-255, 255);
}

void FORK::CalcPID()
{
	ForkPID.Compute();
}
 
void FORK::Task() {
	if (Robot.State.ForkIsRunningPID)
	{
		//Handle Timeout
		if (millis() > Robot.State.ForkIsRunningPIDExpiry)
		{
			Robot.State.ForkIsRunningPID = false; 
			ForkPID.SetMode(MANUAL);
			Robot.State.ForkSpeedPID = 0;
		}
	}
}

void FORK::Write() {
	ForkMotor.SetMotorSpeed(Robot.State.ForkSpeed + Robot.State.ForkSpeedPID);
}


void FORK::To(int setpoint, int timeout)
{
	Robot.State.ForkIsRunningPID = true;
	Robot.State.ForkIsRunningPIDExpiry = millis() + timeout;

	Robot.State.ForkPIDSetpoint = setpoint;

	ForkPID.SetMode(AUTOMATIC);

	//LeftPID on
	//TurnPid on
	//No RightPid
	//Write same values to left and right minus
}

void FORK::Down()
{
	To(forkMin, 500); 
	Robot.State.ForkIsUp = false;
}

void FORK::Up()
{
	To(forkMax, 500);
	Robot.State.ForkIsUp = true;
}
 
void FORK::Toggle()
{
	if(Robot.State.ForkIsUp)
		Down();
	else
		Up();
}