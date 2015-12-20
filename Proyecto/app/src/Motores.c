#include "main.h"

/*==========================[GLOBALES]==========================*/
//-----------------------------------------------------------------------------------------------
extern uint32_t Cycle[4], AntiRebo;

extern volatile uint32_t Match_Cnt[4];

extern uint32_t PORT_Qa_[4][3],PIN_Qa_[4][3],PORT_Qb_[4][3],PIN_Qb_[4][3],PORT_Z_[4][3],PIN_Z_[4][3];

extern volatile uint32_t CruceZero[4][3], CruceZero0[4][3];


extern struct StartParams_s start;	//Cantidad de pasos, período inicial y final, pwm inicial y final para startup
												//-----> 50*20microseg = 1mSeg
extern uint32_t StepPeriod[4];     			// step duration, us
extern volatile uint32_t DutyCycle[4], DutyCycle0[4]; 	// fraction of period hi pins are high

extern volatile uint32_t StepID[4];  		// commutation step counter, 0..5
extern volatile uint32_t Count[4];  					// no full commutation cycles completed



extern uint32_t motor[4],PWM_number[4],sel_motor;

extern uint32_t estado_motorstartup[4];

void InitPWM0(void)
{
	//Initialize PWM peipheral, timer mode
	//-----------------------------------------------------------------------------------------------
	Chip_PWM_PrescaleSet(LPC_PWM1, 0);		//Valor preescalar=100 (divisor de clock)

	//Set match value for PWM match channel0 (frecuency)
	//-----------------------------------------------------------------------------------------------
	Chip_PWM_SetMatch(LPC_PWM1, 0, 1000);		//Establezco el valor en clock del período (canal 0) 25kHz
	Chip_PWM_MatchEnableInt(LPC_PWM1, 0);		//Habilito interrupción
	Chip_PWM_ResetOnMatchEnable(LPC_PWM1, 0);	//Reset auto
	Chip_PWM_StopOnMatchDisable(LPC_PWM1, 0);	//No stop


	//Reset and Start Counter
	//-----------------------------------------------------------------------------------------------
	Chip_PWM_Reset(LPC_PWM1);

	//Start PWM
	//-----------------------------------------------------------------------------------------------
	Chip_PWM_Enable(LPC_PWM1);

	//Enable PWM interrupt
	//-----------------------------------------------------------------------------------------------
	NVIC_EnableIRQ(PWM1_IRQn);
}

void InitPWM_motores(uint32_t num_motor)
{
	//Configure PWM channel edge (single) CHANNEL channel={3,4,5,6} (depende el caso)
	//-----------------------------------------------------------------------------------------------
	Chip_PWM_SetControlMode(LPC_PWM1, PWM_number[num_motor], PWM_SINGLE_EDGE_CONTROL_MODE, PWM_OUT_DISABLED);

	//Configure match value for channel channel
	//-----------------------------------------------------------------------------------------------
	Chip_PWM_SetMatch(LPC_PWM1, PWM_number[num_motor], 20);		//Establezco el valor en clock del Duty (canal PWM_num) / 20 -> 2%Duty
	Chip_PWM_MatchEnableInt(LPC_PWM1, PWM_number[num_motor]);		//Habilito interrupción
	Chip_PWM_ResetOnMatchDisable(LPC_PWM1, PWM_number[num_motor]);	//No reset auto
	Chip_PWM_StopOnMatchDisable(LPC_PWM1, PWM_number[num_motor]);	//No stop
	Chip_PWM_LatchEnable(LPC_PWM1, PWM_number[num_motor], PWM_OUT_ENABLED);
	Chip_PWM_Reset(LPC_PWM1);
}

