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

#ifndef __INTERRUPT_ROUTINES_H
    #define __INTERRUPT_ROUTINES_H
    #include "cytypes.h"
    #include <stdio.h>

    volatile uint8 flag_timer; // Flag that tells 100ms (timer isr) have passed and we can sample our signals
    volatile uint8 flag_start; // Flag that tells when to enable or disable the sampling process
    
    // Declaration of timer ISR
    CY_ISR_PROTO(Custom_ISR_Timer);
    // Declaration of UART ISR
    CY_ISR_PROTO(Custom_ISR_RX);
#endif

/* [] END OF FILE */
