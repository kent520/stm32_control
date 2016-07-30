#include "handle.h"

pwmout_t pwm_motor[4];
PinName  pwm_motor_pin[4] =  {PWM_1, PWM_2, PWM_3, PWM_4};

void wifi_init()
{ 
	fATW3("smart_car");
	fATWA(NULL);
}

void pwm_init()
{
	for (int i = 0; i < 4; i++)
	{
		pwmout_init(&pwm_motor[i], pwm_motor_pin[i]);
		pwmout_period_us(&pwm_motor[i], PWM_PERIOD);
		pwmout_pulsewidth_us(&pwm_motor[i], 0);
	}
}

void system_init()
{
	wifi_init();
	pwm_init();
}