void InitGPIO(uint32_t num_motor)
{
	//CONFIGURAR SALIDAS
	//-----------------------------------------------------------------------------------------------
		Chip_GPIO_WriteDirBit(LPC_GPIO, PORT_Qa_[num_motor][0], PIN_Qa_[num_motor][0] , SALIDA);	//Configuro el pin como salida
		Chip_GPIO_WriteDirBit(LPC_GPIO, PORT_Qa_[num_motor][1], PIN_Qa_[num_motor][1] , SALIDA);	//Configuro el pin como salida
		Chip_GPIO_WriteDirBit(LPC_GPIO, PORT_Qa_[num_motor][2], PIN_Qa_[num_motor][2] , SALIDA);	//Configuro el pin como salida
		Chip_GPIO_WriteDirBit(LPC_GPIO, PORT_Qb_[num_motor][0], PIN_Qb_[num_motor][0] , SALIDA);	//Configuro el pin como salida
		Chip_GPIO_WriteDirBit(LPC_GPIO, PORT_Qb_[num_motor][1], PIN_Qb_[num_motor][1] , SALIDA);	//Configuro el pin como salida
		Chip_GPIO_WriteDirBit(LPC_GPIO, PORT_Qb_[num_motor][2], PIN_Qb_[num_motor][2] , SALIDA);	//Configuro el pin como salida
		//APAGAR TRANSISTORES
		//-----------------------------------------------------------------------------------------------
		Chip_GPIO_WritePortBit(LPC_GPIO, PORT_Qa_[num_motor][0], PIN_Qa_[num_motor][0], 0);		//PMOS
		Chip_GPIO_WritePortBit(LPC_GPIO, PORT_Qa_[num_motor][1], PIN_Qa_[num_motor][1], 0);		//PMOS
		Chip_GPIO_WritePortBit(LPC_GPIO, PORT_Qa_[num_motor][2], PIN_Qa_[num_motor][2], 0);		//PMOS
		Chip_GPIO_WritePortBit(LPC_GPIO, PORT_Qb_[num_motor][0], PIN_Qb_[num_motor][0], 1);		//NMOS
		Chip_GPIO_WritePortBit(LPC_GPIO, PORT_Qb_[num_motor][1], PIN_Qb_[num_motor][1], 1);		//NMOS
		Chip_GPIO_WritePortBit(LPC_GPIO, PORT_Qb_[num_motor][2], PIN_Qb_[num_motor][2], 1);		//NMOS
		//CONFIGURAR ENTRADAS
		//-----------------------------------------------------------------------------------------------
	/*=============[TODAVIA NO ESTA IMPLEMENTADO]========================*/

		Chip_GPIO_WriteDirBit(LPC_GPIO, PORT_Z_[num_motor][0], PIN_Z_[num_motor][0], ENTRADA);
		Chip_GPIO_WriteDirBit(LPC_GPIO, PORT_Z_[num_motor][1], PIN_Z_[num_motor][1], ENTRADA);
		Chip_GPIO_WriteDirBit(LPC_GPIO, PORT_Z_[num_motor][2], PIN_Z_[num_motor][2], ENTRADA);

	/*===================================================================*/

}

void Stop_and_Default(uint32_t num_motor)
{
	//Set Period and PWM
	//-----------------------------------------------------------------------------------------------
	StepPeriod[num_motor] = start.periodRange[0];
	DutyCycle[num_motor] = start.powerRange[0];
	DutyCycle0[num_motor] = DutyCycle[num_motor];
	//Shut Down All
	//-----------------------------------------------------------------------------------------------
	Chip_GPIO_WritePortBit(LPC_GPIO, PORT_Qa_[num_motor][0], PIN_Qa_[num_motor][0], 0);		//PMOS
	Chip_GPIO_WritePortBit(LPC_GPIO, PORT_Qa_[num_motor][1], PIN_Qa_[num_motor][1], 0);		//PMOS
	Chip_GPIO_WritePortBit(LPC_GPIO, PORT_Qa_[num_motor][2], PIN_Qa_[num_motor][2], 0);		//PMOS
	Chip_GPIO_WritePortBit(LPC_GPIO, PORT_Qb_[num_motor][0], PIN_Qb_[num_motor][0], 1);		//NMOS
	Chip_GPIO_WritePortBit(LPC_GPIO, PORT_Qb_[num_motor][1], PIN_Qb_[num_motor][1], 1);		//NMOS
	Chip_GPIO_WritePortBit(LPC_GPIO, PORT_Qb_[num_motor][2], PIN_Qb_[num_motor][2], 1);		//NMOS
}

