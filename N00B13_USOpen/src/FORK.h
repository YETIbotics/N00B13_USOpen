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

	void To(int setpoint, int timeout);
	void Up();
	void Down();
	void Toggle();

	double Kp=10, Ki=0, Kd=0;

private:
	ROBOT &Robot;
	PID ForkPID;
	MDD10A ForkMotor;

	double forkMax = 149;

	double forkMin = 210;
};

#endif
