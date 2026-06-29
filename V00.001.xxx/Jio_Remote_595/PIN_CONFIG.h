#ifndef _PIN_CONFIG_H
#define _PIN_CONFIG_H


#define ASW_TIMERS 1  // from Appl_Header_files.h
/* max timers */
#define MAX_TIMERS BSW_TIMERS + ASW_TIMERS   // minimum is 4 // BSW is using 0,1,2,3 timers

#if defined(ESP8266)  
  #define DATA_PIN D1  // 5
  #define CLK_PIN D3   // 0
  #define LATCH_PIN D4 // 2

  #define IR_LED_PIN D2 //4 
  #define IR_RECEIVE_PIN D5 //14
  #define JIO_REMOTE_ON_OFF_PIN D7 //13

  #define TV_SWITCH D6 //12

#endif

#if defined(ESP32)  
  #define DATA_PIN    4  // 5
  #define CLK_PIN    13   // 0
  #define LATCH_PIN  18 // 2

  #define IR_LED_PIN 19 //4 
  #define IR_RECEIVE_PIN 23 //14
  #define JIO_REMOTE_ON_OFF_PIN 25 //13

  #define TV_SWITCH 26 //12

#endif

#if 0
4 , 13, 18, 19, 23, 25, 26, 27, 32, 33 -> 10
UART 2 = 16,17                         -> 2
I2C    = 21, 22                        -> 2
INPUT Only Pins    34, 35 , 36 , 39    -> 4

~ ADC at boot pins   5 , 14, 15        -> 3 OK but at boot it will give PWM


~ Emitts PWM signals at boot

#define GPIO0 0 boot pin ( OUT OK ) Unsafe
#define GPIO1 1 TX pin ( OUT OK ) Unsafe
#define GPIO2 2  leave float. Unsafe
#define GPIO3 3 RX pin ( IN OK ) Unsafe

#define GPIO4   4 OK safe       ADC
#define GPIO5   5 OK safe     ~
#define GPIO12 12 (OUT Only)  ~ ADC
#define GPIO13 13 OK safe       ADC
#define GPIO14 14 OK safe     ~ ADC
#define GPIO15 15 OK safe     ~ ADC
#define GPIO16 16 OK safe    UART2 RX
#define GPIO17 17 OK safe    UART2 TX 
#define GPIO18 18 OK safe 
#define GPIO19 19 OK safe

#define GPIO21 21 OK safe  SDA 
#define GPIO22 22 OK safe  SCL 
#define GPIO23 23 OK safe

#define GPIO25 25 OK safe  ADC DAC
#define GPIO26 26 OK safe  ADC DAC
#define GPIO27 27 OK safe  ADC

#define GPIO32 32 OK safe  ADC
#define GPIO33 33 OK safe  ADC

/* INPUT Only*/

#define GPIO34 34 Input Only ADC
#define GPIO35 35 Input Only ADC
#define GPIO36 36 Input Only ADC
#define GPIO39 39 Input Only ADC

#endif //(ESP8266)

/*********************************************  ESP12F PINS *************************************************************************/
#if 0
/*
INPUT / OUTPUT PINS = 5
OUTPUT PINS         = 3
                    = 8 PINS
*/
#define ESP_D0 D0 // 16 HIGH at BOOT (No interuppts) (WAKUP PIN) Mostly don't use
#define ESP_D1 D1 // 5   SCL (INPUT / OUTPUT) (I2C) Safe
#define ESP_D2 D2 // 4   SDA (INPUT / OUTPUT) (I2C) Safe
#define ESP_D3 D3 // 0  OUTPUT only (BOOT fails if pulled Input LOW)
#define ESP_D4 D4 // 2  OUTPUT only (BOOT fails if pulled Input LOW) (ESP BOARD LED)
#define ESP_D5 D5 // 14 CLK  (INPUT / OUTPUT) (SPI) Safe
#define ESP_D6 D6 // 12 MISO (INPUT / OUTPUT) (SPI) Safe
#define ESP_D7 D7 // 13 MOSI (INPUT / OUTPUT) (SPI) Safe
#define ESP_D8 D8 // 15 CS  OUTPUT only (BOOT fails if pulled HIGH ) (SPI chip select)

#define ESP_RX 3  // don't use this pin (HIGH at BOOT)
#define ESP_TX 1  // don't use this pin (HIGH at BOOT)

#endif
/**************************************************************************************************************************/

#endif //_PIN_CONFIG_H