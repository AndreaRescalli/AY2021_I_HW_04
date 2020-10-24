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

//int32 value_digit = 0;
//int32 value_mv = 0;
float dc[2] = {0};


int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    UART_Start();
    ADC_DelSig_Start();
    Timer_Start();
    PWM_LED_Start();
    
    flag_timer = 0;
    
    isr_Timer_StartEx(Custom_ISR_Timer);

    //Pin_LED_Write(ON);
    ADC_DelSig_StartConvert();
    
    //PWM_LED_WriteCompare(0);
    

    for(;;)
    {
        if(flag_timer) {
            
//            value_digit = ADC_DelSig_Read32();
//            if(value_digit < 0) {
//                value_digit = 0;
//            }
//    
//            if(value_digit > 65535) {
//                value_digit = 65535;
//            }
//            
            
            dc[0] = dc[1];
            UART_PutString(DataBuffer);
            flag_timer = 0;
            dc[1] = value_digit/65535.0f*100;
            if((dc[1] >= dc[0]-1/100.0f*dc[0]) || (dc[1] <= dc[0]+1/100.0f*dc[0])) {
                PWM_LED_WriteCompare((uint8)dc[1]);
            }
            
        }
    }
}

/* [] END OF FILE */