uint32_t Start_Up_Brushless(uint32_t num_motor)
{
	static uint32_t t=1, dr=0, dPwr=0;
	static uint32_t Suspender_Task=0;

	//Drive at const rate for a few cycles to make sure rotor is synched.
	//-----------------------------------------------------------------------------------------------

	switch(estado_motorstartup[num_motor])
	{
		case 0:
			NextPWM(num_motor);				//Siguiente conmutación
			Count[num_motor]=0;				//Inicio el conteo para el arranque
			estado_motorstartup[num_motor] = 1;
			break;

		case 1:
/*			if(Count[num_motor]<10)
			{
				if(Match_Cnt[num_motor]>=StepPeriod[num_motor])		//Delay hasta la siguiente conmutación
					NextPWM(num_motor);								//Siguiente conmutación
			}
			else
			{*/
				dPwr = (start.powerRange[1] - start.powerRange[0])/start.duration; 	//Diferencia de Duty
				dr = (start.periodRange[0] -start.periodRange[1])/start.duration;

				t = 0;

				estado_motorstartup[num_motor] = 2;
//			}
			break;

		case 2:
			if(StepPeriod[num_motor] > (uint32_t)start.periodRange[1])
			{
				if(Match_Cnt[num_motor] >= StepPeriod[num_motor])
				{
					NextPWM(num_motor);
					DutyCycle[num_motor] = start.powerRange[0] + t * dPwr;//Incremento Duty de manera lineal desde powerRange0 a powerRange1
					StepPeriod[num_motor] =start.periodRange[0] - t * dr;	//Disminuye período entre conmutaciones de manera exponencial decreciente
					t++;																					//desde periodRange0 hasta periodRange1
				}
			}
			else
			{
				DutyCycle[num_motor] = 150;		// (150/1000)-> 15% Duty

				Chip_PWM_SetMatch(LPC_PWM1, PWM_number[num_motor], DutyCycle[num_motor]);
				//Chip_PWM_Reset(LPC_PWM1);
				Suspender_Task = 1;
				estado_motorstartup[num_motor] = 0;
			}
			break;

		default:
			DutyCycle[num_motor] = 150;		// (150/1000)-> 15% Duty

			Chip_PWM_SetMatch(LPC_PWM1, PWM_number[num_motor], DutyCycle[num_motor]);
			//Chip_PWM_Reset(LPC_PWM1);
			Suspender_Task = 1;
			estado_motorstartup[num_motor] = 0;
			break;
	}

	/*

	Count[num_motor] = 0;
	NextPWM(num_motor);	//Siguiente conmutación
	while (Count[num_motor] < 10)				//Primeras 3 conmutaciones a período inicial (lentas) por sincronismo
	{
		while (Match_Cnt[num_motor] < StepPeriod[num_motor]);	//Delay hasta sig conmutación
		NextPWM(num_motor);						//Siguiente conmutación
	}
	//Set variables para ecuaciones de arranque
	//-----------------------------------------------------------------------------------------------
	dPwr = (start.powerRange[1] - start.powerRange[0])/start.duration; 	//Diferencia de Duty
	dr = (start.periodRange[0] -start.periodRange[1])/start.duration;

	t = 0;
	//Arranque del Motor	(Clock:25MHz, Divisor pwm:1, Ciclos pwm:1000, -> [1 Match_Cnt = 40 MicroSeg]
	//-----------------------------------------------------------------------------------------------
	while (StepPeriod[num_motor] > (uint32_t)start.periodRange[num_motor])
	{
		while (Match_Cnt[num_motor] < StepPeriod[num_motor]);//Delay hasta la siguiente conmutación (bloqueante solo durante arranque)
		NextPWM(num_motor);						//Siguiente conmutación

		DutyCycle[num_motor] = start.powerRange[0] + t * dPwr;//Incremento Duty de manera lineal desde powerRange0 a powerRange1
		StepPeriod[num_motor] =start.periodRange[0] - t * dr;	//Disminuye período entre conmutaciones de manera exponencial decreciente
		t++;																					//desde periodRange0 hasta periodRange1
	}

	DutyCycle[num_motor] = 150;		// (150/1000)-> 15% Duty

	Chip_PWM_SetMatch(LPC_PWM1, PWM_number[num_motor], DutyCycle[num_motor]);
	Chip_PWM_Reset(LPC_PWM1);

	Suspender_Task = 1;
	 */
	return Suspender_Task;
}

