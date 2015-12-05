//ESTRUCTURAS


//IOIntStatus: Indica la presencia de interrupciones pendientes en todos los puertos GPIO
typedef struct
{
	volatile uint32_t	_P0Int:1;
	volatile uint32_t	_RESERVED0:1;
	volatile uint32_t	_P2Int:1;
	volatile uint32_t 	_RESERVED1:29;
} IOIntStatus_t;

#define 	IOIntStatus		((IOIntStatus_t *)		(0x40028080UL))

#define		P0Int		IOIntStatus->_P0Int
#define 	P2Int		IOIntStatus->_P2Int



//IO0IntEnR: Habilita el rising-edge de cada pin del Puerto 0
typedef struct
{
	volatile uint32_t	_P0_0ER:1;
	volatile uint32_t	_P0_1ER:1;
	volatile uint32_t	_P0_2ER:1;
	volatile uint32_t	_P0_3ER:1;
	volatile uint32_t	_P0_4ER:1;
	volatile uint32_t	_P0_5ER:1;
	volatile uint32_t	_P0_6ER:1;
	volatile uint32_t	_P0_7ER:1;
	volatile uint32_t	_P0_8ER:1;
	volatile uint32_t	_P0_9ER:1;
	volatile uint32_t	_P0_10ER:1;
	volatile uint32_t	_P0_11ER:1;
	volatile uint32_t	_RESERVED0:3;
	volatile uint32_t	_P0_15ER:1;
	volatile uint32_t	_P0_16ER:1;
	volatile uint32_t	_P0_17ER:1;
	volatile uint32_t	_P0_18ER:1;
	volatile uint32_t	_P0_19ER:1;
	volatile uint32_t	_P0_20ER:1;
	volatile uint32_t	_P0_21ER:1;
	volatile uint32_t	_P0_22ER:1;
	volatile uint32_t	_P0_23ER:1;
	volatile uint32_t	_P0_24ER:1;
	volatile uint32_t	_P0_25ER:1;
	volatile uint32_t	_P0_26ER:1;
	volatile uint32_t	_P0_27ER:1;
	volatile uint32_t	_P0_28ER:1;
	volatile uint32_t	_P0_29ER:1;
	volatile uint32_t	_P0_30ER:1;
	volatile uint32_t	_RESERVED1:1;
} IO0IntEnR_t;

#define 	IO0IntEnR		((IO0IntEnR_t *) 		(0x40028090UL))

#define		P0_0ER			IO0IntEnR->_P0_0ER
#define		P0_1ER			IO0IntEnR->_P0_1ER
#define		P0_2ER			IO0IntEnR->_P0_2ER
#define		P0_3ER			IO0IntEnR->_P0_3ER
#define		P0_4ER			IO0IntEnR->_P0_4ER
#define		P0_5ER			IO0IntEnR->_P0_5ER
#define		P0_6ER			IO0IntEnR->_P0_6ER
#define		P0_7ER			IO0IntEnR->_P0_7ER
#define		P0_8ER			IO0IntEnR->_P0_8ER
#define		P0_9ER			IO0IntEnR->_P0_9ER
#define		P0_10ER			IO0IntEnR->_P0_10ER
#define		P0_11ER			IO0IntEnR->_P0_10ER
#define		P0_15ER			IO0IntEnR->_P0_15ER
#define		P0_16ER			IO0IntEnR->_P0_16ER
#define		P0_17ER			IO0IntEnR->_P0_17ER
#define		P0_18ER			IO0IntEnR->_P0_18ER
#define		P0_19ER			IO0IntEnR->_P0_19ER
#define		P0_20ER			IO0IntEnR->_P0_20ER
#define		P0_21ER			IO0IntEnR->_P0_21ER
#define		P0_22ER			IO0IntEnR->_P0_22ER
#define		P0_23ER			IO0IntEnR->_P0_23ER
#define		P0_24ER			IO0IntEnR->_P0_24ER
#define		P0_25ER			IO0IntEnR->_P0_25ER
#define		P0_26ER			IO0IntEnR->_P0_26ER
#define		P0_27ER			IO0IntEnR->_P0_27ER
#define		P0_28ER			IO0IntEnR->_P0_28ER
#define		P0_29ER			IO0IntEnR->_P0_29ER
#define		P0_30ER			IO0IntEnR->_P0_30ER



