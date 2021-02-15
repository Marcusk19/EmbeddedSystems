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
#define OFF (0)
#define ON (1)

#define GET_IP (1)
#define PROCESS_IP (2)
#define DISPLAY_IP (3)
#define BLACK_LINE (4)
#define CALIBRATING (5)
#define CONTROL (6)

//Clock macros
#define MCLK_FREQ_MHZ 8                     // MCLK = 8MHz
#define CLEAR_REGISTER     (0X0000)
#define CLOCK_CYCLE (50)
#define WAIT_TIME (9)
#define TWO_SECOND_PAUSE (2)
#define FALSE (0)
#define TRUE (1)
#define USE_GPIO (0x00) // set port 3 pin as gpio
#define USE_SMCLK (0x01) // set port 3 pin a smclk
//-----------------------------------------------------------------------------
//timers
#define TB0CCR0_INTERVAL (50000)
#define TB0CCR1_INTERVAL (5000)
#define TB0CCR2_INTERVAL (8000)
#define DEBOUNCE_THRESHOLD (10)


#define TIME_SEQUENCE_CYCLES (250)

#define UPDATE_DISPLAY_THRESHOLD (4)

#define TB0CCR0_CYCLES (2)
#define CCR0_SEC (20)

#define CCR1_USED (2)
#define CCR2_USED (4)
#define OVERFLOW (14)
#define NO_INTERRUPT (0)
//-----------------------------------------------------------------------------


#define RUN (1)
#define STOP (0)
#define THREE_CYCLES (3)
#define WAIT_CYCLES (3)

#define CALIBRATE (0)
#define ADC_DISPLAY (1)
#define BLACK_LINE_DISPLAY (2)
//------------------------------------------------------------------------------
  //motor control
#define FAST (30000)
#define HALF_SPEED (20000)
#define CRUISE_SPEED (20000)
#define SLOW (10000)
#define MIN_SPEED (10000)
#define MAX_SPEED (30000)
#define WHEEL_OFF (0)

#define WHEEL_PERIOD (40000)

#define RIGHT_FORWARD_SPEED (TB3CCR1)
#define LEFT_FORWARD_SPEED (TB3CCR2)
#define RIGHT_REVERSE_SPEED (TB3CCR3)
#define LEFT_REVERSE_SPEED (TB3CCR4)

#define HOLD (0)
#define FORWARD (1)
#define REVERSE (2)
#define SPIN_CW (3)
#define SPIN_CCW (4)
#define RIGHT_TURN (5)
#define LEFT_TURN (6)
#define TURN_RIGHT (5)
#define TURN_LEFT (6)
#define SPIN (7)
#define EXIT (9)

/* macros for project 5 not used
#define START_FORWARD (1)
//travel one second
#define STOP_FIRST_FORWARD (2) //stop on first second
// wait one second
#define START_REVERSE (3)
//travel two seconds
#define STOP_REVERSE (5)
// stop one second
#define START_SECOND_FORWARD (6)
// travel one second
#define STOP_SECOND_FORWARD (7) 
//stop one second
#define START_SPIN_CW (8)
//spin for next three seconds
#define STOP_SPIN_CW (11)
//wait next two seconds
#define START_SPIN_CCW (13)
//spin next three seconds
#define STOP_SPIN_CCW (16)
//wait next two seconds before resetting
#define MAX_TIME (18)*/

#define MOVE_FORWARD (1)
#define TURN_AROUND (2)


//------------------------------------------------------------------------------
// macros for ADC.c

#define THOUSANDS (999)
#define HUNDREDS (99)
#define TENS (9)
#define BCD_THOUSAND (0)
#define BCD_HUNDRED (1)
#define BCD_TEN (2)
#define BCD_ONE (3)
#define NULL_TERMINATOR (4)
#define BCD_TENTH (4)
#define CIRCLE_NULL (5)
#define THOUSAND_DIV (1000)
#define HUNDRED_DIV (100)
#define TEN_DIV (10)
#define ASCII_CONV (0x30)
#define ADC_NUM_DIGITS (5)

#define DIVIDE_BY_FOUR (2)
#define DIVIDE_BY_TWO (1)

#define ADC_CHANNEL_2 (0x00)
#define ADC_CHANNEL_3 (0x01)
#define ADC_CHANNEL_4 (0x02)
#define ADC_RESET_STATE (0x03)

#define BLACK_THRESHOLD (300)
#define WHITE_THRESHOLD (60)
#define WAIT_SECONDS (10)
#define R_L_DIFF_BUFFER (4)
//------------------------------------------------------------------------------
/* not used
#define TURN_ANGLE (300)
#define LINE_LENGTH (250)
#define TRIANGLE_SEGMENT_TIME (300)
#define circNumTurns (3000)
#define FIG_EIGHT_TURNS (1200)
#define TRIANGLE_SIDES (12)*/
//------------------------------------------------------------------------------
  //shape functions (not used)
