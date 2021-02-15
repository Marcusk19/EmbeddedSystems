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
int UCA1_index;
int UCA0_index = RESET_STATE;
char test_command[NCSU_SIZE] = "NCSU  #1";
extern unsigned int usb_rx_ring_rd;
extern volatile unsigned int usb_rx_ring_wr;
unsigned int pb_wr = BEGINNING;
extern volatile char USB_Char_Rx[SMALL_RING_SIZE];
volatile char process_buf[LARGE_RING_SIZE];
char transmit_char[LARGE_RING_SIZE];
int serial_display = WAIT;
unsigned int serial_state = HOLD;
extern volatile char one_time;
volatile unsigned int next_state = RESET_STATE;

extern unsigned int one_second_flag;
extern unsigned int main_wait_count;
extern unsigned int wait_count;
extern char process_buf[];
extern char command_buf[];
extern volatile char command_ready;

//------------------------------------------------------------------------------
void out_character(char character){
  // The while loop will stall as long as the Flag is not set (port is busy)
  //while(!(UCA0IFG & UCTXIFG));                   
    UCA0TXBUF = character;
}

/*
void Send_And_Receive(void){
  switch(serial_state){
    case HOLD:
      break;
      
    case RECEIVE:
    if(usb_rx_ring_rd != usb_rx_ring_wr){       // only happens when wr differs from rd
        process_buf[pb_wr] = USB_Char_Rx[usb_rx_ring_rd++];   // USB_Char_Rx ring buffer -> process_buff
        
        if(process_buf[pb_wr] == ASCII_CR){     // CR marks end of receiving characters
          usb_rx_ring_rd++;
       // clear arrays to process characters
          clear_transmit_char();
          clear_command_buf();
          process_index = BEGINNING;
          pb_wr = BEGINNING;
          serial_state = PROCESS;       // move state to process array
          one_time = TRUE;
          break;
        }
        
        if(usb_rx_ring_rd >= (sizeof(USB_Char_Rx))){
          usb_rx_ring_rd = BEGINNING;           // circular buffer back to beginning
        }
        if(pb_wr >= (sizeof(process_buf))){
          pb_wr = BEGINNING;                    // circular buffer back to beginning
        }
        pb_wr++;
    }  
    break;
    case PROCESS:
      transmit_char[process_index] = process_buf[process_index]; // process_buf -> transmit_char array
      process_buf[process_index] = NULL;                         // clear out process buffer
      if(transmit_char[process_index] == ASCII_CR){
        if(transmit_char[BEGINNING] == '/'){            // first character marks a command       
          strcpy(command_buf, transmit_char);              // copy receive to command
          serial_state = COMMAND;
        }
        else serial_state = TRANSMIT;
      }
      
      process_index++;
    break;
    
  case COMMAND:
    process_command(); // run function that takes command buffer and sets transmit array according to command
    UCA1_index = BEGINNING;
    UCA1IE |= UCTXIE;                       // trigger UCA1 transmit ISR
    serial_state = RECEIVE;
    break;
    
  case TRANSMIT:
    UCA1_index = BEGINNING;
    UCA1IE |= UCTXIE;           // enable interrupt    
    serial_state = RECEIVE;
    break;
    default: break;
  }
}*/


void clear_command_buf(void){
  for(int i = BEGINNING; i < MAX_STR_SIZE; i++){
    command_buf[i] = NULL;
  }
}




