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
#include "ReadMux.h"
#include "project.h"

// Useful variables
static int32 value_mv; // used to communicate through the terminal the value in mV of the potentiometer


// Function that is in charge of reading the ADC, channel by channel
void readmux(int32 *buffer) {
    
    // Reset AMux to disconnect all channels
    AMux_Init();
    
    // Select the first channel, which is associated to the photoresistor.
    // We can use FastSelect since we have only two channels, and this function disconnects only the last one used.. it's faster
    AMux_FastSelect(PHR_CH);
    buffer[PHR_CH] = ADC_DelSig_Read32();
    
    // Extreme values, near FS, are unstable
    if(buffer[PHR_CH] > 65535) {
        buffer[PHR_CH] = 65535;
    }
    
    if(buffer[PHR_CH] < 0) {
        buffer[PHR_CH] = 0;
    }

    // We sample the potentiometer to regulate the LED only if we have to switch it on
    if(buffer[PHR_CH] <= THRESHOLD) {
        // Set flag of the LED
        flag_led = 1;
        
        // Extreme values, near FS, are unstable

        // Select the second channel, and disconnect the first one, to sample the potentiometer
        AMux_FastSelect(POT_CH);
        buffer[POT_CH] = ADC_DelSig_Read32();
        
        // Extreme values, near FS, are unstable
        if(buffer[POT_CH] > 65535) {
            buffer[POT_CH] = 65535;
        }
    
        if(buffer[POT_CH] < 0) {
            buffer[POT_CH] = 0;
        }
        
        value_mv = ADC_DelSig_CountsTo_mVolts(buffer[POT_CH]);
        sprintf(DataBuffer, "Sample: %ld mV\r\n", value_mv);
    }
    else {
        // The ligh is above threshold and so we need to shut down the LED
        PWM_LED_Stop();
        Pin_LED_Write(OFF);
    }
    
}

/* [] END OF FILE */
