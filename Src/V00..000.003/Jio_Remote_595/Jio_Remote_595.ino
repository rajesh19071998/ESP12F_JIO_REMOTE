#ifndef _JIO_REMOTE_INO
#define _JIO_REMOTE_INO

#define NEW_IDE
//#define OLD_IDE

#if defined OLD_IDE // Arduino IDE version 1.xx
  #include "OTA_V4.h"
#elif defined NEW_IDE  // Arduino IDE version 2.xx
  #include "OTA_V5.h"
#endif

#include "PIN_CONFIG.h"

#include "74HC595.h" // for Jio Remote control
#include "MI_TV_Remote.h"
#include "Tata_Sky_Remote.h"
#include "MIT_APP.h" //please include at last


const String jio_remote_ver = "JIO_REMOTE : V00.000.003";
#if defined OLD_IDE // Arduino IDE version 1.xx
  const String VER[] = {jio_remote_ver, mit_app_ver, mi_remote_ver, ota_v4_ver, tatasky_remote_ver, wifi_conf_ver};
#elif defined NEW_IDE  // Arduino IDE version 2.xx
  const String VER[] = {jio_remote_ver, mit_app_ver, mi_remote_ver, ota_v5_ver, tatasky_remote_ver, wifi_conf_ver};
#endif

int JIO_REMOTE_ON_OFF_PIN_addr = 1; //EEPROM
int JIO_REMOTE_ON_OFF_PIN_state = 0; //OFF

void Application_loop();

void JioRemote_OnOff(int OnOff)
{
  if(OnOff) //ON
  {
    JIO_REMOTE_ON_OFF_PIN_state = 1;

  }
  else //OFF
  {
    JIO_REMOTE_ON_OFF_PIN_state = 0;

  }

  EEPROM.write(JIO_REMOTE_ON_OFF_PIN_addr, JIO_REMOTE_ON_OFF_PIN_state);
  EEPROM.commit();
  delay(100);
  digitalWrite(JIO_REMOTE_ON_OFF_PIN, JIO_REMOTE_ON_OFF_PIN_state); // Remote in OFF State
}


void setup() {
 Serial.begin(115200);
 EEPROM.begin(512); 

 pinMode(JIO_REMOTE_ON_OFF_PIN, OUTPUT);

 JIO_REMOTE_ON_OFF_PIN_state = EEPROM.read(JIO_REMOTE_ON_OFF_PIN_addr);
 digitalWrite(JIO_REMOTE_ON_OFF_PIN, JIO_REMOTE_ON_OFF_PIN_state); // Remote in OFF State

 delay(5000);
 Serial.println("**** SW Versions *****");
 for(byte i = 0 ; i < 6 ; i ++)
    Serial.println(VER[i]);
 
  //WriteWifiCredentials();
 
  ReadWifiCredentials(); 
 
  Serial.println(AP_NameChar);
  Serial.println(WiFiPassword);
  Serial.println(ssid);
  Serial.println(password);
 
  OTA_flag = EEPROM.read(OTA_addr);
 
 if(OTA_flag)
  {
  OTA_Setup();
  }
 else
  {
    No_click();
    delay(3000);

   // WIFI_Setup();
    MIT_APP_Setup();
    MI_TV_setup();
    TataSky_Remote_Setup();
    delay(9000);
    MITV_Power_ON_OFF();

    delay(22000);
    Button_click( Jio_OK );
    delay(1000);
    Etv();

    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    
  }
  
}



void loop() {
 unsigned long currentMillis = millis();
  
  if(OTA_flag)
  {
    OTA_loop();
  }
  else
  {
   MIT_Main_code();
   //wifi_check_loop(); // every 20 min
   TataSky_Remote_loop();
   Application_loop();
  } 

}

void Application_loop()
{
  if(results.value == RED)
  {
    Etv();
    results.value = 0;
  }
  else if(results.value == GREEN)
  {
    EtvPlus();
    results.value = 0;
  }
  else if(results.value == YELLOW)
  {
    EtvCinema();
    results.value = 0;
  }
  else if(results.value == BLUE)
  {
    GeminiComedy();
    results.value = 0;
  }
  else if(results.value == ONE)
  {
    tv9();
    results.value = 0;
  }
  else if(results.value == TWO)
  {
    Sakshi();   
    results.value = 0;
  }
  else if(results.value == THREE)
  {
    Ntv();
    results.value = 0;
  }
  else if(results.value == FOUR)
  {
    tv5();
    results.value = 0;
  }
  else if(results.value == FIVE)
  {
    ABN();
    results.value = 0;
  }
  else if(results.value == SIX)
  {
    GeminiMovies();
    results.value = 0;
  }
  else if(results.value == SEVEN)
  {
    ZCinema();
    results.value = 0;
  }
  else if(results.value == EIGHT)
  {
    StarMaMovies();
    results.value = 0;
  }
  else if(results.value == NINE)
  {
    ZTelugu();
    results.value = 0;
  }
  else if(results.value == ZERO)
  {
    Gemini();
    results.value = 0;
  }

  else if(results.value == VOL_PLUS)
  {
    Button_click(Jio_Vol_Up);
    results.value = 0;
  }
  else if(results.value == VOL_MINUS)
  {
    Button_click(Jio_Vol_Down);
    results.value = 0;
  }

  #if 1 // Jio remote functions

  else if(results.value == OK)
  {
    Button_click( Jio_OK );
    results.value = 0;
  }
  else if(results.value == UP)
  {
    Button_click( Jio_UP );
    results.value = 0;
  }
  else if(results.value == DOWN)
  {
    Button_click( Jio_DOWN );
    results.value = 0;
  }
  else if(results.value == LEFT)
  {
    Button_click( Jio_Left );
    results.value = 0;
  }
  else if(results.value == RIGTH)
  {
    Button_click( Jio_Right );
    results.value = 0;
  }
  else if(results.value == TV)
  {
    Button_click( Jio_TV );
    results.value = 0;
  }
  else if(results.value == HOME)
  {
    Button_click( Jio_HOME );
    results.value = 0;
  }
  else if(results.value == BACK)
  {
    Button_click( Jio_BACK );
    results.value = 0;
  }

  else if(results.value == POWER)
  {
    if(JIO_REMOTE_ON_OFF_PIN_state)
     {
       JioRemote_OnOff(0);
     }
     else
     {
       JioRemote_OnOff(1);
     }
    
    results.value = 0;
  }


  #endif // Jio remote functions
  


}


#endif //_JIO_REMOTE_INO
