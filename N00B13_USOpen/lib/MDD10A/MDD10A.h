#pragma once

class MDD10A{
	
public:

	MDD10A(int pinpwm, int pindir, bool reversed);
	MDD10A(int pinpwm, int pindir, bool reversed, int deadzone);

	void SetMotorSpeed(int speed);

	void EnableSlewRate();
	void DisableSlewRate();
	void SetSlewRate(int slewrate);

private:
	int dir = 0;	

	int _pinPWM;
	int _pinDIR;
	bool _reverse;
	int _deadZone;
	int _slewRate = 0;
	bool _slewEnabled = false;

	int _speedPrev=0;
};


