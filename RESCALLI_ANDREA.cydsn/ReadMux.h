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

#ifndef __READ_MUX_H
    #define __READ_MUX_H
    
    #include "cytypes.h"
    #include <stdio.h>
    
    #define ON  1
    #define OFF 0
    
    #define CHANNELS  2                     // # OF CHANNELS OF THE MUX
    #define PHR_CH    0                     // CHANNEL FOR PHOTORESISTOR
    #define POT_CH    1                     // CHANNEL FOR POTENTIOMETER
    #define THRESHOLD 32767                 // THRESHOLD ON PHOTORESISTOR TO TURN LED ON
    
    #define TRANSMIT_BUFFER_SIZE 2*CHANNELS // DIMENSION OF MESSAGE TO BE SENT
    
    uint8 DataBuffer[TRANSMIT_BUFFER_SIZE]; // Message to be displayed with the value in mV sampled form the potentiometer
    int32 samples[CHANNELS];                // Buffer that contains the digit values of the sampled signals
    volatile uint8 flag_led;                // Flag that tells us when to switch on the LED
    
    // Declaration of function that reads value from the ADC, channel-per-channel
    void readmux(int32 *buffer);    
#endif

/* [] END OF FILE */
