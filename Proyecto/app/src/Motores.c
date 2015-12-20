#include "main.h"

/*==========================[GLOBALES]==========================*/
//-----------------------------------------------------------------------------------------------
<<<<<<< HEAD
extern uint32_t Match_Cnt[4], Cycle[4], AntiRebo,DutyCycle_arranque,StepPeriod_arranque,Match_Cnt_arranque;
//extern uint32_t PORT_Qa[3],PIN_Qa[3],PORT_Qb[3],PIN_Qb[3],PORT_Z[3],PIN_Z[3];
=======
extern uint32_t Cycle[4], AntiRebo;

extern volatile uint32_t Match_Cnt[4];
>>>>>>> Sin_SO

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
	uint8_t channel=0;
	//Initialize PWM peipheral, timer mode
	//-----------------------------------------------------------------------------------------------
	Chip_PWM_PrescaleSet(LPC_PWM1, 0);		//Valor preescalar=100 (divisor de clock)
	//Set match value for PWM match channel0 (frecuency)

	//-----------------------------------------------------------------------------------------------
	Chip_PWM_SetMatch(LPC_PWM1, 0, 1000);		//Establezco el valor en clock del período (canal 0) 25kHz
	Chip_PWM_MatchEnableInt(LPC_PWM1, 0);		//Habilito interrupción
	Chip_PWM_ResetOnMatchEnable(LPC_PWM1, 0);	//Reset auto
	Chip_PWM_StopOnMatchDisable(LPC_PWM1, 0);	//No stop

<<<<<<< HEAD
	//Configuro los demas canales (3 -> 6)
	for(channel=3; channel <= 6; channel++)
	{
		//Configure PWM channel edge (single) CHANNEL 5
		//-----------------------------------------------------------------------------------------------
		Chip_PWM_SetControlMode(LPC_PWM1, channel, PWM_SINGLE_EDGE_CONTROL_MODE, PWM_OUT_DISABLED);

		//Configure match value for channel 5
		//-----------------------------------------------------------------------------------------------
		Chip_PWM_SetMatch(LPC_PWM1, channel, 10);		//Establezco el valor en clock del Duty (canal 5) 1%Duty
		Chip_PWM_MatchEnableInt(LPC_PWM1, channel);		//Habilito interrupción
		Chip_PWM_ResetOnMatchDisable(LPC_PWM1, channel);	//No reset auto
		Chip_PWM_StopOnMatchDisable(LPC_PWM1, channel);	//No stop
	}
=======

