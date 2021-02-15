//==============================================================================
// Filename : ADC.c
//
// Description: This file contains functions for analog to digital
// converter
//
// Author: Marcus Kok
// Date: February 2020
// Compiler: Built with IAR Embedded Workbench for MSP430 7.12.4
//==============================================================================

#include "macros.h"
#include "msp430.h"
#include "functions.h"
#include <string.h>

//--------------------------- globals ------------------------------------------
char adc_char[ADC_NUM_DIGITS];
char display_Buffer[] = "      ";
extern volatile unsigned char display_changed;
extern char display_line[numLines][strSize];
extern volatile unsigned int CCR0_COUNT;
  
  unsigned int black_threshold = BLACK_THRESHOLD;
  unsigned int white_threshold = WHITE_THRESHOLD;
  unsigned int calibrate_state = CAL_BLACK;
  unsigned int calibrated = FALSE;
  
  extern unsigned int Button_One;
  extern unsigned int ADC_Left_Detect;
  extern unsigned int ADC_Right_Detect;
  extern unsigned int ADC_Thumb; 
  extern unsigned int circle_clock;
  char circle_timer[6];
//------------------------------------------------------------------------------

void display_ADC(void){
      HEXtoBCD(ADC_Left_Detect);          // convert result to a string
      ClrDisplay_Buffer_3();
      adc_line4(POSITION_ONE);            // place string in display
      
      HEXtoBCD(ADC_Right_Detect);         // convert result to a string
      ClrDisplay_Buffer_2();
      adc_line3(POSITION_ONE);            // place string in display
      
      HEXtoBCD(ADC_Thumb);                // convert result to a string
      ClrDisplay_Buffer_1();
      adc_line2(POSITION_ONE);            // place string in display
}

void getCircleTime(int hex_value){
  int value;
  circle_timer[BCD_THOUSAND] = '0';
  while(hex_value > THOUSANDS){
    hex_value = hex_value - THOUSAND_DIV;
    value++;
    circle_timer[BCD_THOUSAND] = ASCII_CONV + value;
  }
  value = RESET_STATE;
  circle_timer[BCD_HUNDRED] = '0';
  while(hex_value > HUNDREDS){
    hex_value = hex_value - HUNDRED_DIV;
    value++;
    circle_timer[BCD_HUNDRED] = ASCII_CONV + value;
  }
  value = RESET_STATE;
  adc_char[BCD_TEN] = '0';
  while(hex_value > TENS){
    hex_value = hex_value - TEN_DIV;
    value++;
    circle_timer[BCD_TEN] = ASCII_CONV + value;
  }
  circle_timer[BCD_ONE] = '.';
  circle_timer[BCD_TENTH] = '0';
  circle_timer[BCD_TENTH] = ASCII_CONV + hex_value;
  circle_timer[CIRCLE_NULL] = NULL;
}

// hex to BCD conversion
void HEXtoBCD(int hex_value){
  int value;
  adc_char[BCD_THOUSAND] = '0';
  while(hex_value > THOUSANDS){
    hex_value = hex_value - THOUSAND_DIV;
    value++;
    adc_char[BCD_THOUSAND] = ASCII_CONV + value;
  }
  value = RESET_STATE;
  adc_char[BCD_HUNDRED] = '0';
  while(hex_value > HUNDREDS){
    hex_value = hex_value - HUNDRED_DIV;
    value++;
    adc_char[BCD_HUNDRED] = ASCII_CONV + value;
  }
  value = RESET_STATE;
  adc_char[BCD_TEN] = '0';
  while(hex_value > TENS){
    hex_value = hex_value - TEN_DIV;
    value++;
    adc_char[BCD_TEN] = ASCII_CONV + value;
  }
  adc_char[BCD_ONE] = '0';
  adc_char[BCD_ONE] = ASCII_CONV + hex_value;
  adc_char[NULL_TERMINATOR] = '\0';
}

void calibrate_sensors(void){
  //ReadADC();
  switch(calibrate_state){
  case CAL_BLACK:
    if(Button_One){
      Button_One = FALSE;
      int var1 = ADC_Right_Detect;
      int var2 = ADC_Left_Detect;
      var1 = var1 + var2;
      black_threshold = var1 >> DIVIDE_BY_TWO;
      calibrate_state = CAL_WHITE;
    }
    break;
  case CAL_WHITE:
    if(Button_One){
      Button_One = FALSE;
      int var1 = ADC_Right_Detect;
      int var2 = ADC_Left_Detect;
      var1 = var1 + var2;
      white_threshold = var1 >> DIVIDE_BY_TWO;
      white_threshold += CALIBRATION_ERROR;     // offset to ensure accuracy
      calibrate_state = CAL_BLACK;
      calibrated = TRUE;
    }
    break;      
  default:break;
  }
}
void adc_line4(int position){                   // print adc value to 4th line
    strcat(adc_char, display_Buffer);
    strcpy(display_line[line4], adc_char);      // update display
    update_string(display_line[line4], line4);
    display_changed = TRUE;
    
    //clear_adc_char();                          // reset adc_char
}

void adc_line2(int position){                   // print adc value to 2nd line
  strcat(adc_char, display_Buffer);
  strcpy(display_line[line2], adc_char);        // update display
  update_string(display_line[line2], line2);
  display_changed = TRUE;
  
  //clear_adc_char();                            // reset adc_char
}

void adc_line3(int position){                   // print adc value to 3rd line
  strcat(adc_char, display_Buffer);
  strcpy(display_line[line3], adc_char);        // update display
  update_string(display_line[line3], line3);
  display_changed = TRUE;
}

void emitter_Off(void){
  P3OUT &= ~IR_LED;                             // turn emitter off
}

void emitter_On(void){                          // turne emitter on
  P3OUT |= IR_LED;
}

void ReadADC(void){
    ADCCTL0 |= ADCENC;                //  Enable Conversions
    ADCCTL0 |= ADCSC;                 // Start next Sample
}

void clear_adc_char(void){
  for(int i = RESET_STATE; i < ADC_NUM_DIGITS; i++){
    adc_char[i] = '0';
  }
}
  
  