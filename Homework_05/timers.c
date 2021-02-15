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

