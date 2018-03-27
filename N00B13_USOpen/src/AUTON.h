#ifndef AUTON_h
#define AUTON_h

#include <Arduino.h>
#include <Servo.h>

class ROBOT;

class AUTON
{
public:	
	AUTON(ROBOT &refRobot);

	void Setup();
	void Task();
	void Write();
	
	void StartAutonomous();
	void StartAutonomous(int progNum);
	void StopAutonomous();

	void PreviousProgram();
	void NextProgram();

private:
	ROBOT &Robot;

	int NumRegisteredPrograms;

	void Program1();
	void Program2();
	void Program3();
	void Program4();
	void Program5();
	void Program6();
	void Program7();
	void Program8();
	void Program9();
	void Program10();
	void Program11();
	void Program12();
	void Program13();
	void Program14();
	void Program15();
};

#endif
