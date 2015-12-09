	/* Usamos sintaxis unificada */
	.syntax unified

	/* a partir de acá, todo a memoria de programa */
	.text

	/* declaramos símbolo global */
	.global asm_NextPWM_mot3

/* prototipo:
void asm_NextPWM_mot3(uint8_t *DutyCycle,uint8_t *DutyCycle0,uint8_t *Cycle,uint8_t *StepID,uint8_t *Count,uint8_t *MatchCount);
*/
	/* rutina de modo Thumb */
	.thumb_func

// Constantes

       	.equ PINSELx,  		0x4002C000			//La idea seria ir sumandole a este de a 4
       	.equ PINSEL0,  		0x4002C000			//Aca estan el P0.0-11 y P0.15
        .equ PINSEL1,  		0x4002C004			//Aca P0.16-30
       	.equ PINSEL2,  		0x4002C008			//Aca P1.0, P0.1, P1.4, P1.8-10, P1.14-15
        .equ PINSEL3,  		0x4002C00C			//Aca P1.16-31
        .equ PINSEL4,  		0x4002C010			//Aca P2.0-7

        .equ FIO0SET,      	0x2009C018			//Setea los pines
       	.equ FIO1SET,      	0x2009C038
       	.equ FIO2SET,      	0x2009C058
       	.equ FIO3SET,      	0x2009C078
       	.equ FIO4SET,      	0x2009C098

        .equ FIO0CLR,      	0x2009C01C			//Limpia los pines
        .equ FIO1CLR,      	0x2009C03C
        .equ FIO2CLR,      	0x2009C05C
        .equ FIO3CLR,      	0x2009C07C
        .equ FIO4CLR,      	0x2009C09C


		.equ MR3,			0x40018024			//Match Register 3.
		.equ MR4,			0x40018040			//Match Register 4.
		.equ MR5,			0x40018044			//Match Register 5.
		.equ MR6,			0x40018048			//Match Register 6.
		.equ PWM1LER,		0x40018050			//Para el LatchEnable del PWM (pines 3,4,5,6)

		.equ PIN0,			0x00200000			//Pin 22

		.equ DUTY,			0x00000096			//150 de DutyCycle

		.equ MATCH3,		0x00000008			//Para escribir en el registro de LER
												//00000000000000000000000000001000
		.equ MATCH4,		0x00000010			//Para escribir en el registro de LER
												//00000000000000000000000000010000
		.equ MATCH5,		0x00000020			//Para escribir en el registro de LER
												//00000000000000000000000000100000
		.equ MATCH6,		0x00000040			//Para escribir en el registro de LER
												//00000000000000000000000001000000


		.equ PINQ0,			0x00000008			//00000000000000000000000000001000
		.equ PINQ1,			0x00000001			//00000000000000000000000000000001
		.equ PINQ2,			0x00000010			//00000000000000000000000000010000
		.equ PINQ3,			0x00000002			//00000000000000000000000000000010
		.equ PINQ4,			0x00000020			//00000000000000000000000000100000
		.equ PINQ5,			0x00000004			//00000000000000000000000000000100



asm_NextPWM_mot3:
			push {lr}




/*

			//=======[PARA ESCRIBIR EN LOS PINES DE SALIDA]======

			ldr		r0,=FIO0SET
			ldr		r1,=PIN0

			str		r1,[r0,#0]					//Set P0.22
			str		r1,[r0,#4]					//Clear P0.22

			//===================================================



			//====[PARA RESETEAR EL CANAL DE PWM QUE QUIERO]=====

			//Para PWMSetMatch

			ldr		r2,=MR3
			ldr		r3,=DUTY

			str		r3,[r2]						//Set Match PWM 3 con DUTY cycle

			//Para PWMLatchEnable

			ldr		r4,=PWM1LER
			ldr		r5,=MATCH3

			str		r5,[r4]						//Habilito Latch de Match 3

			//===================================================


*/




			//=========[INICIO DEL CODIGO POSTA]=================


//			ldr		r0,=&DutyCycle				//Cargo con DutyCycle a r0 (hay que ver si se carga asi)
//			ldr		r1,=&DutyCycle0				//Lo mismo con DutyCylce0 a r1

//			ldr 	r6,=&Cycle					//Cargo Cycle en r6

//			cmp		[r0],[r1]					//Comparo DutyCycle con DutyCycle0

			ldr		r9,[r0]						//Cargo en r9 lo apuntado por r0 (!!!!)
			ldr		r10,[r1]					//Lo mismo


//			cmp		[r0],[r1]					//Comparo DutyCycle con DutyCycle0
			cmp		r9,r10						//Comparo DutyCycle con DutyCycle0

			beq		StepMotor					//Si DutyCycle = DutyCycle0, no actualizo el pwm
												//Si son distintos, lo hago

			push	{r2,r3,r4}					//Para usar los registros
//			ldr		r2,=MR6						//Cargo MR6 (para el motor0) en r2
			ldr		r2,=MR6						//Cargo MR6 (para el motor0) en r2

//			str		[r0],[r2]					//Set Match PWM 6 con DutyCycle
//			str		[r0],[r2]					//Set Match PWM 6 con DutyCycle
			str		r9,[r2]						//Set Match PWM 6 con DutyCycle

			//Para PWMLatchEnable

