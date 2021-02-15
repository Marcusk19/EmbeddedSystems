//==============================================================================
// Filename : interrupt_ports.c
//
// Description: This file contains the interrupt service routines for ports
//
// Author: Marcus Kok
// Date: February 2020
// Compiler: Built with IAR Embedded Workbench for MSP430 7.12.4
//==============================================================================


//------------------------- globals --------------------------------------------
#include "macros.h"
#include "msp430.h"
#include "functions.h"
#include <string.h>

unsigned int debounce_flag_SW1 = RESET_STATE;
unsigned int debounce_flag_SW2 = RESET_STATE;
extern volatile unsigned int debounce_count_SW1;
extern volatile unsigned int debounce_count_SW2;
extern volatile unsigned int wheel_state;
unsigned int emitter_flag = TRUE;               // true if emitter on, false if off
extern unsigned int emitter_display_change;
extern unsigned int one_second_flag;
extern unsigned int wait_count;
int display_state = TOGGLE_TWO;                 

extern char test_command[NCSU_SIZE];
extern char transmit_char[MAX_STR_SIZE];
extern int UCA1_index;
extern int UCA0_index;

extern volatile unsigned char display_changed;
extern char display_line[numLines][strSize];
//char* S1_display = "switch 1"; not used
//char* S2_display = "switch 2"; not used

extern volatile unsigned int main_state;
extern volatile unsigned int next_state;
extern int serial_mode;
//------------------------------------------------------------------------------

#pragma vector = PORT4_VECTOR
__interrupt void switchP4_interrupt(void){
  //Switch 1
  if(P4IFG & SW1){
    //strcpy(display_line[line2], " switch 1 ");
    //update_string(display_line[line2], line2);
    //enable_display_update();
    //display_changed = TRUE;   
    P4IFG &= ~SW1;                      // IFG SW1 cleared
    P4IE &= ~SW1;                       // disable switch interrupt  
    debounce_flag_SW1 = TRUE;           // set flag
    debounce_count_SW1 = RESET_STATE;   // clear debounce count
    TB0CCTL1 |= CCIE;                   // enable debounce interrupt
    
    strcpy(display_line[line1], "          ");  // clear lines 1 and 2 of display
    update_string(display_line[line1], line1);
    strcpy(display_line[line2], "          ");
    update_string(display_line[line2], line2);
    enable_display_update();
    display_changed = TRUE;

    UCA0_index = BEGINNING;              // enable transmit interrupt
    UCA0TXBUF = transmit_char[UCA0_index++];
    UCA0IE |= UCTXIE; 
    
    serial_mode = TRANSMITTING;
  }
}

#pragma vector = PORT2_VECTOR
__interrupt void switchP2_interrupt(void){
  //Switch 2
  if(P2IFG & SW2){
    P2IFG &= ~SW2;                      // IFG SW2 cleared
    P2IE &= ~SW2;                       // disable switch interrupt
    debounce_flag_SW2 = TRUE;           //set flag
    debounce_count_SW2 = RESET_STATE;   // clear debounce count
    TB0CCTL1 |= CCIE;                   // enable debounce interrupt
    
    
    strcpy(display_line[line1], "          ");  // clear lines 1 and 2 of display
    update_string(display_line[line1], line1);
    strcpy(display_line[line2], "          ");
    update_string(display_line[line2], line2);
    enable_display_update();
    display_changed = TRUE;
    
    
    if(display_state == TOGGLE_ONE){
    display_state = TOGGLE_TWO;
    
    UCA0BRW = UCA0BRW_115200;           // set baud rate to 460800
    UCA0MCTLW = UCA0MCTLW_115200;
    UCA1BRW = UCA0BRW_115200;           // set baud rate to 460800
    UCA1MCTLW = UCA0MCTLW_115200;
    }else{
      display_state = TOGGLE_ONE;
      
      UCA0BRW = UCA0BRW_460800;           // set baud rate to 460800
      UCA0MCTLW = UCA0MCTLW_460800;
      UCA1BRW = UCA0BRW_460800;           // set baud rate to 460800
      UCA1MCTLW = UCA0MCTLW_460800;
    }
    // emitter toggle not used
    /*
    // toggle emitter on/off
    if(emitter_flag){
      emitter_Off();
      emitter_flag = FALSE;                        
    }
    else{
      emitter_On();
      emitter_flag = TRUE;      
    } */   
  }
}

