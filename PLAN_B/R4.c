#pragma config(Sensor, in2,    potClaw,        sensorPotentiometer)
#pragma config(Sensor, dgtl1,  LED,            sensorLEDtoVCC)
#pragma config(Sensor, dgtl3,  encLift,        sensorQuadEncoder)
#pragma config(Sensor, dgtl5,  encFR,          sensorQuadEncoder)
#pragma config(Sensor, dgtl7,  encFL,          sensorQuadEncoder)
#pragma config(Sensor, dgtl9,  encBL,          sensorQuadEncoder)
#pragma config(Sensor, dgtl11, encFL,          sensorQuadEncoder)
#pragma config(Motor,  port1,           mFL,           tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port2,           mBL,           tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           mBR,           tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           mIntake,       tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           mLift,         tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port6,           mFR,           tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           mClaw,         tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           mFlyWheelR,    tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port9,           mFlyWheelL,    tmotorVex393HighSpeed_MC29, openLoop)

/*

 --- README ---

8U: Set flyWheel full speed
8L: Set flyWheel half speed
8D: Set flyWheel zero speed (turn off)
*there is no flyWheel toggle button

see line 174 for adjusting flipbot function

*/

//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

// potClaw {up: 4096, down: 600}

#pragma platform(VEX2)

#pragma competitionControl(Competition)

#include "Vex_Competition_Includes.c"

#define __DRIVE_SPEED_FACTOR_SLOW 0.5
#define __FLYWHEEL_SECONDARY_SPEED 67


void pre_auton() {
  bStopTasksBetweenModes = true;
}


task autonomous() {
}

// USER CONTROL


int flyWheelSpeed = 0;
int flyWheelSpeed_Memory = __FLYWHEEL_SECONDARY_SPEED;

float driveFactor = 1.0;
float FL, FR, BL, BR, headflip = 1.0;

task LED_Update () {
	int LEDFlashStatus = 0;
	while (true) {
		if (flyWheelSpeed == 127 || flyWheelSpeed == 127) {
			SensorValue[LED] = 0;
		} else if (flyWheelSpeed > __FLYWHEEL_SECONDARY_SPEED) {
			SensorValue[LED] = LEDFlashStatus;
			LEDFlashStatus = 1 - LEDFlashStatus;
			wait1Msec(100);
		} else if (flyWheelSpeed == __FLYWHEEL_SECONDARY_SPEED) {
			SensorValue[LED] = 1;
		} else if (flyWheelSpeed < __FLYWHEEL_SECONDARY_SPEED) {
			SensorValue[LED] = LEDFlashStatus;
			LEDFlashStatus = 1 - LEDFlashStatus;
			wait1Msec(500);
		}
		EndTimeSlice();
	}
}

task ballIntake () {
	while (true) {
		if (vexRT[Btn6U] && !vexRT[Btn6D]) {
			motor[mIntake] = 127;
		} else if (!vexRT[Btn6U] && vexRT[Btn6D]) {
			motor[mIntake] = -127;
		} else {
			motor[mIntake] = 0;
		}
		EndTimeSlice();
	}
}

task flyWheel () {
	while (true) {
		motor[mFlyWheelL] = motor[mFlyWheelR] = flyWheelSpeed;
		if (vexRT[Btn8U]) { // set full speed button pushed
			flyWheelSpeed = 127;
		} else if (vexRT[Btn8L]) { // set secondary speed button pushed
			flyWheelSpeed = __FLYWHEEL_SECONDARY_SPEED;
		} else if (vexRT[Btn8D]) {
			flyWheelSpeed = 0;
		} else if (vexRT[Btn8R]) {
			flyWheelSpeed = flyWheelSpeed_Memory;
		}
		if (vexRT[Btn6U] && vexRT[Btn6D]) {
			if (vexRT[Btn8U]) {
				while (vexRT[Btn8U]) {
					wait1Msec(10);
				}
				flyWheelSpeed_Memory += 10;
				flyWheelSpeed_Memory = flyWheelSpeed_Memory > 127 ? 127 : flyWheelSpeed_Memory;
				flyWheelSpeed = flyWheelSpeed_Memory;
			} else if (vexRT[Btn8D]) {
				while (vexRT[Btn8D]) {
					wait1Msec(10);
				}
				flyWheelSpeed_Memory -= 10;
				flyWheelSpeed_Memory = flyWheelSpeed_Memory < 0 ? 0 : flyWheelSpeed_Memory;
				flyWheelSpeed = flyWheelSpeed_Memory;
			}
		}
		EndTimeSlice();
	}
}
task lifter () { // task controlling the cascade-lift an the claw
	while (true) {
		if (vexRT[Btn5U] && vexRT[Btn5D]) {
			motor[mLift] = 0;
		}	else if (vexRT[Btn5U]) {
			motor[mLift] = 127;
		} else if (vexRT[Btn5D]) {
			motor[mLift] = -127;
		} else {
			motor[mLift] = 0;
		}
		EndTimeSlice();
	}
}

