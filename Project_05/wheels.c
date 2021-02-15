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
  RIGHT_FORWARD_SPEED = FAST;               // right forward on
  LEFT_FORWARD_SPEED = FAST;                // left forward on 
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
  LEFT_FORWARD_SPEED = FAST;                // left forward on
}

void spin_CCW(void){
  LEFT_FORWARD_SPEED = WHEEL_OFF;           // left forward off
  RIGHT_REVERSE_SPEED = WHEEL_OFF;          // right reverse off
  LEFT_REVERSE_SPEED = FAST;                // left reverse on
  RIGHT_FORWARD_SPEED = FAST;               // right forward on
}






  
  