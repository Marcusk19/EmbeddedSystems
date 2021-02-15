//==============================================================================
// Filename : wheels.c
//
// Description: This file contains the functions for the wheels 
//
// Author: Marcus Kok
// Date: February 2020
// Compiler: Built with IAR Embedded Workbench for MSP430 7.12.4
//==============================================================================

#include  "functions.h"
#include  "msp430.h"
#include "macros.h"

//GLOBALS=======================================================================
extern unsigned int myTime;
int waitCount = RESET_STATE;
extern unsigned int prevButton;
extern unsigned int buttonPress;
extern int wheelCount;
//==============================================================================

void turnOnRight(void){
  P6OUT |= R_FORWARD;
}

void turnOnLeft(void){
  P6OUT |= L_FORWARD;
}

void turnOffRight(void){
  P6OUT &= ~R_FORWARD;
}

void turnOffLeft(void){
  P6OUT &= ~L_FORWARD;
}

void setRightSpeed(int speed){
  if(myTime < speed){
    turnOnRight();
  }else{
    turnOffRight();
  }
}

void setLeftSpeed(int speed){
  if(myTime < speed){
    turnOnLeft();
  }else{
    turnOffLeft();
  }
}

void resetMotors(void){ // turn off all forward movement
  turnOffLeft();
  turnOffRight();
}

void rightTurn(void){
    setLeftSpeed(FAST);
    setRightSpeed(SLOW);
}

void leftTurn(void){
    setRightSpeed(FAST);
    setLeftSpeed(SLOW); 
}

void straightLine(void){
      setRightSpeed(FAST);
      setLeftSpeed(FAST);
}

void sharpTurnRight(void){
      turnOffRight();
      setLeftSpeed(FAST);
}

void sharpTurnLeft(void){
      turnOffLeft();
      setRightSpeed(FAST);
}

void turnRightEight(void){
  setRightSpeed(VERY_SLOW);
  setLeftSpeed(FAST);
}
  
void turnLeftEight(void){
    setLeftSpeed(VERY_SLOW);
    setRightSpeed(FAST);
}

/*void stop(int nCycles){
  buttonPress = HOLD;
  if(myTime == WAIT_TIME){
    waitCount ++;
  }
  if(waitCount == nCycles){
    waitCount = RESET_STATE;
    buttonPress = prevButton;
  }       
}*/
  
  