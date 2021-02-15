//==============================================================================
// Filename : interrupt_ports.c
//
// Description: This file contains the interrupt service routines for ports
//
// Author: Marcus Kok
// Date: February 2020
// Compiler: Built with IAR Embedded Workbench for MSP430 7.12.4
//==============================================================================

#include "macros.h"
#include "msp430.h"
#include "functions.h"
#include <string.h>

unsigned int debounce_flag_SW1 = RESET_STATE;
unsigned int debounce_flag_SW2 = RESET_STATE;
extern volatile unsigned int debounce_count_SW1;
extern volatile unsigned int debounce_count_SW2;

extern volatile unsigned char display_changed;
extern char display_line[numLines][strSize];
//char* S1_display = "switch 1"; not used
//char* S2_display = "switch 2"; not used


#pragma vector = PORT4_VECTOR
__interrupt void switchP4_interrupt(void){
  //Switch 1
  if(P4IFG & SW1){
    strcpy(display_line[line2], " switch 1 ");
    update_string(display_line[line2], line2);
    enable_display_update();
    display_changed = TRUE;
    
    P4IFG &= ~SW1;                      // IFG SW1 cleared
    P4IE &= ~SW1;                       // disable switch interrupt
    
    debounce_flag_SW1 = TRUE;           // set flag
    debounce_count_SW1 = RESET_STATE;   // clear debounce count
    
    TB0CCTL1 |= CCIE;                   // enable debounce interrupt
    
    TB0CCTL0 &= ~CCIE;                  // disable backlight interrupt
    P6OUT &= ~LCD_BACKLITE;             // turn off backlight
    
  }
}

#pragma vector = PORT2_VECTOR
__interrupt void switchP2_interrupt(void){
  //Switch 2
  if(P2IFG & SW2){
    strcpy(display_line[line2], " switch 2 ");
    update_string(display_line[line2], line2);
    enable_display_update();
    display_changed = TRUE;
    
    P2IFG &= ~SW2;                      // IFG SW2 cleared
    P2IE &= ~SW2;                       // disable switch interrupt
    debounce_flag_SW2 = TRUE;           //set flag
    debounce_count_SW2 = RESET_STATE;   // clear debounce count
    TB0CCTL1 |= CCIE;                   // enable debounce interrupt
    TB0CCTL0 &= ~CCIE;                  // disable backlight interrupt
    P6OUT &= ~LCD_BACKLITE;             // turn off backlight
  }
}