//IO2IntEnR: Habilita el rising-edge de cada pin del Puerto 2
typedef struct
{
	volatile uint32_t	_P2_0ER:1;
	volatile uint32_t	_P2_1ER:1;
	volatile uint32_t	_P2_2ER:1;
	volatile uint32_t	_P2_3ER:1;
	volatile uint32_t	_P2_4ER:1;
	volatile uint32_t	_P2_5ER:1;
	volatile uint32_t	_P2_6ER:1;
	volatile uint32_t	_P2_7ER:1;
	volatile uint32_t	_P2_8ER:1;
	volatile uint32_t	_P2_9ER:1;
	volatile uint32_t	_P2_10ER:1;
	volatile uint32_t	_P2_11ER:1;
	volatile uint32_t	_P0_12ER:1;
	volatile uint32_t	_P0_13ER:1;
	volatile uint32_t	_RESERVED:18;
} IO2IntEnR_t;

#define 	IO2IntEnR		((IO2IntEnR_t *) 		(0x400280B0UL))

#define		P2_0ER			IO2IntEnR->_P2_0ER
#define		P2_1ER			IO2IntEnR->_P2_1ER
#define		P2_2ER			IO2IntEnR->_P2_2ER
#define		P2_3ER			IO2IntEnR->_P2_3ER
#define		P2_4ER			IO2IntEnR->_P2_4ER
#define		P2_5ER			IO2IntEnR->_P2_5ER
#define		P2_6ER			IO2IntEnR->_P2_6ER
#define		P2_7ER			IO2IntEnR->_P2_7ER
#define		P2_8ER			IO2IntEnR->_P2_8ER
#define		P2_9ER			IO2IntEnR->_P2_9ER
#define		P2_10ER			IO2IntEnR->_P2_10ER
#define		P2_11ER			IO2IntEnR->_P2_11ER
#define		P2_12ER			IO2IntEnR->_P2_12ER
#define		P2_13ER			IO2IntEnR->_P2_13ER



//IO0IntEnF: Habilita el falling-edge de cada pin del Puerto 0
typedef struct
{
	volatile uint32_t	_P0_0EF:1;
	volatile uint32_t	_P0_1EF:1;
	volatile uint32_t	_P0_2EF:1;
	volatile uint32_t	_P0_3EF:1;
	volatile uint32_t	_P0_4EF:1;
	volatile uint32_t	_P0_5EF:1;
	volatile uint32_t	_P0_6EF:1;
	volatile uint32_t	_P0_7EF:1;
	volatile uint32_t	_P0_8EF:1;
	volatile uint32_t	_P0_9EF:1;
	volatile uint32_t	_P0_10EF:1;
	volatile uint32_t	_P0_11EF:1;
	volatile uint32_t	_RESERVED0:3;
	volatile uint32_t	_P0_15EF:1;
	volatile uint32_t	_P0_16EF:1;
	volatile uint32_t	_P0_17EF:1;
	volatile uint32_t	_P0_18EF:1;
	volatile uint32_t	_P0_19EF:1;
	volatile uint32_t	_P0_20EF:1;
	volatile uint32_t	_P0_21EF:1;
	volatile uint32_t	_P0_22EF:1;
	volatile uint32_t	_P0_23EF:1;
	volatile uint32_t	_P0_24EF:1;
	volatile uint32_t	_P0_25EF:1;
	volatile uint32_t	_P0_26EF:1;
	volatile uint32_t	_P0_27EF:1;
	volatile uint32_t	_P0_28EF:1;
	volatile uint32_t	_P0_29EF:1;
	volatile uint32_t	_P0_30EF:1;
	volatile uint32_t	_RESERVED1:1;
} IO0IntEnF_t;

#define 	IO0IntEnF		((IO0IntEnF_t *) 		(0x40028094UL))