void NextPWM(uint32_t num_motor)
{
	//Actualizar DutyCycle
	//-----------------------------------------------------------------------------------------------

	if (DutyCycle[num_motor] != DutyCycle0[num_motor])
	{
		Chip_PWM_SetMatch(LPC_PWM1, PWM_number[num_motor], DutyCycle[num_motor]);
		//Chip_PWM_Reset(LPC_PWM1);
		Chip_PWM_LatchEnable(LPC_PWM1, PWM_number[num_motor], PWM_OUT_ENABLED);
		DutyCycle0[num_motor] = DutyCycle[num_motor];
	}

	//Conmutaciones MOSfet
	//-----------------------------------------------------------------------------------------------
	switch (StepID[num_motor])
	{
	case 0:
		Chip_GPIO_WritePortBit(LPC_GPIO, PORT_Qb_[num_motor][2], PIN_Qb_[num_motor][2], 1);	//Apago Q4
		Chip_GPIO_WritePortBit(LPC_GPIO, PORT_Qb_[num_motor][0], PIN_Qb_[num_motor][0], 0);	//Prendo Q0
		break;
	case 1:
		Chip_GPIO_WritePortBit(LPC_GPIO, PORT_Qa_[num_motor][1], PIN_Qa_[num_motor][1], 0);	//Apago Q3
																							//Prendo Q5
		Cycle[num_motor] = 2;
		break;
	case 2:
		Chip_GPIO_WritePortBit(LPC_GPIO, PORT_Qb_[num_motor][0], PIN_Qb_[num_motor][0], 1);	//Apago Q0
		Chip_GPIO_WritePortBit(LPC_GPIO, PORT_Qb_[num_motor][1], PIN_Qb_[num_motor][1], 0);	//Prendo Q2
		break;
	case 3:
		Chip_GPIO_WritePortBit(LPC_GPIO, PORT_Qa_[num_motor][2], PIN_Qa_[num_motor][2], 0);	//Apago Q5
																							//Prendo Q1
		Cycle[num_motor] = 0;
		break;
	case 4:
		Chip_GPIO_WritePortBit(LPC_GPIO, PORT_Qb_[num_motor][1], PIN_Qb_[num_motor][1], 1);	//Apago Q2
		Chip_GPIO_WritePortBit(LPC_GPIO, PORT_Qb_[num_motor][2], PIN_Qb_[num_motor][2], 0);	//Prendo Q4
		break;
	default:
		Chip_GPIO_WritePortBit(LPC_GPIO, PORT_Qa_[num_motor][0], PIN_Qa_[num_motor][0], 0);	//Apago Q1
																							//Prendo Q3
		Cycle[num_motor] = 1;
	}

	if (StepID[num_motor] > 4)	//Si StepID es mayor a 4 reseteo variable StepID
	{
		StepID[num_motor] = 0;
		Count[num_motor]++;
	} else
		StepID[num_motor]=StepID[num_motor]+1;//Incremento StepID para la siguiente conmutación (6 conmutaciones)

	Match_Cnt[num_motor] = 0;	//Reinicio Match_Cnt

	//Estado anterior cruces zeros
	//-----------------------------------------------------------------------------------------------
/*=============[TODAVIA NO ESTA IMPLEMENTADO]========================*/
/*
	CruceZero0[num_motor][0] = GETPIN(PORT_Z_[num_motor][0], PIN_Z_[num_motor][0]);
	CruceZero0[num_motor][1] = GETPIN(PORT_Z_[num_motor][1], PIN_Z_[num_motor][1]);
	CruceZero0[num_motor][2] = GETPIN(PORT_Z_[num_motor][2], PIN_Z_[num_motor][2]);
*/
/*===================================================================*/
}

