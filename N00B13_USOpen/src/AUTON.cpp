#include "AUTON.h"
#include "ROBOT.h"

AUTON::AUTON(ROBOT &refRobot)
	: Robot(refRobot)
{
}

void AUTON::Setup()
{
	NumRegisteredPrograms = 15; //MAX 15
}

void AUTON::Task()
{

	if (Robot.State.IsAutonomousRunning)
	{

		switch (Robot.State.AutonomousProgramNumber)
		{
		case 0:
			Robot.State.IsAutonomousRunning = false;
			break;
		case 1:
			Program1();
			break;
		case 2:
			Program2();
			break;
		case 3:
			Program3();
			break;
		case 4:
			Program4();
			break;
		case 5:
			Program5();
			break;
		case 6:
			Program6();
			break;
		case 7:
			Program7();
			break;
		case 8:
			Program8();
			break;
		case 9:
			Program9();
			break;
		case 10:
			Program10();
			break;
		case 11:
			Program11();
			break;
		case 12:
			Program12();
			break;
		case 13:
			Program13();
			break;
		case 14:
			Program14();
			break;
		case 15:
			Program15();
			break;
		default:
			Robot.State.AutonomousProgramNumber = 0;
		}

		if (Robot.State.IsAutonomousRunning)
			Robot.State.AutonomousTime = ((millis() - Robot.State.AutonStartTime) / 100) * 100;
		else
			Robot.State.AutonomousTime = 0;
	}
}

void AUTON::Write()
{
}

void AUTON::StartAutonomous()
{
	StartAutonomous(Robot.State.AutonomousProgramNumber);
}

void AUTON::StartAutonomous(int progNum)
{
	Robot.State.AutonomousProgramNumber = progNum;
	Robot.State.AutonStartTime = millis();
	Robot.State.AutonomousTime = 0;
	Robot.State.IsAutonomousRunning = true;
}

void AUTON::StopAutonomous()
{
	Robot.State.AutonomousProgramNumber = 0;
}

void AUTON::PreviousProgram()
{
	Robot.State.AutonomousProgramNumber--;

	if (Robot.State.AutonomousProgramNumber < 0)
		Robot.State.AutonomousProgramNumber = NumRegisteredPrograms;
}
void AUTON::NextProgram()
{
	Robot.State.AutonomousProgramNumber++;

	if (Robot.State.AutonomousProgramNumber > NumRegisteredPrograms)
		Robot.State.AutonomousProgramNumber = 0;
}

void AUTON::Program1() //skills auton
{
	switch (Robot.State.AutonomousTime)
	{
	case 0:
		Robot.Fork.Down();
		Robot.Drive.To(1042, 200, 1500);
		break;

	case 1500:
		Robot.Fork.Up();
		break;

	case 2000:
		Robot.Drive.TurnRelative(175, 200, 1500);
		break;

	case 3000:
		Robot.Drive.To(1022, 200, 1500);
		break;

	case 4500:
		Robot.Fork.Down();
		break;

	case 5000:
		Robot.Drive.To(2920 - 3400, 200, 5000);
		break;

	case 6000:
		Robot.State.AutonomousProgramNumber = 0;
		break;
	}
}

