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
#include "project.h"

#define ON 1

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    UART_Start();

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    Pin_LED_Write(ON);
    UART_PutString("Hello, World!\r\n");
    

    for(;;)
    {
        /* Place your application code here. */
    }
}

/* [] END OF FILE */