#define		P0_0EF			IO0IntEnF->_P0_0EF
#define		P0_1EF			IO0IntEnF->_P0_1EF
#define		P0_2EF			IO0IntEnF->_P0_2EF
#define		P0_3EF			IO0IntEnF->_P0_3EF
#define		P0_4EF			IO0IntEnF->_P0_4EF
#define		P0_5EF			IO0IntEnF->_P0_5EF
#define		P0_6EF			IO0IntEnF->_P0_6EF
#define		P0_7EF			IO0IntEnF->_P0_7EF
#define		P0_8EF			IO0IntEnF->_P0_8EF
#define		P0_9EF			IO0IntEnF->_P0_9EF
#define		P0_10EF			IO0IntEnF->_P0_10EF
#define		P0_11EF			IO0IntEnF->_P0_11EF
#define		P0_15EF			IO0IntEnF->_P0_15EF
#define		P0_16EF			IO0IntEnF->_P0_16EF
#define		P0_17EF			IO0IntEnF->_P0_17EF
#define		P0_18EF			IO0IntEnF->_P0_18EF
#define		P0_19EF			IO0IntEnF->_P0_19EF
#define		P0_20EF			IO0IntEnF->_P0_20EF
#define		P0_21EF			IO0IntEnF->_P0_21EF
#define		P0_22EF			IO0IntEnF->_P0_22EF
#define		P0_23EF			IO0IntEnF->_P0_23EF
#define		P0_24EF			IO0IntEnF->_P0_24EF
#define		P0_25EF			IO0IntEnF->_P0_25EF
#define		P0_26EF			IO0IntEnF->_P0_26EF
#define		P0_27EF			IO0IntEnF->_P0_27EF
#define		P0_28EF			IO0IntEnF->_P0_28EF
#define		P0_29EF			IO0IntEnF->_P0_29EF
#define		P0_30EF			IO0IntEnF->_P0_30EF



//IO2IntEnF: Habilita el falling-edge de cada pin del Puerto 2
typedef struct
{
	volatile uint32_t	_P2_0EF:1;
	volatile uint32_t	_P2_1EF:1;
	volatile uint32_t	_P2_2EF:1;
	volatile uint32_t	_P2_3EF:1;
	volatile uint32_t	_P2_4EF:1;
	volatile uint32_t	_P2_5EF:1;
	volatile uint32_t	_P2_6EF:1;
	volatile uint32_t	_P2_7EF:1;
	volatile uint32_t	_P2_8EF:1;
	volatile uint32_t	_P2_9EF:1;
	volatile uint32_t	_P2_10EF:1;
	volatile uint32_t	_P2_11EF:1;
	volatile uint32_t	_P0_12EF:1;
	volatile uint32_t	_P0_13EF:1;
	volatile uint32_t	_RESERVED:18;
} IO2IntEnF_t;

#define 	IO2IntEnF		((IO2IntEnF_t *) 		(0x400280B4UL))

#define		P2_0EF			IO2IntEnF->_P2_0EF
#define		P2_1EF			IO2IntEnF->_P2_1EF
#define		P2_2EF			IO2IntEnF->_P2_2EF
#define		P2_3EF			IO2IntEnF->_P2_3EF
#define		P2_4EF			IO2IntEnF->_P2_4EF
#define		P2_5EF			IO2IntEnF->_P2_5EF
#define		P2_6EF			IO2IntEnF->_P2_6EF
#define		P2_7EF			IO2IntEnF->_P2_7EF
#define		P2_8EF			IO2IntEnF->_P2_8EF
#define		P2_9EF			IO2IntEnF->_P2_9EF
#define		P2_10EF			IO2IntEnF->_P2_10EF
#define		P2_11EF			IO2IntEnF->_P2_11EF
#define		P2_12EF			IO2IntEnF->_P2_12EF
#define		P2_13EF			IO2IntEnF->_P2_13EF



