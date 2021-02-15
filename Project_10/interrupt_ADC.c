//==============================================================================
// Filename : interrupt_ADC.c
//
// Description: This file contains the interrupt service routines for ADC        
//
// Author: Marcus Kok
// Date: March 2020
// Compiler: Built with IAR Embedded Workbench for MSP430 7.12.4
//==============================================================================
#include "macros.h"
#include "msp430.h"
#include "functions.h"
#include <string.h>
// globals
//------------------------------------------------------------------------------
  
  unsigned int ADC_Channel;
  unsigned int ADC_Left_Detect;
  unsigned int ADC_Right_Detect;
  unsigned int ADC_Thumb; 

//------------------------------------------------------------------------------

  #pragma vector = ADC_VECTOR
__interrupt void ADC_ISR(void){
    switch(__even_in_range(ADCIV,ADCIV_ADCIFG)){
    case ADCIV_NONE:
    break;
    case ADCIV_ADCOVIFG: // When a conversion result is written to the ADCMEM0
    // before its previous conversion result was read.
    break;
    case ADCIV_ADCTOVIFG:               // ADC conversion-time overflow
    break;
    case ADCIV_ADCHIIFG:                // Window comparator interrupt flags
    break;
    case ADCIV_ADCLOIFG:                // Window comparator interrupt flag
    break;
    case ADCIV_ADCINIFG:                // Window comparator interrupt flag
    break;
    case ADCIV_ADCIFG:                  // ADCMEM0 memory register with the conversion result
      ADCCTL0 &= ~ADCENC;               // disable enc bit
      switch(ADC_Channel++){            // create global ADC_Channel variable
      case ADC_CHANNEL_2:
        ADCMCTL0 &= ~ADCINCH_2;         //disable last channel A2
        ADCMCTL0 |= ADCINCH_3;          // enable next channel A3
        ADC_Left_Detect = ADCMEM0;      // move result into global
        ADC_Left_Detect = ADC_Left_Detect >> DIVIDE_BY_FOUR; // divide result by 4
        break;
      case ADC_CHANNEL_3:
        //replicate for each channel being used
        ADCMCTL0 &= ~ADCINCH_3;         // disable last channel A3
        ADCMCTL0 |= ADCINCH_5;          // enable next channel A5
        ADC_Right_Detect = ADCMEM0;     // move result into global
        ADC_Right_Detect = ADC_Right_Detect >> DIVIDE_BY_FOUR; // divide result by 4
        break;
      case ADC_CHANNEL_4:
        ADCMCTL0 &= ~ADCINCH_5;         // disable last channel A5
        ADCMCTL0 |= ADCINCH_2;          // enable initial channel A2
        ADC_Thumb = ADCMEM0;            // move result into global
        //ADC_Thumb = ADC_Thumb >> DIVIDE_BY_FOUR; // divide result by 4
        ADC_Channel = RESET_STATE; 
        break;
      case ADC_RESET_STATE:
        ADC_Channel = RESET_STATE;      // set state back to beginning channel
      default: break;            
      }
    ADCCTL0 |= ADCENC;                //  Enable Conversions
    ADCCTL0 |= ADCSC;                 // Start next Sample
    break;
    default:
    break;
  }
}