/* ========================================
 *
 * Copyright LTEBS srl, 2020
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF LTEBS srl.
 *
 * \file  InterruptRoutines.h
 * \brief Header file containing the ISRs of Timer and UART
 *
 * Development of a smart lamp that can be controlled in its ON/OFF state via remote, is sensible to
 * ambient light (turns ON/OFF whenever the light is below a predefined threshold, if active) and can 
 * be adjusted in its intensity by the user through a potentiometer
 *
 * \author: Andrea Rescalli
 * \date:   30/10/2020
 *
 * ========================================
*/

#ifndef __INTERRUPT_ROUTINES_H
    #define __INTERRUPT_ROUTINES_H
    
    // Includes
    #include "cytypes.h"
    #include <stdio.h>
    
    
    // Defines
    #define ON  1
    #define OFF 0
    
    #define CHANNELS  2                     // # OF CHANNELS OF THE MUX
    #define PHR_CH    0                     // CHANNEL FOR PHOTORESISTOR
    #define POT_CH    1                     // CHANNEL FOR POTENTIOMETER
    #define THRESHOLD 32767                 // THRESHOLD ON PHOTORESISTOR TO TURN LED ON 
    
    #define TRANSMIT_BUFFER_SIZE 2*CHANNELS // DIMENSION OF PACKET TO BE SENT
    
    
    // Globals
    volatile uint8 flag_packet;             // Flag that tells a packet has been sampled
    volatile uint8 flag_start;              // Flag that tells we can operate
    uint8 DataBuffer[TRANSMIT_BUFFER_SIZE]; // Packet of sampled data
    
    
    // Declaration of timer ISR
    CY_ISR_PROTO(Custom_ISR_Timer);
    // Declaration of UART ISR
    CY_ISR_PROTO(Custom_ISR_RX);
    
#endif

/* [] END OF FILE */
