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

/*void Init_Timer_B2(void){
  TB2CTL = TBSSEL__SMCLK;       // smclk source
  TB2CTL = TBCLR;               // resets TB2R, clock divider, count direction
  TB2CTL = MC__CONTINUOUS;      // continuous up
  TB2CTL |= ID__2;              // divide clock by two
  TB2EX0 = TBIDEX__8;           // divide clock by an additional 8
  
  TB2CCR0 = TB2_CCR0_INTERVAL;  // CCR0
  TB2CCR0 |= CCIE;              // CCR0 enable interrupt
  
  //TB2CCR1 = TB1_CCR0_INTERVAL;  // CCR1
  //TB2CCR1 &= ~CCIE;              // disable interrupt
  
  //TB2CCR2 = TB1CCR2_INTERVAL;    // CCR2
  //TB2CCTL2 &= ~CCIE;            // CCR2 disable interrupt
  
  TB1CTL &= ~TBIE;              // Disable Overflow interrupt
  TB1CTL &= ~TBIFG;             // Clear Overflow Interrupt Flag 
}*/
    

void Init_Timer_B3(void){
 //----------------------------------------------------------------------------
 // smclk source, up count mode, PWM right side
 // TB3.1 P6.0 R_FORWARD
 // TB3.2 P6.1 L_FORWARD
 // TB3.3 P6.2 R_REVERSE
 // TB3.4 P6.3 L_REVERSE
 //----------------------------------------------------------------------------
  TB3CTL = TBSSEL__SMCLK;               //smclk source
  TB3CTL |= MC__UP;                     // up mode
  TB3CTL |= TBCLR;                      // clear TAR
  
  TB3CCR0 = WHEEL_PERIOD;               // PWM period
  
  TB3CCTL1 = OUTMOD_7;                  // CCR1 reset/set
  RIGHT_FORWARD_SPEED = WHEEL_OFF;      // P6.0 Right Forward PWM duty cycle
  
  TB3CCTL2 = OUTMOD_7;                  // CCR2 reset/set
  LEFT_FORWARD_SPEED = WHEEL_OFF;       // P6.1 Left Forward PWM duty cycle
  
  TB3CCTL3 = OUTMOD_7;                  // CCR3 reset/set
  RIGHT_REVERSE_SPEED = WHEEL_OFF;      // P6.2 Right Reverse PWM duty cycle
  
  TB3CCTL4 = OUTMOD_7;                  // CCR4 reset/set
  LEFT_REVERSE_SPEED = WHEEL_OFF;       // P6.3 Left Reverse PWM duty cycle
//------------------------------------------------------------------------------
}
    

