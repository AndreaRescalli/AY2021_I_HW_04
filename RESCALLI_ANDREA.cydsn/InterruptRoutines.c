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

#include "InterruptRoutines.h"
#include "project.h"

// DEVONO ESSERE 32 PERCHÈ SE SIAMO IN SINGLE-ENDED A 16 BIT DOBBIAMO LEGGERE CON GET/READ32,
// ALTRIMENTI CIOCCA IL CODICE


CY_ISR(Custom_ISR_Timer) {

    // Bring interrupt low
    Timer_ReadStatusRegister();

    value_digit = ADC_DelSig_Read32();
    
    // High values, near FS, are unstable
    if(value_digit < 0) {
        value_digit = 0;
    }
    
    if(value_digit > 65535) {
        value_digit = 65535;
    }
    
    value_mv = ADC_DelSig_CountsTo_mVolts(value_digit);
    sprintf(DataBuffer, "Sample: %ld mV\r\n", value_mv);
    flag_timer = 1;
    
}

/* [] END OF FILE */
