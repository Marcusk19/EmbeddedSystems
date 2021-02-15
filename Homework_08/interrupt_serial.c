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
  volatile char USB_Char_Rx[SMALL_RING_SIZE];
  volatile char USB_Char_Tx[SMALL_RING_SIZE];
  extern char test_command[NCSU_SIZE];
  extern int UCA0_index;
  extern int UCA1_index;
  extern volatile unsigned int main_state;
//------------------------------------------------------------------------------

  
// UCA0 transmit and receive interrupt
#pragma vector = EUSCI_A0_VECTOR
__interrupt void eUSCI_A0_ISR(void){
  unsigned int temp;
  switch(__even_in_range(UCA0IV, 0x08)){         // Vector 0 - no interrupt
  case NO_INTERRUPT:    
    break;
  case RXIFG:                                       // Vector 2 - RXIFG
    //code for receive
    temp = usb_rx_ring_wr++;
    USB_Char_Rx[temp] = UCA0RXBUF;              // RX -> USB_Char_Rx character
    if(usb_rx_ring_wr >= (sizeof(USB_Char_Rx))){
      usb_rx_ring_wr = BEGINNING;               // Circular buffer back to beginning
    }
    
    break;
  case TXIFG:                                       // Vector 4 - TXIFG
    // code for transmit
        
    switch(UCA0_index++){
      case TX_CHAR0: //
        UCA0TXBUF = test_command[UCA0_index];
        break;
      case TX_CHAR1: //
        UCA0TXBUF = test_command[UCA0_index];
        break;
      case TX_CHAR2: //
        UCA0TXBUF = test_command[UCA0_index];
        break;
      case TX_CHAR3: //
        UCA0TXBUF = test_command[UCA0_index];
        break;
      case TX_CHAR4: //
        UCA0TXBUF = test_command[UCA0_index];
        break;
      case TX_CHAR5: //
       UCA0TXBUF = test_command[UCA0_index];
        break;
      case TX_CHAR6: //
        UCA0TXBUF = test_command[UCA0_index];
        break;
      case TX_CHAR7: //
        UCA0TXBUF = test_command[UCA0_index];
        break;
      case TX_CHAR8: //
        UCA0TXBUF = test_command[UCA0_index];
        break;
      case TX_CR:                                     // 
      UCA0TXBUF = ASCII_CR;
      break;
      case TX_LF:                                    // Vector 10 - no interrupt
      UCA0TXBUF = ASCII_LF;                      
      break;
      default:
      UCA0IE &= ~UCTXIE;                          // Disable TX interrupt
      break;
    }
    break;
  default: break;
  }
}


// UCA1 transmit and receive interrupt
#pragma vector = EUSCI_A1_VECTOR
__interrupt void eUSCI_A1_ISR(void){
  unsigned int temp;
  switch(__even_in_range(UCA1IV, 0x08)){         // Vector 0 - no interrupt
  case NO_INTERRUPT:    
    break;
  case RXIFG:                                       // Vector 2 - RXIFG
    //code for receive
    temp = usb_rx_ring_wr++;
    USB_Char_Rx[temp] = UCA1RXBUF;              // RX -> USB_Char_Rx character
    if(usb_rx_ring_wr >= (sizeof(USB_Char_Rx))){
      usb_rx_ring_wr = BEGINNING;               // Circular buffer back to beginning
    }
    break;
  case TXIFG:                                       // Vector 4 - TXIFG
    // code for transmit
        
    switch(UCA1_index++){
      case TX_CHAR0: //
        UCA1TXBUF = test_command[UCA1_index];
        break;
      case TX_CHAR1: //
        UCA1TXBUF = test_command[UCA1_index];
        break;
      case TX_CHAR2: //
        UCA1TXBUF = test_command[UCA1_index];
        break;
      case TX_CHAR3: //
        UCA1TXBUF = test_command[UCA1_index];
        break;
      case TX_CHAR4: //
        UCA1TXBUF = test_command[UCA1_index];
        break;
      case TX_CHAR5: //
        UCA1TXBUF = test_command[UCA1_index];
        break;
      case TX_CHAR6: //
        UCA1TXBUF = test_command[UCA1_index];
        break;
      case TX_CHAR7: //
        UCA1TXBUF = test_command[UCA1_index];
        break;
      case TX_CHAR8: //
        UCA1TXBUF = ASCII_LF;
      break;
      case TX_CR:                                     // 
      UCA1TXBUF = ASCII_CR;
      break;
      case TX_LF:                                    // Vector 10 - no interrupt
      UCA1TXBUF = ASCII_LF;
      break;
      default:
      UCA1IE &= ~UCTXIE;                          // Disable TX interrupt
      break;
    }
    break;
  default: break;
  }
}