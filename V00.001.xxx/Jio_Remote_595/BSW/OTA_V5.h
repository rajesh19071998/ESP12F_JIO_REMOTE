/*
  -----------------------
  ElegantOTA - Demo Example
  -----------------------
 
  Skill Level: Beginner
 
  This example provides with a bare minimal app with ElegantOTA functionality.
 
  Github: https://github.com/ayushsharma82/ElegantOTA
  WiKi: https://docs.elegantota.pro
 
  Works with both ESP8266 & ESP32
 
  -------------------------------
 
  Upgrade to ElegantOTA Pro: https://elegantota.pro
 
*/
 #ifndef _OTA_H
 #define _OTA_H

//#define _OTA_DEBUG

extern String Hotspot_IP;
String OTA_info = ""; 

#if defined(ESP8266)
  ESP8266WebServer OTA_server(80);
#elif defined(ESP32)
  WebServer OTA_server(80);
#endif

unsigned long ota_progress_millis = 0;

void create_info()
{
  String MYIP = "http://"+ MY_IP;
  
  OTA_info = " Hi OTA vertion 5 User\nBOARD Details mentioned below\nBoard_Name : "+BOARD_NAME +"\nBoard_Number : "+BOARD_NUMBER +"\nTo Update Board Firmware\nBoard_Local_IP : "+MYIP+"/update"+"\nBoard Local DNS : "+"http://"+Local_DNS_Name+".local"+"\nBoard_Global_IP : "+Global_IP+"/update"; //+"\nHotspot_IP : "+Hotspot_IP+"/update" ;

}

void Disable_OTA()
{
    OTA_flag = 0;
#ifdef _OTA_DEBUG    
    Serial.println("OTA_loop_TIME OUT give control to Application");
#endif    
    EEPROM.write(OTA_addr, OTA_flag);
    EEPROM.commit();
    delay(5000);
    ESP.restart();
}


void onOTAStart() {
  // Log when OTA has started
#ifdef _OTA_DEBUG
  Serial.println("OTA update started!");
#endif  
  // <Add your own code here>
}

void onOTAProgress(size_t current, size_t final) {
  // Log every 1 second
  if (millis() - ota_progress_millis > 1000) {
    ota_progress_millis = millis();
#ifdef _OTA_DEBUG    
    Serial.printf("OTA Progress Current: %u bytes, Final: %u bytes\n", current, final);
#endif    
  }
}

void onOTAEnd(bool success) {
  // Log when OTA has finished
  if (success) {
#ifdef _OTA_DEBUG    
    Serial.println("OTA update finished successfully!");
#endif    
    Disable_OTA();
  } else {
#ifdef _OTA_DEBUG    
    Serial.println("There was an error during OTA update!");
#endif    
  }
  // <Add your own code here>
}



void OTA_Setup(void) {
 
   init_timer_delay_sec(OTA_TIMER , OTA_DELAY_SEC ); /*600 sec = 10 min*/
   OTA_server.on("/", []() {
    create_info();
    OTA_server.send(200, "text/plain",OTA_info.c_str());
  });

  OTA_server.on("/OTA_OFF", []() {

    OTA_server.send(200, "text/plain", "OTA was Diasabled....!");
    Disable_OTA();
  });

  ElegantOTA.begin(&OTA_server);    // Start ElegantOTA

  // ElegantOTA callbacks
  ElegantOTA.onStart(onOTAStart);
  ElegantOTA.onProgress(onOTAProgress);
  ElegantOTA.onEnd(onOTAEnd);

  OTA_server.begin();
#ifdef _OTA_DEBUG  
  Serial.println("HTTP OTA_server started");
#endif  
activate_timer(OTA_TIMER);
}


void OTA_loop()
{
  OTA_server.handleClient();
  ElegantOTA.loop();

  if (is_timer_timeout( OTA_TIMER )) 
  {
    deactivate_timer( OTA_TIMER );
    Disable_OTA();
  }
}



#endif //_OTA_H
