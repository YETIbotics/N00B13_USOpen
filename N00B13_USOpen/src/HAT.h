#ifndef HAT_h
#define HAT_h

#include <Arduino.h>
#include <Servo.h>

class ROBOT;

class HAT
{
public:	
	HAT(ROBOT &refRobot);

	void Setup();
	void Task();
	void Write();

	void Open();
	void Close();
	void Toggle();
	void Release();

private:
	ROBOT &Robot;
	Servo HatServo;

	static const int OpenPos = 100;
	static const int ClosedPos = 160;

	static const int ReleaseDuration = 160;
	static const int MoveDuration = 160;
};

#endif