void moveClawUp (int toPos) {
	clearTimer(T1); // set timer in order to prevent burning out motors
	while (SensorValue[potClaw] < toPos && time1[T1] < 3000) {
		motor[mClaw] = 127;
	}
	motor[mClaw] = 0;
}
void moveClawDown (int toPos) {
	clearTimer(T1); // set timer in order to prevent burning out motors
	while (SensorValue[potClaw] > toPos && time1[T1] < 3000) {
		motor[mClaw] = -127;
	}
	motor[mClaw] = 0;
}

task claw () {
	while (true) {
		if (vexRT[Btn5U] && vexRT[Btn5D]) {
			if (vexRT[Btn7U]) {
				motor[mClaw] = 127;
			} else if (vexRT[Btn7D]) {
				motor[mClaw] = -127;
			} else {
				motor[mClaw] = 0;
			}
		} else {
			if (vexRT[Btn7R]) {
				moveClawDown (580);
			}
			if (vexRT[Btn7U]) { // flip on ground
				moveClawUp (2500);
				moveClawDown (580);
			}
			if (vexRT[Btn7D]) { // flip on bot
				moveClawUp (2000); // change this number to change the target pot position
			}
		}
		EndTimeSlice();
	}
}

float fmax (float a, float b) {
	return a > b ? a : b;
}

task drive() {
  float maxMotor, targetRatio;
  int i;
	while (true) {
		driveFactor = __DRIVE_SPEED_FACTOR_SLOW;
    // Death zones
		if (abs(vexRT[Ch4]) < 20 && abs(vexRT[Ch3]) < 20 && abs(vexRT[Ch1]) < 20) {
			driveFactor = 0;
		} else {
			FR = (headflip * (-vexRT[Ch4] + vexRT[Ch3])) - vexRT[Ch1]; //Determines motor speeds. Joshua's Code.
      FL = (headflip * (-vexRT[Ch4] - vexRT[Ch3])) - vexRT[Ch1];
      BL = (headflip * (vexRT[Ch4] - vexRT[Ch3])) - vexRT[Ch1];
      BR = (headflip * (vexRT[Ch4] + vexRT[Ch3])) - vexRT[Ch1];

			if(sqrt((vexRT[Ch4] * vexRT[Ch4]) + (vexRT[Ch3] * vexRT[Ch3])) < 120 &&
				 sqrt((vexRT[Ch1] * vexRT[Ch1]) + (vexRT[Ch2] * vexRT[Ch2])) < 120) {
				driveFactor = 0.5;
			} else {
				driveFactor = 1.0;
			}

		}
		if (vexRT[Btn7L]) { // flip head
    	while (vexRT[Btn7L]) { wait1Msec(10);}
      headFlip = -headFlip;
    }
		// Make sure at least one of the motors is running at full spead
		/*
		maxMotor = ms[0];
		for (i = 1; i < 4; ++i) {
			maxMotor = fmax (ms[i], maxMotor);
		}
		targetRatio = 127.0 / maxMotor;
		for (i = 0; i < 4; ++i) {
			ms[i] *= targetRatio;
		}
		motor[mFL] = ms[0] * driveFactor;
		motor[mFR] = ms[1] * driveFactor;
		motor[mBL] = ms[2] * driveFactor;
		motor[mBR] = ms[3] * driveFactor;
		*/

    // Set each motor to a target speed
		motor[mFL] = FL * driveFactor;
		motor[mFR] = FR * driveFactor;
		motor[mBL] = BL * driveFactor;
		motor[mBR] = BR * driveFactor;
		EndTimeSlice();
	}
}

task usercontrol() {
	startTask(drive);
	startTask(ballIntake);
	startTask(flyWheel);
	startTask(lifter);
	startTask(claw);
	startTask(LED_Update);
  while (true) {
    EndTimeSlice();
  }
}
