#include "main.h"

//GLOBALES
//-----------------------------------------------------------------------------------------------
extern uint32_t Match_Cnt, Cycle, AntiRebo,PORT_Qa[3],PIN_Qa[3],PORT_Qb[3],PIN_Qb[3],PORT_Z[3],PIN_Z[3];

extern volatile uint8_t CruceZero[3], CruceZero0[3];

struct StartParams_s {		// params for startup seq.
	long duration; 			// duration of accel phase of startup, us
	long periodRange[2]; 	// commutation period range for startup, us
	long powerRange[2];  	// frac of full power over startup accel
} start= { 150,   {500, 300},   {60, 150} };	//Cantidad de pasos, período inicial y final, pwm inicial y final para startup
												//-----> 50*20microseg = 1mSeg
extern long StepPeriod;     			// step duration, us
extern volatile uint16_t DutyCycle, DutyCycle0; 	// fraction of period hi pins are high

extern volatile int StepID;  		// commutation step counter, 0..5
extern uint8_t Count;  					// no full commutation cycles completed





void InitPWM(void)
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

	//Configure PWM channel edge (single) CHANNEL 5
	//-----------------------------------------------------------------------------------------------
	Chip_PWM_SetControlMode(LPC_PWM1, 5, PWM_SINGLE_EDGE_CONTROL_MODE, PWM_OUT_DISABLED);

	//Configure match value for channel 5
	//-----------------------------------------------------------------------------------------------
	Chip_PWM_SetMatch(LPC_PWM1, 5, 20);		//Establezco el valor en clock del Duty (canal 5) / 20 -> 2%Duty
	Chip_PWM_MatchEnableInt(LPC_PWM1, 5);		//Habilito interrupción
	Chip_PWM_ResetOnMatchDisable(LPC_PWM1, 5);	//No reset auto
	Chip_PWM_StopOnMatchDisable(LPC_PWM1, 5);	//No stop

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

void InitGPIO(void)
{
	//CONFIGURAR SALIDAS
	//-----------------------------------------------------------------------------------------------
	Chip_GPIO_WriteDirBit(LPC_GPIO, PORT_Q0, PIN_Q0 , SALIDA);	//Configuro el pin como salida
	Chip_GPIO_WriteDirBit(LPC_GPIO, PORT_Q1, PIN_Q1 , SALIDA);	//Configuro el pin como salida
	Chip_GPIO_WriteDirBit(LPC_GPIO, PORT_Q2, PIN_Q2 , SALIDA);	//Configuro el pin como salida
	Chip_GPIO_WriteDirBit(LPC_GPIO, PORT_Q3, PIN_Q3 , SALIDA);	//Configuro el pin como salida
	Chip_GPIO_WriteDirBit(LPC_GPIO, PORT_Q4, PIN_Q4 , SALIDA);	//Configuro el pin como salida
	Chip_GPIO_WriteDirBit(LPC_GPIO, PORT_Q5, PIN_Q5 , SALIDA);	//Configuro el pin como salida
	//APAGAR TRANSISTORES
	//-----------------------------------------------------------------------------------------------
	Chip_GPIO_WritePortBit(LPC_GPIO, PORT_Q1, PIN_Q1, 0);		//PMOS
	Chip_GPIO_WritePortBit(LPC_GPIO, PORT_Q2, PIN_Q2, 1);		//NMOS
	Chip_GPIO_WritePortBit(LPC_GPIO, PORT_Q3, PIN_Q3, 0);		//PMOS
	Chip_GPIO_WritePortBit(LPC_GPIO, PORT_Q4, PIN_Q4, 1);		//NMOS
	Chip_GPIO_WritePortBit(LPC_GPIO, PORT_Q5, PIN_Q5, 0);		//PMOS
	Chip_GPIO_WritePortBit(LPC_GPIO, PORT_Q0, PIN_Q0, 1);		//NMOS
	//CONFIGURAR ENTRADAS
	//-----------------------------------------------------------------------------------------------
	Chip_GPIO_WriteDirBit(LPC_GPIO, PORT_Z1, PIN_Z1, 0);
	Chip_GPIO_WriteDirBit(LPC_GPIO, PORT_Z2, PIN_Z2, 0);
	Chip_GPIO_WriteDirBit(LPC_GPIO, PORT_Z3, PIN_Z3, 0);
}

void Stop_and_Default(void)
{
	//Set Period and PWM
	//-----------------------------------------------------------------------------------------------
	StepPeriod = start.periodRange[0];
	DutyCycle = start.powerRange[0];
	DutyCycle0 = DutyCycle;
	//Shut Down All
	//-----------------------------------------------------------------------------------------------
	Chip_GPIO_WritePortBit(LPC_GPIO, PORT_Q1, PIN_Q1, 0);		//PMOS
	Chip_GPIO_WritePortBit(LPC_GPIO, PORT_Q2, PIN_Q2, 1);		//NMOS
	Chip_GPIO_WritePortBit(LPC_GPIO, PORT_Q3, PIN_Q3, 0);		//PMOS
	Chip_GPIO_WritePortBit(LPC_GPIO, PORT_Q4, PIN_Q4, 1);		//NMOS
	Chip_GPIO_WritePortBit(LPC_GPIO, PORT_Q5, PIN_Q5, 0);		//PMOS
	Chip_GPIO_WritePortBit(LPC_GPIO, PORT_Q0, PIN_Q0, 1);		//NMOS
}

