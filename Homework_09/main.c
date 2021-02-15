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
unsigned int emitter_display_change = TRUE;

volatile unsigned int wheel_state = HOLD;
volatile unsigned int main_state = HOLD;
extern volatile unsigned int next_state;
extern int display_state;

unsigned int black_line_flag = FALSE;
extern unsigned int one_second_flag;
unsigned int main_wait_count = RESET_STATE;
unsigned int wait_count = RESET_STATE;

extern unsigned int ADC_Left_Detect;
extern unsigned int ADC_Right_Detect;



extern unsigned int usb_rx_ring_rd;
extern volatile unsigned int usb_rx_ring_wr;
extern volatile char USB_Char_Rx[SMALL_RING_SIZE];
extern int UCA0_index;
extern int UCA1_index;
extern char receive_char[MAX_STR_SIZE];
extern char transmit_char[MAX_STR_SIZE];

extern unsigned int Button_One;
extern unsigned int Button_Two;



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
  Init_Timers();                        // Initialize Timers
  Init_LCD();                          // Initialize LCD
  Init_Wheels();
  Init_ADC();
  Init_Serial_UCA0();                   // Initialize Serial communication
  Init_Serial_UCA1();
  Init_Chars();                         // Initialize char display on screen
  
// Place the contents of what you want on the display, in between the quotes
// Limited to 10 characters per line
//



  UCA0_index = RESET_STATE;
  UCA1_index = RESET_STATE;

//------------------------------------------------------------------------------
// Begining of the "While" Operating System
//------------------------------------------------------------------------------
  while(ALWAYS){  // Can the Operating system run
    switch(main_state){
    case HOLD:
      lcd_BIG_mid();
      strcpy(display_line[line1], "Marcus    ");
      update_string(display_line[line1], line1);
      strcpy(display_line[line3], "HW #9     ");
      update_string(display_line[line3], line3);
      display_changed = TRUE;
      if(Button_One || Button_Two){
        Button_One = FALSE;
        Button_Two = FALSE;
        main_state = MENU;
      }
      break;
    case MENU:
      menu_process();
    break;
    default: break;
    }
    Display_Process(); 
    //Serial_Display_Process();
    //clock_process(); // update myTime
    //Switches_Process(); //check switches
  }

//------------------------------------------------------------------------------
}

void clear_receive_char(void){
  for(int i = BEGINNING; i < MAX_STR_SIZE; i++){
    receive_char[i] = NULL;
  }
}

void clear_transmit_char(void){
  for(int i = BEGINNING; i < MAX_STR_SIZE; i++){
    transmit_char[i] = NULL;
  }
}
  