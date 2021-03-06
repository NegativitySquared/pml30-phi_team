#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTMotor)
#pragma config(Hubs,  S2, HTServo,  none,     none,     none)
#pragma config(Sensor, S3,     color,          sensorCOLORRED)
#pragma config(Motor,  mtr_S1_C1_1,     BR,            tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     FR,            tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     FL,            tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C2_2,     BL,            tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C3_1,     UL,            tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C3_2,     ULT,           tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C4_1,     UR,            tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C4_2,     URT,           tmotorTetrix, openLoop, encoder)
#pragma config(Servo,  srvo_S2_C1_1,    servoBall,            tServoContinuousRotation)
#pragma config(Servo,  srvo_S2_C1_2,    servoTube,            tServoStandard)
#pragma config(Servo,  srvo_S2_C1_3,    servoMvClaws,         tServoStandard)
#pragma config(Servo,  srvo_S2_C1_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "JoystickDriver.c"

int a = 64;

void L_R (int ii, int jj, int tt) // + forward; - backward
{
	motor[FR] = -jj;
	motor[FL] = -ii;
	motor[BR] = -jj;
	motor[BL] = -ii;
	wait1Msec(tt);
}

void UP (int iii, int ttt)
{
	motor[UR] = iii;
	motor[UL] = -iii;
	motor[URT] = iii;
	motor[ULT] = -iii;
	wait1Msec(ttt);
}

void L_R_UP (int i, int j, int k, int t)
{
	motor[FR] = -j;
	motor[FL] = -i;
	motor[BR] = -j;
	motor[BL] = -i;
	motor[UR] = k;
	motor[UL] = -k;
	motor[URT] = k;
	motor[ULT] = -k;
	wait1Msec(t);
}

void Servosetup()
{
	//	servo[servoClaws] = 235;
	servo[servoBall] = 127;
	servo[servoTube] = 70;
	servo[servoMvClaws] = 255;
	L_R(0, 0, 1);
	UP(0, 1);
}

void zero()
{
  L_R_UP(0, 0, 0, 1);
}

void motion_elevator(int l, int h)
{
	nMotorEncoder[BL] = 0;
	nMotorEncoder[UL] = 0;
	while (-nMotorEncoder[BL] < l && -nMotorEncoder[UL] < h)
	{
  		L_R_UP(20, 20, 100, 1);
  }
  zero();
  while (-nMotorEncoder[BL] < l)
	{
			L_R(20, 20, 1);
	}
	zero();
}

void motion(int l_ramp_goal, int a)
{
	int enc;
	int pow = 100;
  nMotorEncoder[FR] = 0;
	nMotorEncoder[BL] = 0;
  L_R(a * -100, a * -100, 1500);
  enc = nMotorEncoder[BL];
  nxtDisplayBigTextLine(1, "%i", enc);
  if(a * nMotorEncoder[BL] < 10)
  {
  	while(true)
  	{
  		for (; pow >= 0; pow--)
  		{
        L_R(-pow, -pow, 5);
        enc = nMotorEncoder[BL];
        nxtDisplayBigTextLine(2, "%i", enc);
      }
  	}
  }
 /* if (SensorValue[S3] == color)
  {
  	  nMotorEncoder[BR] = 0;
    	nMotorEncoder[BL] = 0;*/
	while(a * nMotorEncoder[BL] < l_ramp_goal - 4096)// * 1024 /(3.1415 * 10 ))// - 50)
	{
    L_R(a * -100, a * -100, 1);
    enc = nMotorEncoder[BL];
    nxtDisplayBigTextLine(2, "%i", enc);
  }
  for (int pow = a * 100; pow >= a * 20; pow--)
  {
  	L_R(-pow, -pow, 5);
  }
  while(a * nMotorEncoder[BL] < l_ramp_goal)
	{
    L_R(a * -20, a * -20, 1);
  }
  servo[servoMvClaws] = 18;
  while(a * nMotorEncoder[BL] < l_ramp_goal + 2048)
  {
    L_R(a * -20, a * -20, 1);
  }

  zero();
}

void elevator()
{
	int enc;
	nMotorEncoder[UL] = 0;
  UP(100, 1000);
  if(-nMotorEncoder[UL] < 10)
  {
    while(true)
    {
  	  UP(0, 1);
    }
  }

 	while(-nMotorEncoder[UL] < 7300)
	{
    UP(100, 1);
  }

  UP(0, 1);

  servo[servoTube] = 245;
  wait1Msec(3500);

  servo[servoTube] = 70;

  while(nMotorEncoder[UL] < -10)
  {
    UP(-100, 1);
  }

  UP(0, 1);
}

void R(float l_ramp_goal, int pow)
{
	nMotorEncoder[FR] = 0;
	int sign = abs(pow) / pow;
	while(sign * nMotorEncoder[FR] /*/ 1000) * 3.14159265 * 10*/ < l_ramp_goal)
	{
    L_R(0, pow, 1);
  }

  motor[FR] = pow;
  motor[BR] = pow;

  zero();
}

void L(float l_ramp_goal, int pow)
{
	nMotorEncoder[BL] = 0;
	int sign = abs(pow) / -pow;
	while(sign * nMotorEncoder[BL] /*/ 1000) * 3.14159265 * 10*/ < l_ramp_goal)
	{
    L_R(pow, 0, 1);
    nxtDisplayBigTextLine(2, "%i", nMotorEncoder[FR]);
  }

  motor[FL] = pow;
  motor[BL] = pow;

  zero();
}

void rotate(float l_ramp_goal)
{
	wait1Msec(500);
	nMotorEncoder[BL] = 0;
	nMotorEncoder[FR] = 0;
	while(nMotorEncoder[FR] /*/ 1000) * 3.14159265 * 10*/ < l_ramp_goal)
	{
    L_R(-100, 50, 1);
  }

  L_R(100, 100, 1);

  zero();
}

void rotate2(float l_ramp_goal)
{
	wait1Msec(500);
	nMotorEncoder[BL] = 0;
	nMotorEncoder[FR] = 0;
	while(-nMotorEncoder[FR] /*/ 1000) * 3.14159265 * 10*/ < l_ramp_goal)
	{
    L_R(50, -100, 1);
  }

  L_R(100, 100, 1);

  zero();
}

void LR(int pow, float l_ramp_goal) // + forward; - backward
{
	nMotorEncoder[BL] = 0;
	int sign = abs(pow) / -pow;
	while(sign * nMotorEncoder[BL] /*/ 1000) * 3.14159265 * 10*/ < l_ramp_goal)
	{
	  motor[FR] = -pow;
	  motor[BR] = -pow;
	  motor[FL] = -pow;
	  motor[BL] = -pow;
  }

  motor[FR] = 0;
  motor[BR] = 0;
  motor[FL] = 0;
  motor[BL] = 0;
}


task main()
{
	 Servosetup();
   servo[servoMvClaws] = 50;
   LR(-100, 1500);
   rotate(1400);
   LR(-100, 11000);
   L(2000, 100);
   LR(-100, 5000);
   R(10000, 100);
   motion(10000,-1);
   L(1000, 100);

   //elevator();
   //rotate(1000);
   //L(2000, -100);
   //wait1Msec(1000);
   //motion(800, 1);
   //L(1000, 100);
   //motion(8000,-1);
	while(true)
	{
		motor[FR] = 0;
    motor[BR] = 0;
    motor[FL] = 0;
    motor[BL] = 0;
    motor[UR] = 0;
    motor[UL] = 0;
    motor[URT] = 0;
    motor[ULT] = 0;
  }
}
