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
#include "ReadMux.h"
#include <stdio.h>


// Defines


// Globals
float dc[2] = {0};


int main(void) {

    CyGlobalIntEnable; /* Enable global interrupts. */
    
    // Start of all the components
    UART_Start();
    ADC_DelSig_Start();
    AMux_Start();
    Timer_Start();
    PWM_LED_Start();
    
    // Init of timer flag and enable its ISR
    flag_timer = 0;
    isr_Timer_StartEx(Custom_ISR_Timer);

    //
    ADC_DelSig_StartConvert();
    
    //PWM_LED_WriteCompare(0);
    

    for(;;) {
        
        if(flag_timer) {
            
            // We are ready to sample our signals
            readmux(samples);
            
            // Check the led flag to know wheather we have to turn it on and, in case, pilot it
            if(flag_led) {
                
                // Turn LED on
                Pin_LED_Write(ON);
                // Keep track of the previous duty cycle
                dc[0] = dc[1];
                
                // Display the value, in mV, of the potentiometer
                UART_PutString(DataBuffer);
                
                // Adjust the duty cycle of the PWM piloting the LED to control its intensity according to the
                // potentiometer position set by the user
                dc[1] = samples[1]/65535.0f*100;
                // Set the new duty cycle only if it differs for at least 1% of the previous one
                if((dc[1] >= dc[0]-1/100.0f*dc[0]) || (dc[1] <= dc[0]+1/100.0f*dc[0])) {
                    PWM_LED_WriteCompare((uint8)dc[1]);
                }
            }
            
            // Reset the flags
            flag_timer = 0;
            flag_led = 0;
            
        } // end flag_timer
        
    } //end for
    
} // end main

/* [] END OF FILE */
