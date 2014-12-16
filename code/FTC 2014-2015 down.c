#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTServo,  HTMotor)
#pragma config(Sensor, S2,     touchB,         sensorTouch)
#pragma config(Sensor, S3,     touchF,         sensorTouch)
#pragma config(Motor,  mtr_S1_C1_1,     FR,            tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     BR,            tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     FL,            tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C2_2,     BL,            tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C4_1,     UR,            tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_2,     UL,            tmotorTetrix, openLoop, encoder)
#pragma config(Servo,  srvo_S1_C3_1,    servoBall,            tServoContinuousRotation)
#pragma config(Servo,  srvo_S1_C3_2,    servoTube,            tServoStandard)
#pragma config(Servo,  srvo_S1_C3_3,    servoMvClaws,          tServoStandard)
#pragma config(Servo,  srvo_S1_C3_4,    servoClaws,            tServoStandard)
#pragma config(Servo,  srvo_S1_C3_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "JoystickDriver.c"

int a = 64;

void Servosetup()
{
		servo[servoClaws] = 235;
	servo[servoBall] = 127;
	servo[servoTube] = 140;
	servo[servoMvClaws] = 235;
	nMotorEncoder[FR] = 0;
	nMotorEncoder[FL] = 0;
	nMotorEncoder[BR] = 0;
	nMotorEncoder[BL] = 0;
	nMotorEncoder[UR] = 0;
	nMotorEncoder[UL] = 0;
}

void motion(int l_ramp_goal)
{
	int enc;
	servo[servoMvClaws] = 50;
	while((-nMotorEncoder[BR] / 1000) * 3.14159265 * 10 < l_ramp_goal - 50)
	{
	  motor[FR] = 100;
    motor[BR] = 100;
    motor[FL] = 100;
    motor[BL] = 100;
  //  servo[servoBall] = 255;
    enc = -nMotorEncoder[BR];
    nxtDisplayBigTextLine(2, "%i", enc);
  }

  motor[FR] = -100;
  motor[BR] = -100;
  motor[FL] = -100;
  motor[BL] = -100;
  wait1Msec(100);

  /*while((-nMotorEncoder[BR] / 1000) * 3.14159265 * 10 < l_ramp_goal)
	{
	  motor[FR] = 20;
    motor[BR] = 20;
    motor[FL] = 20;
    motor[BL] = 20;
    servo[servoBall] = 255;
  }

  while((-nMotorEncoder[BR] / 1000) * 3.14159265 * 10 < l_ramp_goal + 18)
  {
    motor[FR] = 10;
    motor[BR] = 10;
    motor[FL] = 10;
    motor[BL] = 10;
    servo[servoBall] = 255;
    servo[servoMvClaws] = 18;
  }

  motor[FR] = 0;
  motor[BR] = 0;
  motor[FL] = 0;
  motor[BL] = 0;*/
}

void elevator()
{
	int enc;
	while(nMotorEncoder[UL] < 25000)
	{
    motor[UR] = -100;
    motor[UL] = 100;
    enc = nMotorEncoder[UL];
    nxtDisplayBigTextLine(1, "%i\n", enc);
    if(nMotorEncoder[UL] > 10000)
    	servo[servoBall] = 127;
  }
  motor[UR] = 0;
  motor[UL] = 0;

 	while(nMotorEncoder[UL] > 15000)
	{
    motor[UR] = 100;
    motor[UL] = -100;
    servo[servoBall] = 127;
  }
  motor[UR] = 0;
  motor[UL] = 0;

  servo[servoTube] = 5;
  wait1Msec(4000);

  servo[servoTube] = 140;
  while(nMotorEncoder[UL] > 0)
  {
    motor[UR] = 100;
    motor[UL] = -100;
    servo[servoBall] = 127;
  }

  motor[UR] = 0;
  motor[UL] = 0;
  servo[servoBall] = 255;
}

void rotate(int l_ramp_goal)
{
	nMotorEncoder[BR] = 0;
	while((nMotorEncoder[BR] / 1000) * 3.14159265 * 10 < l_ramp_goal)
	{
	  motor[FR] = -100;
    motor[BR] = -100;
    motor[FL] = 100;
    motor[BL] = 100;
  }

  motor[FR] = 0;
  motor[BR] = 0;
  motor[FL] = 0;
  motor[BL] = 0;

  servo[servoMvClaws] = 90;

	while((nMotorEncoder[BR] / 1000) * 3.14159265 * 10 < 2 * l_ramp_goal)
	{
	  motor[FR] = -100;
    motor[BR] = -100;
    motor[FL] = 100;
    motor[BL] = 100;
  }

  motor[FR] = 0;
  motor[BR] = 0;
  motor[FL] = 0;
  motor[BL] = 0;
}

task main()
{
  waitForStart();

	//StartTask(stage);
	//StartTask(tube);
   motion(220);
   //elevator();
   //rotate(80);

	while(true)
	{
		motor[FR] = 0;
    motor[BR] = 0;
    motor[FL] = 0;
    motor[BL] = 0;
    motor[UR] = 0;
    motor[UL] = 0;
  }
}