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
volatile unsigned int next_state = RESET_STATE;
extern int display_state;

unsigned int black_line_flag = FALSE;
extern unsigned int one_second_flag;
unsigned int main_wait_count = RESET_STATE;
unsigned int wait_count = RESET_STATE;

extern unsigned int ADC_Left_Detect;
extern unsigned int ADC_Right_Detect;

int UCA1_index;
int UCA0_index = RESET_STATE;
char test_command[NCSU_SIZE] = "NCSU  #1";
extern unsigned int usb_rx_ring_rd;
extern volatile unsigned int usb_rx_ring_wr;
extern volatile char USB_Char_Rx[SMALL_RING_SIZE];
volatile char process_buf[LARGE_RING_SIZE];
char receive_char[MAX_STR_SIZE];
char transmit_char[MAX_STR_SIZE];
int process_index = BEGINNING;
int serial_mode = WAIT;


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


  UCA0_index = RESET_STATE;
  UCA1_index = RESET_STATE;
  //UCA0IE |= UCRXIE; // Enable RX interrupt
  //UCA1IE |= UCRXIE; // Enable Rx interrupt
//------------------------------------------------------------------------------
// Begining of the "While" Operating System
//------------------------------------------------------------------------------
  while(ALWAYS){  // Can the Operating system run
    
    switch(main_state){
    case HOLD:
      if(one_second_flag){
        main_wait_count ++;
        one_second_flag = FALSE;
      }
      if(wait_count == TWO_SECOND_PAUSE){
        main_wait_count = RESET_STATE;
        main_state = next_state;
      }
      break;
      
    case RECEIVE:
    if(usb_rx_ring_rd != usb_rx_ring_wr){
      
        process_buf[usb_rx_ring_rd] = USB_Char_Rx[usb_rx_ring_rd];
        
        if(process_buf[usb_rx_ring_rd] == 0x0A || process_buf[usb_rx_ring_rd] == 0x0D){
          clear_receive_char();
          clear_transmit_char();
          usb_rx_ring_rd = BEGINNING;
          usb_rx_ring_wr = BEGINNING;
          main_state = PROCESS;
          one_time = TRUE;
          break;
        }
        usb_rx_ring_rd++;
        if(usb_rx_ring_rd >= (sizeof(USB_Char_Rx))){
          usb_rx_ring_rd = BEGINNING;
        }
    }
    
    break;
    case PROCESS:
      receive_char[process_index] = process_buf[process_index];
      process_buf[process_index] = '\0';                // clear out process buffer
      process_index++;
      if(process_buf[process_index] == 0x0A || process_buf[process_index] == 0x0D){
        receive_char[process_index] = '\0';             // null last char
        strcpy(transmit_char, receive_char);            // copy receive to transmit
        clear_line4();
        main_state = HALT;
        serial_mode = RECEIVE;
        process_index = BEGINNING;
      }
    break;
    case HALT:
      
      break;
    default: break;
    }
    
    Display_Process(); 
    Serial_Display_Process();
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
  