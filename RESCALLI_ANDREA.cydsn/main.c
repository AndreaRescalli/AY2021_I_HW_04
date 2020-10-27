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

// Includes
#include "project.h"
#include "InterruptRoutines.h"
#include <stdio.h>


int main(void) {

    CyGlobalIntEnable; /* Enable global interrupts. */
    
    // Start of all the components (except for the timer piloted through UART)
    UART_Start();
    PWM_LED_Start();
    AMux_Start();
    ADC_DelSig_Start();
    ADC_DelSig_StartConvert();
    
    // Init of flags and enable of the ISRs
    isr_Timer_StartEx(Custom_ISR_Timer);
    isr_RX_StartEx(Custom_ISR_RX);
    
    flag_packet = 0;
    flag_start = 0;

    
    // Message for the user
    UART_PutString("Send B or b to start the device, S or s to stop it\r\n");
    
    
    for(;;) {
        
        if(flag_packet) {
            // Since the packet of data has been sampled and it's ready, we send it
            UART_PutArray(DataBuffer, TRANSMIT_BUFFER_SIZE);
            flag_packet = 0;
        }
        
        // When we stop the device, the LED must be OFF
        if(flag_start == 0) {
            if(Pin_LED_Read() == ON) {
                PWM_LED_WriteCompare(0);
            }
        }
        
    } // end for
    
} // end main

/* [] END OF FILE */