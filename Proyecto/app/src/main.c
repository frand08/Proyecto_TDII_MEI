
/*==================[inclusions]=============================================*/


#include "main.h"


/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/


/*==================[internal functions declaration]=========================*/

/** @brief hardware initialization function
 *	@return none
 */
static void initHardware(void);

/*==================[internal data definition]===============================*/

const char str1[] = ">111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111<\r\n";
const char str2[] = ">222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222<\r\n";

static xSemaphoreHandle sem;

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

static void initHardware(void)
{
    SystemCoreClockUpdate();

    Board_Init();

    Board_LED_Set(0, false);
}

static void task(void * p)
{
	char * str = (char *)p;

   while (1)
   {
	   xSemaphoreTake(sem, portMAX_DELAY);
	   DEBUGSTR(str);
	   xSemaphoreGive(sem);
   }
}

static void taskLED(void * p)
{
	int i = 1;
	while(1)
	{
		if (i==1)
		{
			Chip_GPIO_WritePortBit(LPC_GPIO, PLED0, LED0 , 0);
			Chip_GPIO_WritePortBit(LPC_GPIO, PLED1, LED1 , 1);
			Chip_GPIO_WritePortBit(LPC_GPIO, PLED2, LED2 , 0);
			Chip_GPIO_WritePortBit(LPC_GPIO, PLED2, LED3 , 1);
			Chip_GPIO_WritePortBit(LPC_GPIO, PLED4, LED4 , 0);
			//Chip_GPIO_WritePortBit(LPC_GPIO, PLED5, LED5 , 1);
			Chip_GPIO_WritePortBit(LPC_GPIO, PLED6, LED6 , 0);
			Chip_GPIO_WritePortBit(LPC_GPIO, PLED7, LED7 , 1);
			i=0;
		}
		else
		{

			Chip_GPIO_WritePortBit(LPC_GPIO, PLED0, LED0 , 1);
			Chip_GPIO_WritePortBit(LPC_GPIO, PLED1, LED1 , 0);
			Chip_GPIO_WritePortBit(LPC_GPIO, PLED2, LED2 , 1);
			Chip_GPIO_WritePortBit(LPC_GPIO, PLED3, LED3 , 0);
			Chip_GPIO_WritePortBit(LPC_GPIO, PLED4, LED4 , 1);
			//Chip_GPIO_WritePortBit(LPC_GPIO, PLED5, LED5 , 0);
			Chip_GPIO_WritePortBit(LPC_GPIO, PLED6, LED6 , 1);
			Chip_GPIO_WritePortBit(LPC_GPIO, PLED7, LED7 , 0);
			i=1;
		}
		vTaskDelay(200 / portTICK_RATE_MS);
	}
}

/*==================[external functions definition]==========================*/

int main(void)
{
	Chip_GPIO_WriteDirBit(LPC_GPIO, PLED0, LED0 , SALIDA);	//Configuro el pin como salida
	Chip_GPIO_WriteDirBit(LPC_GPIO, PLED1, LED1 , SALIDA);	//Configuro el pin como salida
	Chip_GPIO_WriteDirBit(LPC_GPIO, PLED2, LED2 , SALIDA);	//Configuro el pin como salida
	Chip_GPIO_WriteDirBit(LPC_GPIO, PLED3, LED3 , SALIDA);	//Configuro el pin como salida
	Chip_GPIO_WriteDirBit(LPC_GPIO, PLED4, LED4 , SALIDA);	//Configuro el pin como salida
	//Chip_GPIO_WriteDirBit(LPC_GPIO, PLED5, LED5 , SALIDA);	//Configuro el pin como salida
	Chip_GPIO_WriteDirBit(LPC_GPIO, PLED6, LED6 , SALIDA);	//Configuro el pin como salida
	Chip_GPIO_WriteDirBit(LPC_GPIO, PLED7, LED7 , SALIDA);	//Configuro el pin como salida


	initHardware();

	xTaskCreate(task, (signed const char *)"task1", 1024, (void *)str1, tskIDLE_PRIORITY+1, 0);

	xTaskCreate(task, (signed const char *)"task2", 1024, (void *)str2, tskIDLE_PRIORITY+1, 0);

	xTaskCreate(taskLED, (signed const char *)"taskLED", 1024, 0, tskIDLE_PRIORITY+1, 0);

	sem = xSemaphoreCreateMutex();

	vTaskStartScheduler();

	while(1);
}

/*==================[end of file]============================================*/
