//==============================================================================
// Filename : menus.c
//
// Description: This file contains functions for menus used in Homework_09
// converter
//
// Author: Marcus Kok
// Date: April 2020
// Compiler: Built with IAR Embedded Workbench for MSP430 7.12.4
//==============================================================================


#include "macros.h"
#include "msp430.h"
#include "functions.h"
#include <string.h>

//globals-----------------------------------------------------------------------
  
  extern char display_line[numLines][strSize];
  extern volatile unsigned char display_changed;

  extern unsigned int ADC_Thumb;
  unsigned int menu_state = MAIN;
  unsigned int main_menu_state;
  unsigned int menu_display;
  extern unsigned int Button_One;
  extern unsigned int Button_Two; 
  char song[] = "We're the Red and White from State And we know we are the best. A hand behind our back, We can take on all the rest. Come over the hill, Carolina, Devils and Deacs stand in line. The Red and White from N.C. State. Go State!";
  int thumb_val = RESET_STATE;
  int prev_thumb_val = RESET_STATE;
  char out_song[MAX_STR_SIZE] = "";
  int index = RESET_STATE;
  int red_white = TRUE;

//------------------------------------------------------------------------------
void menu_process(void){                        // what runs in main loop 
  switch(menu_state){
  case MAIN:
    lcd_BIG_mid();
    clear_line1();
    clear_line3();
    main_menu();
    break;
  case RESISTORS:
    lcd_4line();
    //lcd_clear();
    strcpy(display_line[line1], "Color:    ");
    update_string(display_line[line1], line1);
    strcpy(display_line[line3], "Value:    ");
    update_string(display_line[line3], line3);
    display_changed = TRUE;
    Resistor_Scroll();
    Resistor_Menu_Process();
    break;
  case SHAPES:
    lcd_BIG_mid();
    Shapes_Scroll();
    Shapes_Menu_Process();
    break;
  case SONG:
    lcd_BIG_mid();
    clear_line2();
    Song_Scroll();
    break;
  default: break;
  }
}

void Resistor_Menu_Process(void){
  switch(menu_display){
  case RES_ONE:
    strcpy(display_line[line2], "  Black   ");
    update_string(display_line[line2], line2);
    strcpy(display_line[line4], "    0     ");
    update_string(display_line[line4], line4);
    display_changed = TRUE;
    break;
  case RES_TWO:
    strcpy(display_line[line2], "  Brown   ");
    update_string(display_line[line2], line2);
    strcpy(display_line[line4], "    1     ");
    update_string(display_line[line4], line4);
    display_changed = TRUE;
    break;
  case RES_THREE:
    strcpy(display_line[line2], "  Red     ");
    update_string(display_line[line2], line2);
    strcpy(display_line[line4], "    2     ");
    update_string(display_line[line4], line4);
    display_changed = TRUE;
    break;
  case RES_FOUR:
    strcpy(display_line[line2], "  Orange  ");
    update_string(display_line[line2], line2);
    strcpy(display_line[line4], "    3     ");
    update_string(display_line[line4], line4);
    display_changed = TRUE;
    break;
  case RES_FIVE:
    strcpy(display_line[line2], "  Yellow  ");
    update_string(display_line[line2], line2);
    strcpy(display_line[line4], "    4     ");
    update_string(display_line[line4], line4);
    display_changed = TRUE;
    break;
  case RES_SIX:
    strcpy(display_line[line2], "  Green   ");
    update_string(display_line[line2], line2);
    strcpy(display_line[line4], "    5     ");
    update_string(display_line[line4], line4);
    display_changed = TRUE;
    break;
  case RES_SEVEN:
    strcpy(display_line[line2], "  Blue    ");
    update_string(display_line[line2], line2);
    strcpy(display_line[line4], "    6     ");
    update_string(display_line[line4], line4);
    display_changed = TRUE;
    break;
  case RES_EIGHT:
    strcpy(display_line[line2], "  Violet  ");
    update_string(display_line[line2], line2);
    strcpy(display_line[line4], "    7     ");
    update_string(display_line[line4], line4);
    display_changed = TRUE;
    break;
  case RES_NINE:
    strcpy(display_line[line2], "   Gray   ");
    update_string(display_line[line2], line2);
    strcpy(display_line[line4], "    8     ");
    update_string(display_line[line4], line4);
    display_changed = TRUE;
    break;
  case RES_TEN:
    strcpy(display_line[line2], "   White  ");
    update_string(display_line[line2], line2);
    strcpy(display_line[line4], "    9     ");
    update_string(display_line[line4], line4);
    display_changed = TRUE;
    break;
  default: break;
  }
}

