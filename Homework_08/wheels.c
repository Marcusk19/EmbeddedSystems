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
      stop_Movement();
      if(black_line_flag){
        if(one_second_flag){
          wait_count++;
        }
        if(wait_count == WAIT_SECONDS){
          black_line_flag = FALSE;
          wait_count = RESET_STATE;
          wheel_state = TURN_AROUND;
        }
      }
      break;
    case MOVE_FORWARD:
      if(one_second_flag){
        wait_count++;
      }
      if(wait_count > WAIT_SECONDS){
      move_Forward();
      }
      if(ADC_Left_Detect > BLACK_THRESHOLD || ADC_Right_Detect > BLACK_THRESHOLD){
        wheel_state = HOLD;
        black_line_flag = TRUE;
        wait_count = RESET_STATE;
      }
      break;
    case TURN_AROUND: 
      spin_CW();
      if(ADC_Right_Detect > BLACK_THRESHOLD && ADC_Left_Detect > BLACK_THRESHOLD){
        wheel_state = HOLD;
      }
      break;   
    default: break;
    }
}