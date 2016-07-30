#ifndef __HANDLE_H__
#define __HANDLE_H__

#include "FreeRTOS.h"
#include "task.h"
#include "diag.h"
#include "main.h"
#include <lwip/sockets.h>
#include <lwip/raw.h>
#include <lwip/icmp.h>
#include <lwip/inet_chksum.h>
#include <platform/platform_stdlib.h>
#include "pwmout_api.h"

#define PWM_1       PC_0 
#define PWM_2       PC_1 
#define PWM_3       PC_2 
#define PWM_4       PC_3 
#define PWM_PERIOD  1000


#define STACKSIZE  		1024
#define GENERAL_SIZE 	128

#endif
