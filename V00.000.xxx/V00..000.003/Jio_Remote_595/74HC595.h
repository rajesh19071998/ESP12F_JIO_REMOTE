#ifndef _74HC595_H
#define _74HC595_H

/*
  ShiftRegister74HC595 - Library for simplified control of 74HC595 shift registers.
  Developed and maintained by Timo Denk and contributers, since Nov 2014.
  Additional information is available at https://timodenk.com/blog/shift-register-arduino-library/
  Released into the public domain.
*/
#ifndef _SHIFT_REGISTER_74HC595_H
  #define _SHIFT_REGISTER_74HC595_H
  #include <ShiftRegister74HC595.h>
#endif

#include "Remote_Macro.h"
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
/******* JIO REMOTE start*/

void Etv()//k
{
  Serial.println(" ETV ");
  Button_click(Jio_TV);
  Button_click(1);
  Button_click(4);
  Button_click(1);
  Button_click(1);
}

void tv9()//k
{
  Serial.println(" TV9 ");
  Button_click(Jio_TV);
  Button_click(1);
  Button_click(4);
  Button_click(5);
  Button_click(9);
}

void GeminiMovies()//k
{
  Serial.println(" GEMINI MOVIES ");
  Button_click(Jio_TV);
  Button_click(1);
  Button_click(4);
  Button_click(3);
  Button_click(0);
  delay(2000);
  Button_click(Jio_OK);
}

void Gemini()//k
{
  Serial.println(" GEMINI ");
  Button_click(Jio_TV);
  Button_click(1);
  Button_click(4);
  Button_click(0);
  Button_click(5);
  delay(2000);
  Button_click(Jio_OK);
}

void GeminiComedy()//k
{
  Serial.println(" GEMINI COMEDY ");
  Button_click(Jio_TV);
  Button_click(1);
  Button_click(4);
  Button_click(4);
  Button_click(2);
  delay(2000);
  Button_click(Jio_OK);
}

void ZTelugu() //k
{
  Serial.println(" ZEE TELUGU ");
  Button_click(Jio_TV);
  Button_click(1);
  Button_click(4);
  Button_click(0);
  Button_click(3);
  delay(2000);
  Button_click(Jio_OK);
}

void EtvCinema()
{
  Serial.println(" ETV CINEMA ");
  Button_click(Jio_TV);
  Button_click(1);
  Button_click(4);
  Button_click(6);
  Button_click(9);
}

void Sakshi()
{
  Serial.println(" SAKSHI ");
  Button_click(Jio_TV);
  Button_click(1);
  Button_click(4);
  Button_click(5);
  Button_click(6);
}

void ABN()
{
  Serial.println(" ABN ");
  Button_click(Jio_TV);
  Button_click(1);
  Button_click(4);
  Button_click(6);
  Button_click(1);
}

void EtvPlus()
{
  Serial.println(" ETV PLUS ");
  Button_click(Jio_TV);
  Button_click(1);
  Button_click(4);
  Button_click(1);
  Button_click(7);
}

void ZCinema()
{
  Serial.println(" ZEE CINEMA ");
  Button_click(Jio_TV);
  Button_click(1);
  Button_click(4);
  Button_click(3);
  Button_click(7);
  delay(2000);
  Button_click(Jio_OK);
}

void Ntv()
{
  Serial.println(" NTV ");
  Button_click(Jio_TV);
  Button_click(1);
  Button_click(4);
  Button_click(6);
  Button_click(0);
}

void tv5()
{
  Serial.println(" TV5 ");
  Button_click(Jio_TV);
  Button_click(1);
  Button_click(4);
  Button_click(5);
  Button_click(8);
}

void StarMaMovies()
{
  Serial.println(" STAR MA MOVIES ");
  Button_click(Jio_TV);
  Button_click(1);
  Button_click(4);
  Button_click(3);
  Button_click(2);
  delay(2000);
  Button_click(Jio_OK);
}


 /******* JIO REMOTE end*/
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


#endif //_74HC595_H
