#ifndef LIFT_h
#define LIFT_h

#include <Arduino.h>
#include <PID_v1.h>
#include "MDD10A.h"

class ROBOT;

class LIFT
{
public:	
	LIFT(ROBOT &refRobot);

	void Setup();
	void Task();
	void Write();
	void CalcPID();
	
	void To(int degrees);

	void UpdateSetpointFromState(int bonusclicks);
	void UpdateSetpointFromStatePartTwo(int bonusclicks);
	void UpdateSetpoint(int sp);
	void UpdateSetpoint(int sp, int timeout);
	void Previous();
	void Next();
	void AquireCone();
	void ReleaseCone();

	
	double Kp=.9, Ki=.15, Kd=0.03;

private:
	ROBOT &Robot;
	PID LiftPID;
	MDD10A LiftMotor;

	// 0 - 1200
	static const int SetpointFloor = 200;
	static const int SetpointDcl = 425;
	static const int SetpointStat = 609;
	static const int SetpointMogo = 1128;
	static const int SetpointBack = 369;
};

#endif