/*
#define NUM_SHAPES (4)
#define HOLD (5)
#define CIRCLE (1)
#define TRIANGLE (3)
#define FIGURE_EIGHT (2)
#define FIG_EIGHT_TWO (6)
#define FIGURE_EIGHT_THREE (7)
#define FIGURE_EIGHT_FINISH (8)*/
//------------------------------------------------------------------------------
// state definitions
#define SET_SMCLK (01)
#define SET_GPIO (02)
#define HOLD (0)
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

  #define LCD_HOME_L1 (0)
  #define LCD_HOME_L2 (1)
  #define LCD_HOME_L3 (2)
  #define LCD_HOME_L4 (3)

  #define POSITION_ONE (0)
  #define NUM_CHARS (11)

  #define charlength (10) // number of characters allowed

//------------------------------------------------------------------------------
// define macros for USB Serial Port Initialization
#define BEGINNING (0)
#define SMALL_RING_SIZE (16)
#define LARGE_RING_SIZE (32)
#define CLEAR (0x00)
#define ASCII_LF (0x0A)
#define ASCII_CR (0x0D)
#define BRW_460800 (1)
#define BRW_115200 (4)
#define MCTLW_460800 (0x4A11)
#define MCTLW_115200 (0X5541)
#define BRW_9600 (52)
#define MCTLW_9600 (0x4911)

#define NO_INTERRUPT (0)
#define RXIFG (2)
#define TXIFG (4)
#define NCSU_SIZE (8)
#define MAX_STR_SIZE (11)

#define WAIT (0)
#define TRANSMITTING (1)
#define RECEIVED (2)
#define TRANSMIT (1)
#define RECEIVE (2)
#define PROCESS (3)
#define COMMAND (5)
#define HALT (4)

#define TOGGLE_ONE (1)
#define TOGGLE_TWO (2)

#define TX_CHAR0 (0)
#define TX_CHAR1 (1)
#define TX_CHAR2 (2)
#define TX_CHAR3 (3)
#define TX_CHAR4 (4)
#define TX_CHAR5 (5)
#define TX_CHAR6 (6)
#define TX_CHAR7 (7)
#define TX_CHAR8 (8)
#define TX_CR (9)
#define TX_LF (10)

// macros for menu -------------------------------------------------------------

#define RES_MENU_ONE (410)
#define RES_MENU_TWO (820)
#define RES_MENU_THREE (1230)
#define RES_MENU_FOUR (1640)
#define RES_MENU_FIVE (2050)
#define RES_MENU_SIX (2460)
#define RES_MENU_SEVEN (2870)
#define RES_MENU_EIGHT (3280)
#define RES_MENU_NINE (3690)
#define RES_MENU_TEN (4100)

#define SHIFT_TEN (10)

#define RES_ONE (0)
#define RES_TWO (1)
#define RES_THREE (2)
#define RES_FOUR (3)
#define RES_FIVE (4)
#define RES_SIX (5)
#define RES_SEVEN (6)
#define RES_EIGHT (7)
#define RES_NINE (8)
#define RES_TEN (9)

#define CIRCLE (0)
#define SQUARE (1)
#define TRIANGLE (2)
#define OCTAGON (3)
#define PENTAGON (4)
#define HEXAGON (5)
#define CUBE (6)
#define OVAL (7)
#define SPHERE (8)
#define CYLINDER (9)

#define SHAPE_MENU_ONE (410)
#define SHAPE_MENU_TWO (820)
#define SHAPE_MENU_THREE (1230)
#define SHAPE_MENU_FOUR (1640)
#define SHAPE_MENU_FIVE (2050)
#define SHAPE_MENU_SIX (2460)
#define SHAPE_MENU_SEVEN (2870)
#define SHAPE_MENU_EIGHT (3280)
#define SHAPE_MENU_NINE (3690)
#define SHAPE_MENU_TEN (4100)
#define SCROLL_RANGE (10)


#define MAIN (0)
#define RESISTORS (1)
#define SHAPES (2)
#define SONG (3)

#define MENU (8)

#define IOT_WAIT_TIME (30)

#define IP_ADDRESS_SIZE (13)
#define KEYWORD (5)
#define ONE_SECOND (20)


#define ASCII_ESC (0x1B)
#define XLARGE_RING_SIZE (64)
#define START (7)

#define FORWARD_DISP (6)
#define REVERSE_DISP (7)
#define RIGHT_DISP (8)
#define LEFT_DISP (9)
#define PING (10)

#define ONE_SEC (20)
#define EXIT_TURN_TIME (6)
#define CORRECTION_TURN_TIME (3)
#define ADC_TIME (5)
#define START_LINE (8)
#define CORRECTION_TIME (5)
#define LOOP_TIME (185)
#define TIMER_DIGITS (6)
#define TWO_HUNDRED_MS (2)

#define CAL_BLACK (0)
#define CAL_WHITE (1)
#define CALIBRATION_ERROR (10)

// PID macros
#define REFERENCE (0)
#define Kp (1)
#define Ki (0)
#define Kd (0)
#define READ_ADC (5)











  

  