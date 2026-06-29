#ifndef _WIFI_CONFIG_H
#define _WIFI_CONFIG_H

#if defined(ESP8266)
  const String BOARD_NUMBER = "1";
  const String BOARD_NAME = "JIO_REMOTE";
  const String Local_DNS_Name = ""; // Disabled
  String  AP_NameChar = "JioRemote" ;
  const String MODULE_TYPE = "ESP12F" ;

#elif defined(ESP32)
  const String BOARD_NUMBER = "100";
  const String BOARD_NAME = "ESP32_BASIC";
  const String Local_DNS_Name = "esp32";
  String  AP_NameChar = "ESP32_BASIC" ;
  const String MODULE_TYPE = "ESP32" ;
#endif

String WiFiPassword = "123456789";

String     ssid = "RajeshJioFiber";
const String WIFI_HOTSPOT_MODE = "BOTH"; // WIFI / HOTSPOT / BOTH 


#if defined _TEST
String password = "Rajesh@1998";
String Global_IP = "https://basic.rajeshv.in";
const String STATIC_IP = "";
const String GATEWAY_IP = "";

#else

String password = "Rajesh@1234";
String Global_IP = "https://remote.rajeshv.in";

const String STATIC_IP = "192.168.31.143";
const String GATEWAY_IP = "192.168.31.1";

#endif



#endif //_WIFI_CONFIG_H
