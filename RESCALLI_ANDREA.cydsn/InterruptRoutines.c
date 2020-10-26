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
#include "InterruptRoutines.h"
#include "project.h"


// Defines
#define ON  1
#define OFF 0


// Useful variables
uint8 ch_rx;


// ISR of the timer that tells us when to sample our signals (once every 100ms)
CY_ISR(Custom_ISR_Timer) {

    // Bring interrupt low
    Timer_ReadStatusRegister();
    
    // Set flag to tell we can sample
    flag_timer = 1;
    
}


// ISR of the UART that is used to pilot remotely the device based on commands recieved
CY_ISR(Custom_ISR_RX) {
    
    ch_rx = UART_ReadRxData();
    
    switch(ch_rx) {
    
        case 'B':
        case 'b':
            flag_start = 1;
            // Turn internal LED ON since the PSoC is operating
            Pin_COM_Write(ON);
            // Enable timer and ADC conversion
            Timer_Start();
            ADC_DelSig_Start();
            ADC_DelSig_StartConvert();
            break;
            
        case 'S':
        case 's':
            flag_start = 0;
            // Turn internal LED OFF since the PSoC is not operating
            Pin_COM_Write(OFF);
            // Stop timer and disable ADC conversion
            Timer_Stop();
            ADC_DelSig_Stop();
            break;
            
        default:
            break;
            
    }
}

/* [] END OF FILE */
