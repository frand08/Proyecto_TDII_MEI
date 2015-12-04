
/*==================[inclusions]=============================================*/


#include "main.h"


/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/


/*==================[internal functions declaration]=========================*/

static void initHardware(void);

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

//GLOBALES
//-----------------------------------------------------------------------------------------------

uint32_t  Cycle[4]={0,0,0,0}, AntiRebo=REBOTE_;

volatile uint32_t Match_Cnt[4]={0,0,0,0};

uint32_t PORT_Qb_[4][3]={{PORT_Q01,PORT_Q03,PORT_Q05},
		{PORT_Q11,PORT_Q13,PORT_Q15},
		{PORT_Q21,PORT_Q23,PORT_Q25},
		{PORT_Q31,PORT_Q33,PORT_Q35}
};
uint32_t PIN_Qb_[4][3]={{PIN_Q01,PIN_Q03,PIN_Q05},
		{PIN_Q11,PIN_Q13,PIN_Q15},
		{PIN_Q21,PIN_Q23,PIN_Q25},
		{PIN_Q31,PIN_Q33,PIN_Q35}
};
uint32_t PORT_Qa_[4][3]={{PORT_Q00,PORT_Q02,PORT_Q04},
		{PORT_Q10,PORT_Q12,PORT_Q14},
		{PORT_Q20,PORT_Q22,PORT_Q24},
		{PORT_Q30,PORT_Q32,PORT_Q34}
};
uint32_t PIN_Qa_[4][3]={{PIN_Q00,PIN_Q02,PIN_Q04},
		{PIN_Q10,PIN_Q12,PIN_Q14},
		{PIN_Q20,PIN_Q22,PIN_Q24},
		{PIN_Q30,PIN_Q32,PIN_Q34}
};
uint32_t PORT_Z_[4][3]={{PORT_Z01, PORT_Z02, PORT_Z03},
		{PORT_Z11, PORT_Z12, PORT_Z13},
		{PORT_Z21, PORT_Z22, PORT_Z23},
		{PORT_Z31, PORT_Z32, PORT_Z33}
};
uint32_t PIN_Z_[4][3]={{PIN_Z01, PIN_Z02, PIN_Z03},
		{PIN_Z11, PIN_Z12, PIN_Z13},
		{PIN_Z21, PIN_Z22, PIN_Z23},
		{PIN_Z31, PIN_Z32, PIN_Z33}
};

struct StartParams_s  start= { 150,   {180, 30},   {20, 320} };	//Cantidad de pasos, período inicial y final, pwm inicial y final para startup


volatile uint8_t CruceZero[4][3]={{0,0,0},{0,0,0},{0,0,0},{0,0,0}},
		CruceZero0[4][3]={{0,0,0},{0,0,0},{0,0,0},{0,0,0}};
												//-----> 50*20microseg = 1mSeg
uint32_t StepPeriod[4]={0,0,0,0};     			// step duration, us
volatile uint16_t DutyCycle[4]={0,0,0,0}, DutyCycle0[4]={0,0,0,0}; 	// fraction of period hi pins are high

volatile uint32_t StepID[4]={0,0,0,0};  		// commutation step counter, 0..5
volatile uint32_t Count[4]={0,0,0,0};  					// no full commutation cycles completed

unsigned int motor[4]={0,1,2,3},PWM_number[4]={3,4,5,6};	//motor: cada uno de los motores
																//PWM_number: el pwm para cada uno
																//sel_motor: elijo cual motor voy a ver


xSemaphoreHandle sem_motor[4],sem_startup[4],sem_cruces;

uint32_t estado_motorstartup[4]={0,0,0,0};

/*==================[internal functions definition]==========================*/

static void initHardware(void)
{
	Chip_SetupXtalClocking();
	Chip_SYSCTL_SetFLASHAccess(FLASHTIM_100MHZ_CPU);
    SystemCoreClockUpdate();
    SysTick_Config(SystemCoreClock/1000);

    Board_Init();


	InitPWM_motores(0);			//Función inicialización modulo PWM
	InitPWM_motores(1);			//Función inicialización modulo PWM
	InitPWM_motores(2);			//Función inicialización modulo PWM
	InitPWM_motores(3);			//Función inicialización modulo PWM
	InitPWM0();
	InitGPIO(0);			//Llamo función para inicializar GPIO
	InitGPIO(1);			//Llamo función para inicializar GPIO
	InitGPIO(2);			//Llamo función para inicializar GPIO
	InitGPIO(3);			//Llamo función para inicializar GPIO
	Stop_and_Default(0);	//Condiciones iniciales
	Stop_and_Default(1);	//Condiciones iniciales
	Stop_and_Default(2);	//Condiciones iniciales
	Stop_and_Default(3);	//Condiciones iniciales


}


