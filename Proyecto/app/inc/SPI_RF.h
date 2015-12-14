
#define 		TOUCH_E				0,16
#define			TOUCH_MOSI			0,18
#define			TOUCH_MISO			0,17
#define			TOUCH_CLK			0,15

uint8_t SPI_ReadWrite(uint8_t);
void InitSPI (void);
void InitHardware(void);
