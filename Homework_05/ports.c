//==============================================================================
// Filename : ports.c
// Description: This file contains the Initialization for all port pins
//
// Author: Marcus Kok
// Date: January 2020
// Compiler: Built with IAR Embedded Workbench for MSP430 7.12.4
//==============================================================================

#include  "msp430.h"
#include "macros.h"

// configure port 1

void Init_Port1(void){
//------------------------------------------------------------------------------
  // configure Port1
  P1OUT = PIN_OUT; // P1OUT set to low
  P1DIR = OUT_LOW; // set direction to output
  
  P1SEL0 &= ~RED_LED; //RED LED GPIO operation
  P1SEL1 &= ~RED_LED; // RED_LED GPIO operation
  P1DIR |= RED_LED; // set RED_LED to output
  P1OUT |= RED_LED; // set output to high
  
  P1SEL0 |= A1_SEEED; // GPIO operation
  P1SEL1 |= A1_SEEED; // A1_SEEED operation
  P1DIR &= ~A1_SEEED; //set direction to input
  
  P1SEL0 |= V_DETECT_L; // V_DETECT_L Operation
  P1SEL1 |= V_DETECT_L; // V_DETECT_L Operation
  P1DIR &= ~V_DETECT_L; // set to input
  
  P1SEL0 |= V_DETECT_R; // V_DETECT_R operation
  P1SEL1 |= V_DETECT_R; // V_DETECT_R operation
  P1DIR &= ~V_DETECT_R; // set to input
  
  P1SEL0 |= A4_SEEED; // A4_SEEED operation
  P1SEL1 |= A4_SEEED;  // A4_SEED operation
  P1DIR &= ~A4_SEEED; // set to input
  
  P1SEL0 |= V_THUMB; // V_THUMB operation
  P1SEL1 |= V_THUMB; // V_THUMB operation
  P1DIR &= ~V_THUMB; // set to input
  
  P1SEL0 &= ~UCA0RXD; // UCA0RXD operation
  P1SEL1 |= UCA0RXD; // UCA0RXD operation
  P1DIR &= ~UCA0RXD; // set to input
  
  P1SEL0 &= ~UCA0TXD; // UCA0TXD operation
  P1SEL1 |= UCA0TXD; // UCA0TXD operation
  P1DIR &= ~UCA0TXD; // set to input
}
  
//------------------------------------------------------------------------------
  

// configure port 2
void Init_Port2(void){
//------------------------------------------------------------------------------
  P2DIR = PIN_OUT; // Set P1 direction to output
  P2OUT = OUT_LOW; // P1 set Low

  P2SEL0 &= ~P2_0; // P2_0 GPIO operation
  P2SEL1 &= ~P2_0; // P2_0 GPIO operation
  P2DIR &= ~P2_0; // Direction = input

  P2SEL0 &= ~P2_1; // P2_1 GPIO operation
  P2SEL1 &= ~P2_1; // P2_1 GPIO operation
  P2DIR &= ~P2_1; // Direction = input

  P2SEL0 &= ~P2_2; // P2_2 GPIO operation
  P2SEL1 &= ~P2_2; // P2_2 GPIO operation
  P2DIR &= ~P2_2; // Direction = input

  P2SEL0 &= ~SW2; // SW2 Operation
  P2SEL1 &= ~SW2; // SW2 Operation
  P2DIR &= ~SW2; // Direction = input
  P2OUT |= SW2; // Configure pullup resistor
  P2REN |= SW2; // Enable pullup resistor
  // P2IES |= SW2; // P2.0 Hi/Lo edge interrupt
  // P2IFG &= ~SW2; // Clear all P2.6 interrupt flags
  // P2IE |= SW2; // P2.6 interrupt enabled

  P2SEL0 &= ~P2_4; // P2_4 GPIO operation
  P2SEL1 &= ~P2_4; // P2_4 GPIO operation
  P2DIR &= ~P2_4; // Direction = input

  P2SEL0 &= ~P2_5; // P2_5 GPIO operation
  P2SEL1 &= ~P2_5; // P2_5 GPIO operation
  P2DIR &= ~P2_5; // Direction = input

  P2SEL0 &= ~LFXOUT; // LFXOUT Clock operation
  P2SEL1 |= LFXOUT; // LFXOUT Clock operation

  P2SEL0 &= ~LFXIN; // LFXIN Clock operation
  P2SEL1 |= LFXIN; // LFXIN Clock operation
//------------------------------------------------------------------------------
}

