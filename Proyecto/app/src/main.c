
/*==================[inclusions]=============================================*/


#include "main.h"


/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/


/*==================[internal functions declaration]=========================*/

static void initHardware(void);

/*==================[internal data definition]===============================*/

const char str1[] = ">111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111<\r\n";
const char str2[] = ">222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222<\r\n";

static xSemaphoreHandle sem;
static xTaskHandle stup_motor0_task,stup_motor1_task,stup_motor2_task,stup_motor3_task;

/*==================[external data definition]===============================*/

//GLOBALES
//-----------------------------------------------------------------------------------------------

uint32_t Match_Cnt=0, Cycle=0, AntiRebo=REBOTE_;
/*
uint32_t PORT_Qa[3]={PORT_Q1,PORT_Q3,PORT_Q5},
PIN_Qa[3]={PIN_Q1,PIN_Q3,PIN_Q5},
PORT_Qb[3]={PORT_Q0,PORT_Q2,PORT_Q4},
PIN_Qb[3]={PIN_Q0,PIN_Q2,PIN_Q4},
PORT_Z[3]={PORT_Z1, PORT_Z2, PORT_Z3},
PIN_Z[3]={PIN_Z1, PIN_Z2, PIN_Z3};
*/

uint32_t PORT_Qa_[4][3]={{PORT_Q1,PORT_Q3,PORT_Q5},
		{0,0,0},
		{0,0,0},
		{0,0,0}
};
uint32_t PIN_Qa_[4][3]={{PIN_Q1,PIN_Q3,PIN_Q5},
		{0,0,0},
		{0,0,0},
		{0,0,0}
};
uint32_t PORT_Qb_[4][3]={{PORT_Q0,PORT_Q2,PORT_Q4},
		{0,0,0},
		{0,0,0},
		{0,0,0}
};
uint32_t PIN_Qb_[4][3]={{PIN_Q0,PIN_Q2,PIN_Q4},
		{0,0,0},
		{0,0,0},
		{0,0,0}
};
uint32_t PORT_Z_[4][3]={{PORT_Z1, PORT_Z2, PORT_Z3},
		{0, 0, 0},
		{0, 0, 0},
		{0, 0, 0}
};
uint32_t PIN_Z_[4][3]={{PIN_Z1, PIN_Z2, PIN_Z3},
		{0, 0, 0},
		{0, 0, 0},
		{0, 0, 0},
};

struct StartParams_s  start= { 150,   {300, 100},   {60, 150} };	//Cantidad de pasos, período inicial y final, pwm inicial y final para startup


volatile uint8_t CruceZero[4][3]={{0,0,0},{0,0,0},{0,0,0},{0,0,0}},
		CruceZero0[4][3]={{0,0,0},{0,0,0},{0,0,0},{0,0,0}};
												//-----> 50*20microseg = 1mSeg
long StepPeriod[4];     			// step duration, us
volatile uint16_t DutyCycle[4], DutyCycle0[4]; 	// fraction of period hi pins are high

volatile int StepID[4]={0,0,0,0};  		// commutation step counter, 0..5
uint8_t Count=0;  					// no full commutation cycles completed

uint8_t mot_1 = 1;


/*==================[internal functions definition]==========================*/

static void initHardware(void)
{
    SystemCoreClockUpdate();

    Board_Init();

	Stop_and_Default(0);	//Condiciones iniciales
	InitGPIO();			//Llamo función para inicializar GPIO
	InitPWM();			//Función inicialización modulo PWM

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
//	int i = 1;
	while(1)
	{
/*		if (i==1)
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
*/	}
}


static void Motor(void * p)
{
	while(1)
	{
		NextPWM(0);
		vTaskDelay(StepPeriod[0] / portTICK_RATE_MS);
	}
}

static void StartUpMotor(void* p)
{
	uint8_t *motor_number=(uint8_t*)p;
	Start_Up_Brushless(*motor_number);
/*
	switch (*motor_number)
	{
	case 0:
		vTaskSuspend(stup_motor0_task);
		break;
	case 1:
		vTaskSuspend(stup_motor1_task);
		break;
	case 2:
		vTaskSuspend(stup_motor2_task);
		break;
	case 3:
		vTaskSuspend(stup_motor3_task);
		break;
	default:
		break;
	}
	*/

	vTaskSuspend(NULL);
}

/*==================[external functions definition]==========================*/

int main(void)
{

	unsigned int motor[4]={0,1,2,3};
	/*

	Chip_GPIO_WriteDirBit(LPC_GPIO, PLED0, LED0 , SALIDA);	//Configuro el pin como salida
	Chip_GPIO_WriteDirBit(LPC_GPIO, PLED1, LED1 , SALIDA);	//Configuro el pin como salida
	Chip_GPIO_WriteDirBit(LPC_GPIO, PLED2, LED2 , SALIDA);	//Configuro el pin como salida
	Chip_GPIO_WriteDirBit(LPC_GPIO, PLED3, LED3 , SALIDA);	//Configuro el pin como salida
	Chip_GPIO_WriteDirBit(LPC_GPIO, PLED4, LED4 , SALIDA);	//Configuro el pin como salida
	//Chip_GPIO_WriteDirBit(LPC_GPIO, PLED5, LED5 , SALIDA);	//Configuro el pin como salida
	Chip_GPIO_WriteDirBit(LPC_GPIO, PLED6, LED6 , SALIDA);	//Configuro el pin como salida
	Chip_GPIO_WriteDirBit(LPC_GPIO, PLED7, LED7 , SALIDA);	//Configuro el pin como salida

	 */
	initHardware();


	xTaskCreate(task, (signed const char *)"task1", 1024, (void *)str1, tskIDLE_PRIORITY+1, 0);

	xTaskCreate(task, (signed const char *)"task2", 1024, (void *)str2, tskIDLE_PRIORITY+1, 0);

	xTaskCreate(taskLED, (signed const char *)"taskLED", 1024, 0, tskIDLE_PRIORITY+1, 0);

	xTaskCreate(StartUpMotor,(signed const char*)"StartUp Motor 0",1024,(void*)motor[0],tskIDLE_PRIORITY+2,stup_motor0_task);

	xTaskCreate(Motor, (signed const char *)"Motor0",1024,(void*)motor[0],tskIDLE_PRIORITY+1,0);

	/*
	xTaskCreate(StartUpMotor,(signed const char*)"StartUp Motor 1",1024,(void*)motor[1],tskIDLE_PRIORITY+2,stup_motor1_task);

	xTaskCreate(Motor, (signed const char *)"Motor1",1024,(void*)motor[1],tskIDLE_PRIORITY+1,0);

	xTaskCreate(StartUpMotor,(signed const char*)"StartUp Motor 2",1024,(void*)motor[2],tskIDLE_PRIORITY+2,stup_motor2_task);

	xTaskCreate(Motor, (signed const char *)"Motor2",1024,(void*)motor[2],tskIDLE_PRIORITY+1,0);

	xTaskCreate(StartUpMotor,(signed const char*)"StartUp Motor 3",1024,(void*)motor[3],tskIDLE_PRIORITY+2,stup_motor3_task);

	xTaskCreate(Motor, (signed const char *)"Motor3",1024,(void*)motor[3],tskIDLE_PRIORITY+1,0);
	*/

	sem = xSemaphoreCreateMutex();

	vTaskStartScheduler();

	while(1);

}

/*==================[end of file]============================================*/
