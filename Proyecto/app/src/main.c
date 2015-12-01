
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

uint32_t  Cycle=0, AntiRebo=REBOTE_;

volatile uint32_t Match_Cnt=0;

uint32_t PORT_Qa_[4][3]={{PORT_Q01,PORT_Q03,PORT_Q05},
		{PORT_Q11,PORT_Q13,PORT_Q15},
		{PORT_Q21,PORT_Q23,PORT_Q25},
		{PORT_Q31,PORT_Q33,PORT_Q35}
};
uint32_t PIN_Qa_[4][3]={{PIN_Q01,PIN_Q03,PIN_Q05},
		{PIN_Q11,PIN_Q13,PIN_Q15},
		{PIN_Q21,PIN_Q23,PIN_Q25},
		{PIN_Q31,PIN_Q33,PIN_Q35}
};
uint32_t PORT_Qb_[4][3]={{PORT_Q00,PORT_Q02,PORT_Q04},
		{PORT_Q10,PORT_Q12,PORT_Q14},
		{PORT_Q20,PORT_Q22,PORT_Q24},
		{PORT_Q30,PORT_Q32,PORT_Q34}
};
uint32_t PIN_Qb_[4][3]={{PIN_Q00,PIN_Q02,PIN_Q04},
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

struct StartParams_s  start= { 150,   {300, 100},   {60, 150} };	//Cantidad de pasos, período inicial y final, pwm inicial y final para startup


volatile uint8_t CruceZero[4][3]={{0,0,0},{0,0,0},{0,0,0},{0,0,0}},
		CruceZero0[4][3]={{0,0,0},{0,0,0},{0,0,0},{0,0,0}};
												//-----> 50*20microseg = 1mSeg
long StepPeriod[4];     			// step duration, us
volatile uint16_t DutyCycle[4], DutyCycle0[4]; 	// fraction of period hi pins are high

volatile int StepID[4]={0,0,0,0};  		// commutation step counter, 0..5
uint8_t Count=0;  					// no full commutation cycles completed

unsigned int motor[4]={0,1,2,3},PWM_number[4]={3,4,5,6},sel_motor=1;	//motor: cada uno de los motores
																//PWM_number: el pwm para cada uno
																//sel_motor: elijo cual motor voy a ver


/*==================[internal functions definition]==========================*/

static void initHardware(void)
{
    SystemCoreClockUpdate();

    //Board_Init();


	InitPWM(motor[sel_motor]);			//Función inicialización modulo PWM
	InitGPIO(motor[sel_motor]);			//Llamo función para inicializar GPIO
	Stop_and_Default(motor[sel_motor]);	//Condiciones iniciales


}


static void Motor(void * p)
{
	uint8_t *motor_number=(uint8_t*)p;
	while(1)
	{
		NextPWM(motor[*motor_number]);
		vTaskDelay(100 / portTICK_RATE_MS);
	}
}

static void StartUpMotor(void* p)
{
	uint8_t *motor_number=(uint8_t*)p;
	Start_Up_Brushless(motor[*motor_number]);

	vTaskSuspend(NULL);
}


/*==================[external functions definition]==========================*/

int main(void)
{


	initHardware();

	xTaskCreate(StartUpMotor,(signed const char*)"StartUp Motor",1024,(void*)motor[sel_motor],tskIDLE_PRIORITY+2,0);

	xTaskCreate(Motor, (signed const char *)"Motor",1024,(void*)motor[sel_motor],tskIDLE_PRIORITY+1,0);

	vTaskStartScheduler();

	while(1);

}

/*==================[end of file]============================================*/