static void Motor(void * p)
{
	uint8_t *motor_number=(uint8_t*)p;
	while(1)

	{
		xSemaphoreTake(sem_cruces,portMAX_DELAY);
		CruceZero[*motor_number][0] = Chip_GPIO_ReadPortBit(LPC_GPIO, PORT_Z_[*motor_number][0], PIN_Z_[*motor_number][0]);
		CruceZero[*motor_number][1] = Chip_GPIO_ReadPortBit(LPC_GPIO, PORT_Z_[*motor_number][1], PIN_Z_[*motor_number][1]);
		CruceZero[*motor_number][2] = Chip_GPIO_ReadPortBit(LPC_GPIO, PORT_Z_[*motor_number][2], PIN_Z_[*motor_number][2]);

		if((CruceZero0[*motor_number][0] != CruceZero[*motor_number][0]) || (CruceZero0[*motor_number][1] != CruceZero[*motor_number][1]) || (CruceZero0[*motor_number][2] != CruceZero[*motor_number][2]))
			NextPWM(*motor_number);
		//		vTaskDelay(10/portTICK_RATE_MS);
		xSemaphoreGive(sem_cruces);
	}
}

static void StartUpMotor(void* p)
{
	uint8_t *motor_number=(uint8_t*)p;
	static uint8_t Task_suspend=0;
	while(1)
	{
//		xSemaphoreTake(sem_startup[*motor_number],portMAX_DELAY);
		Task_suspend=Start_Up_Brushless(*motor_number);
		if(Task_suspend)
		{
//			xSemaphoreGive(sem_startup[*motor_number]);
			vTaskSuspend(NULL);
		}


//		xSemaphoreGive(sem_startup[*motor_number]);
	}
}
/*
static void Conmutation(void *p)
{
	uint8_t *zero_motor=(uint8_t*)p;
	while(1)
	{
		xSemaphoreTake(sem_startup[*zero_motor],portMAX_DELAY);
		CruceZero[*zero_motor][0] = Chip_GPIO_ReadPortBit(LPC_GPIO, PORT_Z_[*zero_motor][0], PIN_Z_[*zero_motor][0]);
		CruceZero[*zero_motor][1] = Chip_GPIO_ReadPortBit(LPC_GPIO, PORT_Z_[*zero_motor][1], PIN_Z_[*zero_motor][1]);
		CruceZero[*zero_motor][2] = Chip_GPIO_ReadPortBit(LPC_GPIO, PORT_Z_[*zero_motor][2], PIN_Z_[*zero_motor][2]);

		if((CruceZero0[*zero_motor][0] != CruceZero[*zero_motor][0]) || (CruceZero0[*zero_motor][1] != CruceZero[*zero_motor][1]) || (CruceZero0[*zero_motor][2] != CruceZero[*zero_motor][2]))
			xSemaphoreGive(sem_motor[*zero_motor]);

		xSemaphoreGive(sem_startup[*zero_motor]);
	}

}
*/
/*==================[external functions definition]==========================*/

int main(void)
{


	initHardware();

/*
	xTaskCreate(StartUpMotor,(signed const char*)"StartUp Motor 0",128,(void*)&motor[0],tskIDLE_PRIORITY+2,0);

	xTaskCreate(Motor, (signed const char *)"Motor 0",128,(void*)&motor[0],tskIDLE_PRIORITY+1,0);

//	xTaskCreate(Conmutation,(signed const char *)"Conmutacion 0",128,(void*)&motor[0],tskIDLE_PRIORITY+1,0);
*/



	xTaskCreate(StartUpMotor,(signed const char*)"StartUp Motor 1",128,(void*)&motor[1],tskIDLE_PRIORITY+2,0);

	xTaskCreate(Motor, (signed const char *)"Motor 1",128,(void*)&motor[1],tskIDLE_PRIORITY+1,0);

//	xTaskCreate(Conmutation,(signed const char *)"Conmutacion 1",128,(void*)&motor[1],tskIDLE_PRIORITY+1,0);


/*
	xTaskCreate(StartUpMotor,(signed const char*)"StartUp Motor 2",128,(void*)&motor[2],tskIDLE_PRIORITY+2,0);

	xTaskCreate(Motor, (signed const char *)"Motor 2",128,(void*)&motor[2],tskIDLE_PRIORITY+1,0);

	xTaskCreate(Conmutation,(signed const char *)"Conmutacion 2",128,(void*)&motor[2],tskIDLE_PRIORITY+1,0);



	xTaskCreate(StartUpMotor,(signed const char*)"StartUp Motor 3",128,(void*)&motor[3],tskIDLE_PRIORITY+2,0);

	xTaskCreate(Motor, (signed const char *)"Motor 3",128,(void*)&motor[3],tskIDLE_PRIORITY+1,0);

	xTaskCreate(Conmutation,(signed const char *)"Conmutacion 3",128,(void*)&motor[3],tskIDLE_PRIORITY+1,0);
*/

/*
	sem_motor[0] = xSemaphoreCreateMutex();
	sem_motor[1] = xSemaphoreCreateMutex();
	sem_motor[2] = xSemaphoreCreateMutex();
	sem_motor[3] = xSemaphoreCreateMutex();

	sem_startup[0] = xSemaphoreCreateMutex();
	sem_startup[1] = xSemaphoreCreateMutex();
	sem_startup[2] = xSemaphoreCreateMutex();
	sem_startup[3] = xSemaphoreCreateMutex();
*/
	sem_cruces = xSemaphoreCreateMutex();
vTaskStartScheduler();

	while(1);

}

/*==================[end of file]============================================*/
