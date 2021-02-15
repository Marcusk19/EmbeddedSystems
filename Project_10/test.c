//==============================================================================
// Filename : test.c
//
// Description: This file contains test functions before they are moved to corresponding files        
//
// Author: Marcus Kok
// Date: March 2020
// Compiler: Built with IAR Embedded Workbench for MSP430 7.12.4
//==============================================================================
#include "macros.h"
#include "msp430.h"
#include "functions.h"
#include <string.h>
// globals
extern int UCA0_index;
extern int UCA1_index;
extern char command_buf[MAX_STR_SIZE];
extern char transmit_char[LARGE_RING_SIZE];
extern volatile char command_ready;
extern unsigned int usb_rx_ring_rd;
extern volatile unsigned int usb_rx_ring_wr;
extern volatile unsigned int IOT_ring_wr;
unsigned int IOT_ring_rd = BEGINNING;
extern volatile char USB_Char_Rx[SMALL_RING_SIZE];
extern volatile char process_buf[LARGE_RING_SIZE];
extern char transmit_char[LARGE_RING_SIZE];
extern unsigned int IOT_state;
extern int process_index;
extern unsigned int command_output;
extern int UCA1_index;
extern volatile char IOT_out_ring[LARGE_RING_SIZE];
unsigned int IP_index = BEGINNING;
char IP_addr[IP_ADDRESS_SIZE];
char IP_buffer[XLARGE_RING_SIZE];
int parse = FALSE;

char AT_NSTAT[] = {"AT+NSTAT=?\r"};
char ip_one[10];
char ip_two[10];
char ip_three[4];
char ip_four[4];

extern char display_line[numLines][strSize];
extern volatile unsigned char display_changed;

extern volatile unsigned int main_state;
extern char current_IOT_char;
extern int new_IOT_char;

//==============================================================================


void get_ip(void){
  
    
    if(new_IOT_char){
      
      if(current_IOT_char >= 0x2E && current_IOT_char < 0x3A){    // is it a number?
        IP_addr[IP_index++] = current_IOT_char;
        if(IP_index >= (sizeof(IP_addr)))
          main_state = PROCESS_IP;
      }
      if(current_IOT_char == ':'){
        IP_addr[IP_index] = NULL;
        main_state = PROCESS_IP;
      }
      new_IOT_char = FALSE;
      
    }
    
}


void display_ip(void){
  lcd_4line();
  
  strcpy(display_line[line1], "IP address");
  update_string(display_line[line1], line1);
  
  strcpy(display_line[line2], ip_one);
  update_string(display_line[line2], line2);
  
  strcpy(display_line[line3], ip_two);
  update_string(display_line[line3], line3);
  
  display_changed = TRUE;
}

void process_ip(void){
  int m = BEGINNING;
  int j = BEGINNING;
  for(int i = BEGINNING; i < (sizeof(IP_addr)); i++){
    switch(m){
    case 0:
      ip_one[j++] = IP_addr[i];
      if(j >= 10){
        j = BEGINNING;
        m++;
      }
      break;
    case 1:
      ip_two[j++] = IP_addr[i];
      if(j >= 10){
        j = BEGINNING;
        m++;
      }
      break;
    default: break;
    }
  }
  main_state = DISPLAY_IP;
}

//this code can replace the code in interrupt_serial for termite use
/*#pragma vector = EUSCI_A1_VECTOR
__interrupt void eUSCI_A1_ISR(void){           
  switch(__even_in_range(UCA1IV, 0x08)){         // Vector 0 - no interrupt
  case NO_INTERRUPT:    
    break;
  case RXIFG:                                       // Vector 2 - RXIFG, characters coming from the PC to FRAM
    PC_receive_char = UCA1RXBUF;                   // Rx -> receive char character
        
      if(PC_receive_char == '/'){
        FRAM_Command = TRUE;                      // checks to see if it is a command
      }
      if(FRAM_Command){                           // if command put char into ring buffer
        temp = usb_rx_ring_wr++;
        USB_Char_Rx[temp] = PC_receive_char;
        if(usb_rx_ring_wr >= (sizeof(USB_Char_Rx))){
          usb_rx_ring_wr = BEGINNING;             // circular buffer
          serial_state = RECEIVE;
        }
      }else{                                      // if not command send to UCA0TXBUF
        UCA0TXBUF = PC_receive_char;
        UCA1IE |= UCTXIE;
      }
      if(PC_receive_char == ASCII_CR && FRAM_Command){
        FRAM_Command = FALSE;                     // command finished, stop putting characters in ring buffer
        IOT_state = PROCESS;                      // put IOT in process state
      }
         
    break;*/
