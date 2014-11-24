#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTServo,  HTMotor)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C1_1,     FR,            tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     BR,            tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     FL,            tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C2_2,     BL,            tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C4_1,     UR,            tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_2,     UL,            tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C3_1,    servoBall,            tServoContinuousRotation)
#pragma config(Servo,  srvo_S1_C3_2,    servoTube,            tServoStandard)
#pragma config(Servo,  srvo_S1_C3_3,    servoMvClaws,         tServoStandart)
#pragma config(Servo,  srvo_S1_C3_4,    servoClaws,           tServoStandart)
#pragma config(Servo,  srvo_S1_C3_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "JoystickDriver.c"

int a = -64;
//float  b = time1[T1];

void Servosetup()
{
	servo[servoClaws] = 235;
	servo[servoBall] = 127;
	servo[servoTube] = 140;
	servo[servoMvClaws] = 165;
	nMotorEncoder[FR] = 0;
	nMotorEncoder[FL] = 0;
	nMotorEncoder[BR] = 0;
	nMotorEncoder[BL] = 0;
	nMotorEncoder[UR] = 0;
	nMotorEncoder[UL] = 0;
}

task Ball()
{
	while (true)
	{
   if(joy1Btn(2) > 0)
   {
     a = -a;
     servo[servoBall] = 191 + a;
     while (joy1Btn(2) > 0)
     	 wait1Msec(1);
   }
  }
}

task Claw()
{
	int r = 50,start_val = ServoValue[servoClaws];
	while (true)
	{
  if (joy2Btn(5) == 1)
  	servo[servoClaws] = r;
   if (joy2Btn(4) == 1)
  		servo[servoClaws] = start_val;
  }
}

task MvClaw()
{
  int r1 = 50,start_val = ServoValue[servoMvClaws];
  while (true)
  {
  	if(joy1Btn(6) == 1)
		servo[servoMvClaws] = r1;
    if(joy1Btn(7) == 1)
  	servo[servoMvClaws] = start_val;
  }
}

task tube ()
{
	int up;
	int r2 = 7, start_val = ServoValue[servoTube];
	while(true)
	{
    up = joystick.joy1_y1;
  	if(up < -5)
	  	servo[servoTube] = start_val;
    if(up > 5)
  	  servo[servoTube] = r2;
    //if (up == 0)
  }
}

task elevator()
{
	while(true)
	{
	/*if(nMotorEncoder[UL] < 0)
	{
		motor[UR] = -100;
    motor[UL] = 100;
	}
	else*/
	//{
		/*if(nMotorEncoder[UL] > 14000)
	  {
	  	motor[UR] = 100;
      motor[UL] = -100;
	  }
	  else
	  {*/
	    if(abs(joystick.joy1_y2) > 90 && nMotorEncoder[UL] < 14000)
	    {
	    	motor[UR] = -70 * joystick.joy1_y2 / abs(joystick.joy1_y2);
        motor[UL] = 70 * joystick.joy1_y2 / abs(joystick.joy1_y2);
	    }
	    else
	    {
    		motor[UR] = 0;
        motor[UL] = 0;
    	}
    //}
  }
}


task  motion()
{
 // float k = 0.3;
	while(true)
	{
    if(abs(joystick.joy2_y1) + abs(joystick.joy2_x1) > 10)
	  {
	    motor[FR] = (-joystick.joy2_y1 + joystick.joy2_x1) * 100 / 128;
      motor[BR] = (-joystick.joy2_y1 + joystick.joy2_x1) * 100 / 128;
      motor[FL] = (-joystick.joy2_y1 - joystick.joy2_x1) * 100 / 128;
      motor[BL] = (-joystick.joy2_y1 - joystick.joy2_x1) * 100 / 128;
    }
   /* else
    {
    	if(abs(joystick.joy2_y1) + abs(joystick.joy2_x1) > 10 && joy2Btn(10) == 1)
      {
      	motor[BR] = (-joystick.joy2_y1 + joystick.joy2_x1) * 100 / 128 * k;
        motor[BL] = (-joystick.joy2_y1 - joystick.joy2_x1) * 100 / 128 * k;
        motor[FR] = 0;
        motor[FL] = 0;
      }*/
if(abs(joystick.joy2_y2 + joystick.joy2_x2) > 10 || abs(joystick.joy2_y2- joystick.joy2_x2) > 10)
	{
	  motor[FR] = (-joystick.joy2_y2 + joystick.joy2_x2) * 30 / 128;
    motor[BR] = (-joystick.joy2_y2 + joystick.joy2_x2) * 30 / 128;
    motor[FL] = (-joystick.joy2_y2 - joystick.joy2_x2) * 30 / 128;
    motor[BL] = (-joystick.joy2_y2 - joystick.joy2_x2) * 30 / 128;
  }
  if(abs(joystick.joy2_y1 + joystick.joy2_x1) <= 10 && abs(joystick.joy2_y1 - joystick.joy2_x1) <= 10 &&
  abs(joystick.joy2_y2 + joystick.joy2_x2) <= 10 && abs(joystick.joy2_y2- joystick.joy2_x2) <= 10)
  {
     	  motor[FR] = 0;
        motor[BR] = 0;
        motor[FL] = 0;
        motor[BL] = 0;
  }
}
}

task main()
{
  Servosetup();

  waitForStart();

  StartTask(MvClaw);
  StartTask(Claw);
	StartTask(Ball);
	StartTask(tube);
	StartTask(motion);
	StartTask(elevator);
	while(true)
	{
		getJoystickSettings(joystick);
  }
}