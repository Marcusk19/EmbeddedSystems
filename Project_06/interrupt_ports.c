//==============================================================================
// Filename : interrupt_ports.c
//
// Description: This file contains the interrupt service routines for ports
//
// Author: Marcus Kok
// Date: February 2020
// Compiler: Built with IAR Embedded Workbench for MSP430 7.12.4
//==============================================================================


//------------------------- globals --------------------------------------------
#include "macros.h"
#include "msp430.h"
#include "functions.h"
#include <string.h>

unsigned int debounce_flag_SW1 = RESET_STATE;
unsigned int debounce_flag_SW2 = RESET_STATE;
extern volatile unsigned int debounce_count_SW1;
extern volatile unsigned int debounce_count_SW2;
extern volatile unsigned int wheel_state;
unsigned int emitter_flag = TRUE;               // true if emitter on, false if off
extern unsigned int emitter_display_change;

extern volatile unsigned char display_changed;
extern char display_line[numLines][strSize];
//char* S1_display = "switch 1"; not used
//char* S2_display = "switch 2"; not used

unsigned int ADC_Channel;
unsigned int ADC_Left_Detect;
unsigned int ADC_Right_Detect;
unsigned int ADC_Thumb; 
//------------------------------------------------------------------------------

#pragma vector = PORT4_VECTOR
__interrupt void switchP4_interrupt(void){
  //Switch 1
  if(P4IFG & SW1){
    //strcpy(display_line[line2], " switch 1 ");
    //update_string(display_line[line2], line2);
    //enable_display_update();
    //display_changed = TRUE;   
    P4IFG &= ~SW1;                      // IFG SW1 cleared
    P4IE &= ~SW1;                       // disable switch interrupt  
    debounce_flag_SW1 = TRUE;           // set flag
    debounce_count_SW1 = RESET_STATE;   // clear debounce count
    wheel_state = MOVE_FORWARD;
    TB0CCTL1 |= CCIE;                   // enable debounce interrupt        
  }
}

#pragma vector = PORT2_VECTOR
__interrupt void switchP2_interrupt(void){
  //Switch 2
  if(P2IFG & SW2){
    P2IFG &= ~SW2;                      // IFG SW2 cleared
    P2IE &= ~SW2;                       // disable switch interrupt
    debounce_flag_SW2 = TRUE;           //set flag
    debounce_count_SW2 = RESET_STATE;   // clear debounce count
    TB0CCTL1 |= CCIE;                   // enable debounce interrupt
    // toggle emitter on/off
    if(emitter_flag){
      emitter_Off();
      emitter_flag = FALSE;                        
    }
    else{
      emitter_On();
      emitter_flag = TRUE;      
    }    
  }
}

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
        HEXtoBCD(ADC_Left_Detect);      // convert result to a string
        //adc_line4(POSITION_ONE);                   // place string in display
        break;
      case ADC_CHANNEL_3:
        //replicate for each channel being used
        ADCMCTL0 &= ~ADCINCH_3;         // disable last channel A3
        ADCMCTL0 |= ADCINCH_5;          // enable next channel A5
        ADC_Right_Detect = ADCMEM0;     // move result into global
        ADC_Right_Detect = ADC_Right_Detect >> DIVIDE_BY_FOUR; // divide result by 4
        HEXtoBCD(ADC_Right_Detect);     // convert result to a string
        //adc_line3(POSITION_ONE);                   // place string in display
        break;
      case ADC_CHANNEL_4:
        ADCMCTL0 &= ~ADCINCH_5;         // disable last channel A5
        ADCMCTL0 |= ADCINCH_2;          // enable initial channel A2
        ADC_Thumb = ADCMEM0;            // move result into global
        ADC_Thumb = ADC_Thumb >> DIVIDE_BY_FOUR; // divide result by 4
        HEXtoBCD(ADC_Thumb);            // convert result to a string
        ADC_Channel = RESET_STATE; 
        //adc_line2(POSITION_ONE);                   // place string in display
        break;
      case ADC_RESET_STATE:
        ADC_Channel = RESET_STATE;      // set state back to beginning channel
      default: break;            
      }
      ADCCTL0 |= ADCENC;                // Enable Conversions
      ADCCTL0 |= ADCSC;                 // Start next Sample
    break;
    default:
    break;
  }
}