void Start_Up_Brushless(void)
{
	uint32_t t = 1, dr, dPwr;

	//Drive at const rate for a few cycles to make sure rotor is synched.
	//-----------------------------------------------------------------------------------------------
	Count = 0;
	NextPWM();	//Siguiente conmutación
	while (Count < 10)				//Primeras 3 conmutaciones a período inicial (lentas) por sincronizmo
	{
		while (Match_Cnt < StepPeriod);	//Delay hasta sig conmutación
		NextPWM();						//Siguiente conmutación
	}
	//Set variables para ecuaciones de arranque
	//-----------------------------------------------------------------------------------------------
	dPwr = (start.powerRange[1] - start.powerRange[0])/start.duration; 	//Diferencia de Duty
	dr = (start.periodRange[0] -start.periodRange[1])/start.duration;

	t = 0;
	//Arranque del Motor	(Clock:25MHz, Divisor pwm:1, Ciclos pwm:1000, -> [1 Match_Cnt = 40 MicroSeg]
	//-----------------------------------------------------------------------------------------------
	while (StepPeriod > start.periodRange[1])
	{
		while (Match_Cnt < StepPeriod);//Delay hasta la siguiente conmutación (bloqueante solo durante arranque)
		NextPWM();						//Siguiente conmutación

		DutyCycle = start.powerRange[0] + t * dPwr;//Incremento Duty de manera lineal desde powerRange0 a powerRange1
		StepPeriod =start.periodRange[0] - t * dr;	//Disminuye período entre conmutaciones de manera exponencial decreciente
		t++;																					//desde periodRange0 hasta periodRange1
	}

	DutyCycle = 150;		// (150/1000)-> 15% Duty

	Chip_PWM_SetMatch(LPC_PWM1, 5, DutyCycle);
	Chip_PWM_Reset(LPC_PWM1);
}

void NextPWM(void)
{
	//Actualizar DutyCycle
	//-----------------------------------------------------------------------------------------------
	if (DutyCycle != DutyCycle0)
	{
		Chip_PWM_SetMatch(LPC_PWM1, 5, DutyCycle);
		Chip_PWM_Reset(LPC_PWM1);
		DutyCycle0 = DutyCycle;
	}
	//Conmutaciones MOSfet
	//-----------------------------------------------------------------------------------------------
	switch (StepID)
	{
	case 0:
		Chip_GPIO_WritePortBit(LPC_GPIO, PORT_Qb[2], PIN_Qb[2], 1);	//Apago Q4
		Chip_GPIO_WritePortBit(LPC_GPIO, PORT_Qb[0], PIN_Qb[0], 0);	//Prendo Q0
		break;
	case 1:
		Chip_GPIO_WritePortBit(LPC_GPIO, PORT_Qa[1], PIN_Qa[1], 0);	//Apago Q3
		Cycle = 2;													//Prendo Q5
		break;
	case 2:
		Chip_GPIO_WritePortBit(LPC_GPIO, PORT_Qb[0], PIN_Qb[0], 1);	//Apago Q0
		Chip_GPIO_WritePortBit(LPC_GPIO, PORT_Qb[1], PIN_Qb[1], 0);	//Prendo Q2
		break;
	case 3:
		Chip_GPIO_WritePortBit(LPC_GPIO, PORT_Qa[2], PIN_Qa[2], 0);	//Apago Q5
		Cycle = 0;													//Prendo Q1
		break;
	case 4:
		Chip_GPIO_WritePortBit(LPC_GPIO, PORT_Qb[1], PIN_Qb[1], 1);	//Apago Q2
		Chip_GPIO_WritePortBit(LPC_GPIO, PORT_Qb[2], PIN_Qb[2], 0);	//Prendo Q4
		break;
	default:
		Chip_GPIO_WritePortBit(LPC_GPIO, PORT_Qa[0], PIN_Qa[0], 0);	//Apago Q1
		Cycle = 1;													//Prendo Q3
	}

	if (StepID > 4)	//Si StepID es mayor a 4 reseteo variable StepID
	{
		StepID = 0;
		Count++;
	} else
		StepID++;//Incremento StepID para la siguiente conmutación (6 conmutaciones)

	Match_Cnt = 0;	//Reinicio Match_Cnt

	//Estado anterior cruces zeros
	//-----------------------------------------------------------------------------------------------
	CruceZero0[0] = Chip_GPIO_ReadPortBit(LPC_GPIO, PORT_Z[0], PIN_Z[0]);
	CruceZero0[1] = Chip_GPIO_ReadPortBit(LPC_GPIO, PORT_Z[1], PIN_Z[1]);
	CruceZero0[2] = Chip_GPIO_ReadPortBit(LPC_GPIO, PORT_Z[2], PIN_Z[2]);
}

//INTERRUPT PWM
void PWM1_IRQHandler(void)
{
	//Interupción Canal 0 -> PERIODO
	//-----------------------------------------------------------------------------------------------
	if (Chip_PWM_MatchPending(LPC_PWM1, 0))	//Reviso interrupción pendiente canal PWM 0
	{
		Match_Cnt++;						//Incremento contador para el brillo
		Chip_PWM_ClearMatch(LPC_PWM1, 0);	//Limpio interrupción canal PWM 0

		//PWM sobre transistores PMOS
		Chip_GPIO_WritePortBit(LPC_GPIO, PORT_Qa[Cycle], PIN_Qa[Cycle], 1);	//Encender
	}
	//Interrupción Canal 5 -> DUTYCICLE
	//-----------------------------------------------------------------------------------------------
	if (Chip_PWM_MatchPending(LPC_PWM1, 5)) //Reviso interrupción pendiente canal PWM 5
	{
		Chip_PWM_ClearMatch(LPC_PWM1, 5);	//Limpio interrupción canal PWM 5

		//PWM sobre transistores NMOS
		Chip_GPIO_WritePortBit(LPC_GPIO, PORT_Qa[Cycle], PIN_Qa[Cycle], 0);	//Apagar
	}
}