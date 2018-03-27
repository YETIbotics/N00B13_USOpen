#ifndef DRIVE_h
#define DRIVE_h

#include <Arduino.h>
#include <PID_v1.h>
#include "MDD10A.h"

class ROBOT;

class DRIVE
{
public:	
	DRIVE(ROBOT &refRobot);

	void Task();
	void Write();
	void Setup();

	void UpdateSetpoint(int sp);
	void UpdateSetpoint(int sp, int timeout);

	void To(int setpoint, double speed, int timeout);
	void To(int setpoint, double speed, int timeout, int heading);

	void TurnRelative(int deg, double speed, int timeout);
	void TurnAbsolute(int deg, double speed, int timeout);
	void SweepRelative(int deg, double speed, int timeout, bool lockLeft);
	void SweepAbsolute(int deg, double speed, int timeout, bool lockLeft);
	
	double Kp=1, Ki=0, Kd=0;
	double tKp=4, tKi=0, tKd=0;

private:
	ROBOT &Robot;
	PID DrivePID;
	PID TurnPID;
	MDD10A Left;
	MDD10A Right;
};

#endif
