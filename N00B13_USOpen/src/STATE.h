#ifndef STATE_h
#define STATE_h

#include <Arduino.h>

class STATE
{

	public:
		STATE();

		int GetLeftSpeedPercent();
		int GetRightSpeedPercent();

		void PrintSensors();
		void PrintSpeeds();
		void PrintSetpoints();

		void PrintLift();

		void ResetSpeeds();

		unsigned long LoopFrequency = 10;


		
		//double Heading = 0;
		int Temp = 0;

		double DriveRightVelocity = 0;
		double DriveRightSpeed;
		double DriveRightSpeedPrev = 0;
		double DriveLeftSpeed;
		double DriveLeftSpeedPrev = 0;

		double LeftEncoder;
		double RightEncoder;
		unsigned long RightEncoderTime=0;
		double RightEncoderPrev=0;
		unsigned long RightEncoderPrevTime=0;
		bool DriveIsRunningPID = false;
		unsigned long DriveIsRunningPIDExpiry = 0;

		bool DrivePIDIsLeft = true;
		double DrivePIDInput = 0;
		double DrivePIDOutput = 0;
		double DrivePIDSetpoint = 0;

		double HeadingSpeed;
		double HeadingSetpoint;
		bool TurnPIDIsHeadingLock;

		double ForkSpeed;
		double FlexSensor;
		double ForkPIDSetpoint = 0;
		bool ForkIsRunningPID = false;
		unsigned long ForkIsRunningPIDExpiry = 0;
		bool ForkIsUp = true;

		//HAT Class States
		int HatSetpoint;
		enum HATSTATES {
			IsOpen = 0,
			IsClosed = 1
		};
		enum HATSTATES HatState;
		bool HatIsReleasing = false;
		int HatIsReleasingTime = 0;
		
		//LIFT Class States
		double LiftEncoder;
		double LiftSpeed;
		double LiftSpeedPrev = 0;
		double LiftSetpoint;
		enum LIFTSTATES {
			FromFloorToMogo = 0,
			FromDclToMogo = 1,
			FromStatToBack = 2,
			FromMogoToStat = 3
		};
		enum LIFTSTATES LiftState = FromStatToBack;
		bool LiftIsRunningPID = false;
		unsigned long LiftIsRunningPIDExpiry = 0;

		bool LiftIsAquiring = false;
		int LiftIsAquiringTime = 0;

		bool LiftIsReleasing = false;
		int LiftIsReleasingTime = 0;

		int AutonomousProgramNumber = 0;
		bool IsAutonomousRunning = false;
		int AutonomousTime = 0;

		double Heading = 0;
		void UpdateHeading(double newHeading);	


		//Controller Stuff
		double ForkSpeedCont = 0 ;
		double LiftSpeedCont = 0;
		double DriveLeftSpeedCont = 0;
		double DriveRightSpeedCont = 0;

	private:
		double _gyroDegrees;
		int _gyroRotations = 0;

};

#endif