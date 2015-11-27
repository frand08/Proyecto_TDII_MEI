/*
 * pwm_17xx_40xx.c
 *
 *  Created on: Apr 17, 2014
 *      Author: Özen Özkaya
 */

#include "chip.h"
#include <stdint.h>
/*****************************************************************************
 * Private types/enumerations/variables
 ****************************************************************************/

/*****************************************************************************
 * Public types/enumerations/variables
 ****************************************************************************/

/*****************************************************************************
 * Private functions
 ****************************************************************************/

/* Returns clock for the peripheral block */
STATIC CHIP_SYSCTL_CLOCK_T Chip_Pwm_GetClockIndex(LPC_PWM_T *pTMR)
{
        CHIP_SYSCTL_CLOCK_T clkTMR;

        if (pTMR == LPC_PWM1) {
                clkTMR = SYSCTL_CLOCK_PWM1;
        }

        return clkTMR;
}

/*****************************************************************************
 * Public functions
 ****************************************************************************/

/* Initialize a pwm */
void Chip_PWM_Init(LPC_PWM_T *pTMR)
{
        Chip_Clock_EnablePeriphClock(Chip_Pwm_GetClockIndex(pTMR));
}

/*      Shutdown a pwm */
void Chip_PWM_DeInit(LPC_PWM_T *pTMR)
{
        Chip_Clock_DisablePeriphClock(Chip_Pwm_GetClockIndex(pTMR));
}

/* Resets the timer terminal and prescale counts to 0 */
void Chip_PWM_Reset(LPC_PWM_T *pTMR)
{
        uint32_t reg;

        /* Disable timer, set terminal count to non-0 */
        reg = pTMR->TCR;
        pTMR->TCR = 0;
        pTMR->TC = 1;

        /* Reset timer counter */
        pTMR->TCR |= PWM_RESET;

        /* Wait for terminal count to clear */
//        while (pTMR->TC != 0) {}

        /* Restore timer state */
        pTMR->TCR = reg;
}

void Chip_PWM_SetControlMode(LPC_PWM_T *pTMR, uint8_t pwmChannel,PWM_EDGE_CONTROL_MODE pwmEdgeMode, PWM_OUT_CMD pwmCmd )
{
    if(pwmChannel)
    {
        if(pwmCmd)
        {
            pTMR->PCR |= (1<<(pwmChannel+8));
        }
        else
        {
            pTMR->PCR &= ~(1<<(pwmChannel+8));
        }

        if(pwmEdgeMode==PWM_DOUBLE_EDGE_CONTROL_MODE)
        {
            pTMR->PCR |= (1<<(pwmChannel));
        }
        else
        {
            pTMR->PCR &= ~(1<<(pwmChannel));
        }
    }
}

void Chip_PWM_LatchEnable(LPC_PWM_T *pTMR, uint8_t pwmChannel, PWM_OUT_CMD pwmCmd )
{

        if(pwmCmd)
        {
            pTMR->LER |= (1<<(pwmChannel));
        }
        else
        {
            pTMR->LER &= ~(1<<(pwmChannel));
        }
}
