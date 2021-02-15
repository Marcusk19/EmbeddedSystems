//==============================================================================
// Filename : wheels.c
//
// Description: This file contains the functions for wheel movement
//
// Author: Marcus Kok
// Date: February 2020
// Compiler: Built with IAR Embedded Workbench for MSP430 7.12.4
//==============================================================================

#include  "functions.h"
#include  "msp430.h"
#include "macros.h"
#include <string.h>

//GLOBALS=======================================================================
extern unsigned int myTime;
int waitCount = RESET_STATE;
extern unsigned int prevButton;
extern unsigned int buttonPress;
extern int wheelCount;

extern volatile unsigned int wheel_state;

extern unsigned int black_line_flag;
extern unsigned int one_second_flag;
extern unsigned int wait_count;

extern unsigned int ADC_Left_Detect;
extern unsigned int ADC_Right_Detect;

extern volatile unsigned int command_count;
extern int command_duration;
extern int serial_display;

extern char display_line[numLines][strSize];
extern volatile unsigned char display_changed;
int wheel_one_time = TRUE;
//==============================================================================

void stop_Movement(void){
  RIGHT_FORWARD_SPEED = WHEEL_OFF;
  LEFT_FORWARD_SPEED = WHEEL_OFF;
  RIGHT_REVERSE_SPEED = WHEEL_OFF;
  LEFT_REVERSE_SPEED = WHEEL_OFF;
}

void move_Forward(void){
  RIGHT_REVERSE_SPEED = WHEEL_OFF;          // right reverse off
  LEFT_REVERSE_SPEED = WHEEL_OFF;           // left reverse off
  RIGHT_FORWARD_SPEED = HALF_SPEED;               // right forward on
  LEFT_FORWARD_SPEED = HALF_SPEED;                // left forward on 
}

void move_Reverse(void){
  RIGHT_FORWARD_SPEED = WHEEL_OFF;          // right foward off
  LEFT_FORWARD_SPEED = WHEEL_OFF;           // left forward off
  RIGHT_REVERSE_SPEED = FAST;               // right reverse on
  LEFT_REVERSE_SPEED = HALF_SPEED;          // left reverse on 
}

void spin_CW(void){
  RIGHT_FORWARD_SPEED = WHEEL_OFF;          // right forward off
  LEFT_REVERSE_SPEED = WHEEL_OFF;           // left reverese off
  RIGHT_REVERSE_SPEED = FAST;               // right reverse on 
  LEFT_FORWARD_SPEED = SLOW;                // left forward on
}

void spin_CCW(void){
  LEFT_FORWARD_SPEED = WHEEL_OFF;           // left forward off
  RIGHT_REVERSE_SPEED = WHEEL_OFF;          // right reverse off
  LEFT_REVERSE_SPEED = FAST;                // left reverse on
  RIGHT_FORWARD_SPEED = SLOW;               // right forward on
}

void turn_CW(void){
  LEFT_REVERSE_SPEED = WHEEL_OFF;
  RIGHT_REVERSE_SPEED = WHEEL_OFF;
  RIGHT_FORWARD_SPEED = SLOW;
  LEFT_FORWARD_SPEED = FAST;
}


void wheel_control(void){
    switch(wheel_state){
    case HOLD:
      command_count = RESET_STATE;
      if(wheel_one_time){
        /*lcd_BIG_mid();
        strcpy(display_line[line2], "   HOLD   ");
        update_string(display_line[line2], line2);
        display_changed = TRUE;*/
        wheel_one_time = FALSE;
      }
      
      stop_Movement();
      break;
    case FORWARD:
      if(wheel_one_time){
        serial_display = FORWARD_DISP;
        wheel_one_time = FALSE;
      }
      move_Forward();
      if(command_count >= command_duration){
        wheel_state = HOLD;
        wheel_one_time = TRUE;
      }
      break;
    case REVERSE:
      if(wheel_one_time){
        serial_display = REVERSE_DISP;
        wheel_one_time = FALSE;
      }
      
      move_Reverse();
      
      if(command_count >= command_duration){
        wheel_state = HOLD;
        wheel_one_time = TRUE;
      }
      break;
    case RIGHT_TURN:
      if(wheel_one_time){
        serial_display = RIGHT_DISP;
        wheel_one_time = FALSE;
      }
      
      spin_CW();
      
      if(command_count >= command_duration){
        wheel_state = HOLD;
        wheel_one_time = TRUE;
      }
      break;
    case LEFT_TURN:
      if(wheel_one_time){
        serial_display = LEFT_DISP;
        wheel_one_time = FALSE;
      }
      
      spin_CCW();
      if(command_count >= command_duration){
        wheel_state = HOLD;
        wheel_one_time = TRUE;
      }
      break;   
    default: break;
    }
}