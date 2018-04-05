#include <Arduino.h>
#include "ROBOT.h"

ROBOT Robot;

void setup()
{
	Serial.begin(115200);
	Serial.println("Initialized!");

	Robot.Setup();
}

void loop()
{
	Robot.Loop();
}
