
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


volatile uint32_t CruceZero[4][3]={{0,0,0},{0,0,0},{0,0,0},{0,0,0}},
		CruceZero0[4][3]={{0,0,0},{0,0,0},{0,0,0},{0,0,0}};
												//-----> 50*20microseg = 1mSeg
uint32_t StepPeriod[4]={0,0,0,0};     			// step duration, us
volatile uint32_t DutyCycle[4]={0,0,0,0}, DutyCycle0[4]={0,0,0,0}; 	// fraction of period hi pins are high

volatile uint32_t StepID[4]={0,0,0,0};  		// commutation step counter, 0..5
volatile uint32_t Count[4]={0,0,0,0};  					// no full commutation cycles completed

uint32_t motor[4]={0,1,2,3},PWM_number[4]={3,4,5,6};			//motor: cada uno de los motores
																//PWM_number: el pwm para cada uno
																//sel_motor: elijo cual motor voy a ver


xSemaphoreHandle sem_motor[4],sem_startup[4],sem_cruces;

uint32_t estado_motorstartup[4]={0,0,0,0};

volatile uint32_t Conmutar[4]={0,0,0,0},End[4]={0,0,0,0};


uint32_t t=1, dr=0, dPwr=0;
uint32_t Suspender_Task=0;



/*==================[internal functions definition]==========================*/

static void initHardware(void)
{
	Chip_SetupXtalClocking();
	Chip_SYSCTL_SetFLASHAccess(FLASHTIM_120MHZ_CPU);
    SystemCoreClockUpdate();
    SysTick_Config(SystemCoreClock/1000);





//    Board_Init();



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


    P2_6ER = 1;    P2_7ER = 1;    P2_8ER = 1;

    P2_6EF = 1;    P2_7EF = 1;    P2_8EF = 1;



    P0_15ER = 1;    P0_16ER = 1;    P2_9ER = 1;

    P0_15EF = 1;    P0_16EF = 1;    P2_9EF = 1;

//    NVIC_SetPriority(EINT3_IRQn,1);			//Le pongo la mayor prioridad a la interrupcion
    NVIC_EnableIRQ(EINT3_IRQn);

}

/*==================[external functions definition]==========================*/

int main(void)
{

	uint32_t Fin_StartUp = 0, estado = 0,i;


	initHardware();


	while(1)
	{
/*		switch(estado)
		{
			case 0:
				Fin_StartUp = Start_Up_Brushless(3);
				if(Fin_StartUp)
				{
					estado = 1;
					Fin_StartUp = 0;
				}
				break;
			case 1:
				if(Conmutar[3])
				{
*/					NextPWM(3);
					for(i=0;i<40000;i++);
//					Conmutar[3] = 0;
//				}


//		}
	}

}


void EINT3_IRQHandler(void)
{

	 if((P2_6REI || P2_6FEI) || (P2_7REI || P2_7FEI) || (P2_8REI || P2_8FEI))
	 {
		 P2_6CI=1;P2_7CI=1;P2_8CI=1;
		 Conmutar[3]=1;
	 }

	 if((P0_15REI || P0_15FEI) || (P0_16REI || P0_16FEI) || (P2_9REI || P2_9FEI))
	 {
		 P0_15CI=1;P0_16CI=1;P2_9CI=1;
		 Conmutar[2]=1;
	 }
}

/*==================[end of file]============================================*/