void AUTON::Program2()
{
	switch (Robot.State.AutonomousTime)
	{
	case 0:
		Robot.Drive.TurnRelative(45, 200, 1000);
		//Robot.Drive.SweepAbsolute(45, 200, 1000, false);
		break;

	case 1500:
		Robot.Drive.TurnRelative(-45, 200, 1000);
		//Robot.Drive.SweepAbsolute(0, 200, 1000, false);
		break;

	case 4000:
		Robot.State.AutonomousProgramNumber = 0;
		break;
	}
}
void AUTON::Program3()
{
	switch (Robot.State.AutonomousTime)
	{
	case 0:
		Robot.Drive.SweepRelative(45, 200, 1000, false);
		break;

	case 1500:
		Robot.Drive.SweepRelative(-45, 200, 1000, false);
		break;

	case 4000:
		Robot.State.AutonomousProgramNumber = 0;
		break;
	}
}
void AUTON::Program4()
{
	switch (Robot.State.AutonomousTime)
	{
	case 0:
		Robot.Fork.Down();
		Robot.Drive.To(1042, 200, 1500);
		break;

	case 1500:
		Robot.Fork.Up();
		break;

	case 2000:
		Robot.Drive.TurnRelative(175, 200, 1500);
		break;

	case 1600:
		Robot.Drive.To(2044, 200, 1500);
		break;
	}
}
void AUTON::Program5()
{ //match Auton
	switch (Robot.State.AutonomousTime)
	{
	case 0:
		Robot.Drive.To(1420, 175, 2000);
		Robot.Lift.To(1000);
		break;

	case 2000:
		Robot.Fork.Up();
		break;

	case 2500:
		Robot.Drive.To(-1200, 175, 2000);
		break;

	case 4500:
		Robot.Drive.TurnRelative(-215, 135, 2000);
		break;

	case 6500:
		Robot.Drive.To(400, 200, 1500);
		break;

	case 8500:
		Robot.Fork.Down();
		break;

	case 9000:
		Robot.Drive.To(-400, 200, 1500);
		break;

	case 11000:
		Robot.Drive.TurnAbsolute(-286, 135, 2000);
		Robot.Lift.To(520);
		break;

	case 13000:
		Robot.Drive.To(-500, 200, 1500);
		break;

	case 50000:
		Robot.State.AutonomousProgramNumber = 0;
		break;
	}
}
void AUTON::Program6()
{ //Skills Auton
	switch (Robot.State.AutonomousTime)
	{
	case 0:
		Robot.Drive.To(1420, 220, 3000, 10);
		//Robot.Lift.To(500);
		break;

	case 1900:
		Robot.Fork.Up();
		break;

	case 2900:
		Robot.Drive.To(-1250, 220, 3000, 10);
		break;

	case 5600:
		Robot.Drive.TurnAbsolute(-220, 150, 3000);
		break;

	case 8300:
		Robot.Drive.To(500, 220, 3000);
		break;

	case 10400:
		Robot.Fork.Down();
		break;

	case 11400:
		Robot.Drive.To(-360, 220, 3000);
		break;

	case 13700:
		Robot.Drive.TurnAbsolute(-65, 200, 3000);
		break;

	case 15500:
		Robot.Drive.To(600, 220, 3000);
		break;

	case 18000:
		Robot.Fork.Up(); // first red mogo
		break;

	case 19000:
		Robot.Drive.To(-600, 220, 3000);
		break;

	case 21500:
		Robot.Drive.TurnAbsolute(-171, 150, 3000);
		break;

	case 23600:
		Robot.Drive.To(570, 220, 3000);
		break;

	case 26500:
		Robot.Drive.TurnAbsolute(-240, 150, 3000);
		break;

	case 28800:
		Robot.Drive.To(220, 220, 3000);
		break;

	case 31400:
		Robot.Fork.Down(); // scores first red mogo
		break;

	case 32400:
		Robot.Drive.To(-295, 220, 3000);
		break;

	case 34900:
		Robot.Drive.TurnAbsolute(-150, 200, 3000);
		break;

	case 37000:
		Robot.Drive.To(585, 200, 3000);
		break;

	case 40000:
		Robot.Drive.TurnAbsolute(-45, 200, 3000);
		break;

	case 43000:
		Robot.Drive.To(675, 200, 3000);
		break;

	case 46000:
		Robot.Fork.Up();
		break;

	case 49000:
		Robot.Drive.TurnAbsolute(-225, 150, 3000);
		break;

	case 52000:
		Robot.Drive.To(675, 220, 3000);
		break;

	case 100000:
		Robot.State.AutonomousProgramNumber = 0;
		break;
	}
}
void AUTON::Program7()
{ // dance mode
	switch (Robot.State.AutonomousTime)
	{
		case 0:
			Robot.Drive.TurnAbsolute(45, 200, 3000);
			break;

		case 400:
			Robot.Drive.TurnAbsolute(-45, 200, 3000);
			break;

		case 800:
			Robot.Drive.TurnAbsolute(45, 200, 3000);
			break;

		case 1200:
			Robot.Drive.TurnAbsolute(-45, 200, 3000);
			break;

		case 1500:
			Robot.Drive.TurnAbsolute(360, 200, 3000);
			break;

		case 100000:
			Robot.State.AutonomousProgramNumber = 0;
			break;
	}
}

void AUTON::Program8()
{
	switch (Robot.State.AutonomousTime)
	{
	case 0:
		Robot.State.AutonomousProgramNumber = 0;
		break;
	}
}
void AUTON::Program9()
{
	switch (Robot.State.AutonomousTime)
	{
	case 0:
		Robot.State.AutonomousProgramNumber = 0;
		break;
	}
}
void AUTON::Program10()
{
	switch (Robot.State.AutonomousTime)
	{
	case 0:
		Robot.State.AutonomousProgramNumber = 0;
		break;
	}
}
void AUTON::Program11()
{
	switch (Robot.State.AutonomousTime)
	{
	case 0:
		Robot.State.AutonomousProgramNumber = 0;
		break;
	}
}
void AUTON::Program12()
{
	switch (Robot.State.AutonomousTime)
	{
	case 0:
		Robot.State.AutonomousProgramNumber = 0;
		break;
	}
}
void AUTON::Program13()
{
	switch (Robot.State.AutonomousTime)
	{
	case 0:
		Robot.State.AutonomousProgramNumber = 0;
		break;
	}
}
void AUTON::Program14()
{
	switch (Robot.State.AutonomousTime)
	{
	case 0:
		Robot.Drive.To(1000, 220, 3000);
		break;

	case 3000:
		Robot.Drive.To(-1000, 220, 3000);
		break;

	case 6000:
		Robot.State.AutonomousProgramNumber = 0;
		break;
	}
}
void AUTON::Program15()
{
	switch (Robot.State.AutonomousTime)
	{
	case 0:
		Robot.State.LiftSpeed = 125;
		Robot.State.ForkSpeed = 255;
		break;
	case 1000:
		Robot.State.LiftSpeed = 0;
		Robot.State.ForkSpeed = 0;
		break;
	case 3000:
		Robot.Drive.TurnAbsolute(90, 200, 3000);
		break;
	case 6000:
		Robot.Drive.TurnAbsolute(-90, 200, 3000);
		break;

	case 9000:
		Robot.Drive.TurnAbsolute(0, 200, 3000);
		break;

	case 12000:
		Robot.State.AutonomousProgramNumber = 0;
		break;
	}
}