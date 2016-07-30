#include "handle.h"

extern void console_init(void);


/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */

void system_init_thread(void* param)
{
	system_init();
	
	vTaskDelete(NULL);
}

void handle_thread(void* param)
{
	handle();
}

void main(void)
{
	if ( rtl_cryptoEngine_init() != 0 ) {
		DiagPrintf("crypto engine init failed\r\n");
	}

	/* Initialize log uart and at command service */
	console_init();	

	/* pre-processor of application example */
	//pre_example_entry();

	/* wlan intialization */
#if defined(CONFIG_WIFI_NORMAL) && defined(CONFIG_NETWORK)
	wlan_network();
#endif
	if(xTaskCreate(system_init_thread, ((const char*)"init"), STACKSIZE, NULL, tskIDLE_PRIORITY + 2, NULL) != pdPASS)
		printf("\n\r%s xTaskCreate(system_init_thread) failed", __FUNCTION__);
	
	if(xTaskCreate(handle_thread, ((const char*)"init"), STACKSIZE, NULL, tskIDLE_PRIORITY + 1, NULL) != pdPASS)
		printf("\n\r%s xTaskCreate(handle_thread) failed", __FUNCTION__);

	/* Execute application example */
	//example_entry();

    	/*Enable Schedule, Start Kernel*/
#if defined(CONFIG_KERNEL) && !TASK_SCHEDULER_DISABLED
	#ifdef PLATFORM_FREERTOS
	vTaskStartScheduler();
	#endif
#else
	RtlConsolTaskRom(NULL);
#endif
}
