#ifndef _TATA_SKY_REMOTE_H
#define _TATA_SKY_REMOTE_H

const String tatasky_remote_ver = "TATASKY_REMOTE : V00.000.001";

//#define RECV_PIN 14 //D5

#ifndef _ARDUINO_H
  #define _ARDUINO_H
  #include <Arduino.h>
#endif //_ARDUINO_H
#ifndef _IR_REMOTE_ESP8266_H
  #define _IR_REMOTE_ESP8266_H
  #include <IRremoteESP8266.h>
#endif //_IR_REMOTE_ESP8266_H
#ifndef _IR_RECV_H
  #define _IR_RECV_H
  #include <IRrecv.h>
#endif //_IR_RECV_H
#ifndef _IR_UTILS_H
  #define _IR_UTILS_H
  #include <IRutils.h>
#endif  //_IR_UTILS_H

//int IR_RECEIVE_PIN = 14;

IRrecv irrecv(IR_RECEIVE_PIN); //RECV_PIN
decode_results results;

#define ZERO  0xC00000
#define ONE   0xC00001
#define TWO   0xC00002
#define THREE 0xC00003
#define FOUR  0xC00004
#define FIVE  0xC00005
#define SIX   0xC00006
#define SEVEN 0xC00007
#define EIGHT 0xC00008
#define NINE  0xC00009

#define RED       0xC0006D
#define GREEN     0xC0006E
#define YELLOW    0xC0006F
#define BLUE      0xC00070
#define HOME      0xC00084
#define BACK      0xC00083
#define VOL_PLUS  0xC00010
#define VOL_MINUS 0xC00011
#define POWER     0xC0000C
#define OK        0xC0005C
#define UP        0xC00058
#define DOWN      0xC00059
#define LEFT      0xC0005A
#define RIGTH     0xC0005B
#define TV        0xC00080
#define FAV       0xC0003C



void TataSky_Remote_Setup()
{
  irrecv.enableIRIn();
}

void TataSky_Remote_loop()
{

 if(irrecv.decode(&results))
  { 
   irrecv.resume();
   serialPrintUint64(results.value, HEX);
   Serial.println("");
  }
  delay(1000);
}




#endif //_TATA_SKY_REMOTE_H
