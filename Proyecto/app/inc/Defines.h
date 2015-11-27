/*
 * Variables globales y puertos para controlar motores.
 *
 * PORT_Qa y PIN_Qa -> PWM
 * PORT_Qb y PIN_Qb -> Encendido digital
 */

//DEFINICIONES PUERTOS SALIDAS ENTRADAS
//-----------------------------------------------------------------------------------------------
#define PORT_Q1		1
#define PORT_Q2		1
#define PORT_Q3		1
#define PORT_Q4		1
#define PORT_Q5		1
#define PORT_Q0		1
#define PIN_Q0		24
#define PIN_Q1		26
#define PIN_Q2		21
#define PIN_Q3		23
#define PIN_Q4		18
#define PIN_Q5		20
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

//FUNCIONES
//-----------------------------------------------------------------------------------------------

void PWM1_IRQHandler(void);
void InitPWM(void);
void InitGPIO(void);
void Stop_and_Default(void);
void Start_Up_Brushless(void);
void NextPWM(void);
void Zero_Detect(void);

