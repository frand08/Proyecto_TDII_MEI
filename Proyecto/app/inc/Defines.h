/*
 * Variables globales y puertos para controlar motores.
 *
 * PORT_Qa y PIN_Qa -> PWM
 * PORT_Qb y PIN_Qb -> Encendido digital
 */

//DEFINICIONES PUERTOS SALIDAS ENTRADAS
//-----------------------------------------------------------------------------------------------


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
void InitPWM(void);
void InitGPIO(void);
void Stop_and_Default(void);
void Start_Up_Brushless(void);
void NextPWM(void);
void Zero_Detect(void);

