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
#include <string.h>

//--------------------------- globals ------------------------------------------
volatile unsigned int CCR0_COUNT = RESET_STATE;
extern unsigned int myTime;
volatile unsigned int display_count = RESET_STATE;
volatile unsigned int one_second_count = RESET_STATE;
unsigned int one_second_flag = FALSE;
volatile unsigned int debounce_count_SW1 = RESET_STATE;
volatile unsigned int debounce_count_SW2 = RESET_STATE;
extern unsigned int debounce_flag_SW1;
extern unsigned int debounce_flag_SW2;

volatile unsigned int Time_Sequence = RESET_STATE;
extern volatile unsigned char update_display;
extern volatile unsigned int update_display_count;
extern volatile unsigned int wheel_state;

extern volatile unsigned char display_changed;
extern char display_line[numLines][strSize];

extern unsigned int ADC_Left_Detect;
extern unsigned int ADC_Right_Detect;
extern unsigned int ADC_Thumb;

//------------------------------------------------------------------------------
// CCR0 interrupt 

#pragma vector = TIMER0_B0_VECTOR
__interrupt void TIMER0_B0_ISR(void){
  // timer interrupt B0 handler every 50 ms
  CCR0_COUNT++;
  display_count++;
  one_second_count++;
  if(CCR0_COUNT == TB0CCR0_CYCLES){                     // 0.2 seconds passed
    
    HEXtoBCD(ADC_Left_Detect);          // convert result to a string
    ClrDisplay_Buffer_3();
    adc_line4(POSITION_ONE);            // place string in display
    
    HEXtoBCD(ADC_Right_Detect);         // convert result to a string
    ClrDisplay_Buffer_2();
    adc_line3(POSITION_ONE);            // place string in display
    
    HEXtoBCD(ADC_Thumb);                // convert result to a string
    ClrDisplay_Buffer_1();
    adc_line2(POSITION_ONE);            // place string in display
    
    CCR0_COUNT = RESET_STATE;
    }
  
  if(one_second_count == CCR0_SEC){             // one second has passed
    one_second_flag = TRUE;
    one_second_count = RESET_STATE;
  }
  else{
    one_second_flag = FALSE;
  }
  
  if(display_count > UPDATE_DISPLAY_THRESHOLD){         // 200 ms has passed
      update_display = TRUE; // set update display true
      display_count = RESET_STATE; //reset count
    }
  TB0CCR0 += TB0CCR0_INTERVAL;
}

//------------------------- overflow handler TB0 -------------------------------
#pragma vector = TIMER0_B1_VECTOR
__interrupt void TIMER0_B1_ISR(void){
  //Timer B0 1-2 overflow interrupt vector (TBIV) handler
  
  switch(__even_in_range(TB0IV, OVERFLOW)){
  case NO_INTERRUPT: break; // no interrupt
  case CCR1_USED:       // CCR1 not used
//---------------------- debounce timer interrupt --------------------------
      if(debounce_flag_SW1){
         debounce_count_SW1++;
         if(debounce_count_SW1 > DEBOUNCE_THRESHOLD){
            P4IE |= SW1;                      // re-enable SW1 interrupt
            debounce_flag_SW1 = FALSE;        // flag set to false
            if(!debounce_flag_SW2){
              TB0CCTL0 |= CCIE;               // enable CCR0 interrupt
              wheel_state = MOVE_FORWARD;
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
  case CCR2_USED:                       // Time_Sequence interrupt CCR2
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
