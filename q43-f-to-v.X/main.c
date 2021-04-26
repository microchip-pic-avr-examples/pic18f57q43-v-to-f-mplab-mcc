/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.7
        Device            :  PIC18F16Q41
        Driver Version    :  2.00
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#include "mcc_generated_files/mcc.h"

#include <math.h>

volatile static bool sendDataFtoV = false;

void __OnTMR2Overflow(void)
{
    sendDataFtoV = true;
}

//Fast division of a 24-bit number by a 16-bit number, with no remainder returned.
uint8_t fastDivision24(uint24_t dividend, uint16_t divisor)
{
    uint8_t counter = 0;
    
    while (dividend >= divisor)
    {
        dividend -= divisor;
        counter++;
    }
    
    return counter;
}

void main(void)
{
    // Initialize the device
    SYSTEM_Initialize();
    
    //Set DMA Priorities
    DMA1_SetDMAPriority(0);
    
    //Clear "Send Data" Flag
    sendDataFtoV = false;
    
    //TMR2 Interrupt for Freq. Measurements
    TMR2_SetInterruptHandler(&__OnTMR2Overflow);
        
    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();
    
    //Start the SMT
    SMT1_DataAcquisitionEnable();
        
    while (1)
    {        
        if (sendDataFtoV)
        {
            sendDataFtoV = false;
            
            //For a software based approach, use this! 
            //DMA should be disabled before use.
            
            /*uint16_t DACvalue = floor(SMT1_GetCapturedPeriod() / 392.157);
            if (DACvalue > UINT8_MAX)
            {
                DAC1_SetOutput(UINT8_MAX);
            }
            else
            {
                DAC1_SetOutput(DACvalue);
            }*/
            
            //End of Software Approach
            
            if (SMT1_GetCapturedPeriod() > UINT16_MAX)
            {
                //Exceeds the size that printf can handle - show in kHz instead.
                uint8_t freq = fastDivision24(SMT1_GetCapturedPeriod(), 1000);
                printf("Measured Input Frequency: %ukHz\n\r", freq);
            }
            else if (SMT1_GetCapturedPeriod() > 5)
            {
                printf("Measured Input Frequency: %uHz\n\r", SMT1_GetCapturedPeriod());
            }
            else
            {
                printf("Open Wire Detected.\n\r");
            }
        }   
    }
}
/**
 End of File
*/