//IO0IntStatR: Indica el estado de la interrupcion por rising-edge de cada pin del puerto 0
typedef struct
{
	volatile uint32_t	_P0_0REI:1;
	volatile uint32_t	_P0_1REI:1;
	volatile uint32_t	_P0_2REI:1;
	volatile uint32_t	_P0_3REI:1;
	volatile uint32_t	_P0_4REI:1;
	volatile uint32_t	_P0_5REI:1;
	volatile uint32_t	_P0_6REI:1;
	volatile uint32_t	_P0_7REI:1;
	volatile uint32_t	_P0_8REI:1;
	volatile uint32_t	_P0_9REI:1;
	volatile uint32_t	_P0_10REI:1;
	volatile uint32_t	_P0_11REI:1;
	volatile uint32_t	_RESERVED0:3;
	volatile uint32_t	_P0_15REI:1;
	volatile uint32_t	_P0_16REI:1;
	volatile uint32_t	_P0_17REI:1;
	volatile uint32_t	_P0_18REI:1;
	volatile uint32_t	_P0_19REI:1;
	volatile uint32_t	_P0_20REI:1;
	volatile uint32_t	_P0_21REI:1;
	volatile uint32_t	_P0_22REI:1;
	volatile uint32_t	_P0_23REI:1;
	volatile uint32_t	_P0_24REI:1;
	volatile uint32_t	_P0_25REI:1;
	volatile uint32_t	_P0_26REI:1;
	volatile uint32_t	_P0_27REI:1;
	volatile uint32_t	_P0_28REI:1;
	volatile uint32_t	_P0_29REI:1;
	volatile uint32_t	_P0_30REI:1;
	volatile uint32_t	_RESERVED1:1;
} IO0IntStatR_t;

#define		IO0IntStatR		((IO0IntStatR_t *) 		(0x40028084UL))

#define		P0_0REI			IO0IntStatR->_P0_0REI
#define		P0_1REI			IO0IntStatR->_P1_1REI
#define		P0_2REI			IO0IntStatR->_P2_2REI
#define		P0_3REI			IO0IntStatR->_P3_3REI
#define		P0_4REI			IO0IntStatR->_P4_4REI
#define		P0_5REI			IO0IntStatR->_P5_5REI
#define		P0_6REI			IO0IntStatR->_P6_6REI
#define		P0_7REI			IO0IntStatR->_P7_7REI
#define		P0_8REI			IO0IntStatR->_P8_8REI
#define		P0_9REI			IO0IntStatR->_P9_9REI
#define		P0_10REI		IO0IntStatR->_P10_10REI
#define		P0_11REI		IO0IntStatR->_P11_11REI
#define		P0_15REI		IO0IntStatR->_P15_15REI
#define		P0_16REI		IO0IntStatR->_P16_16REI
#define		P0_17REI		IO0IntStatR->_P17_17REI
#define		P0_18REI		IO0IntStatR->_P18_18REI
#define		P0_19REI		IO0IntStatR->_P19_19REI
#define		P0_20REI		IO0IntStatR->_P20_20REI
#define		P0_21REI		IO0IntStatR->_P21_21REI
#define		P0_22REI		IO0IntStatR->_P22_22REI
#define		P0_23REI		IO0IntStatR->_P23_23REI
#define		P0_24REI		IO0IntStatR->_P24_24REI
#define		P0_25REI		IO0IntStatR->_P25_25REI
#define		P0_26REI		IO0IntStatR->_P26_26REI
#define		P0_27REI		IO0IntStatR->_P27_27REI
#define		P0_28REI		IO0IntStatR->_P28_28REI
#define		P0_29REI		IO0IntStatR->_P29_29REI
#define		P0_30REI		IO0IntStatR->_P30_30REI



//IO2IntStatR: Indica el estado de la interrupcion por rising-edge de cada pin del puerto 2
typedef struct
{
	volatile uint32_t	_P2_0REI:1;
	volatile uint32_t	_P2_1REI:1;
	volatile uint32_t	_P2_2REI:1;
	volatile uint32_t	_P2_3REI:1;
	volatile uint32_t	_P2_4REI:1;
	volatile uint32_t	_P2_5REI:1;
	volatile uint32_t	_P2_6REI:1;
	volatile uint32_t	_P2_7REI:1;
	volatile uint32_t	_P2_8REI:1;
	volatile uint32_t	_P2_9REI:1;
	volatile uint32_t	_P2_10REI:1;
	volatile uint32_t	_P2_11REI:1;
	volatile uint32_t	_P2_12REI:1;
	volatile uint32_t	_P2_13REI:1;
	volatile uint32_t	_RESERVED:18;
} IO2IntStatR_t;

#define 	IO2IntStatR		((IO2IntStatR_t *) 		(0x400280A4UL))

