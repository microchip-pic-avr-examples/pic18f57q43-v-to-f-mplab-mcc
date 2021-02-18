/**
   NCO3 Generated Driver File
 
   @Company
     Microchip Technology Inc.
 
   @File Name
     nco3.c
 
   @Summary
     This is the generated driver implementation file for the NCO3 driver using PIC10 / PIC12 / PIC16 / PIC18 MCUs
 
   @Description
     This source file provides implementations for driver APIs for NCO3.
     Generation Information :
         Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.6
         Device            :  PIC18F57Q43
         Driver Version    :  2.11
     The generated drivers are tested against the following:
         Compiler          :  XC8 2.30 and above or later
         MPLAB             :  MPLAB X 5.40
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
 
 /**
   Section: Included Files
 */

#include <xc.h>
#include "nco3.h"

/**
  Section: NCO Module APIs
*/

void NCO3_Initialize (void)
{
    // Set the NCO to the options selected in the GUI
    // EN disabled; POL active_hi; PFM PFM_mode; 
    NCO3CON = 0x01;
    // CKS CLC2; PWS 1_clk; 
    NCO3CLK = 0x14;
    // 
    NCO3ACCU = 0x00;
    // 
    NCO3ACCH = 0x00;
    // 
    NCO3ACCL = 0x00;
    // 
    NCO3INCU = 0x00;
    // 
    NCO3INCH = 0x0A;
    // 
    NCO3INCL = 0x71;

    // Enable the NCO module
    NCO3CONbits.EN = 1;
   
}

bool NCO3_GetOutputStatus(void)
{
    // Return output status on accumulator over flow
    return (NCO3CONbits.OUT);
}
/**
 End of File
*/

