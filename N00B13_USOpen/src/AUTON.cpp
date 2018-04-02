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

void AUTON::Program1() //skills auton
{
	switch(Robot.State.AutonomousTime)
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
			Robot.Drive.To(1022,200, 1500);
			break;

		case 4500:
			Robot.Fork.Down();
			break;

		case 5000:
			Robot.Drive.To(2920-3400, 200, 5000);
			break;

		case 6000:
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
void AUTON::Program5(){
	switch(Robot.State.AutonomousTime)
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
void AUTON::Program6(){
	switch(Robot.State.AutonomousTime)
	{	
		case 0:
			Robot.Drive.To(1420, 175, 2000);
			Robot.Lift.To(1000);
			break;

		case 2000:
			Robot.Fork.Up();
			break;

		case 2500:
			Robot.Drive.To(-1250, 175, 2000);
			break;

		case 4500:
			Robot.Drive.TurnRelative(-213, 150, 2000);
			break;


		case 6500:
			Robot.Drive.To(400, 200, 1500);
			break;

		case 8500:
			Robot.Fork.Down();
			break;

		case 9000:
			Robot.Drive.To(-360, 200, 2000);
			break;

		case 9500:
			Robot.Drive.TurnRelative(-205, 150, 2000);
			break;

		case 10500:
			Robot.Drive.To(540, 200, 2000);
			break;

		case 11000:
			Robot.Fork.Up();
			break;

		case 11500:
			Robot.Drive.To(-600, 200, 2000);
			break;

		case 12000:
			Robot.Drive.TurnRelative(-111, 150, 2000);
			break;

		case 12500:
			Robot.Drive.To(510, 200, 2000);
			break;

		case 13500:
			Robot.Drive.TurnRelative(-80.43, 150, 2000);
			break;

		case 14000:
			Robot.Fork.Down();
			break;

		case 14500:
			Robot.Drive.To(60, 200, 2000);
			break;

		case 15000:
			Robot.Drive.To(-295, 200, 2000);
			break;


		case 15500:
			Robot.Drive.TurnRelative(80, 150, 2000);
			break;

		case 16500:
			Robot.Drive.To(950, 200, 2000);
			break;

		case 17000:
			Robot.Drive.TurnRelative(45, 150, 2000);
			break;

		case 17500:
			Robot.Drive.To(1200, 200, 2000);
			break;

		case 18500:
			Robot.Fork.Up();
			break;

		case 100000:
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