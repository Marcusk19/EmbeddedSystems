//==============================================================================
// Filename : wheels.c
//
// Description: This file contains the functions for the wheels 
//
// Author: Marcus Kok
// Date: February 2020
// Compiler: Built with IAR Embedded Workbench for MSP430 7.12.4
//==============================================================================
#include  "functions.h"
#include  "msp430.h"
#include "macros.h"

//GLOBALS=======================================================================
extern volatile unsigned int Time_Sequence;
extern unsigned int prevTime_Sequence; 
extern unsigned int myTime;
int shapeCount = RESET_STATE;
int wheelCount = RESET_STATE;
//==============================================================================

//------------------------------------------------------------------------------
//timer B0 initialization

void Init_Timer_B0(void){
  TB0CTL = TBSSEL__SMCLK; //smclk source
  TB0CTL |= TBCLR; //resets TB0R, clock divider, count direction
  TB0CTL |= MC__CONTINUOUS; //continuous up
  TB0CTL |= ID__2; //divide clock by 2
  
  TB0EX0 = TBIDEX__8; // Divide clock by an additional 8
  
  TB0CCR0 = TB0CCR0_INTERVAL; // CCR0
  TB0CCTL0 |= CCIE; // CCR0 enable interrupt

  TB0CCR1 = TB0CCR1_INTERVAL; // CCR1
  TB0CCTL1 &=  ~CCIE; // CCR1 disable interrupt
  
  TB0CCR2 = TB0CCR2_INTERVAL; // CCR2
  TB0CCTL2 |= CCIE; // CCR2 disable interrupt
  
  
  TB0CTL &= ~TBIE ; // Disable Overflow Interrupt
  TB0CTL &= ~TBIFG ; // Clear Overflow Interrupt flag
}


// my own timer function
void clock_process(void){
  if(prevTime_Sequence != Time_Sequence){
    prevTime_Sequence = Time_Sequence; 
    myTime ++; 
    shapeCount ++;
    wheelCount ++;
  }
  if(myTime == CLOCK_CYCLE){
    myTime = RESET_STATE;
  }
}

