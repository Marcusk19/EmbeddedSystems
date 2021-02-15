//==============================================================================
// Filename : Serial.c
//
// Description: This file contains the functions for serial communication
//
// Author: Marcus Kok
// Date: February 2020
// Compiler: Built with IAR Embedded Workbench for MSP430 7.12.4
//==============================================================================

#include "macros.h"
#include "msp430.h"
#include "functions.h"
#include <string.h>

//------------------------- globals --------------------------------------------

//------------------------------------------------------------------------------
void out_character(char character){
  // The while loop will stall as long as the Flag is not set (port is busy)
  while(!(UCA1IFG & UCTXIFG)){
    UCA1TXBUF = character;
  }
}