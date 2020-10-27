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


// Useful variables
static int32 value_phr = THRESHOLD + 10000; // Stores the value of the photoresistor. Initialized high above THRESHOLD
static int32 value_pot = 0;                 // Stores the value of the potentiometer
static uint8 ch_rx = 0;                     // Stores the recieved byte
static float dc = 0.0;                      // Stores the DutyCycle to pilot the PWM with
static uint8 count = 0;                     // Read disclaimer below

/* 
 * !IMPORTANT!
 * After trying the device out several times, I've noticed that the very first sample is acquired by the ADC after the build 
 * (or a reset of the PSoC), which happens to be the photoresistor signal (since it's the first of the two signals 
 * that is acquired), was very unstable: while the steady state of the measurement was (for instance) 62000, the first 
 * acquisition could go down to even 24000 with no reason at all.. from the second sampling it was super stable.
 * This led to the problem that, for a moment, the value of the photoresistor was (BUT NOT ALWAYS, IT WAS DEPENDENT ON THE 
 * AMPLITUDE OF THE OSCILLATION!) below threshold, resulting in a piloting of the LED for one cycle (it blinks once with 
 * an intensity set by the position of the potentiometer), and then the situation stabilized (as it should have been since 
 * the beginning) to LED OFF..
 * For this reason, I've decided to discard the very first measurement (using an auxiliary variable, count) done by the device
 * in order to avoid a random behaviour of the LED in the initial stage.
 * 
 * The problem was not found in the case of device stopped with 'S' and then restarted with 'B', but just in the very first run
 *
*/


// ISR of the timer that tells us when to sample our signals (once every 100ms)
CY_ISR(Custom_ISR_Timer) {

    // Bring interrupt low
    Timer_ReadStatusRegister();
    
    if(flag_start) {
        
        // Reset AMux to disconnect all channels
        AMux_Init();
        
        // Actually tells us wheather it's the first time we enter this part of the code or not
        count++;
        
        // Select the first channel, which is associated to the photoresistor.
        // FastSelect disconnects only the last one used: ok since we have only two channels; it's faster.
        AMux_FastSelect(PHR_CH);
        value_phr = ADC_DelSig_Read32();
        
        // Extreme values, near FS, are unstable
        if(value_phr > 65535) {
            value_phr = 65535;
        }
        
        if(value_phr < 0) {
            value_phr = 0;
        }
        
        // Select the second channel, and disconnect the first one, to sample the potentiometer
        AMux_FastSelect(POT_CH);
        value_pot = ADC_DelSig_Read32();
        
        // Extreme values, near FS, are unstable
        if(value_pot > 65535) {
            value_pot = 65535;
        }

        if(value_pot < 0) {
            value_pot = 0;
        }
        
        // This is the control we do to discard the first sampling operation
        if(count > 1) {
            // Set count to 1 so that:
            // 1. we will enter this part of the code from now on
            // 2. it does not undergo overflow
            count = 1;
            
            // All the data relative to both photoresistor and potentiometer are stored, even in case
            // of light above threshold, to be able to monitor the correct functioning of the device in
            // any situation
            DataBuffer[0] = value_phr >> 8;   // 8 most significant bits
            DataBuffer[1] = value_phr & 0xFF; // 8 least significant bits
            DataBuffer[2] = value_pot >> 8;   // 8 most significant bits
            DataBuffer[3] = value_pot & 0xFF; // 8 least significant bits
            
            // If the light is below THRESHOLD we need to turn the LED ON and pilot it according to
            // the value imposed by the user through the potentiometer
            if(value_phr <= THRESHOLD) {
                // Compute the DutyCycle
                dc = value_pot/65535.0f*100;
                PWM_LED_WriteCompare((uint8) dc);
            }
            else {
                // The LED does not need to be turned on
                PWM_LED_WriteCompare(0);
            }
            
            // Tell the main that we're done
            flag_packet = 1;
        } // if count
        
    } // end if(flag_start)
    
} // end timer ISR


// ISR of the UART that is used to pilot remotely the device based on commands recieved
CY_ISR(Custom_ISR_RX) {
    
    // Read the recieved data
    ch_rx = UART_ReadRxData();
    
    // Drive the behaviour of the device according to the recieved data
    switch(ch_rx) {
    
        case 'B':
        case 'b':
            flag_start = 1;
            // Turn internal LED ON since the PSoC is operating
            Pin_COM_Write(ON);
            // Enable the sampling
            Timer_Start();
            break;
            
        case 'S':
        case 's':
            flag_start = 0;
            // Turn internal LED OFF since the PSoC is not operating
            Pin_COM_Write(OFF);
            // Disable the sampling
            Timer_Stop();
            break;
            
        default:
            break;
            
    }
    
} // end UART ISR

/* [] END OF FILE */
