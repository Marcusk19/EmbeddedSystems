//------------------------------------------------------------------------------
//
//  Description: This file contains the Main Routine - "While" Operating System
//
//
//  Jim Carlson
//  Jan 2018
//  Built with IAR Embedded Workbench Version: V4.10A/W32 (7.11.2)
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
#include  "functions.h"
#include  "msp430.h"
#include "macros.h"
#include <string.h>


// Function Prototypes
void main(void);
void Init_Conditions(void);
void Init_LEDs(void);

  // Global Variables
volatile char slow_input_down;
extern char display_line[numLines][strSize];
extern char *display[numLines];
unsigned char display_mode;
extern volatile unsigned char display_changed;
extern volatile unsigned char update_display;
extern volatile unsigned int update_display_count;
extern volatile unsigned int Time_Sequence;
unsigned int prevTime_Sequence = RESET_STATE; 
unsigned int myTime = RESET_STATE;
unsigned int buttonState = HOLD; //initialize state to be circle
volatile char one_time = TRUE;
unsigned int test_value;
char chosen_direction;
char change;
unsigned int num_presses = RESET_STATE;
extern unsigned int emitter_flag;
unsigned int emitter_display_change = TRUE;

volatile unsigned int wheel_state = HOLD;

unsigned int black_line_flag = FALSE;
extern unsigned int one_second_flag;
unsigned int wait_count = RESET_STATE;

extern unsigned int ADC_Left_Detect;
extern unsigned int ADC_Right_Detect;


void main(void){
//------------------------------------------------------------------------------
// Main Program
// This is the main routine for the program. Execution of code starts here.
// The operating system is Back Ground Fore Ground.
//
//------------------------------------------------------------------------------
// Disable the GPIO power-on default high-impedance mode to activate
// previously configured port settings
  PM5CTL0 &= ~LOCKLPM5;
  Init_Ports();                        // Initialize Ports
  Init_Clocks();                       // Initialize Clock System
  Init_Conditions();                   // Initialize Variables and Initial Conditions
  Init_Timers();  // Initialize Timers
  Init_LCD();                          // Initialize LCD
  Init_Wheels();
  Init_ADC();
// Place the contents of what you want on the display, in between the quotes
// Limited to 10 characters per line
//

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


//------------------------------------------------------------------------------
// Begining of the "While" Operating System
//------------------------------------------------------------------------------
while(ALWAYS){  // Can the Operating system run
      // Check for switch state change
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
    
    Display_Process(); 
    //clock_process(); // update myTime
    Switches_Process(); //check switches, display emit on or off
  }

//------------------------------------------------------------------------------
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
  



