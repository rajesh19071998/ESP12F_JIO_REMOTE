#define NEW_IDE
//#define OLD_IDE

#if defined OLD_IDE // Arduino IDE version 1.xx
  #include "OTA_V4.h"
#elif defined NEW_IDE  // Arduino IDE version 2.xx
  #include "OTA_V5.h"
#endif

#include "74HC595.h" // for Jio Remote control
#include "MI_TV_Remote.h"
#include "Tata_Sky_Remote.h"

#define DEBUG 1

const String jio_remote_ver = "JIO_REMOTE : V00.000.001";

const String VER[] = {jio_remote_ver, mi_remote_ver, /* ota_v4_ver, */ tatasky_remote_ver, ota_v5_ver, wifi_conf_ver};

WiFiServer MIT_server(80);
//we are not using this html
String header = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
String request = "";

void Application_loop();


void MIT_APP_Setup()
{
  MIT_server.begin();
}

void setup() {
 Serial.begin(115200);
 EEPROM.begin(512); 
 
 delay(5000);
 Serial.println("Rajesh Remote");
 
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

    WIFI_Setup();
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


void MIT_Main_code()
{
  // Check if a client has connected
    WiFiClient MIT_client = MIT_server.available();
     if (!MIT_client)  {  goto L;  }
 
    // Read the first line of the request
    request = MIT_client.readStringUntil('\r');
    
    MIT_flag = 0;
    
         if(request.indexOf("ETV") > 0 )  { Serial.println(request); Etv(); }
    else if(request.indexOf("TV9") > 0 )  { Serial.println(request); tv9(); }
    else if(request.indexOf("GEMINI_MOVIES") > 0 )  { Serial.println(request); GeminiMovies(); }
    else if(request.indexOf("GEMINI") > 0 )  { Serial.println(request); Gemini(); }
    else if(request.indexOf("GEMINI_COMEDY") > 0 )  { Serial.println(request); GeminiComedy(); }
    else if(request.indexOf("ZEE_TELUGU") > 0 )  { Serial.println(request); ZTelugu(); }
    else if(request.indexOf("ETV_CINEMA") > 0 )  { Serial.println(request); EtvCinema(); }
    else if(request.indexOf("SAKSHI") > 0 )  { Serial.println(request); Sakshi(); }
    else if(request.indexOf("ABN") > 0 )  { Serial.println(request); ABN(); }
    else if(request.indexOf("ETV_PLUS") > 0 )  { Serial.println(request); EtvPlus(); }
    else if(request.indexOf("ZEE_CINEMA") > 0 )  { Serial.println(request); ZCinema(); }
    else if(request.indexOf("NTV") > 0 )  { Serial.println(request); Ntv(); }
    else if(request.indexOf("TV5") > 0 )  { Serial.println(request); tv5(); }
    else if(request.indexOf("STAR_MOVIES") > 0 )  { Serial.println(request); StarMaMovies(); }
    
    else if(request.indexOf("JIO_UP") > 0 )  { Serial.println(request); Button_click( Jio_UP ); }
    else if(request.indexOf("JIO_DOWN") > 0 )  { Serial.println(request); Button_click( Jio_DOWN );}
    else if(request.indexOf("JIO_RIGHT") > 0 )  { Serial.println(request); Button_click( Jio_Right );}
    else if(request.indexOf("JIO_LEFT") > 0 )  { Serial.println(request); Button_click( Jio_Left );}
    else if(request.indexOf("JIO_BACK") > 0 )  { Serial.println(request); Button_click( Jio_BACK );}
    else if(request.indexOf("JIO_OK") > 0 )  { Serial.println(request); Button_click( Jio_OK );}
    else if(request.indexOf("JIO_HOME") > 0 )  { Serial.println(request); Button_click( Jio_HOME );}
    else if(request.indexOf("JIO_TV") > 0 )  { Serial.println(request); Button_click( Jio_TV );}
    else if(request.indexOf("JIO_VOL_UP") > 0 )  { Serial.println(request); Button_click( Jio_Vol_Up );}
    else if(request.indexOf("JIO_VOL_DOWN") > 0 )  { Serial.println(request); Button_click( Jio_Vol_Down );}

    else if(request.indexOf("MI_POWER") > 0 )  { Serial.println(request); MITV_Power_ON_OFF(); }
    else if(request.indexOf("MI_UP") > 0 )  { Serial.println(request); MI_UP();}
    else if(request.indexOf("MI_DOWN") > 0 )  { Serial.println(request); MI_DOWN();}
    else if(request.indexOf("MI_RIGHT") > 0 )  { Serial.println(request); MI_RIGHT();}
    else if(request.indexOf("MI_LEFT") > 0 )  { Serial.println(request); MI_LEFT();}
    else if(request.indexOf("MI_BACK") > 0 )  { Serial.println(request); MI_BACK();}
    else if(request.indexOf("MI_OK") > 0 )  { Serial.println(request); MI_OK();}
    else if(request.indexOf("MI_HOME") > 0 )  { Serial.println(request); MI_HOME();}
    else if(request.indexOf("MI_VOL_UP") > 0 )  { Serial.println(request); MI_VOL_UP();}
    else if(request.indexOf("MI_VOL_DOWN") > 0 )  { Serial.println(request); MI_VOL_DOWN();}

    else if(request.indexOf("MI_JIO_HDMI") > 0 )  { Serial.println(request); MITV_HDMI_Input_TATASKY_Selection(); }
    else if(request.indexOf("MI_PC_HDMI") > 0 )  { Serial.println(request);  MITV_HDMI_Input_PC_Selection(); }
    else if(request.indexOf("MI_CCTV_HDMI") > 0 )  { Serial.println(request); MITV_HDMI_Input_CCTV_Selection(); }


    /*
    else if(request.indexOf("") > 0 )  { Serial.println(request); }
    else if(request.indexOf("") > 0 )  { Serial.println(request); }
    */






    else if ( request.indexOf("OTA") > 0 )  {OTA_flag?OTA_flag = 0:OTA_flag = 1;
   
            EEPROM.write(OTA_addr, OTA_flag);
            EEPROM.commit();
            delay(5000);
            ESP.restart();
   }
    else if  ( request.indexOf("WNQ") > 0 ) { MIT_flag = 1; Serial.println(request);sprintf(DATA_1, "%s%s","WNA ",AP_NameChar.c_str());}
    else if  ( request.indexOf("WPQ") > 0 ) { MIT_flag = 1; Serial.println(request);sprintf(DATA_1, "%s%s","WPA ",WiFiPassword.c_str()); }
    else if  ( request.indexOf("HNQ") > 0 ) { MIT_flag = 1; Serial.println(request);sprintf(DATA_1, "%s%s","HNA ",ssid.c_str()); }
    else if  ( request.indexOf("HPQ") > 0 ) { MIT_flag = 1; Serial.println(request);sprintf(DATA_1, "%s%s","HPA ",password.c_str()); }
    else if  ( request.indexOf("STA") > 0 ) { MIT_flag = 3;Serial.println(request); /*Last_OTA_Status(); */}
    
    else if  ( request.indexOf("WN") > 0 ) { MIT_flag = 2;if(DEBUG) Serial.println(request); Wifi_update(request,1); }
    else if  ( request.indexOf("WP") > 0 ) { MIT_flag = 2;if(DEBUG) Serial.println(request); Wifi_update(request,2); }
    else if  ( request.indexOf("HN") > 0 ) { MIT_flag = 2;if(DEBUG) Serial.println(request); Wifi_update(request,3); }
    else if  ( request.indexOf("HP") > 0 ) { MIT_flag = 2;if(DEBUG) Serial.println(request); Wifi_update(request,4); }
    else if  ( request.indexOf("WIFIUPDATE") > 0 ) { MIT_flag = 2;if(DEBUG) Serial.println(request); ReadWifiCredentials(); }
    else if  ( request.indexOf("RST") > 0 ) { MIT_flag = 2;if(DEBUG) Serial.println(request);delay(5000);ESP.restart(); }
    
    else if  ( request == "GET / HTTP/1.1" ) { MIT_flag = 4; Serial.println(request);} // For INFO
    
    MIT_client.flush();
   
    MIT_client.print( header );
    //MIT_client.print(" "); // put data to send mobile

    if (MIT_flag == 1)
    {
     MIT_client.print(DATA_1);
     Serial.println(DATA_1);
    }
    else if(MIT_flag == 3)
    {
     MIT_client.print(DATA);
     Serial.println(DATA); 
    }
    else if(MIT_flag == 4)
    {
      MIT_client.print(MIT_INFO_DATA);
     Serial.println(MIT_INFO_DATA);
    }
 
    L:
    delay(5);
  
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
   wifi_check_loop(); // every 20 min
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


  #endif // Jio remote functions
  


}
