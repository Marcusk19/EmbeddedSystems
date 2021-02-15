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
unsigned int rspeed, lspeed = RESET_STATE;
unsigned int e = RESET_STATE;
unsigned int reference = RESET_STATE;
int current_error, previous_error, sum_error, delta_error = RESET_STATE;


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

//Monitoring loop 
void LineFollowing(void){
  if(ready){
    ready = FALSE;
    
    // Get state information
    current_state = GetCurrentState();
    if(current_state == WHITE_STATE){
      switch(previous_state){
      case LEFT_STATE: TurnRight();
      break;
      case RIGHT_STATE: turnLeft(); 
      break;
      default: SpinInPlace();
      break;
      }
    }
    else{
      WheelControl(SimplePID); // not just reading white so able to set track point
      //set variables for next iteration
      previous_state = current_state;
      ready = false;
    }
  }
}

// Basic PID
int control SimplePID(void){
  //get sensor readings
  Read_ADC();
  
  // calculate error
  e = reference - (ADC_Left_Detect - ADC_Right_Detect); // magnitude of error indicates how far off the line
  
  // set PID error variables
  current_error = e;
  sum_error = sum_error + (current_error * sample_time);
  delta_error = (current_error - previous_error)/sample_time;
  previous_error = current_error;               // save error for next loop
  
  // calculate individual error components
  P = current_error;
  I = sum_error;
  D = delta_error;
  
  // calculate PID control signal
  
  u = Kp*P + Ki*I + Kd*D;
  return u;
}

// Basic control actuation
void Wheel_Control(control){
  // Assume vehicle is designed to move at some  cruise speed and adjust wheel 
  // PWM values to track a curved line
  // Negative valued control indicates a right turn, positive indicates left
  
  lspeed = CRUISE_SPEED - control;
  rspeed = CRUISE_SPEED + control;
  
  // saturate speed values within PWM range
  if(lspeed < MIN_SPEED){
    lspeed = MIN_SPEED;
  }
  if(rspeed < MIN_SPEED){
    rspeed = MIN_SPEED;
  }
  else if (lspeed > MAX_SPEED){
    lspeed = MAX_SPEED;
  }
  else if (rspeed > MAX_SPEED){
    rspeed = MAX_SPEED;
  }
  
  // set speed values to pwm registers
  LEFT_FORWARD_SPEED = lspeed;
  RIGHT_FORWARD_SPEED = rspeed;
}