//configure port 3

void Init_Port3(int configure){
//------------------------------------------------------------------------------
  P3DIR = PIN_OUT; // set to output
  P3OUT = OUT_LOW; // set to 0
  
  P3SEL0 &= ~TEST_PROBE; // TEST_PROBE operation
  P3SEL1 &= ~TEST_PROBE; // TEST_PROBE operation
  P3DIR |= TEST_PROBE; //set direction to output
  P3OUT |= TEST_PROBE; // set output to high
  
  P3SEL0 |= CHECK_BAT; // CHECK_BAT operation
  P3SEL1 |= CHECK_BAT; // CHECK_BAT operation
  P3DIR &= ~CHECK_BAT; // set to input
  
  P3SEL0 |= OA2N; // OA2N operation
  P3SEL1 |= OA2N; // OA2N operation
  P3DIR &= ~OA2N; // set to input
  
  P3SEL0 |= OA2P; // OA2P operation
  P3SEL1 |= OA2P; // OA2P operation
  P3DIR &= ~OA2P; // set to input
  
  if(configure == USE_GPIO){
  P3SEL0 &= ~SMCLK_OUT; // SMCLK_OUT operation
  P3SEL1 &= ~SMCLK_OUT; // SMCLK_OUT operation
  P3DIR |= SMCLK_OUT; // set to output
  P3OUT |= SMCLK_OUT; // output set high
  }else if(configure == USE_SMCLK)
  {
    P3SEL0 |= SMCLK_OUT; // SMCLK_OUT operation
    P3SEL1 &= ~SMCLK_OUT; // SMCLK_OUT operation
    P3DIR |= SMCLK_OUT; // set to input
    P3OUT |= SMCLK_OUT; //configure pull up resistor
    P3REN |= SMCLK_OUT; //enable pull up resistor
  }
    
  
  P3SEL0 |= IR_LED; // IR_LED operation
  P3SEL1 |=IR_LED; // IR_LED operation
  P3DIR  &= ~IR_LED; // set to input
  
  P3SEL0 |= IOT_LINK; // IOT_LINK operation
  P3SEL1 |= IOT_LINK; // IOT_LINK operation
  P3DIR &= ~IOT_LINK; // set to input
  
  P3SEL0 |= P3_7; // P3_7 operation
  P3SEL1 |= P3_7; // P3_7 operation
  P3DIR &= ~P3_7; // set to input
//------------------------------------------------------------------------------
}

//------------------------------------------------------------------------------

void Init_Port4(void){
//------------------------------------------------------------------------------
// Configure PORT 4
P4OUT = OUT_LOW; // P4 set to low
P4DIR = PIN_OUT; // Set P4 direction to output
P4SEL0 &= ~RESET_LCD; // RESET_LCD GPIO operation
P4SEL1 &= ~RESET_LCD; // RESET_LCD GPIO operation
P4DIR |= RESET_LCD; // Set RESET_LCD direction to output
P4OUT |= RESET_LCD; // Set RESET_LCD Off [High]

P4SEL0 &= ~SW1; // SW1 GPIO operation
P4SEL1 &= ~SW1; // SW1 GPIO operation
P4DIR &= ~SW1; // Direction = input
P4OUT |= SW1; // Configure pullup resistor
P4REN |= SW1; // Enable pullup resistor
// P4IES |= SW1; // P2.0 Hi/Lo edge interrupt
// P4IFG &= ~SW1; // Clear all P2.6 interrupt flags
// P4IE |= SW1; // P2.6 interrupt enabled

P4SEL0 |= UCA1TXD; // USCI_A1 UART operation
P4SEL1 &= ~UCA1TXD; // USCI_A1 UART operation
P4SEL0 |= UCA1RXD; // USCI_A1 UART operation
P4SEL1 &= ~UCA1RXD; // USCI_A1 UART operation

P4SEL0 &= ~UCB1_CS_LCD; // UCB1_CS_LCD GPIO operation
P4SEL1 &= ~UCB1_CS_LCD; // UCB1_CS_LCD GPIO operation
P4DIR |= UCB1_CS_LCD; // Set SPI_CS_LCD direction to output
P4OUT |= UCB1_CS_LCD; // Set SPI_CS_LCD Off [High]

P4SEL0 |= UCB1CLK; // UCB1CLK SPI BUS operation
P4SEL1 &= ~UCB1CLK; // UCB1CLK SPI BUS operation

P4SEL0 |= UCB1SIMO; // UCB1SIMO SPI BUS operation
P4SEL1 &= ~UCB1SIMO; // UCB1SIMO SPI BUS operation

P4SEL0 |= UCB1SOMI; // UCB1SOMI SPI BUS operation
P4SEL1 &= ~UCB1SOMI; // UCB1SOMI SPI BUS operation
//------------------------------------------------------------------------------
}

