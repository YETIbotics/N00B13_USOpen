
#include "MDD10A.h"
#include <Arduino.h>

MDD10A::MDD10A(int pinpwm, int pindir, bool reversed) {
	_pinPWM = pinpwm;
	_pinDIR = pindir;
	_reverse = reversed;

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

	digitalWrite(_pinDIR, dir);
	if(speed == 0)
		analogWrite(_pinPWM, 0);
	else
		analogWrite(_pinPWM, map(abs(speed), 1, 255, 50, 255));
}

int MDD10A::NormalizeSpeed(int speed)
{
	speed = abs(speed);

	int retVal = 0;

	if(speed > 0 && speed <= 25)
	{
		retVal = map(speed, 0, 25, 100, 115);
	} 
	else if(speed > 25 && speed <= 50)
	{
		retVal = map(speed, 25, 50, 115, 130);
	}
	else if(speed > 50 && speed <= 75)
	{
		retVal = map(speed, 50, 75, 130, 145);
	}
	else if(speed > 75 && speed <= 100)
	{
		retVal = map(speed, 75, 100, 145, 160);
	}
	else if(speed > 100 && speed <= 125)
	{
		retVal = map(speed, 100, 125, 160, 175);
	}
	else if(speed > 125 && speed <= 150)
	{
		retVal = map(speed, 125, 150, 175, 190);
	}
	else if(speed > 150 && speed <= 175)
	{
		retVal = map(speed, 150, 175, 190, 205);
	}
	else if(speed > 175 && speed <= 200)
	{
		retVal = map(speed, 175, 200, 205, 220);
	}
	else if(speed > 200 && speed <= 225)
	{
		retVal = map(speed, 200, 225, 220, 235);
	}
	else if(speed > 225 && speed <= 255)
	{
		retVal = map(speed, 225, 255, 235, 255);
	}


	return retVal;
}
