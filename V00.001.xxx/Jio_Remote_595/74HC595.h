#ifndef _74HC595_H
#define _74HC595_H

/*
  ShiftRegister74HC595 - Library for simplified control of 74HC595 shift registers.
  Developed and maintained by Timo Denk and contributers, since Nov 2014.
  Additional information is available at https://timodenk.com/blog/shift-register-arduino-library/
  Released into the public domain.
*/

#include <ShiftRegister74HC595.h>

extern String Channel;
//#include "PIN_CONFIG.h"
/*
int DATA_PIN = 5;
int CLK_PIN = 0;
int LATCH_PIN = 2;
*/
// create a global shift register object
// parameters: <number of shift registers> (data pin, clock pin, latch pin)
ShiftRegister74HC595<3> sr(DATA_PIN, CLK_PIN, LATCH_PIN);

void Button_click(uint8_t pin);

void No_click()
{
  sr.setAllLow(); // set all pins LOW
  //Serial.println(" All LOW");
}

void All_click()
{
  sr.setAllHigh(); // set all pins HIGH
  Serial.println("All HIGH ");
}

void Button_click(uint8_t pin)
{
   sr.set(pin, 1);
/*
   Serial.print("PIN : ");
   Serial.print(pin);
   Serial.println("  STATE  : Clicked");
*/
   delay(50);
   No_click();

   delay(1000);  
}

void Fast_Button_click(uint8_t pin)
{
   sr.set(pin, 1);

   delay(50);
   No_click();

   delay(50);  
}

void pair_remote()
{
  Serial.println("Pair Jio Remote");
  sr.set(Jio_OK, 1);
  delay(25000);

  No_click();
  delay(1000);

}


#endif //_74HC595_H
