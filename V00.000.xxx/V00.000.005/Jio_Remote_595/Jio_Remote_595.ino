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

#include "google_sheet.h"


const String jio_remote_ver = "JIO_REMOTE : V00.000.005";
#if defined OLD_IDE // Arduino IDE version 1.xx
  const String VER[] = {jio_remote_ver, mit_app_ver, mi_remote_ver, ota_v4_ver, tatasky_remote_ver, wifi_conf_ver};
#elif defined NEW_IDE  // Arduino IDE version 2.xx
  const String VER[] = {jio_remote_ver, mit_app_ver, mi_remote_ver, ota_v5_ver, tatasky_remote_ver, wifi_conf_ver};
#endif

int JIO_REMOTE_ON_OFF_PIN_addr = 1; //EEPROM
int JIO_REMOTE_ON_OFF_PIN_state = 0; //OFF

String Channel = "ETV";

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

 delay(1000);
 Serial.println("**** SW Versions *****");
 for(byte i = 0 ; i < 6 ; i ++)
    Serial.println(VER[i]);
 
 // WriteWifiCredentials();
 
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
    delay(100);

   // WIFI_Setup();
    MIT_APP_Setup();
    MI_TV_setup();
    TataSky_Remote_Setup();

  //  delay(10000);
    MITV_Power_ON_OFF();

    delay(15000);
    Button_click( Jio_OK );
    Button_click( Jio_HOME );
    delay(15000);
    Button_click( Jio_OK );
    Button_click( Jio_HOME );
    delay(23000);
    Button_click( Jio_OK );
    Button_click( Jio_HOME );
    
    delay(1000);
    Button_click( Jio_TV );
    delay(4000);
    Etv();
    delay(10000);
    Etv();
    
  //pair_remote();

    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    
  }

  google_sheet_setup();
}



void Update_IP_On_Google_Sheet()
{
  static int OneCall = 0; // it will execute one time in RST or power cycle
  if(OneCall == 0)
  {
    
    String MY_IP = WiFi.localIP().toString();
    // String G_Data = "Action=AddESP&ESPName=" + BOARD_NAME + "&ESPNum=" + BOARD_NUMBER + "&ESPIP=" + WiFi.localIP().toString();
    String G_Data = "Action=AddESP&ESPName=" + BOARD_NAME + "&ESPNum=" + BOARD_NUMBER + "&ESPIP=" + MY_IP;
    sendDataToGoogleSheet(G_Data);
    OneCall = 1;
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
   TataSky_Remote_loop();
   Application_loop();
  } 

  Update_IP_On_Google_Sheet();

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
    EtvCinema(); //not
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
    Fast_Button_click(Jio_Vol_Up);
    results.value = 0;
  }
  else if(results.value == VOL_MINUS)
  {
    Fast_Button_click(Jio_Vol_Down);
    results.value = 0;
  }



  else if(results.value == OK)
  {
    Fast_Button_click( Jio_OK );
    results.value = 0;
  }
  else if(results.value == UP)
  {
    Fast_Button_click( Jio_UP );
    results.value = 0;
  }
  else if(results.value == DOWN)
  {
    Fast_Button_click( Jio_DOWN );
    results.value = 0;
  }
  else if(results.value == LEFT)
  {
    Fast_Button_click( Jio_Left );
    results.value = 0;
  }
  else if(results.value == RIGTH)
  {
    Fast_Button_click( Jio_Right );
    results.value = 0;
  }
  else if(results.value == TV)
  {
    Fast_Button_click( Jio_TV );
    results.value = 0;
  }
  else if(results.value == HOME)
  {
    Fast_Button_click( Jio_HOME );
    results.value = 0;
  }
  else if(results.value == BACK)
  {
    Fast_Button_click( Jio_BACK );
    results.value = 0;
  }
  else if(results.value == i_button)
  {
    pair_remote();
    results.value = 0;
  }

  else if(results.value == POWER)
  {
    if(JIO_REMOTE_ON_OFF_PIN_state)
     {
      Serial.println("JIO_Remote OFF");
       JioRemote_OnOff(0);
     }
     else
     {
      Serial.println("JIO_Remote_ON");
       JioRemote_OnOff(1);
     }
    
    results.value = 0;
  }


  

}


#endif //_JIO_REMOTE_INO
