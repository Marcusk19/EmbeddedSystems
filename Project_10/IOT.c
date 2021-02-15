//==============================================================================
// Filename : IOT.c
//
// Description: This file contains functions for communication with IOT       
//
// Author: Marcus Kok
// Date: April 2020
// Compiler: Built with IAR Embedded Workbench for MSP430 7.12.4
//==============================================================================
#include "macros.h"
#include "msp430.h"
#include "functions.h"
#include <string.h>
// globals
extern int UCA0_index;
extern int UCA1_index;
char slash[] = "//\r";
char F[] = "/F\r";
char here[] = "I'm here\r\n";
extern char command_buf[MAX_STR_SIZE];
extern char transmit_char[LARGE_RING_SIZE];
extern volatile char command_ready;
extern unsigned int usb_rx_ring_rd;
extern volatile unsigned int usb_rx_ring_wr;
extern volatile char USB_Char_Rx[SMALL_RING_SIZE];
extern volatile char process_buf[LARGE_RING_SIZE];
extern char transmit_char[LARGE_RING_SIZE];
unsigned int IOT_state = RECEIVE;
int process_index = BEGINNING;
int transmit_index = BEGINNING;
extern unsigned int command_output;
extern int UCA1_index;
extern volatile unsigned int wheel_state;
extern int serial_display;
char command_code[] = "/0816";
int command_duration;
int hundreds = RESET_STATE;
int tens = RESET_STATE;
int ones = RESET_STATE;
int run_wheels = FALSE;

extern int wifi_command;
extern int wifi_command_index;
char transmit_command[LARGE_RING_SIZE];
char test_purpose[LARGE_RING_SIZE];
extern int stop_USB_receive;
char wifi_transmit[LARGE_RING_SIZE];
extern volatile unsigned int main_state;
extern unsigned int exit_line;
extern int display_state;
//------------------------------------------------------------------------------

void wait_for_command(void){
  
  switch(IOT_state){
  case HOLD:
    break;
  case RECEIVE:
    if(usb_rx_ring_rd != usb_rx_ring_wr){
      process_buf[process_index] = USB_Char_Rx[usb_rx_ring_rd++];     // ring buffer -> process buffer
      
      if(usb_rx_ring_rd >= (sizeof(USB_Char_Rx))){
        usb_rx_ring_rd = BEGINNING;               // circular buffer
      }
      if(process_index >= (sizeof(process_buf))){
        process_index = BEGINNING;                        // circular buffer
      }
      if(process_buf[process_index] == ASCII_CR){
        IOT_state = PROCESS;
      }
      else
        process_index++;
    }
    break;
  case PROCESS:
    process_index = BEGINNING;          // reset index for next command
    clear_transmit_char();              // clear transmit char to process commadn
    copy_to_transmit();                 // process_buf -> transmit_char
    verify_command();
    command_duration = RESET_STATE;     // reset command_duration before obtaining it
    get_command_time();                 // obtain command time
    process_command();                  // choose output based on command received
    
    strcat(transmit_char, "\n");
    reset_process_buf();                // reset process buffer for next command
    reset_USB_Char_Rx();
    
    
    UCA1_index = BEGINNING;             // reset index to transmit char
    command_output = TRUE;
    UCA1IE |= UCTXIE;
    IOT_state = RECEIVE;                // move state back
    break;
  case TRANSMIT:
    break;

  default: break;
  }
}


void process_command(void){
  switch(process_buf[KEYWORD]){
  case '/':
    strcat(transmit_char, "\nI'm here\n");
    break;
  case 'M':
  case 'm':
    Init_ADC();                 // enable ADC conversions
    clear_LCD();
    emitter_On();               // turn on emitter;
    wheel_state = HOLD;
    main_state = FIND_LINE;
    break;
  case 'E':
  case 'e':
    clear_LCD();
    display_state = EXIT_LINE;
    exit_line = TRUE;
    break;
  case 'F':
  case 'f':
    clear_LCD();
    serial_display = FORWARD_DISP;
    wheel_state = FORWARD;
    break;
  case 'B':
  case 'b':
    serial_display = REVERSE_DISP;
    wheel_state = REVERSE;
    break;
  case 'R':
  case 'r':
    serial_display = RIGHT_DISP;
    wheel_state = RIGHT_TURN;
    break;
  case 'L':
  case 'l':
    serial_display = LEFT_DISP;
    wheel_state = LEFT_TURN;
    break;
  case 'S':
  case 's':
    wheel_state = HOLD;
    main_state = CONTROL;
    break;
  case '0':
    clear_LCD();
    serial_display = PT_ZERO;
    break;
  case '1':
    clear_LCD();
    serial_display = PT_ONE;
    break;
  case '2':
    clear_LCD();
    serial_display = PT_TWO;
    break;
  case '3':
    clear_LCD();
    serial_display = PT_THREE;
    break;
  case '4':
    clear_LCD();
    serial_display = PT_FOUR;
    break;
  case '5':
    clear_LCD();
    serial_display = PT_FIVE;
    break;
  case '6':
    clear_LCD();
    serial_display = PT_SIX;
    break;
  case '7':
    clear_LCD();
    serial_display = PT_SEVEN;
    break;
  case '8':
    clear_LCD();
    serial_display = PT_EIGHT;
    break;
  default:  
    break;
  }
command_ready = FALSE;                  // reset flag
}

void verify_command(void){
  for(int i = 1; i < 5; i++){
    if(process_buf[i] != command_code[i]){
      strcpy(transmit_char, "Error");
      IOT_state = RECEIVE;
    }
  }
}

void get_command_time(void){
  hundreds = RESET_STATE;
  hundreds = (process_buf[6] - 48) * 100;
  tens = RESET_STATE; 
  tens = (process_buf[7] - 48) * 10;
  ones = RESET_STATE;
  ones = process_buf[8] - 48;
  command_duration = hundreds + tens + ones;
}

void send_command(char* command){
  int m = strlen(command);
    for(int i = BEGINNING; i < m; i++){
        wifi_transmit[i] = *command;
        command++;
    }
    wifi_command = TRUE;
    UCA0_index = BEGINNING;
    UCA0IE |= UCTXIE;   
}

void clear_transmit_char(void){
  for(int i = BEGINNING; i < sizeof(transmit_char); i++){
    transmit_char[i] = NULL;
  }
}

void reset_process_buf(void){
  for(int i = BEGINNING; i < LARGE_RING_SIZE; i++){
    process_buf[i] = NULL;
  }
}

void copy_to_transmit(void){
  for(int i = BEGINNING; i < LARGE_RING_SIZE; i++){
    transmit_char[i] = process_buf[i];
  }
}

void reset_USB_Char_Rx(void){
  for(int i = BEGINNING; i < SMALL_RING_SIZE; i++){
    USB_Char_Rx[i] = NULL;
  }
  usb_rx_ring_rd = BEGINNING;
  usb_rx_ring_wr = BEGINNING;
}

void clear_transmit_command(void){
  for(int i = BEGINNING; i < LARGE_RING_SIZE; i++){
    transmit_command[i] = NULL;
  }
}