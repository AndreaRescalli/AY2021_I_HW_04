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


// ISR of the timer that tells us when to sample our signals (once every 100ms)
CY_ISR(Custom_ISR_Timer) {

    // Bring interrupt low
    Timer_ReadStatusRegister();
    
    // Set flag to tell we can sample
    flag_timer = 1;
    
}


// ISR of the UART that is used to pilot remotely the device based on commands recieved
CY_ISR(Custom_ISR_RX) {
    
    uint8 ch_rx = UART_ReadRxData();
    
    switch(ch_rx) {
    
        case 'B':
        case 'b':
            flag_start = 1;
            // Enable timer and ADC conversion
            Timer_Start();
            ADC_DelSig_StartConvert();
            break;
            
        case 'S':
        case 's':
            flag_start = 0;
            // Stop timer and disable ADC conversion
            Timer_Stop();
            ADC_DelSig_StopConvert();
            break;
        default:
            break;
            
    }
}

/* [] END OF FILE */
