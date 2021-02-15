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
//------------------------------------------------------------------------------


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

void adc_line4(int position){                   // print adc value to 4th line
    strcat(adc_char, display_Buffer);
    strcpy(display_line[line4], adc_char);      // update display
    update_string(display_line[line4], line4);
    enable_display_update();
    display_changed = TRUE;
    
    //clear_adc_char();                          // reset adc_char
}

void adc_line2(int position){                   // print adc value to 2nd line
  strcat(adc_char, display_Buffer);
  strcpy(display_line[line2], adc_char);        // update display
  update_string(display_line[line2], line2);
  enable_display_update();
  display_changed = TRUE;
  
  //clear_adc_char();                            // reset adc_char
}

void adc_line3(int position){                   // print adc value to 3rd line
  strcat(adc_char, display_Buffer);
  strcpy(display_line[line3], adc_char);        // update display
  update_string(display_line[line3], line3);
  enable_display_update();
  display_changed = TRUE;
}

void emitter_Off(void){
  P3OUT &= ~IR_LED;                             // turn emitter off
}

void emitter_On(void){                          // turne emitter on
  P3OUT |= IR_LED;
}

void clear_adc_char(void){
  for(int i = RESET_STATE; i < ADC_NUM_DIGITS; i++){
    adc_char[i] = '0';
  }
}
  
  