//==============================================================================
// Filename : black_line.c
//
// Description: This file contains the functions for following a black line
//
// Author: Marcus Kok
// Date: April 2020
// Compiler: Built with IAR Embedded Workbench for MSP430 7.12.4
//==============================================================================

#include  "functions.h"
#include  "msp430.h"
#include "macros.h"
#include <string.h>

//GLOBALS=======================================================================
extern unsigned int myTime;
extern unsigned int prevButton;
extern unsigned int buttonPress;
extern int wheelCount;
extern volatile unsigned int main_state;

extern volatile unsigned int wheel_state;

extern unsigned int black_line_flag;
extern unsigned int one_second_flag;


extern unsigned int ADC_Left_Detect;
extern unsigned int ADC_Right_Detect;

extern volatile unsigned int command_count;
extern int command_duration;
extern int serial_display;

extern char display_line[numLines][strSize];
extern volatile unsigned char display_changed;
unsigned int current_state;
unsigned int previous_state;
unsigned int follow_ready = TRUE;
int reference = RESET_STATE;
unsigned int wait_count = BEGINNING;
extern volatile unsigned int CCR0_COUNT;
extern unsigned int clock_running;
extern unsigned int black_line_count;
extern unsigned int black_threshold;
extern unsigned int white_threshold;
unsigned int ready = FALSE;
unsigned int exit_line = FALSE;
unsigned int find_line_first_time = TRUE;

// pwm variables
  int lspeed = RESET_STATE;
  int rspeed = RESET_STATE;
  int u = RESET_STATE;
  int e, current_error, previous_error, sum_error, delta_error = RESET_STATE;
  int P, I, D = RESET_STATE;

  
//==============================================================================

//Monitoring loop 
void LineFollowing(void){
  //if(ready){
    getCurrentState();
    if(current_state == WHITE_STATE){
      switch(previous_state){
      case TURN_RIGHT:
        spin_CW();
        break;
      case TURN_LEFT:
        spin_CCW();
        break;
      default:
        spin_CCW();
        break;
      }
    }else{
      int control = SimplePID();        // not just reading white, track point
      PID_WheelControl(control);
    }
     previous_state = current_state;
     ready = FALSE;     //
     
     if(exit_line){                     // check for exit flag
       exit_loop();                     // preset movement directions to exit
       exit_line = FALSE;
       clear_LCD();
       main_state = END;
     }   
}

void searchForLine(void){
  if(find_line_first_time){     // position car so it can intercept course in the middle
  forward_ntime(TWENTY_COUNTS);            // only do this one time at start
  CW_ntime(FIVE_COUNTS);
  forward_ntime(THIRTY_FIVE_COUNTS);
  CW_ntime(FIVE_COUNTS);
  find_line_first_time = FALSE;
  }
  if(ADC_Left_Detect < black_threshold && ADC_Right_Detect < black_threshold){
    inch_Forward();
  }
  else if(ADC_Left_Detect >= black_threshold || ADC_Right_Detect >= black_threshold){
    stop_Movement();
    wait_ntime(ONE_SEC);
    while(ADC_Left_Detect <= white_threshold || ADC_Right_Detect <= white_threshold){
      spin_CCW();
    }
    stop_Movement();
    wait_ntime(ONE_SEC);
    CW_ntime(THREE_COUNTS);
    black_line_flag = TRUE;
    //black_line_count = BEGINNING;
  }
}

void getCurrentState(void){
  if(ADC_Left_Detect < white_threshold && ADC_Right_Detect < white_threshold){      
    current_state = WHITE_STATE;                        // completely off the line
  }
  else if(ADC_Right_Detect <= white_threshold){       // need to turn left 
    current_state = TURN_LEFT;
  }
  else if(ADC_Left_Detect <= white_threshold){       // need to turn right
    current_state = TURN_RIGHT;
  }
  else if(ADC_Left_Detect >= black_threshold && ADC_Right_Detect >= black_threshold)
    current_state = ON_BLACK;
}

void exit_loop(void){
  stop_Movement();
  wait_ntime(ONE_SEC);
  CW_ntime(EXIT_TURN_TIME);
  stop_Movement();
  forward_ntime(EXIT_FORWARD_TIME); 
  clock_running = FALSE;
}

void PID_LineFollowing(void){
  if(ready){
      int control = SimplePID();
      PID_WheelControl(control);
    // set variables for next iteration
      ready = FALSE;
  }
}


int SimplePID(void){
  // Get sensor readings
  
  // Calculate error
  e = REFERENCE - (ADC_Left_Detect - ADC_Right_Detect);     // positive value means left turn, negative means right
  
  // Set PID error variables
  current_error = e;
  sum_error = sum_error + (current_error*READ_ADC);
  delta_error = (current_error - previous_error);
  previous_error = current_error;               // save error for next loop
  
  // Calculate individual controller outputs
  P = current_error;
  I = sum_error;
  D = delta_error;
  
  // calculate PID control signal 
  u = Kp*P+ Ki*I+ Kd*D;
  return u;
}

// Basic control actuation code
void PID_WheelControl(int control){
  // Assume vehicle is designed to move at some cruise speed, and adjust wheel PWM values to track a curved line
  // Negative valued control indicates a right turn, positive means left
  lspeed = CRUISE_SPEED - control;
  rspeed = CRUISE_SPEED + control;
  
  // saturate speed values within PWM range
  if(lspeed < MIN_SPEED)
    lspeed = MIN_SPEED;
  if(rspeed < MIN_SPEED)
    rspeed = MIN_SPEED;
  else if(lspeed > MAX_SPEED)
    lspeed = MAX_SPEED;
  else if (rspeed > MAX_SPEED)
    rspeed = MAX_SPEED;
  
  // set speed values to PWM registers
  LEFT_REVERSE_SPEED = WHEEL_OFF;       // make sure reverse is not on 
  RIGHT_REVERSE_SPEED = WHEEL_OFF;
  LEFT_FORWARD_SPEED = lspeed;
  RIGHT_FORWARD_SPEED = rspeed;
}




