//RoboCode-Alpha v0.6.0


//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*
Port1: LiftMotor2 (Can be combined with Prt. 6 in necessity

Port2: Rear Left Drive

Port3: Rear Right Drive

Port4: Intake Motor

Port5: Front Left Drive

Port6: Front Right Drive

Port7: ClawMotor

Port8: Firing Motors (Splitterx2 + Power Expander)

Port9: LiftMotor1

Port10: Platform Boost system (?)

*/



// ----------------------------------------------IMPORTANT---------------------------------------------
// USE SEPARATE TASKS FOR EVERYTHING. IT ACCOMPLISHES THE SAME THING AS PUTTING EVERYTHING IN MAIN,
// BUT IT'S MORE ORGANIZED AND HELPS DEBUG
//-----------------------------------------------IMPORTANT---------------------------------------------

//Config

//Internal Use Variables
int FR;
int FL;
int BR;
int BL;
bool flywheelRunning;
bool FireReady;
bool halfSpeed = false;
int flySpeed = 127;
int flyModifier = 0;

int mabs (int a) {
	return a < 0 ? -a : a;
}

task drivetrain(){ //Drivetrain Task. Joshua's code.
	while(true){
		FR = (-vexRT[Ch4] + vexRT[Ch3]) - vexRT[Ch1]; //Determines motor speeds. Joshua's Code.
		FL = (-vexRT[Ch4] - vexRT[Ch3]) - vexRT[Ch1];
		BL = (vexRT[Ch4] - vexRT[Ch3]) - vexRT[Ch1];
		BR = (vexRT[Ch4] + vexRT[Ch3]) - vexRT[Ch1];
		if (mabs(vexRT[Ch4]) < 20 && mabs(vexRT[Ch3]) < 20 && mabs(vexRT[Ch1]) < 30){ //Checks if joystick is in deadzone
			FR = FL = BR = BL = 0;																									//if so, sets motor speeds to 0
		}
		if(sqrt((vexRT[Ch4]^2) + (vexRT[Ch3]^2)) < 110){
			FR = FR/2;
			FL = FL/2;
			BR = BR/2;
			BL = BL/2;
			turnLEDOn(LED);
		} else {
			turnLEDOff(LED);
		}
		if(sqrt((vexRT[Ch4]^2) + (vexRT[Ch3]^2)) < 127){
			FR = FR / 2;
			FL = FL / 2;
			BR = BR / 2;
			BL = BL / 2;
			turnLEDOn(LED);
		} else {
		turnLEDOff(LED);
        }
			motor[mFR] = FR;  //Applies Motor Speeds
			motor[mFL] = FL;
			motor[mBR] = BR;
			motor[mBL] = BL;

		EndTimeSlice(); //tells task handler is done
	}
}


task ballGrabber(){ //Ball intake system code
	while(true){
		if (vexRT[Btn6U]) { //if 6U pressed...
			motor[mGRB] = 127; //run intake motor
		} else if (vexRT[Btn6D]) { //if 6D Pressed
			motor[mGRB] = -127; // reverse
		} else {
			motor[mGRB] = 0; //else stop
		}
		EndTimeSlice(); //tell task handler done
	}
}
task speedToggle() {
	while (true) {
		if (vexRT[Btn7U]) {
			halfSpeed = !halfSpeed;
			while (vexRT[Btn7U]) {
				wait1Msec(1);
			}
		}
		EndTimeSlice();
	}
}

task flywheelToggle() { //detects button presses to toggle the flywheel
	while (true) {
		if (vexRT[Btn8D]) { //if toggle button pressed
			flywheelRunning = !flywheelRunning;  //set flywheel running bool to the opposite value
			while (vexRT[Btn8D]) { //wait until button un-pressed
				wait1Msec(1);
			}
		}
		if (flywheelRunning) { // if flywheel set to be on
			motor[mFRE] = flySpeed + (5*flyModifier); //turn on
			motor[port9] = flySpeed + (5*flyModifier);
		} else {
			motor[mFRE] = 0; //else turn off
			motor[port9] = 0;
		}
		EndTimeSlice(); //tell task handler done
	}
}

task flySpeedAdjuster() {
	if (vexRT[Btn8L]) {
		 while(!vexRT[Btn8L]){wait1Msec(1);}
		 switch(flySpeed){
		   case 254:
		   	flySpeed = lv1;
		   break;
/*
		   case lv1:
		   	flySpeed = lv2;
		   break;
*/ /*
		   case lv2:
		   	flySpeed = lv3;
		   break;
*/
		   default:
		   	flySpeed = 254;
		  }
	}/*
	if (vexRT[Btn8R]) {
		 while (!vexRT[Btn8R]){wait1Msec(1);}
		 switch (flySpeed) {
		   case 127:
		   	flySpeed = lv3;
		   break;

		   case lv3:
		   	flySpeed = lv2;
		   break;

		   case lv2:
		   	flySpeed = lv1;
		   break;

		   default:
		   	flySpeed = 127;
		  }
	}*/
	if (vexRT[Btn5U]) {
		 while(!vexRT[Btn5U]){wait1Msec(1);}
		  flyModifier++;
	}
	if (vexRT[Btn5D]) {
		 while(!vexRT[Btn5D]){wait1Msec(1);}
		  flyModifier++;
	}

}


void Start()
{
	startTask(drivetrain);
	startTask(ballGrabber);
	flywheelRunning = false;
	startTask(flywheelToggle);
	startTask(speedToggle);
	startTask(flySpeedAdjuster);
}
