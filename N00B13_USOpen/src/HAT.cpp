#include "HAT.h"
#include "ROBOT.h"

HAT::HAT(ROBOT &refRobot)
	: Robot(refRobot)
{
	
}

void HAT::Setup()
{
	
	HatServo.attach(Robot.HatPWM);
	Close();
}

void HAT::Task() {

	if(Robot.State.HatIsReleasing)
	{
		switch(Robot.State.HatIsReleasingTime)
		{
			case 0:
				HatServo.attach(Robot.HatPWM);
				Open();
				break;
			case ReleaseDuration:
				Close();
				break;
			case ReleaseDuration * 2:
				Robot.State.HatIsReleasing = false;
				break;
		}

		if(Robot.State.HatIsReleasing)
			Robot.State.HatIsReleasingTime += Robot.State.LoopFrequency;
		else
		{
			Robot.State.HatIsReleasingTime = 0;
			HatServo.detach();
		}
	}else if(Robot.State.HatIsMoving)
	{
		switch(Robot.State.HatIsMovingTime)
		{
			case 0:
				HatServo.attach(Robot.HatPWM);
				break;
			case MoveDuration:
				Robot.State.HatIsMoving = false;
				break;
		}

		if(Robot.State.HatIsMoving)
			Robot.State.HatIsMovingTime += Robot.State.LoopFrequency;
		else
		{
			Robot.State.HatIsMovingTime = 0;
			HatServo.detach();
		}
	}

}


void HAT::Write() {

	HatServo.write(Robot.State.HatSetpoint);
}

void HAT::Open()
{
	Robot.State.HatIsMovingTime = 0;
	Robot.State.HatIsMoving = true; 

	Robot.State.HatSetpoint = OpenPos;
	Robot.State.HatState = STATE::HATSTATES::IsOpen; 
}

void HAT::Close()
{
	Robot.State.HatIsMovingTime = 0;
	Robot.State.HatIsMoving = true; 
	
	Robot.State.HatSetpoint = ClosedPos;
	Robot.State.HatState = STATE::HATSTATES::IsClosed; 
}

void HAT::Toggle()
{
	if(Robot.State.HatState == STATE::HATSTATES::IsClosed)
	{
		Open();
	}
	else
	{
		Close();
	}
}

void HAT::Release()
{
	Robot.State.HatIsReleasingTime = 0;
	Robot.State.HatIsReleasing = true; 
}