void Resistor_Scroll(void){
  if(Button_Two){
    clear_line2();
    menu_state = MAIN;
    Button_Two = FALSE;
  }
  if(ADC_Thumb <= RES_MENU_ONE){
    menu_display = RES_ONE;
  }
  if(ADC_Thumb > RES_MENU_ONE && ADC_Thumb <= RES_MENU_TWO){
    menu_display = RES_TWO;
  }
  if(ADC_Thumb > RES_MENU_TWO && ADC_Thumb <= RES_MENU_THREE){
    menu_display = RES_THREE;
  }
  if(ADC_Thumb > RES_MENU_THREE && ADC_Thumb <= RES_MENU_FOUR){
    menu_display = RES_FOUR;
  }
  if(ADC_Thumb > RES_MENU_FOUR && ADC_Thumb <= RES_MENU_FIVE){
    menu_display = RES_FIVE;
  }
  if(ADC_Thumb > RES_MENU_FIVE && ADC_Thumb <= RES_MENU_SIX){
    menu_display = RES_SIX;
  }
  if(ADC_Thumb > RES_MENU_SIX && ADC_Thumb <= RES_MENU_SEVEN){
    menu_display = RES_SEVEN;
  }
  if(ADC_Thumb > RES_MENU_SEVEN && ADC_Thumb <= RES_MENU_EIGHT){
    menu_display = RES_EIGHT;
  }
  if(ADC_Thumb > RES_MENU_EIGHT && ADC_Thumb <= RES_MENU_NINE){
    menu_display = RES_NINE;
  }
  if(ADC_Thumb > RES_MENU_NINE && ADC_Thumb <= RES_MENU_TEN){
    menu_display = RES_TEN;
  }
}

void main_menu(void){
  main_menu_state = ADC_Thumb >> SHIFT_TEN;                      // right shift so there are 2 bits (4 values)
  switch(main_menu_state){
  case RESISTORS:
    strcpy(display_line[line2], " Resistors");
    update_string(display_line[line2], line2);
    display_changed = TRUE;
    
    if(Button_One){
      menu_state = RESISTORS;
      Button_One = FALSE;
    }
    break;
  case SHAPES:
    strcpy(display_line[line2], "  Shapes  ");
    update_string(display_line[line2], line2);
    display_changed = TRUE;
    
    if(Button_One){
      menu_state = SHAPES;
      Button_One = FALSE;
    }
    break;
  case SONG:
    strcpy(display_line[line2], "   Song   ");
    update_string(display_line[line2], line2);
    display_changed = TRUE;
    if(Button_One){
      menu_state = SONG;
      Button_One = FALSE;
    }
    break;
  default:
      strcpy(display_line[line2], " Resistors");
      update_string(display_line[line2], line2);
      display_changed = TRUE;
      
      if(Button_One){
        menu_state = RESISTORS;
        Button_One = FALSE;
      }
    break;
  }
}

void Shapes_Scroll(void){
  if(Button_Two){
    menu_state = MAIN;
    Button_Two = FALSE;
  }
  if(ADC_Thumb <= SHAPE_MENU_ONE){
    menu_display = CIRCLE;
  }
  if(ADC_Thumb > SHAPE_MENU_ONE && ADC_Thumb <= SHAPE_MENU_TWO){
    menu_display = SQUARE;
  }
  if(ADC_Thumb > SHAPE_MENU_TWO && ADC_Thumb <= SHAPE_MENU_THREE){
    menu_display = TRIANGLE;
  }
  if(ADC_Thumb > SHAPE_MENU_THREE && ADC_Thumb <= SHAPE_MENU_FOUR){
    menu_display = OCTAGON;
  }
  if(ADC_Thumb > SHAPE_MENU_FOUR && ADC_Thumb <= SHAPE_MENU_FIVE){
    menu_display = PENTAGON;
  }
  if(ADC_Thumb > SHAPE_MENU_FIVE && ADC_Thumb <= SHAPE_MENU_SIX){
    menu_display = HEXAGON;
  }
  if(ADC_Thumb > SHAPE_MENU_SIX && ADC_Thumb <= SHAPE_MENU_SEVEN){
    menu_display = CUBE;
  }
  if(ADC_Thumb > SHAPE_MENU_SEVEN && ADC_Thumb <= SHAPE_MENU_EIGHT){
    menu_display = OVAL;
  }
  if(ADC_Thumb > SHAPE_MENU_EIGHT && ADC_Thumb <= SHAPE_MENU_NINE){
    menu_display = SPHERE;
  }
  if(ADC_Thumb > SHAPE_MENU_NINE && ADC_Thumb <= SHAPE_MENU_TEN){
    menu_display = CYLINDER;
  }
}