//			ldr		r3,=PWM1LER					//Cargo para el Latch Enable del canal
			ldr		r3,=PWM1LER					//Cargo para el Latch Enable del canal


//			ldr		r4,=MATCH6					//Es el bit para cargarle al Latch Enable
			ldr		r4,=MATCH6					//Es el bit para cargarle al Latch Enable


//			str		r4,[r3]						//Habilito Latch de Match 6
			str		r4,[r3]						//Habilito Latch de Match 6

			pop		{r2,r3,r4}
//			mov		[r1],[r0]					//Hago DutyCylce0 = DutyCycle
//			mov		[r1],[r0]					//Hago DutyCylce0 = DutyCycle

			str		r9,[r1]						//Hago DutyCylce0 = DutyCycle

StepMotor:

//			ldr		r0,=&StepID					//Cargo StepID en r0

//			ldr		r1,=FIO4SET					//Cargo el que es para el motor 3 (P2.0-5 necesito)
			ldr		r6,=FIO4SET					//Cargo el que es para el motor 3 (P2.0-5 necesito)

//			cmp		[r0],0						//Si es 0 (Seria para el StepID=0), no brancheo

			ldr		r11,[r3]
			cmp		r11,0						//Si es 0 (Seria para el StepID=0), no brancheo

			bne		Step1						//sino, salto a ver si es el siguiente



//			ldr		r2,=PINQ1
			ldr		r7,=PINQ1

//			str		r2,[r1,#4]					//Clear P2.0
			str		r7,[r6,#4]					//Clear P2.0

//			ldr		r2,=PINQ5
			ldr		r7,=PINQ5

			str		r7,[r6,#0]					//Set P2.2

			b		End

Step1:

//			cmp		[r0],1						//(StepID=1)
			cmp		r11,1						//(StepID=1)

			bne		Step2



//			ldr		r2,=PINQ2
			ldr		r7,=PINQ2

			str		r7,[r6,#4]					//Clear P2.4

//			mov		[r6],2						//Cargo Cycle = 2
//			mov		[r2],2						//Cargo Cycle = 2

			push	{r8}
			mov		r8,2
			str		r8,[r2]						//Cargo Cycle = 2
			pop		{r8}

			b		End


Step2:
//			cmp		r0,2						//(StepID=2)
//			cmp		[r3],2						//(StepID=2)
			cmp		r11,2						//(StepID=2)

			bne		Step3

//			ldr		r2,=PINQ3
			ldr		r7,=PINQ3

			str		r7,[r6,#4]					//Clear P2.1

//			ldr		r2,=PINQ1
			ldr		r7,=PINQ1

			str		r7,[r6,#0]					//Set P2.0

			b		End



Step3:
//			cmp		[r3],3						//(StepID=3)
			cmp		r11,3						//(StepID=3)

			bne		Step4


//			ldr		r2,=PINQ4
			ldr		r7,=PINQ4

			str		r7,[r6,#4]					//Clear P2.5

//			mov		[r6],0						//Cargo Cycle = 0
//			mov		[r2],0						//Cargo Cycle = 0


			push	{r8}
			mov		r8,0
			str		r8,[r2]						//Cargo Cycle = 0
			pop		{r8}

			b 		End


Step4:
//			cmp		r0,4						//(StepID=4)
//			cmp		[r3],4						//(StepID=4)
			cmp		r11,4						//(StepID=4)

			bne		Default


//			ldr		r2,=PINQ5
			ldr		r7,=PINQ5

			str		r7,[r6,#4]					//Clear P2.2

//			ldr		r2,=PINQ3
			ldr		r7,=PINQ3

			str		r7,[r6,#0]					//Set P2.1



			b		End


Default:
//			ldr		r2,=PINQ0
			ldr		r7,=PINQ0

			str		r7,[r6,#4]					//Clear P2.3

//			mov		[r6],1						//Cargo Cycle = 1
//			mov		[r2],1						//Cargo Cycle = 1

			push	{r8}
			mov		r8,1
			str		r8,[r2]						//Cargo Cycle = 1
			pop		{r8}

End:
//			cmp		r0,4
//			cmp		[r3],4
			cmp		r11,4

			bgt		RESET_STEPID				//Si StepID>4, salto a RESET_STEPID

												//Sino
//			add		[r0],1						//StepID++
//			add 	[r3],1						//StepID++

			add		r11,1						//StepID++

			str		r11,[r3]					//Guardo en la direccion de StepID

			b		EOF							//Salto a EOF


RESET_STEPID:

//			mov		[r0],0						//StepID=0
//			mov		[r3],0						//StepID=0

			mov		r11,0						//StepID=0

			str		r11,[r3]					//Lo cargo en su posicion de memoria

//			ldr		r6,=&Count					//Cargo Count en r6

//			add		[r6],1						//Count++
//			add		[r4],1						//Count++

			ldr		r12,[r4]
			add		r12,1
			str		r12,[r4]

EOF:

//			ldr		r7,=&MatchCount				//Cargo MatchCount en r7

//			mov		[r7],0						//MatchCount = 0
//			mov		[r5],0						//MatchCount = 0

			push	{r8}
			mov		r8,1
			str		r8,[r5]						//MatchCount = 0
			pop		{r8}


			pop {pc}

	.end
