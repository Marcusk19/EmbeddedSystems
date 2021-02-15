//==============================================================================
// Filename : macros.h
//
// Description: This file contains the macros used by all other files
//
// Author: Marcus Kok
// Date: January 2020
// Compiler: Built with IAR Embedded Workbench for MSP430 7.12.4
//==============================================================================

#define ALWAYS                  (1)
#define RESET_STATE             (0)
#define RED_LED              (0x01) // RED LED 0
#define GRN_LED              (0x40) // GREEN LED 1
#define ODD (2)

//Clock macros
#define MCLK_FREQ_MHZ 8                     // MCLK = 8MHz
#define CLEAR_REGISTER     (0X0000)
#define CLOCK_CYCLE (50)
#define WAIT_TIME (9)
#define FALSE (0)
#define TRUE (1)

#define RUN (1)
#define STOP (0)
#define THREE_CYCLES (3)
#define WAIT_CYCLES (3)
//------------------------------------------------------------------------------
  //motor control10)
#define FAST (48)
#define VERY_SLOW (5)
#define SLOW (10)

#define TURN_ANGLE (300)
#define LINE_LENGTH (250)
#define TRIANGLE_SEGMENT_TIME (300)
#define circNumTurns (3000)
#define FIG_EIGHT_TURNS (1200)
#define TRIANGLE_SIDES (12)
//------------------------------------------------------------------------------
  //shape functions
#define NUM_SHAPES (4)
#define HOLD (5)
#define CIRCLE (1)
#define TRIANGLE (3)
#define FIGURE_EIGHT (2)
#define FIG_EIGHT_TWO (6)
#define FIGURE_EIGHT_THREE (7)
#define FIGURE_EIGHT_FINISH (8)
//------------------------------------------------------------------------------
#define BINARY0 (250)
#define BINARY1 (200)
#define BINARY2 (150)
#define BINARY3 (100)
#define BINARYRES (50)
//------------------------------------------------------------------------------
  // Port 1 Pins
  #define RED_LED (0x01)        // 0 RED LED 0
  #define A1_SEEED (0x02)       // 1 A1_SEEED
  #define V_DETECT_L (0x04)     // 2 V_DETECT_L
  #define V_DETECT_R (0x08)     // 3 V_DETECT_R
  #define A4_SEEED (0x10)      // 4 A4_ SEEED
  #define V_THUMB (0x20)        // 5 V_THUMB
  #define UCA0RXD (0x40)        // 6 Back Channel UCA0RXD
  #define UCA0TXD (0x80)        // 7 Back Channel UCA0TXD

   // Port 2 Pins
  #define P2_0 (0x01)   // 0 P2_0
  #define P2_1 (0x02)   // 1 P2_1
  #define P2_2 (0x04)   // 2 P2_2
  #define SW2 (0x08)    // 3 SW2
  #define P2_4 (0x10)   // 4 P2_4
  #define P2_5 (0x20)   // 5 P2_5
  #define LFXOUT (0x40) // 6 XOUTR
  #define LFXIN (0x80) // 7 XINR

  // Port 3 Pins
  #define TEST_PROBE (0x01)     // 0 TEST PROBE
  #define CHECK_BAT (0x02)      // 1 CHECK_BAT
  #define OA2N (0x04)           // 2 Photodiode Circuit
  #define OA2P (0x08)           // 3 Photodiode Circuit
  #define SMCLK_OUT (0x10)      // 4 SMCLK
  #define IR_LED (0x20)         // 5 IR_LED
  #define IOT_LINK (0x40)       // 6 IOT_LINK
  #define P3_7 (0x80)           // 7 P3_7

  // Port 4 Pins
  #define RESET_LCD (0x01)              // 0 LCD Reset
  #define SW1 (0x02)                    // 1 SW1
  #define UCA1RXD (0x04)                // 2 back channel UCA1RXD
  #define UCA1TXD (0x08)                // 3 back channel UCA1TXD
  #define UCB1_CS_LCD (0x10)            // 4 Chip Select
  #define UCB1CLK (0x20)                // 5 SPI mode - clock output - UCB1CLK
  #define UCB1SIMO (0x40)               // UCB1SIMO
  #define UCB1SOMI (0x80)               // 7 UCB1SOMI

  // Port 5 pins
  #define IOT_RESET (0x01)      // 0 IOT_RESET
  #define V_BAT (0x02)          // 1 V_BAT
  #define IOT_PROG_SEL (0x04)   // 2 IOT_PROG_SEL
  #define V_3_3 (0x08)          // 3 V_3_3
  #define IOT_PROG_MODE (0x10)  // 4 IOT_PROG_MODE

  // Port 6 Pins
  #define R_FORWARD (0x01)      // 0 R_FORWARD
  #define L_FORWARD (0x02)      // 1 L_FORWARD
  #define R_REVERSE (0x04)      // 2 R_REVERSE
  #define L_REVERSE (0x08)      // 3 L_REVERSE
  #define LCD_BACKLITE (0x10)   // 4 LCD_BACKLITE
  #define P6_5 (0x20)           // 5 P6_5
  #define GRN_LED (0x40)        // 6 GRN_LED

  //Pin settings
  #define PIN_OUT (0xFF) // set to output
  #define OUT_LOW (0x00) // set output to low
//------------------------------------------------------------------------------
  //for loop in init.c
  #define start (0) // start of loop 
  #define loopEnd (11) // end of for loop
//------------------------------------------------------------------------------
  //display lines
  #define line1 (0) // position of line1
  #define line2 (1) // position of line2
  #define line3 (2) // position of line 3
  #define line4 (3) // position of line4
  #define numLines (4) // number of lines
  #define strSize (11) // size of string per line

  #define charlength (10) // number of characters allowed


  

  