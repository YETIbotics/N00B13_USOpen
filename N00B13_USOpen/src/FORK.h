#ifndef FORK_h
#define FORK_h

#include <Arduino.h>
#include <PID_v1.h>
#include "MDD10A.h"

class ROBOT;

class FORK
{
public:	
	FORK(ROBOT &refRobot);

	void Task();
	void Write();
	void Setup();
	void CalcPID();

	void To(int setpoint, int timeout);
	void Up();
	void Down();
	void Toggle();

	double Kp=10, Ki=1, Kd=0;

private:
	ROBOT &Robot;
	PID ForkPID;
	MDD10A ForkMotor;

	double forkMax = 195;

	double forkMin = 270;
};

#endif
