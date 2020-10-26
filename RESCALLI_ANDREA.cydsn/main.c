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
#define OLD 0
#define NEW 1


// Useful variables
static float dc[2] = {0}; // Buffer that keeps track of the duty cycle to modulate the LED PWM
static uint8 count = 0;   // Variable used to display the message that the device has been stopped


int main(void) {

    CyGlobalIntEnable; /* Enable global interrupts. */
    
    // Start of all the components (except for the timer and ADC, piloted through UART)
    UART_Start();
    AMux_Start();
    PWM_LED_Start();
    
    // Init of flags and enable of the ISRs
    flag_timer = 0;
    flag_led = 0;
    flag_start = 0;
    isr_Timer_StartEx(Custom_ISR_Timer);
    isr_RX_StartEx(Custom_ISR_RX);

    
    // Message for the user
    UART_PutString("Send B or b to start the device, S or s to stop it\r\n");
    

    for(;;) {
        
        if(flag_start) {
            count = 1; // Keeps track of the fact that the device has been started at least once
            
            if(flag_timer) {
                
                // We are ready to sample our signals
                readmux(samples);
                // Send the packet of data
                UART_PutArray(DataBuffer,TRANSMIT_BUFFER_SIZE);
                
                // Check the led flag to know wheather we have to turn it on and, in case, pilot it
                if(flag_led) {
                    
                    // Turn LED on
                    if(Pin_LED_Read() == OFF) {
                        PWM_LED_Enable(); // if the LED is OFF, PWM is disabled
                        Pin_LED_Write(ON);
                    }
                    // Keep track of the previous duty cycle
                    dc[OLD] = dc[NEW];
                                        
                    // Adjust the duty cycle of the PWM piloting the LED to control its intensity according to the
                    // potentiometer position set by the user
                    dc[NEW] = samples[POT_CH]/65535.0f*100;
                    // Set the new duty cycle only if it differs for at least 1% of the previous one
                    if((dc[NEW] >= dc[OLD]-1/100.0f*dc[OLD]) || (dc[NEW] <= dc[OLD]+1/100.0f*dc[OLD])) {
                        PWM_LED_WriteCompare((uint8)dc[NEW]);
                    }
                }
                
                // Reset the flags
                flag_timer = 0;
                flag_led = 0;
                
            } // end flag_timer
        } // end if(flag_start)
        else {
            // The device is stopped. We operate and display messages only if the device was previously working
            if(count) { 
                count = 0;
                // Turn LED OFF
                PWM_LED_Stop();
                Pin_LED_Write(OFF);
                // Communicate with the user
                UART_PutString("Device has been stopped\r\n");
                UART_PutString("Send B or b to start the device\r\n");
                
                // Reset the flags
                flag_timer = 0;
                flag_led = 0;
            }
        } // end else(flag_start)
        
    } //end for
    
} // end main

/* [] END OF FILE */
