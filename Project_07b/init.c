//==============================================================================
// Filename : init.c
// Description: This file contains the initializing function declarations
//              used for wheels, ADC, etc.
// 
// Author: Marcus Kok
// Date: January 2020
// Compiler: Made with IAR Embedded Workbench for MSP430 7.12.4
//==============================================================================

#include "macros.h"
#include "msp430.h"
#include "functions.h"
//----------------------------------globals-------------------------------------

extern volatile unsigned char update_display;
extern volatile unsigned int update_display_count;
extern char display_line[numLines][strSize];
extern char *display[numLines];
extern volatile char USB_Char_Rx[SMALL_RING_SIZE];
extern volatile char USB_Char_Tx[SMALL_RING_SIZE];
extern volatile unsigned int usb_rx_ring_wr;
unsigned int usb_rx_ring_rd, usb_tx_ring_rd = BEGINNING;
extern volatile unsigned int usb_tx_ring_wr;
extern unsigned int PC_transmit;


//------------------------------------------------------------------------------

void enable_interrupts(void){
  __bis_SR_register(GIE);     // enable interrupts
  asm volatile ("eint \n");
}

void Init_Timers(void){
  Init_Timer_B0();
  Init_Timer_B3();
}

void Init_ADC(void){
//------------------------------------------------------------------------------
// V_Detect_L           (0x04) // Pin 2 A2
// V_DETECT_R           (0x08) // Pin 3 A3
// V_THUMB              (0x20) // Pin 5 A5
//------------------------------------------------------------------------------
  //ADCCTL0 Register
  ADCCTL0 = RESET_STATE;                  // reset
  ADCCTL0 |= ADCSHT_2;          // 16 ADC clocks
  ADCCTL0 |= ADCMSC;             // MSC
  ADCCTL0 |= ADCON;             // ADC ON
  
  //ADCCTL1 Register
  ADCCTL1 = RESET_STATE;                  // reset
  ADCCTL1 |= ADCSHS_0;          // 00b = ADCSC bit
  ADCCTL1 |= ADCSHP;            // ADC sample and hold SAMPCON singal from sampling timer
  ADCCTL1 &= ~ADCISSH;          // ADC invert signal sample-and-hold
  ADCCTL1 |= ADCDIV_0;          // ADC clock divider - 00b = Divide by 1
  ADCCTL1 |= ADCSSEL_0;         // ADC clock MODCLK
  ADCCTL1 |= ADCCONSEQ_0;       // ADC conversion sequence 00b = single channel single conversion
  // ADCCTL1 & ADCBUSY identifies a conversion is in process
  
  // ADCCTL2 Register
  ADCCTL2 = RESET_STATE; // Reset
  ADCCTL2 |= ADCPDIV0;          // ADC pre-divider 00b = Pre-divide by 1
  ADCCTL2 |= ADCRES_2;          // ADC resolution 10b = 12 bit (14 clock cycle conversion time)
  ADCCTL2 &= ~ADCDF;            // ADC data read-back format 0b = Binary unsigned.
  ADCCTL2 &= ~ADCSR;            // ADC sampling rate 0b = ADC buffer supports up to 200 ksps
  
  // ADCMCTL0 Register
  ADCMCTL0 |= ADCSREF_0;        // VREF - 000b = {VR+ = AVCC and VR– = AVSS }
  ADCMCTL0 |= ADCINCH_2;        // V_THUMB (0x20) Pin 5 A5
  ADCIE |= ADCIE0;              // Enable ADC conv complete interrupt
  ADCCTL0 |= ADCENC;            // ADC enable conversion.
  ADCCTL0 |= ADCSC;             // ADC start conversion.
}


void Init_Wheels(void){
  RIGHT_FORWARD_SPEED = WHEEL_OFF;
  LEFT_FORWARD_SPEED = WHEEL_OFF;
  RIGHT_REVERSE_SPEED = WHEEL_OFF;
  LEFT_REVERSE_SPEED = WHEEL_OFF;
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

void Init_Serial_UCA0(void){
  int i;
  for(i = BEGINNING; i < SMALL_RING_SIZE; i++){
    USB_Char_Rx[i] = CLEAR;              // USB Rx buffer
  }
  usb_rx_ring_wr = BEGINNING;
  usb_rx_ring_rd = BEGINNING;
  
  for(i = BEGINNING; i < LARGE_RING_SIZE; i++){         // may not use this
    USB_Char_Tx[i] = CLEAR;              // USB Tx buffer
  }
  usb_tx_ring_wr = BEGINNING;
  usb_tx_ring_rd = BEGINNING;
  
  // Configure UART 0
  UCA0CTLW0 = RESET_STATE;              // use word register
  UCA0CTLW0 |= UCSWRST;                 // set software reset enable
  UCA0CTLW0 |= UCSSEL__SMCLK;           // set SMCLK as fBRCLK
  
  // 115,200 baud rate
  // 1. calculate n = fBRCLK / baudrate
  //    n = SMCLK/115,200 = 8,000,000 / 115,200 = 69.4444
  //    if n > 16 continue with step 3 otherwise, step 4
  // 2. OS16 = 0, UCBRx = INT(n)
  // continue with step 4
  // 3. OS16 = 1,
  //    UCx             = INT(n/16)
  //                    = INT(n/16) = 69.44444/16 => 4
  //   UCFx             = INT([(n/16) - INT(n/16)] * 16)
  //                    = INT([69.44444/16 - INT(69.444/16)]*16)
  //                    = INT(.3403*16)
  //                    = 5
  // UCSx found by looking up fractional part of N (= N-INT(N)) in table 
  // Table 18-4 => 0x55
  
  UCA0BRW = BRW_115200;
  // UCA0MCTLW = UCSx concatenate UCFx concatenate UCOS16;
  // UCA0MCTLW = 0x55 concatenate 1
  UCA0MCTLW = MCTLW_115200;
  UCA0CTLW0 &= ~ UCSWRST;       // set software reset enable    
  UCA0IE |= UCRXIE;             // enable Rx interrupt 
  //UCA0IE |= UCTXIE;             // enable Tx interrupt
}

void Init_Serial_UCA1(void){
  
  // Configure UART 0
  UCA1CTLW0 = RESET_STATE;              // use word register
  UCA1CTLW0 |= UCSWRST;                 // set software reset enable
  UCA1CTLW0 |= UCSSEL__SMCLK;           // set SMCLK as fBRCLK
 
  UCA1BRW = BRW_115200;
  // UCA0MCTLW = UCSx concatenate UCFx concatenate UCOS16;
  // UCA0MCTLW = 0x55 concatenate 1
  UCA1MCTLW = MCTLW_115200;
  UCA1CTLW0 &= ~UCSWRST;       // set software reset enable    
  UCA1IE |= UCRXIE;             // enable Rx interrupt 
  UCA1IE &= ~UCTXIE;            // disable Tx interrupt
}

  
    

  