#define		P2_0REI			IO2IntStatR->_P2_0REI
#define		P2_1REI			IO2IntStatR->_P2_1REI
#define		P2_2REI			IO2IntStatR->_P2_2REI
#define		P2_3REI			IO2IntStatR->_P2_3REI
#define		P2_4REI			IO2IntStatR->_P2_4REI
#define		P2_5REI			IO2IntStatR->_P2_5REI
#define		P2_6REI			IO2IntStatR->_P2_6REI
#define		P2_7REI			IO2IntStatR->_P2_7REI
#define		P2_8REI			IO2IntStatR->_P2_8REI
#define		P2_9REI			IO2IntStatR->_P2_9REI
#define		P2_10REI		IO2IntStatR->_P2_10REI
#define		P2_11REI		IO2IntStatR->_P2_11REI
#define		P2_12REI		IO2IntStatR->_P2_12REI
#define		P2_13REI		IO2IntStatR->_P2_13REI



//IO0IntStatF: Indica el estado de la interrupcion por falling-edge de cada pin del puerto 0
typedef struct
{
	volatile uint32_t	_P0_0FEI:1;
	volatile uint32_t	_P0_1FEI:1;
	volatile uint32_t	_P0_2FEI:1;
	volatile uint32_t	_P0_3FEI:1;
	volatile uint32_t	_P0_4FEI:1;
	volatile uint32_t	_P0_5FEI:1;
	volatile uint32_t	_P0_6FEI:1;
	volatile uint32_t	_P0_7FEI:1;
	volatile uint32_t	_P0_8FEI:1;
	volatile uint32_t	_P0_9FEI:1;
	volatile uint32_t	_P0_10FEI:1;
	volatile uint32_t	_P0_11FEI:1;
	volatile uint32_t	_RESERVED0:3;
	volatile uint32_t	_P0_15FEI:1;
	volatile uint32_t	_P0_16FEI:1;
	volatile uint32_t	_P0_17FEI:1;
	volatile uint32_t	_P0_18FEI:1;
	volatile uint32_t	_P0_19FEI:1;
	volatile uint32_t	_P0_20FEI:1;
	volatile uint32_t	_P0_21FEI:1;
	volatile uint32_t	_P0_22FEI:1;
	volatile uint32_t	_P0_23FEI:1;
	volatile uint32_t	_P0_24FEI:1;
	volatile uint32_t	_P0_25FEI:1;
	volatile uint32_t	_P0_26FEI:1;
	volatile uint32_t	_P0_27FEI:1;
	volatile uint32_t	_P0_28FEI:1;
	volatile uint32_t	_P0_29FEI:1;
	volatile uint32_t	_P0_30FEI:1;
	volatile uint32_t	_RESERVED1:1;
} IO0IntStatF_t;

#define		IO0IntStatF		((IO0IntStatF_t *) 		(0x40028088UL))

#define		P0_0FEI			IO0IntStatF->_P0_0FEI
#define		P0_1FEI			IO0IntStatF->_P0_1FEI
#define		P0_2FEI			IO0IntStatF->_P0_2FEI
#define		P0_3FEI			IO0IntStatF->_P0_3FEI
#define		P0_4FEI			IO0IntStatF->_P0_4FEI
#define		P0_5FEI			IO0IntStatF->_P0_5FEI
#define		P0_6FEI			IO0IntStatF->_P0_6FEI
#define		P0_7FEI			IO0IntStatF->_P0_7FEI
#define		P0_8FEI			IO0IntStatF->_P0_8FEI
#define		P0_9FEI			IO0IntStatF->_P0_9FEI
#define		P0_10FEI		IO0IntStatF->_P0_10FEI
#define		P0_11FEI		IO0IntStatF->_P0_11FEI
#define		P0_15FEI		IO0IntStatF->_P0_15FEI
#define		P0_16FEI		IO0IntStatF->_P0_16FEI
#define		P0_17FEI		IO0IntStatF->_P0_17FEI
#define		P0_18FEI		IO0IntStatF->_P0_18FEI
#define		P0_19FEI		IO0IntStatF->_P0_19FEI
#define		P0_20FEI		IO0IntStatF->_P0_20FEI
#define		P0_21FEI		IO0IntStatF->_P0_21FEI
#define		P0_22FEI		IO0IntStatF->_P0_22FEI
#define		P0_23FEI		IO0IntStatF->_P0_23FEI
#define		P0_24FEI		IO0IntStatF->_P0_24FEI
#define		P0_25FEI		IO0IntStatF->_P0_25FEI
#define		P0_26FEI		IO0IntStatF->_P0_26FEI
#define		P0_27FEI		IO0IntStatF->_P0_27FEI
#define		P0_28FEI		IO0IntStatF->_P0_28FEI
#define		P0_29FEI		IO0IntStatF->_P0_29FEI
#define		P0_30FEI		IO0IntStatF->_P0_30FEI