void Shapes_Menu_Process(void){
 switch(menu_display){
  case CIRCLE:
    strcpy(display_line[line1], "          ");
    update_string(display_line[line1], line1);
    strcpy(display_line[line2], "  Circle  ");
    update_string(display_line[line2], line2);
    strcpy(display_line[line3], "  Square  ");
    update_string(display_line[line3], line3);
    display_changed = TRUE;
    break;
  case SQUARE:
    strcpy(display_line[line1], "  Circle   ");
    update_string(display_line[line1], line1);
    strcpy(display_line[line2], "  Square  ");
    update_string(display_line[line2], line2);
    strcpy(display_line[line3], " Triangle ");
    update_string(display_line[line3], line3);
    display_changed = TRUE;
    break;
  case TRIANGLE:
    strcpy(display_line[line1], "  Square  ");
    update_string(display_line[line1], line1);
    strcpy(display_line[line2], " Triangle ");
    update_string(display_line[line2], line2);
    strcpy(display_line[line3], " Octagon  ");
    update_string(display_line[line3], line3);
    display_changed = TRUE;
    break;
  case OCTAGON:
    strcpy(display_line[line1], " Triangle ");
    update_string(display_line[line1], line1);
    strcpy(display_line[line2], " Octagon  ");
    update_string(display_line[line2], line2);
    strcpy(display_line[line3], " Pentagon ");
    update_string(display_line[line3], line3);
    display_changed = TRUE;
    break;
  case PENTAGON:
    strcpy(display_line[line1], " Octagon  ");
    update_string(display_line[line1], line1);
    strcpy(display_line[line2], " Pentagon ");
    update_string(display_line[line2], line2);
    strcpy(display_line[line3], " Hexagon  ");
    update_string(display_line[line3], line3);
    display_changed = TRUE;
    break;
  case HEXAGON:
    strcpy(display_line[line1], " Pentagon ");
    update_string(display_line[line1], line1);
    strcpy(display_line[line2], " Hexagon  ");
    update_string(display_line[line2], line2);
    strcpy(display_line[line3], "  Cube    ");
    update_string(display_line[line3], line3);
    display_changed = TRUE;
    break;
  case CUBE:
    strcpy(display_line[line1], " Hexagon  ");
    update_string(display_line[line1], line1);
    strcpy(display_line[line2], "  Cube    ");
    update_string(display_line[line2], line2);
    strcpy(display_line[line3], "   Oval   ");
    update_string(display_line[line3], line3);
    display_changed = TRUE;
    break;
  case OVAL:
    strcpy(display_line[line1], "  Cube    ");
    update_string(display_line[line1], line1);
    strcpy(display_line[line2], "   Oval   ");
    update_string(display_line[line2], line2);
    strcpy(display_line[line3], "  Sphere  ");
    update_string(display_line[line3], line3);
    display_changed = TRUE;
    break;
  case SPHERE:
    strcpy(display_line[line1], "   Oval   ");
    update_string(display_line[line1], line1);
    strcpy(display_line[line2], "  Sphere  ");
    update_string(display_line[line2], line2);
    strcpy(display_line[line3], " Cylinder ");
    update_string(display_line[line3], line3);
    display_changed = TRUE;
    break;
  case CYLINDER:
    strcpy(display_line[line1], "  Sphere  ");
    update_string(display_line[line1], line1);
    strcpy(display_line[line2], " Cylinder ");
    update_string(display_line[line2], line2);
    strcpy(display_line[line3], "          ");
    update_string(display_line[line3], line3);
    display_changed = TRUE;
    break;
  default: break;
 }
}
 
void Song_Scroll(void){
  if(Button_Two){
    menu_state = MAIN;
    Button_Two = FALSE;
  }
  thumb_val = ADC_Thumb;
  if(thumb_val > prev_thumb_val + SCROLL_RANGE){
    out_song[0] = song[index];
    out_song[1] = song[index+1];
    out_song[2] = song[index+2];
    out_song[3] = song[index+3];
    out_song[4] = song[index+4];
    out_song[5] = song[index+5];
    out_song[6] = song[index+6];
    out_song[7] = song[index+7];
    out_song[8] = song[index+8];
    out_song[9] = song[index+9];
    index++;
    if(index > sizeof(song) - MAX_STR_SIZE){
      index = RESET_STATE;
    }
   
    if(red_white){
    strcpy(display_line[line1], "    Red   ");
    update_string(display_line[line1], line1);
    strcpy(display_line[line3], "   White  ");
    update_string(display_line[line3], line3);
    display_changed = TRUE;
    }
    else{
    strcpy(display_line[line1], "   White  ");
    update_string(display_line[line1], line1);
    strcpy(display_line[line3], "    Red   ");
    update_string(display_line[line3], line3);
    display_changed = TRUE;
    }
    red_white = !red_white;
  }
    strcpy(display_line[line2], out_song);
    update_string(display_line[line2], line2);
    display_changed = TRUE; 
  prev_thumb_val = thumb_val;
}