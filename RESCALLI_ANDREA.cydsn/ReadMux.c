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
    
    DataBuffer[0] = buffer[PHR_CH] >> 8;   // 8 most significant bits
    DataBuffer[1] = buffer[PHR_CH] & 0xFF; // 8 least significant bits
    DataBuffer[2] = buffer[POT_CH] >> 8;   // 8 most significant bits
    DataBuffer[3] = buffer[POT_CH] & 0xFF; // 8 least significant bits    

    // We regulate the LED only if we have to switch it on
    if(buffer[PHR_CH] <= THRESHOLD) {
        // Set flag of the LED
        flag_led = 1;
        
    }
    else {
        // The light is above threshold and so we need to shut down the LED
        PWM_LED_Stop();
        Pin_LED_Write(OFF);
    }
    
}

/* [] END OF FILE */
