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
extern volatile char USB_Char_Rx[SMALL_RING_SIZE];
volatile char process_buf[LARGE_RING_SIZE];
char receive_char[MAX_STR_SIZE];
char transmit_char[MAX_STR_SIZE];
int process_index = BEGINNING;
int serial_mode = WAIT;
unsigned int serial_state = HOLD;
extern volatile char one_time;
volatile unsigned int next_state = RESET_STATE;

extern unsigned int one_second_flag;
extern unsigned int main_wait_count;
extern unsigned int wait_count;

//------------------------------------------------------------------------------
void out_character(char character){
  // The while loop will stall as long as the Flag is not set (port is busy)
  while(!(UCA1IFG & UCTXIFG)){
    UCA1TXBUF = character;
  }
}

void Send_And_Receive(void){
  switch(serial_state){
    case HOLD:
      if(one_second_flag){
        main_wait_count ++;
        one_second_flag = FALSE;
      }
      if(wait_count == TWO_SECOND_PAUSE){
        main_wait_count = RESET_STATE;
        serial_state = next_state;
      }
      break;
      
    case RECEIVE:
    if(usb_rx_ring_rd != usb_rx_ring_wr){
      
        process_buf[usb_rx_ring_rd] = USB_Char_Rx[usb_rx_ring_rd];
        
        if(process_buf[usb_rx_ring_rd] == 0x0A || process_buf[usb_rx_ring_rd] == 0x0D){
          clear_receive_char();
          clear_transmit_char();
          usb_rx_ring_rd = BEGINNING;
          usb_rx_ring_wr = BEGINNING;
          serial_state = PROCESS;
          one_time = TRUE;
          break;
        }
        usb_rx_ring_rd++;
        if(usb_rx_ring_rd >= (sizeof(USB_Char_Rx))){
          usb_rx_ring_rd = BEGINNING;
        }
    }
    
    break;
    case PROCESS:
      receive_char[process_index] = process_buf[process_index];
      process_buf[process_index] = '\0';                // clear out process buffer
      process_index++;
      if(process_buf[process_index] == 0x0A || process_buf[process_index] == 0x0D){
        receive_char[process_index] = '\0';             // null last char
        strcpy(transmit_char, receive_char);            // copy receive to transmit
        clear_line4();
        serial_state = HALT;
        serial_mode = RECEIVE;
        process_index = BEGINNING;
      }
    break;
    case HALT:
      
      break;
    default: break;
  }
}