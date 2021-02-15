//==============================================================================
// Filename: shapes.c
// Description: contains functions for the car to draw shapes
// 
// Author: Marcus Kok
// Date: Feb 2020
// Compiler: Built with IAR Embedded Workbench 7.12.4
//==============================================================================

#include "msp430.h"
#include "macros.h"
#include "functions.h"
#include <string.h>

extern unsigned int buttonPress;
extern unsigned int myTime;
extern char display_line[numLines][strSize];
extern unsigned char display_changed;
extern unsigned int num_presses;
unsigned int prevButton;
extern int shapeCount;
int triangleCount = RESET_STATE;


void runShapes(void){
  switch(buttonPress){
    
  case CIRCLE: 
    drawCCW_Circle();
    break;
    
    
  case TRIANGLE:
    prevButton = TRIANGLE;
    drawTriangle();
    break;
    
  case FIGURE_EIGHT:
    prevButton = FIGURE_EIGHT;
    drawFigureEight();   
    break;  
    
  case FIG_EIGHT_TWO:
     drawFigureEightTwo();
     break;
     
  case FIGURE_EIGHT_THREE:
    drawFigureEightThree();
    break;
  
  case FIGURE_EIGHT_FINISH:
    drawFigureEightFinish();
    break;
 
    
  case HOLD:
    shapeCount = RESET_STATE;
    resetMotors();
    break;
    
   default:
    break;
  }
}

void displayShapes(void){
  switch(buttonPress){
    
  case CIRCLE:
    strcpy(display_line[line2], "  circle ");
    update_string(display_line[line2], line2);
    enable_display_update(); //change display
    break;
    
  case TRIANGLE:
    strcpy(display_line[line2], " triangle ");
    update_string(display_line[line2], line2);
    enable_display_update(); //change display
    break;
    
  case FIGURE_EIGHT:
    strcpy(display_line[line2], "figure 8");
    update_string(display_line[line2], line2);
    enable_display_update(); //change display
    break;
  
  case FIG_EIGHT_TWO:
    strcpy(display_line[line2], "figure 8");
    update_string(display_line[line2], line2);
    enable_display_update(); //change display
    break;
    
    
    
  case HOLD:
    strcpy(display_line[line2], "hold    ");
    update_string(display_line[line2], line2);
    enable_display_update(); //change display
    break;
  
  default: 
    break;
  }
}
    
    

//==============================================================================
//shape functions
//==============================================================================

void drawCW_Circle(void){
      rightTurn();
      if(shapeCount == circNumTurns){
        buttonPress = CIRCLE;
        shapeCount = RESET_STATE;
      }
}

void drawCCW_Circle(void){
    leftTurn();
    if(shapeCount == circNumTurns){
      buttonPress = HOLD;
      shapeCount = RESET_STATE;
  }
}
  
 void drawFigureEight(void){
   turnRightEight();
      if(shapeCount == FIG_EIGHT_TURNS){
        buttonPress = FIG_EIGHT_TWO;
        shapeCount = RESET_STATE;
      }
 }
void drawFigureEightTwo(void){
   turnLeftEight();
    if(shapeCount == FIG_EIGHT_TURNS){
      buttonPress = FIGURE_EIGHT_THREE;
      shapeCount = RESET_STATE;
  }
}

void drawFigureEightThree(void){
  turnRightEight();
  if(shapeCount == FIG_EIGHT_TURNS){
        buttonPress = FIGURE_EIGHT_FINISH;
        shapeCount = RESET_STATE;
      }
}

void drawFigureEightFinish(void){
  turnLeftEight();
  if(shapeCount == FIG_EIGHT_TURNS){
    buttonPress = HOLD;
    shapeCount = RESET_STATE;
  }
}

void drawTriangle(void){
  if(triangleCount%ODD){
    trianglePoint();
  }else{
    triangleLeg();
  }
  
  if(triangleCount == TRIANGLE_SIDES){
    triangleCount = RESET_STATE;
    buttonPress = HOLD;
  }
    
}

void triangleLeg(void){
  straightLine();
  if(shapeCount == LINE_LENGTH){
    triangleCount++;
    shapeCount = RESET_STATE;
  }
}

void trianglePoint(void){
  sharpTurnRight();
  if(shapeCount == TURN_ANGLE){
    triangleCount++;
    shapeCount = RESET_STATE;
  }
}