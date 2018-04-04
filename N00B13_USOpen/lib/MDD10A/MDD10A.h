#pragma once

class MDD10A{
	
public:

	MDD10A(int pinpwm, int pindir, bool reversed, int deadzone);

	void SetMotorSpeed(int speed);

	int NormalizeSpeed(int speed);

private:
	int dir = 0;	

	int _pinPWM;
	int _pinDIR;
	bool _reverse;
	int _deadZone;
};


