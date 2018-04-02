
#include "MDD10A.h"
#include <Arduino.h>

MDD10A::MDD10A(int pinpwm, int pindir, bool reversed) {
	MDD10A(pinpwm, pindir, reversed, 0);
}

MDD10A::MDD10A(int pinpwm, int pindir, bool reversed, int deadzone) {
	_pinPWM = pinpwm;
	_pinDIR = pindir;
	_reverse = reversed;

	/*
		The MDD10A MC is fairly linear with the exception of the first 75. 
		This number can vary depending on the mass being moved.
	*/
	_deadZone = deadzone; 

	/*
	prescaler = 1 ---> PWM frequency is 31000 Hz
	prescaler = 2 ---> PWM frequency is 4000 Hz
	prescaler = 3 ---> PWM frequency is 490 Hz (default value)
	prescaler = 4 ---> PWM frequency is 120 Hz
	prescaler = 5 ---> PWM frequency is 30 Hz
	prescaler = 6 ---> PWM frequency is <20 Hz

	timer 1 (controls pin 12, 11);
	timer 2 (controls pin 10, 9);
	timer 3 (controls pin 5, 3, 2);
	timer 4 (controls pin 8, 7, 6);
	

	int clr = 7;             // this is 111 in binary and is used as an eraser
	int psc = 2;

	switch (_pinPWM)
	{
	// case 12:
	// case 11:
	// 	TCCR1B &= ~clr;
	// 	TCCR1B |= psc;
	// 	break;
	case 10:
	case 9:
		TCCR2B &= ~clr;   
		TCCR2B |= psc;  
		break;
	case 5:
	case 3:
	case 2:
		TCCR3B &= ~clr;
		TCCR3B |= psc;
		break;
	case 8:
	case 7:
	case 6:
		TCCR4B &= ~clr;
		TCCR4B |= psc;
		break;
	}*/

	pinMode(_pinPWM, OUTPUT);
	pinMode(_pinDIR, OUTPUT);
}

void MDD10A::SetMotorSpeed(int speed) {
	if (speed < 0) {
		dir = 1;
	}
	else {
		dir = 0;
	}

	if (_reverse)
	{
		if (dir == 1)
			dir = 0;
		else
			dir = 1;
	}

	if(_slewEnabled)
	{
		if (speed > _speedPrev && speed > 0)
		{
			//Accel
			if (speed - _speedPrev > _slewRate)
			{
				speed = _speedPrev + _slewRate;	 
			}
		}
		else if (speed < _speedPrev && speed < 0)
		{
			//Accel
			if (abs(speed - _speedPrev) > _slewRate)
			{
				speed = _speedPrev - _slewRate;
			}
		}
	}
	_speedPrev = speed;

	digitalWrite(_pinDIR, dir);
	analogWrite(_pinPWM, map(abs(speed), 0, 255, _deadZone, 255));
}


void MDD10A::EnableSlewRate()
{
	_slewEnabled = true;
}
void MDD10A::DisableSlewRate()
{
	_slewEnabled = false;
}
void MDD10A::SetSlewRate(int slewrate)
{
	_slewRate = slewrate;
	_slewEnabled = true;
}