/*
 * Variables globales y puertos para controlar motores.
 *
 * PORT_Qa y PIN_Qa -> PWM
 * PORT_Qb y PIN_Qb -> Encendido digital
 */

//DEFINICIONES PUERTOS SALIDAS ENTRADAS
//-----------------------------------------------------------------------------------------------


#define 	PORT_Q10		1//3//0//2//1//1
#define 	PORT_Q11		0//0//0//2//0//1
#define 	PORT_Q12		1//0//0//2//1//1
#define 	PORT_Q13		1//0//0//2//1//1
#define 	PORT_Q14		1//0//0//2//1//1
#define 	PORT_Q15		1//3//0//2//1//1

#define 	PIN_Q10			26//25//20//2//26//24
#define 	PIN_Q11			10//28//17//5//10//26
#define 	PIN_Q12			25//29//21//1//25//21
#define 	PIN_Q13			28//27//18//4//28//23
#define 	PIN_Q14			24//30//22//0//24//18
#define 	PIN_Q15			27//26//19//3//27//20
#define 	PORT_Z11		1
#define 	PORT_Z12		1
#define 	PORT_Z13		1
#define 	PIN_Z11			19
#define 	PIN_Z12			22
#define 	PIN_Z13			25

#define 	PORT_Q20		3//0//2//1//1
#define 	PORT_Q21		0//0//2//0//1
#define 	PORT_Q22		0//0//2//1//1
#define 	PORT_Q23		0//0//2//1//1
#define 	PORT_Q24		0//0//2//1//1
#define 	PORT_Q25		3//0//2//1//1

#define 	PIN_Q20			25//20//2//26//24
#define 	PIN_Q21			28//17//5//10//26
#define 	PIN_Q22			29//21//1//25//21
#define 	PIN_Q23			27//18//4//28//23
#define 	PIN_Q24			30//22//0//24//18
#define 	PIN_Q25			26//19//3//27//20
#define 	PORT_Z21		1
#define 	PORT_Z22		1
#define 	PORT_Z23		1
#define 	PIN_Z21			19
#define 	PIN_Z22			22
#define 	PIN_Z23			25



#define 	PULS1 			18
#define 	PULS2 			1
#define 	PULS_PORT 		0

#define 	REBOTE_ 		100000
#define 	SALIDA			1

/*========[Prueba para ver por que no andan los pines]=========*/


#define 	PORT_NOANDA1	1
#define 	PORT_NOANDA2	1
#define 	PORT_NOANDA3	0
#define 	PIN_NOANDA1		27
#define 	PIN_NOANDA2		25
#define 	PIN_NOANDA3		25



/*=============================================================*/

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
void InitGPIO(uint8_t);
void Stop_and_Default(uint8_t);
void Start_Up_Brushless(uint8_t);
void NextPWM(uint8_t);
void Zero_Detect(void);