//IO2IntStatF: Indica el estado de la interrupcion por falling-edge de cada pin del puerto 2
typedef struct
{
	volatile uint32_t	_P2_0FEI:1;
	volatile uint32_t	_P2_1FEI:1;
	volatile uint32_t	_P2_2FEI:1;
	volatile uint32_t	_P2_3FEI:1;
	volatile uint32_t	_P2_4FEI:1;
	volatile uint32_t	_P2_5FEI:1;
	volatile uint32_t	_P2_6FEI:1;
	volatile uint32_t	_P2_7FEI:1;
	volatile uint32_t	_P2_8FEI:1;
	volatile uint32_t	_P2_9FEI:1;
	volatile uint32_t	_P2_10FEI:1;
	volatile uint32_t	_P2_11FEI:1;
	volatile uint32_t	_P2_12FEI:1;
	volatile uint32_t	_P2_13FEI:1;
	volatile uint32_t	_RESERVED:18;
} IO2IntStatF_t;

#define		IO2IntStatF		((IO2IntStatF_t *) 		(0x400280A8UL))

#define		P2_0FEI			IO2IntStatF->_P2_0FEI
#define		P2_1FEI			IO2IntStatF->_P2_1FEI
#define		P2_2FEI			IO2IntStatF->_P2_2FEI
#define		P2_3FEI			IO2IntStatF->_P2_3FEI
#define		P2_4FEI			IO2IntStatF->_P2_4FEI
#define		P2_5FEI			IO2IntStatF->_P2_5FEI
#define		P2_6FEI			IO2IntStatF->_P2_6FEI
#define		P2_7FEI			IO2IntStatF->_P2_7FEI
#define		P2_8FEI			IO2IntStatF->_P2_8FEI
#define		P2_9FEI			IO2IntStatF->_P2_9FEI
#define		P2_10FEI		IO2IntStatF->_P2_10FEI
#define		P2_11FEI		IO2IntStatF->_P2_11FEI
#define		P2_12FEI		IO2IntStatF->_P2_12FEI
#define		P2_13FEI		IO2IntStatF->_P2_13FEI




//IO0IntClr: Limpia la interrupcion del pin del puerto 0
typedef struct
{
	volatile uint32_t	_P0_0CI:1;
	volatile uint32_t	_P0_1CI:1;
	volatile uint32_t	_P0_2CI:1;
	volatile uint32_t	_P0_3CI:1;
	volatile uint32_t	_P0_4CI:1;
	volatile uint32_t	_P0_5CI:1;
	volatile uint32_t	_P0_6CI:1;
	volatile uint32_t	_P0_7CI:1;
	volatile uint32_t	_P0_8CI:1;
	volatile uint32_t	_P0_9CI:1;
	volatile uint32_t	_P0_10CI:1;
	volatile uint32_t	_P0_11CI:1;
	volatile uint32_t	_RESERVED0:3;
	volatile uint32_t	_P0_15CI:1;
	volatile uint32_t	_P0_16CI:1;
	volatile uint32_t	_P0_17CI:1;
	volatile uint32_t	_P0_18CI:1;
	volatile uint32_t	_P0_19CI:1;
	volatile uint32_t	_P0_20CI:1;
	volatile uint32_t	_P0_21CI:1;
	volatile uint32_t	_P0_22CI:1;
	volatile uint32_t	_P0_23CI:1;
	volatile uint32_t	_P0_24CI:1;
	volatile uint32_t	_P0_25CI:1;
	volatile uint32_t	_P0_26CI:1;
	volatile uint32_t	_P0_27CI:1;
	volatile uint32_t	_P0_28CI:1;
	volatile uint32_t	_P0_29CI:1;
	volatile uint32_t	_P0_30CI:1;
	volatile uint32_t	_RESERVED1:1;
} IO0IntClr_t;