>>>>>>> Sin_SO
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
<<<<<<< HEAD
	Chip_GPIO_WriteDirBit(LPC_GPIO, PORT_Q10, PIN_Q10 , SALIDA);	//Configuro el pin como salida
	Chip_GPIO_WriteDirBit(LPC_GPIO, PORT_Q11, PIN_Q11 , SALIDA);	//Configuro el pin como salida
	Chip_GPIO_WriteDirBit(LPC_GPIO, PORT_Q12, PIN_Q12 , SALIDA);	//Configuro el pin como salida
	Chip_GPIO_WriteDirBit(LPC_GPIO, PORT_Q13, PIN_Q13 , SALIDA);	//Configuro el pin como salida
	Chip_GPIO_WriteDirBit(LPC_GPIO, PORT_Q14, PIN_Q14 , SALIDA);	//Configuro el pin como salida
	Chip_GPIO_WriteDirBit(LPC_GPIO, PORT_Q15, PIN_Q15 , SALIDA);	//Configuro el pin como salida

	Chip_GPIO_WriteDirBit(LPC_GPIO, PORT_Q20, PIN_Q20 , SALIDA);	//Configuro el pin como salida
	Chip_GPIO_WriteDirBit(LPC_GPIO, PORT_Q21, PIN_Q21 , SALIDA);	//Configuro el pin como salida
	Chip_GPIO_WriteDirBit(LPC_GPIO, PORT_Q22, PIN_Q22 , SALIDA);	//Configuro el pin como salida
	Chip_GPIO_WriteDirBit(LPC_GPIO, PORT_Q23, PIN_Q23 , SALIDA);	//Configuro el pin como salida
	Chip_GPIO_WriteDirBit(LPC_GPIO, PORT_Q24, PIN_Q24 , SALIDA);	//Configuro el pin como salida
	Chip_GPIO_WriteDirBit(LPC_GPIO, PORT_Q25, PIN_Q25 , SALIDA);	//Configuro el pin como salida

	Chip_GPIO_WriteDirBit(LPC_GPIO, PORT_Q30, PIN_Q30 , SALIDA);	//Configuro el pin como salida
	Chip_GPIO_WriteDirBit(LPC_GPIO, PORT_Q31, PIN_Q31 , SALIDA);	//Configuro el pin como salida
	Chip_GPIO_WriteDirBit(LPC_GPIO, PORT_Q32, PIN_Q32 , SALIDA);	//Configuro el pin como salida
	Chip_GPIO_WriteDirBit(LPC_GPIO, PORT_Q33, PIN_Q33 , SALIDA);	//Configuro el pin como salida
	Chip_GPIO_WriteDirBit(LPC_GPIO, PORT_Q34, PIN_Q34 , SALIDA);	//Configuro el pin como salida
	Chip_GPIO_WriteDirBit(LPC_GPIO, PORT_Q35, PIN_Q35 , SALIDA);	//Configuro el pin como salida

	Chip_GPIO_WriteDirBit(LPC_GPIO, PORT_Q40, PIN_Q40 , SALIDA);	//Configuro el pin como salida
	Chip_GPIO_WriteDirBit(LPC_GPIO, PORT_Q41, PIN_Q41 , SALIDA);	//Configuro el pin como salida
	Chip_GPIO_WriteDirBit(LPC_GPIO, PORT_Q42, PIN_Q42 , SALIDA);	//Configuro el pin como salida
	Chip_GPIO_WriteDirBit(LPC_GPIO, PORT_Q43, PIN_Q43 , SALIDA);	//Configuro el pin como salida
	Chip_GPIO_WriteDirBit(LPC_GPIO, PORT_Q44, PIN_Q44 , SALIDA);	//Configuro el pin como salida
	Chip_GPIO_WriteDirBit(LPC_GPIO, PORT_Q45, PIN_Q45 , SALIDA);	//Configuro el pin como salida
	//APAGAR TRANSISTORES
	//-----------------------------------------------------------------------------------------------
	Chip_GPIO_WritePortBit(LPC_GPIO, PORT_Q11, PIN_Q11, 1);
	Chip_GPIO_WritePortBit(LPC_GPIO, PORT_Q12, PIN_Q12, 0);
	Chip_GPIO_WritePortBit(LPC_GPIO, PORT_Q13, PIN_Q13, 1);
	Chip_GPIO_WritePortBit(LPC_GPIO, PORT_Q14, PIN_Q14, 0);
	Chip_GPIO_WritePortBit(LPC_GPIO, PORT_Q15, PIN_Q15, 1);
	Chip_GPIO_WritePortBit(LPC_GPIO, PORT_Q10, PIN_Q10, 0);

	Chip_GPIO_WritePortBit(LPC_GPIO, PORT_Q21, PIN_Q21, 1);
	Chip_GPIO_WritePortBit(LPC_GPIO, PORT_Q22, PIN_Q22, 0);
	Chip_GPIO_WritePortBit(LPC_GPIO, PORT_Q23, PIN_Q23, 1);
	Chip_GPIO_WritePortBit(LPC_GPIO, PORT_Q24, PIN_Q24, 0);
	Chip_GPIO_WritePortBit(LPC_GPIO, PORT_Q25, PIN_Q25, 1);
	Chip_GPIO_WritePortBit(LPC_GPIO, PORT_Q20, PIN_Q20, 0);

	Chip_GPIO_WritePortBit(LPC_GPIO, PORT_Q31, PIN_Q31, 1);
	Chip_GPIO_WritePortBit(LPC_GPIO, PORT_Q32, PIN_Q32, 0);
	Chip_GPIO_WritePortBit(LPC_GPIO, PORT_Q33, PIN_Q33, 1);
	Chip_GPIO_WritePortBit(LPC_GPIO, PORT_Q34, PIN_Q34, 0);
	Chip_GPIO_WritePortBit(LPC_GPIO, PORT_Q35, PIN_Q35, 1);
	Chip_GPIO_WritePortBit(LPC_GPIO, PORT_Q30, PIN_Q30, 0);

	Chip_GPIO_WritePortBit(LPC_GPIO, PORT_Q41, PIN_Q41, 1);		//PMOS
	Chip_GPIO_WritePortBit(LPC_GPIO, PORT_Q42, PIN_Q42, 0);		//NMOS
	Chip_GPIO_WritePortBit(LPC_GPIO, PORT_Q43, PIN_Q43, 1);		//PMOS
	Chip_GPIO_WritePortBit(LPC_GPIO, PORT_Q44, PIN_Q44, 0);		//NMOS
	Chip_GPIO_WritePortBit(LPC_GPIO, PORT_Q45, PIN_Q45, 1);		//PMOS
	Chip_GPIO_WritePortBit(LPC_GPIO, PORT_Q40, PIN_Q40, 0);		//NMOS
	//CONFIGURAR ENTRADAS
	//-----------------------------------------------------------------------------------------------
	Chip_GPIO_WriteDirBit(LPC_GPIO, PORT_Z11, PIN_Z11, 0);
	Chip_GPIO_WriteDirBit(LPC_GPIO, PORT_Z12, PIN_Z12, 0);
	Chip_GPIO_WriteDirBit(LPC_GPIO, PORT_Z13, PIN_Z13, 0);

	Chip_GPIO_WriteDirBit(LPC_GPIO, PORT_Z21, PIN_Z21, 0);
	Chip_GPIO_WriteDirBit(LPC_GPIO, PORT_Z22, PIN_Z22, 0);
	Chip_GPIO_WriteDirBit(LPC_GPIO, PORT_Z23, PIN_Z23, 0);

	Chip_GPIO_WriteDirBit(LPC_GPIO, PORT_Z31, PIN_Z31, 0);
	Chip_GPIO_WriteDirBit(LPC_GPIO, PORT_Z32, PIN_Z32, 0);
	Chip_GPIO_WriteDirBit(LPC_GPIO, PORT_Z33, PIN_Z33, 0);

	Chip_GPIO_WriteDirBit(LPC_GPIO, PORT_Z41, PIN_Z41, 0);
	Chip_GPIO_WriteDirBit(LPC_GPIO, PORT_Z42, PIN_Z42, 0);
	Chip_GPIO_WriteDirBit(LPC_GPIO, PORT_Z43, PIN_Z43, 0);
