//==============================================================================
// Filename : interrupts.c
//
// Description: This file contains the interrupt service routines
//
// Author: Marcus Kok
// Date: February 2020
// Compiler: Built with IAR Embedded Workbench for MSP430 7.12.4
//==============================================================================

#include "macros.h"
#include "msp430.h"
#include "functions.h"

volatile unsigned int CCR0_COUNT = RESET_STATE;
volatile unsigned int display_count = RESET_STATE;
volatile unsigned int debounce_count_SW1 = RESET_STATE;
volatile unsigned int debounce_count_SW2 = RESET_STATE;
extern unsigned int debounce_flag_SW1;
extern unsigned int debounce_flag_SW2;

volatile unsigned int Time_Sequence = RESET_STATE;
extern volatile unsigned char update_display;
extern volatile unsigned int update_display_count;

//------------------------------------------------------------------------------
// CCR0 interrupt 

#pragma vector = TIMER0_B0_VECTOR
__interrupt void TIMER0_B0_ISR(void){
  // timer interrupt B0 handler
  CCR0_COUNT++;
  display_count++;
  if(CCR0_COUNT == TB0CCR0_CYCLES){
    if(P6OUT & LCD_BACKLITE){
      P6OUT &= ~LCD_BACKLITE;
    }
    else{
      P6OUT |= LCD_BACKLITE;
    }
    CCR0_COUNT = RESET_STATE;
  }
  if(display_count > UPDATE_DISPLAY_THRESHOLD){
      update_display = TRUE; // set update display true
      display_count = RESET_STATE; //reset count
    }
  TB0CCR0 += TB0CCR0_INTERVAL;
}

#pragma vector = TIMER0_B1_VECTOR
__interrupt void TIMER0_B1_ISR(void){
  //Timer B0 1-2 overflow interrupt vector (TBIV) handler
  
  switch(__even_in_range(TB0IV, OVERFLOW)){
  case NO_INTERRUPT: break; // no interrupt
  case CCR1PORT:       // CCR1 not used
//---------------------- debounce timer interrupt --------------------------
      if(debounce_flag_SW1){
         debounce_count_SW1++;
         if(debounce_count_SW1 > DEBOUNCE_THRESHOLD){
            P4IE |= SW1;                      // re-enable SW1 interrupt
            debounce_flag_SW1 = FALSE;        // flag set to false
            if(!debounce_flag_SW2){
              TB0CCTL0 |= CCIE;               // enable CCR0 interrupt
              TB0CCTL1 &= ~CCIE;              // disable debounce timer interrupt
            }
         }
        }
  //---------------------------- SW2--------------------------------------------- 
      if(debounce_flag_SW2){
          debounce_count_SW2++;
          if(debounce_count_SW2 > DEBOUNCE_THRESHOLD){
            P2IE |= SW2;                      // re-enable SW2 interrupt
            debounce_flag_SW2 = FALSE;        // flag set to false
            if(!debounce_flag_SW1){
              TB0CCTL0 |= CCIE;               // re-enable CCR0 interrupt
              TB0CCTL1 &= ~CCIE;              //disable timer interrupt
            } 
          }
        }
      TB0CCR1 += TB0CCR1_INTERVAL; // add offset to TBCCR1
    break;
  case CCR2PORT:                       // CCR2 not used  
    Time_Sequence++;
    if(Time_Sequence > TIME_SEQUENCE_CYCLES){
      Time_Sequence = RESET_STATE;
    }
    TB0CCR2 += TB0CCR2_INTERVAL;
    break; 
  case OVERFLOW:                     //overflow
    //implementation
    break;
  default: break;
  }
}





  