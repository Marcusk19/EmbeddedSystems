//==============================================================================
// Filename : display.c
// Description: This file contains the functions display proccesses
// 
// Author: Marcus Kok
// Date: March 2020
// Compiler: Made with IAR Embedded Workbench for MSP430 7.12.4
//==============================================================================

#include  "functions.h"
#include  "msp430.h"
#include "macros.h"
#include <string.h>

// globals
char time_display_buffer[] = "s    ";
extern unsigned int buttonState;
extern char display_line[numLines][strSize];
extern unsigned int num_presses;
extern volatile unsigned char display_changed;
extern char display_line[numLines][strSize];
extern volatile unsigned char update_display;
extern unsigned int emitter_flag;
extern int display_state;
extern volatile char process_buf[LARGE_RING_SIZE];
extern char receive_char[MAX_STR_SIZE];
extern char test_command[NCSU_SIZE];
extern char transmit_char[LARGE_RING_SIZE];
extern int serial_display;

  extern unsigned int circle_clock;
  extern char circle_timer[6];
  unsigned int BL_one_time = TRUE;
  extern unsigned int white_threshold;
  extern unsigned int black_threshold;
  extern unsigned int calibrated;
//------------------------------------------------------------------------------

void Init_Chars(void){
  strcpy(display_line[line1], "          ");
  update_string(display_line[line1], line1);
  strcpy(display_line[line2], "          ");
  update_string(display_line[line2], line2);
  strcpy(display_line[line3], "          ");
  update_string(display_line[line3], line3);
  strcpy(display_line[line4], "          ");
  update_string(display_line[line4], line4);
  enable_display_update();
  display_changed = TRUE;
}
  
void Serial_Display_Process(void){
  
  switch(serial_display){
  case WAIT:
    /*strcpy(display_line[line1], "  Waiting ");
    update_string(display_line[line1], line1);
    display_changed = TRUE;*/
    break;
  case RECEIVED:                                // put received information on line 4
    //clear_line2();                              // clear transmit info

    break;
  case TRANSMITTING:

    break;
    
  case FORWARD_DISP:
        strcpy(display_line[line4], " Forward  ");
        update_string(display_line[line4], line4);
        display_changed = TRUE;
    break;
  case REVERSE_DISP:
        strcpy(display_line[line4], " Reverse  ");
        update_string(display_line[line4], line4);
        display_changed = TRUE;
    break;
  case RIGHT_DISP:
        strcpy(display_line[line4], "Right Turn");
        update_string(display_line[line4], line4);
        display_changed = TRUE;
    break;
    case LEFT_DISP:
        strcpy(display_line[line4], "Left  Turn");
        update_string(display_line[line4], line4);
        display_changed = TRUE;
    break;
  case PT_ZERO:
        strcpy(display_line[line1], "Arrived #0");
        update_string(display_line[line1], line1);
        display_changed = TRUE;    
    break;
  case PT_ONE:
        //lcd_BIG_mid();
        strcpy(display_line[line1], "Arrived #1");
        update_string(display_line[line1], line1);
        display_changed = TRUE;
    break;
  case PT_TWO:
      //lcd_BIG_mid();
      strcpy(display_line[line1], "Arrived #2");
      update_string(display_line[line1], line1);
      display_changed = TRUE;
      break;
  case PT_THREE:
        //lcd_BIG_mid();
        strcpy(display_line[line1], "Arrived #3");
        update_string(display_line[line1], line1);
        display_changed = TRUE;
        break;
  case PT_FOUR:
        //lcd_BIG_mid();
        strcpy(display_line[line1], "Arrived #4");
        update_string(display_line[line1], line1);
        display_changed = TRUE;
        break;
  case PT_FIVE:
        //lcd_BIG_mid();
        strcpy(display_line[line1], "Arrived #5");
        update_string(display_line[line1], line1);
        display_changed = TRUE;
        break;
  case PT_SIX:
        //lcd_BIG_mid();
        strcpy(display_line[line1], "Arrived #6");
        update_string(display_line[line1], line1);
        display_changed = TRUE;
        break;
  case PT_SEVEN:
        //lcd_BIG_mid();
        strcpy(display_line[line1], "Arrived #7");
        update_string(display_line[line1], line1);
        display_changed = TRUE;
        break;
  case PT_EIGHT:
        //lcd_BIG_mid();
        strcpy(display_line[line1], "Arrived #8");
        update_string(display_line[line1], line1);
        display_changed = TRUE;
        break;
  default: break;
  }
  
}

void main_display_process(void){
  switch(display_state){
  case CALIBRATE:
      strcpy(display_line[line1], "Calibrate ");        // update display
      update_string(display_line[line1], line1);
      display_ADC();
      display_changed = TRUE;
    break;
  case BLACK_LINE_DISPLAY:
    lcd_BIG_mid();
    strcpy(display_line[line2], "BL Travel ");        // update display
    update_string(display_line[line2], line2);
    break;
  case EXIT_LINE:
    lcd_BIG_mid();
    strcpy(display_line[line2], "BL Exit ");        // update display
    update_string(display_line[line2], line2);
    break;
  case BL_STOP:
    lcd_BIG_mid();
    strcpy(display_line[line2], "BL Stop ");        // update display
    update_string(display_line[line2], line2);    
    break;
  case ADC_DISPLAY:
    display_ADC();
    break;
  case FIND_BLACK_LINE:
    clear_LCD();
    strcpy(display_line[line1], "Find Line ");        // update display
    update_string(display_line[line1], line1);
    display_changed = TRUE;
    
    break;
  default: break;
  }
}

void display_timer(void){
      getCircleTime(circle_clock);
      strcat(circle_timer, time_display_buffer);
      strcpy(display_line[line1], circle_timer);        // update display
      update_string(display_line[line1], line1);
      display_changed = TRUE;
}
void clear_LCD(void){
  strcpy(display_line[line1], "          ");
  update_string(display_line[line1], line1);
  strcpy(display_line[line2], "          ");
  update_string(display_line[line2], line2);
  strcpy(display_line[line3], "          ");
  update_string(display_line[line3], line3);
  strcpy(display_line[line4], "          ");
  update_string(display_line[line4], line4);
  enable_display_update();
  display_changed = TRUE;
}

void clear_line4(void){
  strcpy(display_line[line4], "          ");
  update_string(display_line[line4], line4);
  display_changed = TRUE;
}

void clear_line2(void){
  strcpy(display_line[line2], "          ");
  update_string(display_line[line2], line2);
  display_changed = TRUE;
}

void clear_line3(void){
  strcpy(display_line[line3], "          ");
  update_string(display_line[line3], line3);
  display_changed = TRUE;
}

void clear_line1(void){
  strcpy(display_line[line1], "          ");
  update_string(display_line[line1], line1);
  display_changed = TRUE;
}
  

  
  