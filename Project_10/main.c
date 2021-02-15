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
unsigned int buttonState = HOLD; 
volatile char one_time = TRUE;
unsigned int test_value;
char chosen_direction;
char change;
unsigned int emitter_display_change = TRUE;
unsigned int IOT_start = TRUE;

volatile unsigned int wheel_state = HOLD;
volatile unsigned int main_state = HOLD;
extern volatile unsigned int next_state;
extern int display_state;

unsigned int black_line_flag = FALSE;
extern unsigned int one_second_flag;
unsigned int main_wait_count = RESET_STATE;
extern unsigned int wait_count;

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

extern volatile unsigned int IOT_enable_count;
extern volatile char command_ready;
extern unsigned int FRAM_Command;
extern volatile unsigned int one_second_count;
extern char current_IOT_char;
extern int new_IOT_char;
int Profile_Start = FALSE;
int LED_blink = FALSE;
unsigned int ADC_conv = FALSE;
extern unsigned int follow_ready;
unsigned int ADC_enable_count = BEGINNING;
unsigned int clock_running = FALSE;
extern unsigned int black_line_count;
extern unsigned int calibrated;
extern unsigned int BL_one_time;
//------------------------------------------------------------------------------
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
  //Init_ADC();
  Init_Serial_UCA0();                   // Initialize Serial communication
  Init_Serial_UCA1();
  Init_Chars();                         // Initialize char display on screen
  
// Place the contents of what you want on the display, in between the quotes
// Limited to 10 characters per line
//

  emitter_Off(); // turn off emitter to conserve power
  UCA0_index = BEGINNING;
  UCA1_index = BEGINNING;
//------------------------------------------------------------------------------
// Begining of the "While" Operating System
//------------------------------------------------------------------------------
  while(ALWAYS){  // Can the Operating system run

        if(IOT_start){              // Only do this on start up 
      if(IOT_enable_count > IOT_WAIT_TIME){
        IOT_enable_count = RESET_STATE;
        P5OUT |= IOT_RESET;     // set IOT_RESET inactive (high)
        main_state = START;
        IOT_start = FALSE;
      }
    }
// main state machine
//==============================================================================    
    switch(main_state){
    case HOLD:
    break;
    case START:
        if(current_IOT_char == '2'){
            main_state = GET_IP;
            new_IOT_char = FALSE;
        }
      break;
    case GET_IP:
      get_ip();
      break;
    case PROCESS_IP:
      process_ip();
      break;
    case DISPLAY_IP:
      display_ip();
      Profile_Start = TRUE;
      main_state = CONTROL;
      break;
    case PING:
      if(one_second_count >= ONE_SECOND){                 // ping google.com every second
        LED_blink = !LED_blink;
        one_second_count = RESET_STATE;
        send_command("AT+DNSLOOKUP=www.google.com\r\n");
        if(LED_blink)
          send_command("AT+DGPIO=30,1");
        else 
          send_command("AT+DGPIO=30,0");
      }
      break;
    
    case FIND_LINE:
      searchForLine();
      if(black_line_flag)
        main_state = BLACK_LINE;
      break;
      
    case BLACK_LINE:
        display_state = BLACK_LINE_DISPLAY;
          LineFollowing();
      if(Button_One){             // Button_One
        Button_One = FALSE;
        Button_Two = FALSE;
        calibrated = FALSE;
        stop_Movement();
        clear_LCD();
        main_state = CALIBRATING;
      }
      wait_for_command();
      main_display_process();
      break;
      
    case CALIBRATING:
      display_state = CALIBRATE;
      calibrate_sensors();
      if(calibrated){
        clear_LCD();
        BL_one_time = TRUE;
        main_state = BLACK_LINE;
      }
      main_display_process();
      break;
      
    case CONTROL:
      if(Button_One){                          // if flag is set send command to connect tcp router
        send_command("AT+NSTCP=50000,2\r");
        Button_One = FALSE;
      }
      wheel_control();
      Serial_Display_Process();
      wait_for_command();
      break;
      
    case EXIT:
      exit_loop();
      Serial_Display_Process();
      break; 
      
    case END:
      stop_Movement();
      display_state = BL_STOP;
      main_display_process();
      break;
      
    default: break;
    }
//==============================================================================
    Display_Process();
    //wait_for_command();
    //wheel_control();
    //Serial_Display_Process();
    //clock_process(); // update myTime
    //Switches_Process(); //check switches
  }
}
//------------------------------------------------------------------------------

  