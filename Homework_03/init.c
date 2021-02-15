//==============================================================================
// Filename : init.c
// Description: This file contains the initializing function declarations
// 
// Author: Marcus Kok
// Date: January 2020
// Compiler: Made with IAR Embedded Workbench for MSP430 7.12.4
//==============================================================================

#include "macros.h"
#include "msp430.h"

extern volatile unsigned char update_display;
extern volatile unsigned int update_display_count;
extern char display_line[numLines][strSize];
extern char *display[numLines];

void enable_interrupts(void){
  __bis_SR_register(GIE);     // enable interrupts
  asm volatile ("eint \n");
}

void Init_Conditions(void){
//------------------------------------------------------------------------------
  int i;

  for(i=start;i<loopEnd;i++){
    display_line[line1][i] = RESET_STATE;
    display_line[line2][i] = RESET_STATE;
    display_line[line3][i] = RESET_STATE;
    display_line[line4][i] = RESET_STATE;
  }
  display_line[line1][charlength] = RESET_STATE;
  display_line[line2][charlength] = RESET_STATE;
  display_line[line3][charlength] = RESET_STATE;
  display_line[line4][charlength] = RESET_STATE;

  display[line1] = &display_line[line1][RESET_STATE];
  display[line2] = &display_line[line2][RESET_STATE];
  display[line3] = &display_line[line3][RESET_STATE];
  display[line4] = &display_line[line4][RESET_STATE];
  update_display = RESET_STATE;
  update_display_count = RESET_STATE;
// Interrupts are disabled by default, enable them.
  enable_interrupts();
//------------------------------------------------------------------------------
}

  