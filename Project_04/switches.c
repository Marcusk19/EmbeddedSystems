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

extern unsigned int buttonPress;
extern char display_line[numLines][strSize];
extern unsigned int num_presses;


void Switches_Process(void){
  
  //Switch 1
  if(!(P4IN &= SW1)){
    buttonPress = FIGURE_EIGHT;
  }
  
   if(!(P2IN &= SW2)){
   buttonPress = TRIANGLE;
   }
    displayShapes(); 
    runShapes();
  //Switch 2
}

//not used =====================================================================

  /*switch(num_presses){
    case CIRCLE: 
      buttonPress = CIRCLE;
      break;
    case FIGURE_EIGHT:
      buttonPress = FIGURE_EIGHT;
      break;
    case TRIANGLE: 
      buttonPress = TRIANGLE;
      break;
    case NUM_SHAPES:
      num_presses = RESET_STATE;
      buttonPress = HOLD;
      break;
    default:
      break;
    }*/
    /*if(num_presses == CIRCLE){
      buttonPress = CIRCLE;
    }
    if(num_presses == FIGURE_EIGHT){
      buttonPress = FIGURE_EIGHT;
    }
    if(num_presses == TRIANGLE){
      buttonPress = TRIANGLE;
    }
    if(num_presses >= NUM_SHAPES){
      num_presses = RESET_STATE;
    }*/

