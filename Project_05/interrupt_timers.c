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

//------------------------------------------------------------------------------
// CCR0 interrupt 

#pragma vector = TIMER0_B0_VECTOR
__interrupt void TIMER0_B0_ISR(void){
  // timer interrupt B0 handler every 50 ms
  CCR0_COUNT++;
  display_count++;
  if(CCR0_COUNT == TB0CCR0_CYCLES){                     // 1 second has passed
    myTime++; 
    switch(myTime){
    case START_FORWARD:
      move_Forward(); 
      
      strcpy(display_line[line2], "  Forward "); // update display
      update_string(display_line[line2], line2);
      enable_display_update();
      display_changed = TRUE;
      break;
    case STOP_FIRST_FORWARD:
      stop_Movement();
      
      strcpy(display_line[line2], "   Hold   "); // update display
      update_string(display_line[line2], line2);
      enable_display_update();
      display_changed = TRUE;
      break;
    case START_REVERSE:
      move_Reverse();
      
      strcpy(display_line[line2], " Reverse  "); // update display
      update_string(display_line[line2], line2);
      enable_display_update();
      display_changed = TRUE;
      break;
    case STOP_REVERSE:
      stop_Movement();
      
      strcpy(display_line[line2], "   Hold   "); // update display
      update_string(display_line[line2], line2);
      enable_display_update();
      display_changed = TRUE;
      break;
    case START_SECOND_FORWARD:
      move_Forward();
      
      strcpy(display_line[line2], "  Forward "); // update display
      update_string(display_line[line2], line2);
      enable_display_update();
      display_changed = TRUE;
      break;
    case STOP_SECOND_FORWARD:
      stop_Movement();
      
      strcpy(display_line[line2], "   Hold   "); // update display
      update_string(display_line[line2], line2);
      enable_display_update();
      display_changed = TRUE;
      break;
    case START_SPIN_CW:
      spin_CW();
      
      strcpy(display_line[line2], " Spin CW  "); // update display
      update_string(display_line[line2], line2);
      enable_display_update();
      display_changed = TRUE;
      break;
    case STOP_SPIN_CW:
      stop_Movement();
      
      strcpy(display_line[line2], "   Hold   "); // update display
      update_string(display_line[line2], line2);
      enable_display_update();
      display_changed = TRUE;
      break;
    case START_SPIN_CCW:
      spin_CCW();                               
      
      strcpy(display_line[line2], " Spin CCW "); // update display
      update_string(display_line[line2], line2);
      enable_display_update();
      display_changed = TRUE;
      break;
    case STOP_SPIN_CCW:
      stop_Movement();
      
      strcpy(display_line[line2], "   Hold   "); // update display
      update_string(display_line[line2], line2);
      enable_display_update();
      display_changed = TRUE;
      break;
    case MAX_TIME:
      myTime = RESET_STATE;
      break;
    default: break;
    }
    CCR0_COUNT = RESET_STATE;
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
    
  case CCR2PORT:                       // Time_Sequence interrupt
    Time_Sequence++;
    if(Time_Sequence > TIME_SEQUENCE_CYCLES){
      Time_Sequence = RESET_STATE;
    }
    //TB0CCR2 += TB0CCR2_INTERVAL;
    break; 
    
  case OVERFLOW:                     //overflow
    //implementation
    break;
  default: break;
  }
}

/*#pragma vector = TIMER3_B0_VECTOR
__interrupt void TIMER3_B0_ISR(void){
    switch(wheel_state){
      
    case HOLD:                          // stop all wheel movement
        stop_Movement();    
        break;
        
    case FORWARD:
        move_Forward();
        break;
        
    case REVERSE:
        move_Reverse();
        break;
        
    case SPIN_CW:
        spin_CW();
        break;
        
    case SPIN_CCW:
        spin_CCW();
        break;
        
    default: break;
  }
}

#pragma vector = TIMER3_B1_VECTOR
__interrupt void TIMER3_B1_ISR(void){
  switch(__even_in_range(TB0IV, OVERFLOW)){
    case NO_INTERRUPT: break;
    case CCR1PORT:
    break;
  case CCR2PORT:
    break;
  case OVERFLOW:
    break;
  default: break;
  }
}*/