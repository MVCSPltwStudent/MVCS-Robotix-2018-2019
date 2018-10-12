//RoboCode-Alpha v0.3.1

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
const int spinUpTimeInMS = abs(1000);

//Internal Use Variables
int FR;
int FL;
int BR;
int BL;
bool flywheelRunning;
bool FireReady;


int mabs (int a) {
	return a < 0 ? -a : a;
}

task drivetrain(){ //Drivetrain Task. Joshua's code.
	while(true){
		FR=(-vexRT[Ch4]+vexRT[Ch3])-vexRT[Ch1]; //Determines motor speeds. Joshua's Code.
		FL=(-vexRT[Ch4]-vexRT[Ch3])-vexRT[Ch1];
		BL=(vexRT[Ch4]-vexRT[Ch3])-vexRT[Ch1];
		BR=(vexRT[Ch4]+vexRT[Ch3])-vexRT[Ch1];
		if(mabs(vexRT[Ch4]) < 20 && mabs(vexRT[Ch3]) < 20 && mabs(vexRT[Ch1]) < 20){ //Checks if joystick is in deadzone
			FR = FL = BR = BL = 0;																									//if so, sets motor speeds to 0
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
		if (vexRT[Btn6U]){ //if 6U pressed...
			motor[mGRB] = 127; //run intake motor
			}else if (vexRT[Btn6D]){ //if 6D Pressed
			motor[mGRB] = -127; // reverse
			} else {
			motor[mGRB] = 0; //else stop
		}
		EndTimeSlice(); //tell task handler done
	}
}

task flywheelToggle(){ //detects button presses to toggle the flywheel
	while (true){
		if(vexRT[Btn8D]){ //if toggle button pressed
			flywheelRunning = !flywheelRunning;  //set flywheel running bool to the opposite value
			while(vexRT[Btn8D]){ //wait until button un-pressed
				wait1Msec(1);
			}
		}
		EndTimeSlice(); //tell taks handler done
	}
}
task flywheelHandler(){ //handles flywheel running
	while(true){
		if(!flywheelRunning){ //if the flywheel is set to be off
			motor[mFRE] = 0;		//turn it off
			FireReady = false;	//tell everythign else that its not ready to fire
		}else if (!FireReady){ //if flywheel is on but the boolean says its not ready to fire (too slow)
			motor[mFRE] = 127;		// start the motor
			for(int a = 0; a < (spinUpTimeInMS/10);a++){ //give it a predetermined spin up time (todo: add encoders and make closed loop
				if(!flywheelRunning){ //check if flywheel turned off while spinning up
					break; //if turned off leave function
				}
				wait1Msec(10); //10 mS delay
			}
			FireReady = true; //tell cortex ready to fire (if loop exited early it will revert to false on next iteration)
		} else {
			motor[mFRE] = 127; //if ready to fire and flywheel is on keep motor running
		}
		EndTimeSlice();	//tell task handler is done
	}
}

void Start()
{
	startTask(drivetrain);
	startTask(ballGrabber);
	flywheelRunning = false;
	startTask(flywheelToggle);
	startTask(flywheelHandler);
}