//INTERRUPT PWM
void PWM1_IRQHandler(void)
{
	//Interupción Canal 0 -> PERIODO
	//-----------------------------------------------------------------------------------------------
	if (Chip_PWM_MatchPending(LPC_PWM1, 0))	//Reviso interrupción pendiente canal PWM 0
	{
		Match_Cnt[0]++;						//Incremento contador para el brillo
		Match_Cnt[1]++;						//Incremento contador para el brillo
		Match_Cnt[2]++;						//Incremento contador para el brillo
		Match_Cnt[3]++;						//Incremento contador para el brillo
		Chip_PWM_ClearMatch(LPC_PWM1, 0);	//Limpio interrupción canal PWM 0

		//PWM sobre transistores PMOS
		Chip_GPIO_WritePortBit(LPC_GPIO, PORT_Qa_[0][Cycle[0]], PIN_Qa_[0][Cycle[0]], 1);	//Encender
		Chip_GPIO_WritePortBit(LPC_GPIO, PORT_Qa_[1][Cycle[1]], PIN_Qa_[1][Cycle[1]], 1);	//Encender
		Chip_GPIO_WritePortBit(LPC_GPIO, PORT_Qa_[2][Cycle[2]], PIN_Qa_[2][Cycle[2]], 1);	//Encender
		Chip_GPIO_WritePortBit(LPC_GPIO, PORT_Qa_[3][Cycle[3]], PIN_Qa_[3][Cycle[3]], 1);	//Encender
	}
	//Interrupción Canal PWM_number[sel_motor] -> DUTYCICLE
	//-----------------------------------------------------------------------------------------------
	if (Chip_PWM_MatchPending(LPC_PWM1, 3)) //Reviso interrupción pendiente canal PWM 3
	{
		Chip_PWM_ClearMatch(LPC_PWM1, 3);	//Limpio interrupción canal PWM 3

		//PWM sobre transistores NMOS
		Chip_GPIO_WritePortBit(LPC_GPIO, PORT_Qa_[0][Cycle[0]], PIN_Qa_[0][Cycle[0]], 0);	//Apagar
	}

	if (Chip_PWM_MatchPending(LPC_PWM1, 4)) //Reviso interrupción pendiente canal PWM 3
	{
		Chip_PWM_ClearMatch(LPC_PWM1, 4);	//Limpio interrupción canal PWM 3

		//PWM sobre transistores NMOS
		Chip_GPIO_WritePortBit(LPC_GPIO, PORT_Qa_[1][Cycle[1]], PIN_Qa_[1][Cycle[1]], 0);	//Apagar
	}

	if (Chip_PWM_MatchPending(LPC_PWM1, 5)) //Reviso interrupción pendiente canal PWM 3
	{
		Chip_PWM_ClearMatch(LPC_PWM1, 5);	//Limpio interrupción canal PWM 3

		//PWM sobre transistores NMOS
		Chip_GPIO_WritePortBit(LPC_GPIO, PORT_Qa_[2][Cycle[2]], PIN_Qa_[2][Cycle[2]], 0);	//Apagar
	}

	if (Chip_PWM_MatchPending(LPC_PWM1, 6)) //Reviso interrupción pendiente canal PWM 3
	{
		Chip_PWM_ClearMatch(LPC_PWM1, 6);	//Limpio interrupción canal PWM 3

		//PWM sobre transistores NMOS
		Chip_GPIO_WritePortBit(LPC_GPIO, PORT_Qa_[3][Cycle[3]], PIN_Qa_[3][Cycle[3]], 0);	//Apagar
	}
}
