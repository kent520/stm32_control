#include "handle.h"
/**************************************
1.前进 2.后退 3.左转 4.右转 5.停止

PC.0 PC.1 控制左边电机 	PC.2 PC.3控制右边电机
PinName  pwm_motor_pin[4] =  {PWM_1, PWM_2, PWM_3, PWM_4};
							  PC.0   PC.1   PC.2   PC.3
**************************************/

extern pwmout_t pwm_motor[];

void advance()
{
	for (int i = 0; i < 2; i++)
	{
		pwmout_pulsewidth_us(&pwm_motor[i * 2], 0);		
		pwmout_pulsewidth_us(&pwm_motor[i * 2 + 1], PWM_PERIOD / 2.5);
	}
}

void recede()
{
	for (int i = 0; i < 2; i++)
	{
		pwmout_pulsewidth_us(&pwm_motor[i * 2], PWM_PERIOD / 2.5);		
		pwmout_pulsewidth_us(&pwm_motor[i * 2 + 1], 0);
	}
}

void turn_left()
{
	
	pwmout_pulsewidth_us(&pwm_motor[0], PWM_PERIOD / 4);
	pwmout_pulsewidth_us(&pwm_motor[1], 0);		
	pwmout_pulsewidth_us(&pwm_motor[2], 0);		
	pwmout_pulsewidth_us(&pwm_motor[3], PWM_PERIOD / 4);
}

void turn_right()
{
	pwmout_pulsewidth_us(&pwm_motor[0], 0);		
	pwmout_pulsewidth_us(&pwm_motor[1], PWM_PERIOD / 4);
	pwmout_pulsewidth_us(&pwm_motor[2], PWM_PERIOD / 4);
	pwmout_pulsewidth_us(&pwm_motor[3], 0);		
}

void stop()
{
	for (int i = 0; i < 4; i++)
	{
		pwmout_pulsewidth_us(&pwm_motor[i], 0);
	}
}
void control_motor(char value[])
{
	switch(value[0])
	{
		case '1':
			advance();
			break;
		case '2':
			recede();
			break;
		case '3':
			turn_left();
			break;
		case '4':
			turn_right();
			break;
		case '5':
			stop();
			break;
		default:
			break;
			
	}
}


