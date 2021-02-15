//==============================================================================
// Filename : switches.c
// Description: This file contains the functions for switches on the fram board
// 
// Author: Marcus Kok
// Date: January 2020
// Compiler: Made with IAR Embedded Workbench for MSP430 7.12.4
//==============================================================================

#include  "functions.h"
#include  "msp430.h"
#include "macros.h"
#include <string.h>

extern unsigned int buttonState;
extern char display_line[numLines][strSize];
extern unsigned int num_presses;


void Switches_Process(void){
  
  //Switch 1
  if(!(P4IN & SW1)){
    buttonState = SET_SMCLK;
    runSwitches();
  }
  
   if(!(P2IN & SW2)){
     buttonState = SET_GPIO;
     runSwitches();
   }
  //Switch 2
}

void runSwitches(void){
  switch(buttonState){
  case HOLD: 
    break;
    
  case SET_SMCLK:
    Init_Port3(USE_SMCLK);
    break;
  
  case SET_GPIO:
    Init_Port3(USE_GPIO);
    break;
    
  default:
    break;
  }
}


