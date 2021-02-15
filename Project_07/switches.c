//==============================================================================
// Filename : switches.c
// Description: This file contains the functions for switches display state
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
extern volatile unsigned char display_changed;
extern char display_line[numLines][strSize];
extern volatile unsigned char update_display;
extern unsigned int emitter_flag;
extern unsigned int black_line_flag;


void Switches_Process(void){
    if(emitter_flag){
      strcpy(display_line[line1], "  Emit.On ");
      update_string(display_line[line1], line1);
      enable_display_update();
      display_changed = TRUE;                        
    }
    else{
      strcpy(display_line[line1], "  Emit.Off");
      update_string(display_line[line1], line1);
      enable_display_update();
      display_changed = TRUE;
    }
    
    if(black_line_flag){
        strcpy(display_line[line1], " BLK LINE ");
        update_string(display_line[line1], line1);
        enable_display_update();
        display_changed = TRUE;
    }
}



