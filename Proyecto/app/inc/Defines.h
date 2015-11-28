/*
 * Variables globales y puertos para controlar motores.
 *
 * PORT_Qa y PIN_Qa -> PWM
 * PORT_Qb y PIN_Qb -> Encendido digital
 */

//DEFINICIONES PUERTOS SALIDAS ENTRADAS
//-----------------------------------------------------------------------------------------------


/*

#define PORT_Q0		2//1
#define PORT_Q1		2//1
#define PORT_Q2		2//1
#define PORT_Q3		2//1
#define PORT_Q4		2//1
#define PORT_Q5		0//1

#define PIN_Q0		12//24
#define PIN_Q1		11//26
#define PIN_Q2		4//21
#define PIN_Q3		3//23
#define PIN_Q4		2//18
#define PIN_Q5		17//20
#define PULS1 		18
#define PULS2 		1
#define PULS_PORT 	0
#define PORT_Z1		1
#define PORT_Z2		1
#define PORT_Z3		1
#define PIN_Z1		19
#define PIN_Z2		22
#define PIN_Z3		25
#define REBOTE_ 	100000
#define SALIDA		1


*/



/*==================[auxiliar]=================================*/


#define	PLED7		2
#define	PLED6		2
//#define	PLED5		0		//NO ANDA EN LA RUBENBOARD QUE TENEMOS
#define	PLED4		2
#define	PLED3		2
#define	PLED2		2
#define	PLED1		0
#define	PLED0		0


#define	LED7		12
#define	LED6		11
//#define	LED5		4			//NO ANDA
#define	LED4		4
#define	LED3		3
#define	LED2		2
#define	LED1		22
#define	LED0		17


/*=============================================================*/



/*==================[Para los motores]=========================*/

#define PORT_Q10		1
#define PORT_Q11		0
#define PORT_Q12		1
#define PORT_Q13		1
#define PORT_Q14		1
#define PORT_Q15		1
#define PIN_Q10		26
#define PIN_Q11		8
#define PIN_Q12		25
#define PIN_Q13		28
#define PIN_Q14		24
#define PIN_Q15		27


#define PORT_Q20		0
#define PORT_Q21		0
#define PORT_Q22		0
#define PORT_Q23		0
#define PORT_Q24		0
#define PORT_Q25		0
#define PIN_Q20		19
#define PIN_Q21		22
#define PIN_Q22		18
#define PIN_Q23		21
#define PIN_Q24		17
#define PIN_Q25		20


#define PORT_Q30		2
#define PORT_Q31		2
#define PORT_Q32		2
#define PORT_Q33		2
#define PORT_Q34		2
#define PORT_Q35		2
#define PIN_Q30		3
#define PIN_Q31		0
#define PIN_Q32		4
#define PIN_Q33		1
#define PIN_Q34		5
#define PIN_Q35		2


#define PORT_Q40		3
#define PORT_Q41		0
#define PORT_Q42		0
#define PORT_Q43		0
#define PORT_Q44		0
#define PORT_Q45		3
#define PIN_Q40		25
#define PIN_Q41		28
#define PIN_Q42		29
#define PIN_Q43		27
#define PIN_Q44		30
#define PIN_Q45		26

#define PORT_Z11		1
#define PORT_Z12		1
#define PORT_Z13		1
#define PIN_Z11		23
#define PIN_Z12		22
#define PIN_Z13		21

#define PORT_Z21		0
#define PORT_Z22		0
#define PORT_Z23		2
#define PIN_Z21		15
#define PIN_Z22		16
#define PIN_Z23		9

#define PORT_Z31		2
#define PORT_Z32		2
#define PORT_Z33		2
#define PIN_Z31		6
#define PIN_Z32		7
#define PIN_Z33		8

#define PORT_Z41		1
#define PORT_Z42		1
#define PORT_Z43		1
#define PIN_Z41		18
#define PIN_Z42		19
#define PIN_Z43		20

#define PULS1 		18
#define PULS2 		1
#define PULS_PORT 	0

#define REBOTE_ 	100000
#define SALIDA		1




/*=============================================================*/

struct StartParams_s {		// params for startup seq.
	long duration; 			// duration of accel phase of startup, us
	long periodRange[2]; 	// commutation period range for startup, us
	long powerRange[2];  	// frac of full power over startup accel
};

//FUNCIONES
//-----------------------------------------------------------------------------------------------

void PWM1_IRQHandler(void);
void InitPWM(void);
void InitGPIO(void);
void Stop_and_Default(uint8_t);
void Start_Up_Brushless(void);
void NextPWM(uint8_t);
void Zero_Detect(void);

