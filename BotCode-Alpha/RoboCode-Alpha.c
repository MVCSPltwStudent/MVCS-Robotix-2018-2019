//RoboCode-Alpha v0.1.0

#pragma config(Motor,  port2,           mBL,           tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           mBR,           tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           mFL,           tmotorNone, openLoop)
#pragma config(Motor,  port6,           mFR,           tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port10,          mG,            tmotorVex393_HBridge, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

// ----------------------------------------------IMPORTANT---------------------------------------------
// USE SEPARATE TASKS FOR EVERYTHING. IT ACCOMPLISHES THE SAME THING AS PUTTING EVERYTHING IN MAIN,
// BUT IT'S MORE ORGANIZED AND HELPS DEBUG
//-----------------------------------------------IMPORTANT---------------------------------------------



task drivetrain(){ //Drivetrain Task. Joshua's code.
	while(true){
		motor[mFR]=(-vexRT[Ch4]+vexRT[Ch3])-vexRT[Ch1];
	  motor[mFL]=(-vexRT[Ch4]-vexRT[Ch3])-vexRT[Ch1];
	  motor[mBL]=(vexRT[Ch4]-vexRT[Ch3])-vexRT[Ch1];
	  motor[mBR]=(vexRT[Ch4]+vexRT[Ch3])-vexRT[Ch1];
	}
}


task ballGrabber(){ //Ball intake system code
	while(true){
		if (vexRT[Btn6U]){
			motor[mG] = 127;
	  }else if (vexRT[Btn6D]){
	  	motor[mG] = -127;
		} else {
			motor[mG] = 0;
		}
	}
}


task main()
{
startTask(drivetrain);
startTask(ballGrabber);

}