=======
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

>>>>>>> Sin_SO
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
<<<<<<< HEAD

	Chip_GPIO_WritePortBit(LPC_GPIO, PORT_Qb_[num_motor][0], PIN_Qb_[num_motor][0], 1);		//NMOS
	Chip_GPIO_WritePortBit(LPC_GPIO, PORT_Qa_[num_motor][0], PIN_Qa_[num_motor][0], 0);		//PMOS
	Chip_GPIO_WritePortBit(LPC_GPIO, PORT_Qb_[num_motor][1], PIN_Qb_[num_motor][1], 1);		//NMOS
	Chip_GPIO_WritePortBit(LPC_GPIO, PORT_Qa_[num_motor][1], PIN_Qa_[num_motor][1], 0);		//PMOS
	Chip_GPIO_WritePortBit(LPC_GPIO, PORT_Qb_[num_motor][2], PIN_Qb_[num_motor][2], 1);		//NMOS
	Chip_GPIO_WritePortBit(LPC_GPIO, PORT_Qa_[num_motor][2], PIN_Qa_[num_motor][2], 0);		//PMOS
}

void Start_Up_Brushless(void)
=======
	Chip_GPIO_WritePortBit(LPC_GPIO, PORT_Qa_[num_motor][0], PIN_Qa_[num_motor][0], 0);		//PMOS
	Chip_GPIO_WritePortBit(LPC_GPIO, PORT_Qa_[num_motor][1], PIN_Qa_[num_motor][1], 0);		//PMOS
	Chip_GPIO_WritePortBit(LPC_GPIO, PORT_Qa_[num_motor][2], PIN_Qa_[num_motor][2], 0);		//PMOS
	Chip_GPIO_WritePortBit(LPC_GPIO, PORT_Qb_[num_motor][0], PIN_Qb_[num_motor][0], 1);		//NMOS
	Chip_GPIO_WritePortBit(LPC_GPIO, PORT_Qb_[num_motor][1], PIN_Qb_[num_motor][1], 1);		//NMOS
	Chip_GPIO_WritePortBit(LPC_GPIO, PORT_Qb_[num_motor][2], PIN_Qb_[num_motor][2], 1);		//NMOS
}

