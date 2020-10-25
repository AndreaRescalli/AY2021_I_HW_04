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

/* [] END OF FILE */
