#ifndef _INO_
#define _INO_

#if defined(ESP32) // ESP12F does't have suffecient RAM so disabled for esp12F
  #define _ADD_LOCAL_DNS
  #define _ADD_WEB_SITE
  #define _ADD_HTTP_URL
#endif

#define _ADD_OTA
//#define _AVAILABLE_RAM_PRINT

//#define _INO_DEBUG
//#define _WIFI_DEBUG
//#define _G_DEBUG
//#define MIT_DEBUG
//#define APPL_DEBUG
//#define _TIMER_DEBUG

//#define _TEST // wifi_config.h

#include "BSW/Header_files.h"

void setup() 
{
  EEPROM.begin(512); 
  OTA_flag = EEPROM.read(OTA_addr);

#ifdef _INO_DEBUG  
  Serial.begin(115200);
#endif //_INO_DEBUG

  //WriteWifiCredentials();
  ReadWifiCredentials();
   
  WIFI_Setup();
  Application_Setup();
  
 if(OTA_flag == ENABLE)
  {
    #ifdef _ADD_OTA
      OTA_Setup();
      wifi_ckeck_delay_update(600); // every 600 sec= 10 MIN , check wifi
    #else
      MIT_APP_Setup();
      wifi_ckeck_delay_update(60); // every 600 sec= 1 MIN , check wifi
    #endif    
  }
 else
  {
    MIT_APP_Setup();
    wifi_ckeck_delay_update(60); // every 600 sec= 1 MIN , check wifi
  }

#ifdef _ADD_LOCAL_DNS  
  local_dns_setup();
#endif  
  delay(100);

  google_sheet_setup();
 // Update_IP_On_Google_Sheet(); // only one time
  G_sheet_send( G_UPDATE_IP );
  
  

#ifdef _ADD_HTTP_URL
  //String responce = http_url("http://sw1.rajeshv.in/info");
  //Serial.println("http://sw1.rajeshv.in/info -> Rsponce");
  //Serial.println(responce);
#endif

Increment_ESP_Restart_Counter();

}



void loop() 
{

  MIT_loop(); /* it will check wifi connected or not in every 20 min */
#ifdef _ADD_LOCAL_DNS
  local_dns_loop();
#endif  
  Timer_loop(); // Millis_Timer.h
  google_sheet_loop();
  
  if(OTA_flag == ENABLE)
  {
    #ifdef _ADD_OTA
      OTA_loop();
    #else
     Application_loop();
    #endif   
  }
  else
  {
    Application_loop();
  } 

#ifdef _AVAILABLE_RAM_PRINT
  Serial.print("Free heap: ");
  Serial.println(ESP.getFreeHeap());  // bytes of free RAM for esp12f FREE Heap should be more than 3500 (3.5 kb)
  delay(2000);
#endif
}



#endif //_INO_
