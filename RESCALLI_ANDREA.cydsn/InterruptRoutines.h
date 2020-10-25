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

    volatile uint8 flag_timer; // flag that tells 100ms (timer isr) have passed and we can sample our signals

    CY_ISR_PROTO(Custom_ISR_Timer);    
#endif

/* [] END OF FILE */
