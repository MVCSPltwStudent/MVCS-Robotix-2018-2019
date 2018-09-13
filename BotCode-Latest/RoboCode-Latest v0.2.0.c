

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

int absv (int a) {
	return a < 0 ? -a : a;
}

task drivetrain(){ //Drivetrain Task. Joshua's code.

	while(true){
		if (absv(vexRT[Ch4]) > 15 || absv(vexRT[Ch3]) > 15 || absv(vexRT[Ch1]) > 15) {
			motor[mFR]=(-vexRT[Ch4]+vexRT[Ch3])-vexRT[Ch1];
	  	motor[mFL]=(-vexRT[Ch4]-vexRT[Ch3])-vexRT[Ch1];
	  	motor[mBL]=(vexRT[Ch4]-vexRT[Ch3])-vexRT[Ch1];
	  	motor[mBR]=(vexRT[Ch4]+vexRT[Ch3])-vexRT[Ch1];
		}
	  /*
	  if(abs(vexRT[Ch4]) < 20 && abs(vexRT[Ch3]) < 20 && abs(vexRT[Ch1]) < 20){
	    motor[mFR] = motor[mFL] = motor[mBL] = motor[mBR] = 0;
	  }*/
	}
}


task ballGrabber(){ //Ball intake system code
	while(true){
		if (vexRT[Btn6U]){ //if 6U pressed...
			motor[mGRB] = 127; //run intake motor
	  }else if (vexRT[Btn6D]){ //if 6D Pressed
	  	motor[mGRB] = -127;
		} else {
			motor[mGRB] = 0;
		}
	}
}


void Start()
{
startTask(drivetrain);
startTask(ballGrabber);

}
