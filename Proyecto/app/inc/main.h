#ifndef _MAIN_H_
#define _MAIN_H_

/*==================[inclusions]=============================================*/


#include "board.h"
#include "chip.h"

#include "Defines.h"

#include "Estructuras_InitsIntGPIO.h"

#include "SPI_RF.h"
#include "nRF24L01.h"
#include "RF24.h"


/*==================[cplusplus]==============================================*/

#ifdef __cplusplus
extern "C" {
#endif

/*==================[macros]=================================================*/

/*==================[typedef]================================================*/

/*==================[external data declaration]==============================*/

/*==================[external functions declaration]=========================*/

/** @brief main function
 * @return main function should never return
 */
int main(void);

void SysTick_Handler(void);

/*==================[cplusplus]==============================================*/

#ifdef __cplusplus
}
#endif

/** @} doxygen end group definition */
/*==================[end of file]============================================*/
#endif /* #ifndef _MAIN_H_ */