uint32_t Start_Up_Brushless(uint32_t num_motor)
>>>>>>> Sin_SO
{
	static uint32_t t=1, dr=0, dPwr=0;
	static uint32_t Suspender_Task=0;

	//Drive at const rate for a few cycles to make sure rotor is synched.
	//-----------------------------------------------------------------------------------------------
<<<<<<< HEAD
	Count = 0;
	NextPWM(0); NextPWM(1);	NextPWM(2);	NextPWM(3);	//Siguiente conmutación

	while (Count < 10)				//Primeras 3 conmutaciones a período inicial (lentas) por sincronizmo
	{
		while (Match_Cnt_arranque < StepPeriod_arranque);	//Delay hasta sig conmutación
		NextPWM(0);NextPWM(1);NextPWM(2);NextPWM(3);						//Siguiente conmutación
=======

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
>>>>>>> Sin_SO
	}
	//Set variables para ecuaciones de arranque
	//-----------------------------------------------------------------------------------------------
	dPwr = (start.powerRange[1] - start.powerRange[0])/start.duration; 	//Diferencia de Duty
	dr = (start.periodRange[0] -start.periodRange[1])/start.duration;

	t = 0;
	//Arranque del Motor	(Clock:25MHz, Divisor pwm:1, Ciclos pwm:1000, -> [1 Match_Cnt = 40 MicroSeg]
	//-----------------------------------------------------------------------------------------------
<<<<<<< HEAD
	while (StepPeriod_arranque > start.periodRange[1])
	{
		while (Match_Cnt_arranque < StepPeriod_arranque);//Delay hasta la siguiente conmutación (bloqueante solo durante arranque)
		NextPWM(0); NextPWM(1); NextPWM(2); NextPWM(3);						//Siguiente conmutación
=======
	while (StepPeriod[num_motor] > (uint32_t)start.periodRange[num_motor])
	{
		while (Match_Cnt[num_motor] < StepPeriod[num_motor]);//Delay hasta la siguiente conmutación (bloqueante solo durante arranque)
		NextPWM(num_motor);						//Siguiente conmutación
>>>>>>> Sin_SO

		DutyCycle_arranque = start.powerRange[0] + t * dPwr;//Incremento Duty de manera lineal desde powerRange0 a powerRange1
		StepPeriod_arranque =start.periodRange[0] - t * dr;	//Disminuye período entre conmutaciones de manera exponencial decreciente
		t++;																					//desde periodRange0 hasta periodRange1
	}

	DutyCycle[0] = 150;		// (150/1000)-> 15% Duty
	DutyCycle[1] = 150;		// (150/1000)-> 15% Duty
	DutyCycle[2] = 150;		// (150/1000)-> 15% Duty
	DutyCycle[3] = 150;		// (150/1000)-> 15% Duty

<<<<<<< HEAD



/*A CORREGIR*/
	Chip_PWM_SetMatch(LPC_PWM1, 5, DutyCycle[0]);
	Chip_PWM_SetMatch(LPC_PWM1, 5, DutyCycle[1]);
	Chip_PWM_SetMatch(LPC_PWM1, 5, DutyCycle[2]);
	Chip_PWM_SetMatch(LPC_PWM1, 5, DutyCycle[3]);
	Chip_PWM_Reset(LPC_PWM1);
/*          */
=======
	Chip_PWM_SetMatch(LPC_PWM1, PWM_number[num_motor], DutyCycle[num_motor]);
	Chip_PWM_Reset(LPC_PWM1);

	Suspender_Task = 1;
	 */
	return Suspender_Task;
>>>>>>> Sin_SO
}

void NextPWM(uint32_t num_motor)
{
	//Actualizar DutyCycle
	//-----------------------------------------------------------------------------------------------

	if (DutyCycle[num_motor] != DutyCycle0[num_motor])
	{
<<<<<<< HEAD
		/*A CORREGIR*/
		Chip_PWM_SetMatch(LPC_PWM1, 5, DutyCycle[num_motor]);
		Chip_PWM_Reset(LPC_PWM1);
		/*          */
=======
		Chip_PWM_SetMatch(LPC_PWM1, PWM_number[num_motor], DutyCycle[num_motor]);
		//Chip_PWM_Reset(LPC_PWM1);
		Chip_PWM_LatchEnable(LPC_PWM1, PWM_number[num_motor], PWM_OUT_ENABLED);
>>>>>>> Sin_SO
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
<<<<<<< HEAD
		Cycle[num_motor] = 2;													//Prendo Q5
=======
																							//Prendo Q5
		Cycle[num_motor] = 2;
>>>>>>> Sin_SO
		break;
	case 2:
		Chip_GPIO_WritePortBit(LPC_GPIO, PORT_Qb_[num_motor][0], PIN_Qb_[num_motor][0], 1);	//Apago Q0
		Chip_GPIO_WritePortBit(LPC_GPIO, PORT_Qb_[num_motor][1], PIN_Qb_[num_motor][1], 0);	//Prendo Q2
		break;
	case 3:
		Chip_GPIO_WritePortBit(LPC_GPIO, PORT_Qa_[num_motor][2], PIN_Qa_[num_motor][2], 0);	//Apago Q5
<<<<<<< HEAD
		Cycle[num_motor] = 0;													//Prendo Q1
=======
																							//Prendo Q1
		Cycle[num_motor] = 0;
>>>>>>> Sin_SO
		break;
	case 4:
		Chip_GPIO_WritePortBit(LPC_GPIO, PORT_Qb_[num_motor][1], PIN_Qb_[num_motor][1], 1);	//Apago Q2
		Chip_GPIO_WritePortBit(LPC_GPIO, PORT_Qb_[num_motor][2], PIN_Qb_[num_motor][2], 0);	//Prendo Q4
		break;
	default:
		Chip_GPIO_WritePortBit(LPC_GPIO, PORT_Qa_[num_motor][0], PIN_Qa_[num_motor][0], 0);	//Apago Q1
<<<<<<< HEAD
		Cycle[num_motor] = 1;													//Prendo Q3
=======
																							//Prendo Q3
		Cycle[num_motor] = 1;
>>>>>>> Sin_SO
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
<<<<<<< HEAD
		Match_Cnt_arranque++;
		Match_Cnt[0]++;Match_Cnt[1]++;Match_Cnt[2]++;Match_Cnt[3]++;	//Incremento contador para el brillo
		Chip_PWM_ClearMatch(LPC_PWM1, 0);	//Limpio interrupción canal PWM 0

		//PWM sobre transistores PMOS
		Chip_GPIO_WritePortBit(LPC_GPIO, PORT_Qb_[0][Cycle[0]], PIN_Qb_[0][Cycle[0]], 0);	//Encender (invertido por el tbj emisor común)
		Chip_GPIO_WritePortBit(LPC_GPIO, PORT_Qb_[1][Cycle[1]], PIN_Qb_[1][Cycle[1]], 0);	//Encender (invertido por el tbj emisor común)
		Chip_GPIO_WritePortBit(LPC_GPIO, PORT_Qb_[2][Cycle[2]], PIN_Qb_[2][Cycle[2]], 0);	//Encender (invertido por el tbj emisor común)
		Chip_GPIO_WritePortBit(LPC_GPIO, PORT_Qb_[3][Cycle[3]], PIN_Qb_[3][Cycle[3]], 0);	//Encender (invertido por el tbj emisor común)
	}
	//Interrupción Canal 3 -> DUTYCICLE
	//-----------------------------------------------------------------------------------------------
	if (Chip_PWM_MatchPending(LPC_PWM1, 3)) //Reviso interrupción pendiente canal PWM 3
	{
		Chip_PWM_ClearMatch(LPC_PWM1, 3);	//Limpio interrupción canal PWM 5

		//PWM sobre transistores NMOS
		Chip_GPIO_WritePortBit(LPC_GPIO, PORT_Qb_[0][Cycle[0]], PIN_Qb_[0][Cycle[0]], 1);	//Apagar (invertido por el tbj emisor común)
	}
	//Interrupción Canal 4 -> DUTYCICLE
	//-----------------------------------------------------------------------------------------------
	if (Chip_PWM_MatchPending(LPC_PWM1, 4)) //Reviso interrupción pendiente canal PWM 4
	{
		Chip_PWM_ClearMatch(LPC_PWM1, 4);	//Limpio interrupción canal PWM 5

		//PWM sobre transistores NMOS
		Chip_GPIO_WritePortBit(LPC_GPIO, PORT_Qb_[1][Cycle[1]], PIN_Qb_[1][Cycle[1]], 1);	//Apagar (invertido por el tbj emisor común)
=======
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
>>>>>>> Sin_SO
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
<<<<<<< HEAD
		Chip_GPIO_WritePortBit(LPC_GPIO, PORT_Qb_[2][Cycle[2]], PIN_Qb_[2][Cycle[2]], 1);	//Apagar (invertido por el tbj emisor común)
	}
	//Interrupción Canal 5 -> DUTYCICLE
	//-----------------------------------------------------------------------------------------------
	if (Chip_PWM_MatchPending(LPC_PWM1, 6)) //Reviso interrupción pendiente canal PWM 6
	{
		Chip_PWM_ClearMatch(LPC_PWM1, 6);	//Limpio interrupción canal PWM 5

		//PWM sobre transistores NMOS
		Chip_GPIO_WritePortBit(LPC_GPIO, PORT_Qb_[3][Cycle[3]], PIN_Qb_[3][Cycle[3]], 1);	//Apagar (invertido por el tbj emisor común)
=======
		Chip_GPIO_WritePortBit(LPC_GPIO, PORT_Qa_[3][Cycle[3]], PIN_Qa_[3][Cycle[3]], 0);	//Apagar
>>>>>>> Sin_SO
	}
}

