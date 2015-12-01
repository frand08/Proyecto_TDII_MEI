/*
 * Variables globales y puertos para controlar motores.
 *
 * PORT_Qa y PIN_Qa -> PWM
 * PORT_Qb y PIN_Qb -> Encendido digital
 */

//DEFINICIONES PUERTOS SALIDAS ENTRADAS
//-----------------------------------------------------------------------------------------------

/*===========================[P8]====================================*/
#define 	PORT_Q00		3
#define 	PORT_Q01		0
#define 	PORT_Q02		0
#define 	PORT_Q03		0
#define 	PORT_Q04		0
#define 	PORT_Q05		3

#define 	PIN_Q00			25
#define 	PIN_Q01			28
#define 	PIN_Q02			29
#define 	PIN_Q03			27
#define 	PIN_Q04			30
#define 	PIN_Q05			26

#define 	PORT_Z01		0
#define 	PORT_Z02		0
#define 	PORT_Z03		0
#define 	PIN_Z01			0
#define 	PIN_Z02			0
#define 	PIN_Z03			0
/*===================================================================*/

/*===========================[P9]====================================*/
#define 	PORT_Q10		1
#define 	PORT_Q11		0
#define 	PORT_Q12		1
#define 	PORT_Q13		1
#define 	PORT_Q14		1
#define 	PORT_Q15		1

#define 	PIN_Q10			26
#define 	PIN_Q11			10
#define 	PIN_Q12			25
#define 	PIN_Q13			28
#define 	PIN_Q14			24
#define 	PIN_Q15			27

#define 	PORT_Z11		0
#define 	PORT_Z12		0
#define 	PORT_Z13		0
#define 	PIN_Z11			0
#define 	PIN_Z12			0
#define 	PIN_Z13			0
/*===================================================================*/

/*===========================[P10]===================================*/
#define 	PORT_Q20		0
#define 	PORT_Q21		0
#define 	PORT_Q22		0
#define 	PORT_Q23		0
#define 	PORT_Q24		0
#define 	PORT_Q25		0

#define 	PIN_Q20			19
#define 	PIN_Q21			22
#define 	PIN_Q22			18
#define 	PIN_Q23			21
#define 	PIN_Q24			17
#define 	PIN_Q25			20

#define 	PORT_Z21		0
#define 	PORT_Z22		0
#define 	PORT_Z23		0
#define 	PIN_Z21			0
#define 	PIN_Z22			0
#define 	PIN_Z23			0
/*===================================================================*/

/*===========================[P11]===================================*/
#define 	PORT_Q30		2
#define 	PORT_Q31		2
#define 	PORT_Q32		2
#define 	PORT_Q33		2
#define 	PORT_Q34		2
#define 	PORT_Q35		2

#define 	PIN_Q30			3
#define 	PIN_Q31			0
#define 	PIN_Q32			4
#define 	PIN_Q33			1
#define 	PIN_Q34			5
#define 	PIN_Q35			2

#define 	PORT_Z31		0
#define 	PORT_Z32		0
#define 	PORT_Z33		0
#define 	PIN_Z31			0
#define 	PIN_Z32			0
#define 	PIN_Z33			0
/*===================================================================*/

#define 	PULS1 			18
#define 	PULS2 			1
#define 	PULS_PORT 		0

#define 	REBOTE_ 		100000
#define 	SALIDA			1
#define 	ENTRADA			0

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





struct StartParams_s {		// params for startup seq.
	long duration; 			// duration of accel phase of startup, us
	long periodRange[2]; 	// commutation period range for startup, us
	long powerRange[2];  	// frac of full power over startup accel
};

//FUNCIONES
//-----------------------------------------------------------------------------------------------

void PWM1_IRQHandler(void);
void InitPWM(unsigned int);
void InitGPIO(unsigned int);
void Stop_and_Default(unsigned int);
void Start_Up_Brushless(unsigned int);
void NextPWM(unsigned int);
void Zero_Detect(void);

