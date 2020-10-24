/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "project.h"
#include "InterruptRoutines.h"
#include <stdio.h>

#define ON 1


int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    UART_Start();
    ADC_DelSig_Start();
    Timer_Start();
    PWM_LED_Start();
    
    flag_timer = 0;
    value_digit = 0;
    value_mv = 0;
    int32 dc[2] = {0};
    
    isr_Timer_StartEx(Custom_ISR_Timer);

    //Pin_LED_Write(ON);
    ADC_DelSig_StartConvert();
    
    PWM_LED_WriteCompare(0);
    

    for(;;)
    {
        if(flag_timer) {
            dc[0] = dc[1];
            UART_PutString(DataBuffer);
            flag_timer = 0;
            dc[1] = value_digit/65535*100;
            if((dc[1] >= dc[0]-1/100*dc[0]) || (dc[1] <= dc[0]+1/100*dc[0])) {
                //PWM_LED_WriteCompare(dc[1]);
            }
            
        }
    }
}

/* [] END OF FILE */
