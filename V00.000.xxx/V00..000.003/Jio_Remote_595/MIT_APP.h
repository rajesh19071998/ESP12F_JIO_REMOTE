#ifndef _MIT_APP_H
#define _MIT_APP_H
const String mit_app_ver = "MIT_APP : V00.000.001";
/*
#ifndef _ESP8266_WIFI_H
  #define _ESP8266_WIFI_H
  #include <ESP8266WiFi.h>
#endif //_ESP8266_WIFI_H
#ifndef _ESPASYNC_WEB_SERVER_H
  #define _ESPASYNC_WEB_SERVER_H  
  #include <ESPAsyncWebServer.h>
#endif //_ESPASYNC_WEB_SERVER_H
*/
#include "Wifi_functions.h"

WiFiServer MIT_server(80);
/******** .INO file functions *********************************/

extern void JioRemote_OnOff(int OnOff); 

/*************************************************************/
//static int DEBUG = 1;

String header = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
String request = "";

 String MIT_INFO_DATA =" Hi MIT APP USER!\n This is JIO_Remote (ESP Board No 2).\nPlease Enter\n For Local -> http://192.168.31.250/update  \n OR \n For Global -> https://remote.rajeshv.in/update \nTo update Firmware.";
 /* Hotspot IP : http://192.168.4.1 */
 String DATA;
 char DATA_1[20];
 int MIT_flag = 0;

void MIT_APP_Setup()
{
  WIFI_Setup();
  MIT_server.begin();
}


void Appliction_MIT_APP_Process()
{
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

    else if(request.indexOf("JIO_REMOTE_ON") > 0 )  { Serial.println(request); JioRemote_OnOff(1);}
    else if(request.indexOf("JIO_REMOTE_OFF") > 0 )  { Serial.println(request); JioRemote_OnOff(0);}

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


}

void Common_MIT_APP_Process()
{
  if ( request.indexOf("OTA") > 0 )  
     {
       OTA_flag?OTA_flag = 0:OTA_flag = 1;
   
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
    
}

void MIT_Main_code()
{
  // Check if a client has connected
    WiFiClient MIT_client = MIT_server.available();
     if (!MIT_client)  {  goto L;  }
 
    // Read the first line of the request
    request = MIT_client.readStringUntil('\r');
    
    MIT_flag = 0;
    
    Appliction_MIT_APP_Process();
    Common_MIT_APP_Process();


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
    wifi_check_loop(); // every 20 min
}







#endif //_MIT_APP_H
