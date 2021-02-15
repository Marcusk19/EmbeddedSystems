//==============================================================================
// Filename : interrupt_serial.c
//
// Description: This file contains the interrupt service routines for serial 
//              communications        
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
//------------------------------------------------------------------------------

  volatile unsigned int usb_rx_ring_wr = BEGINNING;
  volatile unsigned int usb_tx_ring_wr = BEGINNING;
  volatile unsigned int IOT_ring_wr = BEGINNING;
  volatile char USB_Char_Rx[SMALL_RING_SIZE];
  volatile char USB_Char_Tx[SMALL_RING_SIZE];
  volatile char IOT_out_ring[LARGE_RING_SIZE];
  extern char test_command[NCSU_SIZE];
  extern char transmit_char[LARGE_RING_SIZE];
  extern int UCA0_index;
  extern int UCA1_index;
  extern volatile unsigned int main_state;
  extern volatile char one_time;
  unsigned int PC_transmit = FALSE;
  unsigned int FRAM_Command = FALSE;
  unsigned int command_output = FALSE;
  unsigned int read_index;
  volatile char command_ready = FALSE;
  char command_buf[MAX_STR_SIZE];
  int command_index = BEGINNING;
  extern unsigned int serial_state;
  extern unsigned int IOT_state;
  unsigned int temp;
  unsigned int temp_IOT_wr;
  char PC_loopback;
  char PC_receive_char;
  char current_IOT_char;
  int new_IOT_char = FALSE;
  char wifi_message = FALSE;
  char receive_command = TRUE;
  int wifi_command_index = BEGINNING;
  int wifi_command = FALSE;
  extern char transmit_command[LARGE_RING_SIZE];
  extern char wifi_transmit[LARGE_RING_SIZE];
  int stop_USB_receive = FALSE;
  
//------------------------------------------------------------------------------

  
// UCA0 transmit and receive interrupt
#pragma vector = EUSCI_A0_VECTOR
__interrupt void eUSCI_A0_ISR(void){
  switch(__even_in_range(UCA0IV, 0x08)){         // Vector 0 - no interrupt
  case NO_INTERRUPT:    
    break;
  case RXIFG:                                   // Vector 2 - RXIFG
    //code for receive
    PC_loopback = UCA0RXBUF;
    UCA1TXBUF = PC_loopback;                    // what is received on 0 is transmitted out 1
    
    temp_IOT_wr = IOT_ring_wr++;
    IOT_out_ring[temp_IOT_wr] = PC_loopback;
    current_IOT_char = PC_loopback;
    new_IOT_char = TRUE;
  //-------------------- code for receiving commands via wifi-------------------
      if(PC_loopback == '/'){
        FRAM_Command = TRUE;                      // checks to see if it is a command
      }
      if(FRAM_Command){                           // if command put char into ring buffer
        temp = usb_rx_ring_wr++;
        USB_Char_Rx[temp] = PC_loopback;
        if(usb_rx_ring_wr >= (sizeof(USB_Char_Rx))){
          usb_rx_ring_wr = BEGINNING;             // circular buffer
        }
      }
      if(PC_loopback == ASCII_CR && FRAM_Command){
        FRAM_Command = FALSE;                     // command finished, stop putting characters in ring buffer
        IOT_state = PROCESS;                      // put IOT in process state
      }   
  //----------------------------------------------------------------------------  
    if(IOT_ring_wr >= (sizeof(IOT_out_ring))){
      IOT_ring_wr = BEGINNING;                  // circular buffer        
    }
    break;   
  case TXIFG:                                       // Vector 4 - TXIFG
    if(wifi_command){
    UCA0TXBUF = wifi_transmit[UCA0_index++];
    if(wifi_transmit[UCA0_index] == NULL){
      UCA0IE &= ~UCTXIE;
      wifi_command = FALSE;
    }
    }
    break;
  default: break;
  }
}



// UCA1 transmit and receive interrupt
#pragma vector = EUSCI_A1_VECTOR
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
        }
      }else{                                      // if not command send to UCA0TXBUF
        UCA0TXBUF = PC_receive_char;
        UCA0IE |= UCTXIE;
        UCA1IE |= UCTXIE;
      }
      if(PC_receive_char == ASCII_CR && FRAM_Command){
        FRAM_Command = FALSE;                     // command finished, stop putting characters in ring buffer
        IOT_state = PROCESS;                      // put IOT in process state
      }
         
    break;
  case TXIFG:                                       // Vector 4 - TXIFG
    // code for transmit out USB
    if(command_output){                         // only run if command output is happening
      UCA1TXBUF = transmit_char[UCA1_index++];
      if(transmit_char[UCA1_index] == NULL){
        command_output = FALSE;
        UCA1IE &= ~UCTXIE;
      }
    }else{
      UCA1IE &= ~UCTXIE;
    }
    break;
  default: break;
  }
}