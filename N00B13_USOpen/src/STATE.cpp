
#include "STATE.h"
#include <Arduino.h>

STATE::STATE()
{

}

int STATE::GetLeftSpeedPercent()
{
	return map(DriveLeftSpeed,-255,255,-99,99);
}


int STATE::GetRightSpeedPercent() 
{
	return map(DriveRightSpeed, -255, 255, -99, 99);
}

void STATE::PrintSetpoints()
{
	Serial.print("\tLE: ");
	Serial.print(DrivePIDSetpoint);
	Serial.print("\tLiE: ");
	Serial.print(LiftSetpoint);
	Serial.print("\tHD: ");
	Serial.print(HeadingSetpoint);
	Serial.print("\tHa: ");
	Serial.print(HatSetpoint);

	//Serial.println("");Robot.State.HatSetpoint
}

void STATE::PrintSensors()
{
	Serial.print("\tLE: ");
	Serial.print(LeftEncoder);
	Serial.print("\tRE: ");
	Serial.print(RightEncoder);
	Serial.print("\tLiE: ");
	Serial.print(LiftEncoder);
	Serial.print("\tHD: ");
	Serial.print(Heading);
	Serial.print("\tFL: ");
	Serial.print(FlexSensor);

	//Serial.println("");
}


void STATE::PrintSpeeds()
{
	Serial.print("\tLe: ");
	Serial.print(DriveLeftSpeed);
	Serial.print("\tRi: ");
	Serial.print(DriveRightSpeed);
	Serial.print("\tLi: ");
	Serial.print(LiftSpeed);
	Serial.print("\tFo: ");
	Serial.print(ForkSpeed);

	//Serial.println("");
}

void STATE::PrintLift()
{
	Serial.print("\tEnc: ");
	Serial.print(LiftEncoder);
	Serial.print("\tSP: ");
	Serial.print(LiftSetpoint);
	Serial.print("\tPO: ");
	Serial.print(LiftSpeed);
}

void STATE::ResetSpeeds()
{
	DriveLeftSpeed = 0;
	DriveRightSpeed = 0;
	LiftSpeed = 0;
	ForkSpeed = 0;
}

void STATE::UpdateHeading(double newHeading)
{
	float prev = _gyroDegrees;
	float dif = prev - newHeading;
	if (abs(dif) > 180)
	{
		if (dif < 0)
		{
			_gyroRotations--; 
		}
		else
		{
			_gyroRotations++;
		}
	}

	_gyroDegrees = newHeading;

	Heading = _gyroDegrees + (360 * _gyroRotations);
}
