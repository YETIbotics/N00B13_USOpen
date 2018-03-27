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

void AUTON::Task() {

	if(Robot.State.IsAutonomousRunning)
	{

		switch(Robot.State.AutonomousProgramNumber)
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

		if(Robot.State.IsAutonomousRunning)
			Robot.State.AutonomousTime += Robot.State.LoopFrequency;
		else
			Robot.State.AutonomousTime = 0;
	}

}


void AUTON::Write() {
}

void AUTON::StartAutonomous()
{
	StartAutonomous(Robot.State.AutonomousProgramNumber);
}

void AUTON::StartAutonomous(int progNum)
{
	Robot.State.AutonomousProgramNumber = progNum;
	Robot.State.AutonomousTime = 0;
	Robot.State.IsAutonomousRunning = true;
}

void AUTON::StopAutonomous()
{
	Robot.State.AutonomousProgramNumber = 0;
}

void AUTON::PreviousProgram(){
	Robot.State.AutonomousProgramNumber--;

	if(Robot.State.AutonomousProgramNumber < 0)
		Robot.State.AutonomousProgramNumber = NumRegisteredPrograms;
}
void AUTON::NextProgram(){
	Robot.State.AutonomousProgramNumber++;

	if(Robot.State.AutonomousProgramNumber > NumRegisteredPrograms)
		Robot.State.AutonomousProgramNumber = 0;
}

void AUTON::Program1()
{
	switch(Robot.State.AutonomousTime)
	{
		case 0:
			Robot.Drive.To(1000, 200, 1500, 0);
			//Robot.Drive.TurnRelative(20, 100, 1000);
			//Robot.Drive.SweepAbsolute(45, 200, 1000, false);
			break;

		case 1500:
			Robot.Drive.To(-1000, 200, 1500, 0);
			//Robot.Drive.TurnRelative(-20, 100, 1000);
			//Robot.Drive.SweepAbsolute(0, 200, 1000, false);
			break;

		case 4000:
			Robot.State.AutonomousProgramNumber = 0;
			break;
	}
}

void AUTON::Program2(){
	switch(Robot.State.AutonomousTime)
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
void AUTON::Program3(){
	switch(Robot.State.AutonomousTime)
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
void AUTON::Program4(){
	switch(Robot.State.AutonomousTime)
	{
		case 0:
			Robot.State.AutonomousProgramNumber = 0;
			break;
	}
}
void AUTON::Program5(){
	switch(Robot.State.AutonomousTime)
	{
		case 0:
			Robot.State.AutonomousProgramNumber = 0;
			break;
	}
}
void AUTON::Program6(){
	switch(Robot.State.AutonomousTime)
	{
		case 0:
			Robot.State.AutonomousProgramNumber = 0;
			break;
	}
}
void AUTON::Program7(){
	switch(Robot.State.AutonomousTime)
	{
		case 0:
			Robot.State.AutonomousProgramNumber = 0;
			break;
	}
}
void AUTON::Program8(){
	switch(Robot.State.AutonomousTime)
	{
		case 0:
			Robot.State.AutonomousProgramNumber = 0;
			break;
	}
}
void AUTON::Program9(){
	switch(Robot.State.AutonomousTime)
	{
		case 0:
			Robot.State.AutonomousProgramNumber = 0;
			break;
	}
}
void AUTON::Program10(){
	switch(Robot.State.AutonomousTime)
	{
		case 0:
			Robot.State.AutonomousProgramNumber = 0;
			break;
	}
}
void AUTON::Program11(){
	switch(Robot.State.AutonomousTime)
	{
		case 0:
			Robot.State.AutonomousProgramNumber = 0;
			break;
	}
}
void AUTON::Program12(){
	switch(Robot.State.AutonomousTime)
	{
		case 0:
			Robot.State.AutonomousProgramNumber = 0;
			break;
	}
}
void AUTON::Program13(){
	switch(Robot.State.AutonomousTime)
	{
		case 0:
			Robot.State.AutonomousProgramNumber = 0;
			break;
	}
}
void AUTON::Program14(){
	switch(Robot.State.AutonomousTime)
	{
		case 0:
			Robot.State.AutonomousProgramNumber = 0;
			break;
	}
}
void AUTON::Program15(){
	switch(Robot.State.AutonomousTime)
	{
		case 0:
			Robot.State.AutonomousProgramNumber = 0;
			break;
	}
}