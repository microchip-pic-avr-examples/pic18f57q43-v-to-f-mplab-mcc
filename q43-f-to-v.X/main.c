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

volatile static bool sendDataFtoV = false;

void __OnTMR2Overflow(void)
{
    sendDataFtoV = true;
}

//Using Fixed Point Numbers, set the DAC's output from SMT1's value
//Not currently used in the example, but it showcases another way.
void setDACFromFrequencyFixedPoint(void)
{
    //Frequency Range: 100kHz to DC
    //DAC is 8-bits
    //Resolution is 390.625Hz per bit (100kHz / 256)
    
    const uint8_t fraction = 0b10100000;
    
    uint16_t wholeFreq = 390;
    uint8_t fractFreq = fraction; //Binary representation of 0.625 
    
    uint8_t output = 0;
    uint24_t value = SMT1_GetCapturedPeriod();
    
    while (value > wholeFreq)
    {
        //Subtract the whole number frequency
        value -= wholeFreq;
        
        //IF not at max output, then increment the output
        if (output != 0xFF)
            output++;
        
        //Balance the decimal
        if ((fractFreq & 0x80) != 0x00)
        {
            //If there is a remainder...
            fractFreq = (fractFreq << 1) | 0b1;
            value--;
        }
        else
        {
            fractFreq = fractFreq << 1;
        }
    }
    
    DAC1_SetOutput(output);
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
            //setDACFromFrequencyFixedPoint();
                        
            if (SMT1_GetCapturedPeriod() > UINT16_MAX)
            {
                //Exceeds the size that printf can handle - show in kHz instead.
                uint8_t freq = fastDivision24(SMT1_GetCapturedPeriod(), 1000);
                printf("Measured Input Frequency: %ukHz\n\r", freq);
            }
            else
            {
                printf("Measured Input Frequency: %uHz\n\r", SMT1_GetCapturedPeriod());
            }            
        }   
    }
}
/**
 End of File
*/