// configure Port 5

void Init_Port5(void){
//------------------------------------------------------------------------------
  P5OUT = OUT_LOW; // set low
  P5DIR = PIN_OUT; // direction set to output
  
  P5SEL0 &= ~IOT_RESET; // IOT_RESET operation
  P5SEL1 &= ~IOT_RESET; // IOT_RESET operation
  P5DIR |= IOT_RESET; // set to output
  P5OUT |= IOT_RESET; // set output to high
  
  P5SEL0 &= ~V_BAT; // V_BAT operation
  P5SEL1 &= ~V_BAT; // V_BAT operation
  P5DIR |= V_BAT; // set to output
  P5OUT |= V_BAT; // set output to high
  
  P5SEL0 &= ~IOT_PROG_SEL; // IOT_PROG_SEL operation
  P5SEL1 &= ~IOT_PROG_SEL; // IOT_PROG_SEL operation
  P5DIR |= IOT_PROG_SEL; // set to output
  P5OUT |= IOT_PROG_SEL; // set output to high
  
  P5SEL0 &= ~V_3_3; // V_3_3 operation
  P5SEL1 &= ~V_3_3; // V_3_3 operation
  P5DIR |= V_3_3; // set to output
  P5OUT |= V_3_3; // set output to high
  
  P5SEL0 &= ~IOT_PROG_MODE; // IOT_PROG_MODE operation
  P5SEL1 &= ~IOT_PROG_MODE; // IOT_PROG_MODE operation
  P5DIR |= IOT_PROG_MODE; // set to output
  P5OUT |= IOT_PROG_MODE; // set output to high
//------------------------------------------------------------------------------
}

// configure Port 6

void Init_Port6(void){
//------------------------------------------------------------------------------
  P6OUT = OUT_LOW; // set output to low
  P6DIR = PIN_OUT; // set direction to output
  
  P6SEL0 &= ~R_FORWARD; // R_FORWARD operation
  P6SEL1 &= ~R_FORWARD; // R_FORWARD operation
  P6DIR |= R_FORWARD; // Direction set to output
  P6OUT &= ~R_FORWARD; // output set to low
  
  P6SEL0 &= ~L_FORWARD; // L_FORWARD operation
  P6SEL1 &= ~L_FORWARD; // L_FORWARD operation
  P6DIR |= L_FORWARD; // direction set to output
  P6OUT &= ~L_FORWARD; // output set to low
  
  P6SEL0 &= ~R_REVERSE; // R_REVERSE operation
  P6SEL1 &= ~R_REVERSE; // R_REVERSE operation
  P6DIR |= R_REVERSE; // direction set to output
  P6DIR &= ~R_REVERSE; // output set low
  
  P6SEL0 &= ~L_REVERSE; // L_REVERSE operation
  P6SEL1 &= ~L_REVERSE; // L_REVERSE operation
  P6DIR |= L_REVERSE; // direction set to output
  P6OUT &= ~L_REVERSE; // output set low
  
  P6SEL0 &= ~LCD_BACKLITE; // LCD_BACKLITE operation
  P6SEL1 &= ~LCD_BACKLITE; // LCD_BACKLITE operation
  P6DIR |=  LCD_BACKLITE; // direction set to input
  P6OUT &= ~LCD_BACKLITE; // output set low(backlight off)
  
  P6SEL0 &= ~P6_5; // P6_5 operation
  P6SEL1 &= ~P6_5; // P6_5 operation
  P6DIR |= P6_5; // direction set to output
  P6OUT &= ~P6_5; // output set low
  
  P6SEL0 &= ~GRN_LED; // GRN_LED operation
  P6SEL1 &= ~GRN_LED; // GRN_LED operation
  P6DIR |= GRN_LED; // direction set to output
  P6OUT |= GRN_LED; // output set high
 //-----------------------------------------------------------------------------
}

// initialize ports
void Init_Ports(void){
  Init_Port1();
  Init_Port2();
  Init_Port3(USE_GPIO);
  Init_Port4();
  Init_Port5();
  Init_Port6();
}