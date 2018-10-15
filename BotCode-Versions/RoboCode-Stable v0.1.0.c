#pragma config(Motor,  port2,           mBL,           tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           mBR,           tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           mFL,           tmotorNone, openLoop)
#pragma config(Motor,  port6,           mFR,           tmotorVex393_MC29, openLoop)


task main()
{
	while(true){
		motor[mFR]=(-vexRT[Ch4]+vexRT[Ch3])-vexRT[Ch1];
	  motor[mFL]=(-vexRT[Ch4]-vexRT[Ch3])-vexRT[Ch1];
	  motor[mBL]=(vexRT[Ch4]-vexRT[Ch3])-vexRT[Ch1];
	  motor[mBR]=(vexRT[Ch4]+vexRT[Ch3])-vexRT[Ch1];
	}


}
