#ifndef ROBOT_h
#define ROBOT_h

#include <Wire.h>

#include "XBOXRECV.h"
#include "Adafruit_Sensor.h"
#include "Adafruit_BNO055.h"
#include "imumaths.h"
#include "Encoder.h"

#include "STATE.h"
#include "DRIVE.h"
#include "HAT.h"
#include "LIFT.h"
#include "FORK.h"
#include "AUTON.h"


class ROBOT
{
	public:
		ROBOT();

		void Setup();
		void Loop();
		void OI();
		void MapOI();
		void ReadRobot();

		unsigned long lastStateUpdate;

		USB Usb;
		XBOXRECV Xbox;

		STATE State;
		DRIVE Drive;
		HAT Hat;
		LIFT Lift;
		FORK Fork;
		AUTON Auton;

		Encoder RightEnc;
		Encoder LeftEnc;
		Encoder LiftEnc;

		Adafruit_BNO055 bno = Adafruit_BNO055();

		static const int HatPWM = 12;
		static const int DriveLeftPWM = 8;
		static const int DriveRightPWM = 9;
		static const int LiftPWM = 11;
		static const int ForkPWM = 10;

		static const int DriveLeftDir = 47;	
		static const int DriveRightDir = 49;
		static const int LiftDir = 40;
		static const int ForkDir = 38;

		static const int RightEncDig = 35;//
		static const int RightEncInt = 3;
		static const int LeftEncDig = 37;//
		static const int LeftEncInt = 2;
		static const int LiftEncDig = 36;//
		static const int LiftEncInt = 18;//

		static const int FlexSensor = 5;

	private:

};

#endif