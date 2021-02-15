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
//==============================================================================

//Monitoring loop 
void LineFollowing(void){
    getCurrentState();
    switch(current_state){
    case START_LINE:
      spin_CCW();
    case TURN_RIGHT:
      turn_Right();
      break;
    case TURN_LEFT:
      turn_Left();
      break;
    case FORWARD:
      inch_Forward();
      break;
    case SPIN:
      spin_CW();
      break;
    case EXIT:
      exit_loop();
      main_state = HOLD;
      break;
    default: break;
  }
}

void searchForLine(void){
  if(ADC_Left_Detect < white_threshold && ADC_Right_Detect < white_threshold){
    inch_Forward();
  }
  else if(ADC_Left_Detect >= black_threshold || ADC_Right_Detect >= black_threshold){
    stop_Movement();
    wait_ntime(ONE_SEC);
    while(ADC_Left_Detect <= white_threshold || ADC_Right_Detect <= white_threshold){
      spin_CW();
    }
    stop_Movement();
    wait_ntime(ONE_SEC);
    CCW_ntime(CORRECTION_TURN_TIME);
    black_line_flag = TRUE;
    black_line_count = BEGINNING;
  }
}

void getCurrentState(void){
  previous_state = current_state;
  if(ADC_Left_Detect <= white_threshold){        // need to turn right
    current_state = TURN_RIGHT;
  }
  else if(ADC_Right_Detect <= white_threshold){       // need to turn left 
    current_state = TURN_LEFT;
  }
  else if(ADC_Right_Detect >= black_threshold &&
          ADC_Left_Detect >= black_threshold){
            current_state = previous_state;                    // else do nothing                
          }else{
            current_state = SPIN;               // completely off the line, spin
          }
  if(black_line_count >= LOOP_TIME){
    current_state = EXIT;
  }
}

void exit_loop(void){
  stop_Movement();
  wait_ntime(ONE_SEC);
  CW_ntime(EXIT_TURN_TIME);
  stop_Movement();
  forward_ntime(ONE_SEC); 
  clock_running = FALSE;
}

void wait_ntime(int cycletime){
  wait_count = BEGINNING;
  while(wait_count < cycletime);
}

void CCW_ntime(int cycletime){
  wait_count = BEGINNING;
  while(wait_count < cycletime){
    spin_CCW();
  }
  stop_Movement();
}

void CW_ntime(int cycletime){
  wait_count = BEGINNING;
  while(wait_count < cycletime){
    spin_CW();
  }
  stop_Movement();
}

