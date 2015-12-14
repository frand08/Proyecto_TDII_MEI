#include "chip.h"
#include "ssp_17xx_40xx.h"
#include "SPI_RF.h"

void InitHardware()
{

	Chip_GPIO_WriteDirBit(LPC_GPIO, 0, 22, 1); //Led stick
	Chip_GPIO_WriteDirBit(LPC_GPIO, 0, 1, 1); //Puerto CE
	Chip_GPIO_SetPinOutLow(LPC_GPIO, 0, 1); //Puerto CE
	Chip_GPIO_SetPinOutLow(LPC_GPIO, 0, 22);
}

void InitSPI ()
{
    Chip_IOCON_PinMux(LPC_IOCON,TOUCH_E,IOCON_MODE_PULLUP,IOCON_FUNC0);
	Chip_GPIO_SetPinDIROutput(LPC_GPIO,TOUCH_E);
	Chip_IOCON_DisableOD(LPC_IOCON,TOUCH_E);
	Chip_GPIO_SetPinOutHigh(LPC_GPIO,TOUCH_E);

	Chip_IOCON_PinMux(LPC_IOCON,TOUCH_CLK,IOCON_MODE_INACT,IOCON_FUNC2);
	Chip_IOCON_PinMux(LPC_IOCON,TOUCH_MOSI,IOCON_MODE_INACT,IOCON_FUNC2);
	Chip_IOCON_PinMux(LPC_IOCON,TOUCH_MISO,IOCON_MODE_INACT,IOCON_FUNC2);

	Chip_Clock_EnablePeriphClock(SYSCTL_CLOCK_SSP0);
	Chip_SSP_Set_Mode(LPC_SSP0,SSP_MASTER_MODE);
	Chip_SSP_SetFormat(LPC_SSP0,SSP_BITS_8,SSP_FRAMEFORMAT_SPI,SSP_CLOCK_CPHA0_CPOL0);
	Chip_SSP_SetBitRate(LPC_SSP0,1000000 );
	Chip_SSP_Enable(LPC_SSP0);
}

uint8_t SPI_ReadWrite( uint8_t p)
{
    uint8_t rxBuf;
	Chip_SSP_DATA_SETUP_T data;

	Chip_GPIO_SetPinOutLow(LPC_GPIO, TOUCH_E);

	data.rx_data=&rxBuf;
	data.tx_data=&p;

	data.length=1;
	data.rx_cnt = 0;
	data.tx_cnt = 0;
	Chip_SSP_RWFrames_Blocking(LPC_SSP0,&data);

	//Chip_GPIO_SetPinOutHigh(LPC_GPIO,TOUCH_E);

	return rxBuf;
}
