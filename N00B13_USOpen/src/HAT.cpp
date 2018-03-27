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
				Open();
				break;
			case ReleaseDuration:
				Close();
				Robot.State.HatIsReleasing = false;
				break;
		}

		if(Robot.State.HatIsReleasing)
			Robot.State.HatIsReleasingTime += Robot.State.LoopFrequency;
		else
			Robot.State.HatIsReleasingTime = 0;
	}

}


void HAT::Write() {

	HatServo.write(Robot.State.HatSetpoint);
}

void HAT::Open()
{
	Robot.State.HatSetpoint = OpenPos;
	Robot.State.HatState = STATE::HATSTATES::IsOpen; 
}

void HAT::Close()
{
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