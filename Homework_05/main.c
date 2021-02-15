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
extern volatile char one_time;
unsigned int test_value;
char chosen_direction;
char change;
unsigned int num_presses = RESET_STATE;

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
  Init_Timers();                       // Initialize Timers
  Init_LCD();                          // Initialize LCD
// Place the contents of what you want on the display, in between the quotes
// Limited to 10 characters per line
//

  strcpy(display_line[line1], "          ");
  update_string(display_line[line1], line1);
  strcpy(display_line[line2], "hold      ");
  update_string(display_line[line2], line2);
  strcpy(display_line[line3], "          ");
  update_string(display_line[line3], line3);
  strcpy(display_line[line4], "          ");
  update_string(display_line[line4], line4);
  enable_display_update();


//------------------------------------------------------------------------------
// Begining of the "While" Operating System
//------------------------------------------------------------------------------
while(ALWAYS) {                      // Can the Operating system run
    switch(Time_Sequence){
      case BINARY0:                        //
        if(one_time){
          Init_LEDs();
          display_changed = TRUE;
          one_time = FALSE;
        }
        Time_Sequence = FALSE;             //
        break;
      case BINARY1:                        //
        if(one_time){
          P6OUT |= GRN_LED;            // Change State of LED 5
          one_time = FALSE;
        }
        break;
      case BINARY2:                         //
        if(one_time){
          P1OUT |= RED_LED;            // Change State of LED 4
          P6OUT &= ~GRN_LED;           // Change State of LED 5
          one_time = FALSE;
        }
        break;
      case BINARY3:                         //
        if(one_time){
          P6OUT |= GRN_LED;            // Change State of LED 5
          display_changed = TRUE;
          one_time = FALSE;
        }
        break;
      case BINARYRES:                        //
        if(one_time){
          P1OUT &= ~RED_LED;           // Change State of LED 4
          P6OUT &= ~GRN_LED;           // Change State of LED 5
          one_time = FALSE;
        }
        break;                         //
      default: break;
    }
      // Check for switch state change
    Display_Process(); 
    clock_process(); // update myTime
    Switches_Process(); //check switches

  }
//------------------------------------------------------------------------------
}