#define		IO0IntClr		((IO0IntClr_t *) 		(0x4002808CUL))

#define		P0_0CI			IO0IntClr->_P0_0CI
#define		P0_1CI			IO0IntClr->_P0_1CI
#define		P0_2CI			IO0IntClr->_P0_2CI
#define		P0_3CI			IO0IntClr->_P0_3CI
#define		P0_4CI			IO0IntClr->_P0_4CI
#define		P0_5CI			IO0IntClr->_P0_5CI
#define		P0_6CI			IO0IntClr->_P0_6CI
#define		P0_7CI			IO0IntClr->_P0_7CI
#define		P0_8CI			IO0IntClr->_P0_8CI
#define		P0_9CI			IO0IntClr->_P0_9CI
#define		P0_10CI			IO0IntClr->_P0_10CI
#define		P0_11CI			IO0IntClr->_P0_11CI
#define		P0_15CI			IO0IntClr->_P0_15CI
#define		P0_16CI			IO0IntClr->_P0_16CI
#define		P0_17CI			IO0IntClr->_P0_17CI
#define		P0_18CI			IO0IntClr->_P0_18CI
#define		P0_19CI			IO0IntClr->_P0_19CI
#define		P0_20CI			IO0IntClr->_P0_20CI
#define		P0_21CI			IO0IntClr->_P0_21CI
#define		P0_22CI			IO0IntClr->_P0_22CI
#define		P0_23CI			IO0IntClr->_P0_23CI
#define		P0_24CI			IO0IntClr->_P0_24CI
#define		P0_25CI			IO0IntClr->_P0_25CI
#define		P0_26CI			IO0IntClr->_P0_26CI
#define		P0_27CI			IO0IntClr->_P0_27CI
#define		P0_28CI			IO0IntClr->_P0_28CI
#define		P0_29CI			IO0IntClr->_P0_29CI
#define		P0_30CI			IO0IntClr->_P0_30CI



//IO2IntClr: Limpia la interrupcion del pin del puerto 2
typedef struct
{
	volatile uint32_t	_P2_0CI:1;
	volatile uint32_t	_P2_1CI:1;
	volatile uint32_t	_P2_2CI:1;
	volatile uint32_t	_P2_3CI:1;
	volatile uint32_t	_P2_4CI:1;
	volatile uint32_t	_P2_5CI:1;
	volatile uint32_t	_P2_6CI:1;
	volatile uint32_t	_P2_7CI:1;
	volatile uint32_t	_P2_8CI:1;
	volatile uint32_t	_P2_9CI:1;
	volatile uint32_t	_P2_10CI:1;
	volatile uint32_t	_P2_11CI:1;
	volatile uint32_t	_P2_12CI:1;
	volatile uint32_t	_P2_13CI:1;
	volatile uint32_t	_RESERVED:18;
} IO2IntClr_t;

#define 	IO2IntClr		((IO2IntClr_t *) 		(0x400280ACUL))

#define		P2_0CI			IO2IntClr->_P2_0CI
#define		P2_1CI			IO2IntClr->_P2_1CI
#define		P2_2CI			IO2IntClr->_P2_2CI
#define		P2_3CI			IO2IntClr->_P2_3CI
#define		P2_4CI			IO2IntClr->_P2_4CI
#define		P2_5CI			IO2IntClr->_P2_5CI
#define		P2_6CI			IO2IntClr->_P2_6CI
#define		P2_7CI			IO2IntClr->_P2_7CI
#define		P2_8CI			IO2IntClr->_P2_8CI
#define		P2_9CI			IO2IntClr->_P2_9CI
#define		P2_10CI			IO2IntClr->_P2_10CI
#define		P2_11CI			IO2IntClr->_P2_11CI
#define		P2_12CI			IO2IntClr->_P2_12CI
#define		P2_13CI			IO2IntClr->_P2_13CI




//----------------------------
