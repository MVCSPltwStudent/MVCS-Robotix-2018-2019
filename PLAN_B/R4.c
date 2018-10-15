#pragma config(Sensor, dgtl12, LED,            sensorLEDtoVCC)
#pragma config(Motor,  port1,           mLFT2,         tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port2,           mBL,           tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port3,           mBR,           tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port4,           mGRB,          tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           mFL,           tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port6,           mFR,           tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port7,           mCLW,          tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           mFRE,          tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port9,           mLFT1,         tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port10,          mBST,          tmotorVex393_HBridge, openLoop)

#pragma platform(VEX2)

#pragma competitionControl(Competition)

#include "Vex_Competition_Includes.c"

void pre_auton()
{
  bStopTasksBetweenModes = true;
}


task autonomous()
{
}

task usercontrol()
{
  while (true)
  {
    EndTimeSlice();
  }
}
