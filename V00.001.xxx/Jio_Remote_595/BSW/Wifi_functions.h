#ifndef _WIFI_FUNCTIONS_H
#define _WIFI_FUNCTIONS_H

//#define _WIFI_DEBUG

extern void Update_IP_On_Google_Sheet();

#ifndef _WIFI_CONFIG_H

String AP_NameChar = "Rajesh_ESP12F";
String WiFiPassword = "123456789";

String ssid = "RajeshJioFiber";
String password = "Rajesh@1998";
#endif

extern String DATA;

bool Static_IP();
void WIFI_Setup();

String MY_IP = "";
int WIFI_Status = DISCONNECTED;

String Wifi_Pass, Wifi_Name, Hotspot_Name, Hotspot_Pass;

int  Wifi_Name_addr = 350, Wifi_Pass_addr = 370, Hotspot_Name_addr = 390, Hotspot_Pass_addr = 410, OTA_addr = 430 , ESP_Restart_counter_addr = 434;
bool OTA_flag = 0; 

int ESP_Restart_Counter = 0;

void Increment_ESP_Restart_Counter()
{
  ESP_Restart_Counter = EEPROM.read(ESP_Restart_counter_addr);
  ESP_Restart_Counter = ESP_Restart_Counter + 1;
  EEPROM.write(ESP_Restart_counter_addr , ESP_Restart_Counter);
  EEPROM.commit(); 
  delay(50);
}

void Clear_ESP_Restart_Counter()
{
  ESP_Restart_Counter = 0;
  EEPROM.write(ESP_Restart_counter_addr , ESP_Restart_Counter);
  EEPROM.commit();
  delay(50);
}

void No_Static_IP()
{
#if defined(ESP8266)
  WiFi.config(0,0,0);
#endif
}


#ifdef _WIFI_CONFIG_H

bool Static_IP()
{
  bool ok = ENABLE; // Done


  // Set your Static IP address
  //IPAddress local_IP(192, 168, 31, 250);
  IPAddress local_IP;
  local_IP.fromString(STATIC_IP); // from WIFI_CONFIG.h
  // Set your Gateway IP address
  //IPAddress gateway(192, 168, 31, 1);
  IPAddress gateway;
  gateway.fromString(GATEWAY_IP); // from WIFI_CONFIG.h

  IPAddress subnet(255, 255, 0, 0);
  IPAddress primaryDNS(8, 8, 8, 8);    //optional
  IPAddress secondaryDNS(8, 8, 4, 4);  //optional

  // Configures static IP address
  if (!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS)) {
#ifdef _WIFI_DEBUG
    Serial.println("STA Failed to configure");
#endif
    ok = DISABLE; // Not Done
    No_Static_IP();
  }

  return ok;
}

#else  //_WIFI_CONFIG_H

bool Static_IP()
{
  bool ok = ENABLE; //Done
  // Set your Static IP address
  IPAddress local_IP(192, 168, 31, 250);
  // Set your Gateway IP address
  IPAddress gateway(192, 168, 31, 1);

  IPAddress subnet(255, 255, 0, 0);
  IPAddress primaryDNS(8, 8, 8, 8);    //optional
  IPAddress secondaryDNS(8, 8, 4, 4);  //optional

  // Configures static IP address
  if (!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS)) {
#ifdef _WIFI_DEBUG
    Serial.println("STA Failed to configure");
#endif
    ok = DISABLE;
    No_Static_IP();
  }

  return ok;
}


#endif  //_WIFI_CONFIG_H



int writeStringToEEPROM(int addrOffset, String &strToWrite)
{
  byte len = strToWrite.length();
  EEPROM.write(addrOffset, len);

  for (int i = 0; i < len; i++)
  {
    EEPROM.write(addrOffset + 1 + i, strToWrite[i]);
  }
  EEPROM.commit();
  delay(100);
  return addrOffset+ 1 + len;
}

int readStringFromEEPROM(int addrOffset, String *strToRead)
{
  int newStrLen = EEPROM.read(addrOffset);
  char data[newStrLen + 1];

  for (int i = 0; i < newStrLen; i++)
  {
    data[i] = EEPROM.read(addrOffset + 1 + i);
  }
  data[newStrLen] = '\0';  // !!! NOTE !!! Remove the space between the slash "/" and "0" (I've added a space because otherwise there is a display bug)

  *strToRead = String(data);
  delay(100);
  return addrOffset + 1 + newStrLen;
}


void WriteWifiCredentials()
{
  writeStringToEEPROM(Hotspot_Name_addr, AP_NameChar);  // 19 char reserved for
  writeStringToEEPROM(Hotspot_Pass_addr, WiFiPassword);

  writeStringToEEPROM(Wifi_Name_addr, ssid);  // 19 char reserved for
  writeStringToEEPROM(Wifi_Pass_addr, password);
}

void ReadWifiCredentials()
{
  readStringFromEEPROM(Hotspot_Name_addr, &AP_NameChar);  // 19 char reserved for 
  readStringFromEEPROM(Hotspot_Pass_addr, &WiFiPassword);

  readStringFromEEPROM(Wifi_Name_addr, &ssid);  // 19 char reserved for 
  readStringFromEEPROM(Wifi_Pass_addr, &password);
}

void Read_EEPROM_wifi_data(int op)
{
  String read_data;

  if(op == 1)
  {
    readStringFromEEPROM(Hotspot_Name_addr, &read_data);
    DATA = "Writen Data : " + read_data;
  }
  if(op == 2)
  {
    readStringFromEEPROM(Hotspot_Pass_addr, &read_data);
    DATA = "Writen Data : " + read_data;
  }
  if(op == 3)
  {
    readStringFromEEPROM(Wifi_Name_addr, &read_data);
    DATA = "Writen Data : " + read_data;
  }
  if(op == 4)
  {
    readStringFromEEPROM(Wifi_Pass_addr, &read_data);
    DATA = "Writen Data : " + read_data;
  }
}

void Wifi_Hotspot_Write(String data , int op)  // new mit
{
  switch (op) {
    case 1:
#ifdef _WIFI_DEBUG
        Serial.print("WIFI Name from MIT : ");
        Serial.println(data);
#endif
        writeStringToEEPROM(Hotspot_Name_addr, data);
        Read_EEPROM_wifi_data(1);
      break;

    case 2:
#ifdef _WIFI_DEBUG
        Serial.print("WIFI Pass from MIT : ");
        Serial.println(data);
#endif
        writeStringToEEPROM(Hotspot_Pass_addr, data);
        Read_EEPROM_wifi_data(2);
        break;

    case 3:
#ifdef _WIFI_DEBUG
        Serial.print("Hotspot Name from MIT : ");
        Serial.println(data);
#endif
        writeStringToEEPROM(Wifi_Name_addr, data);
        Read_EEPROM_wifi_data(3);
        break;

    case 4:
#ifdef _WIFI_DEBUG
        Serial.print("Hotspot Pass from MIT : ");
        Serial.println(data);
#endif
        writeStringToEEPROM(Wifi_Pass_addr, data);
        Read_EEPROM_wifi_data(4);
        break;

    default:
#ifdef _WIFI_DEBUG
        Serial.print("Invalid option : ");
        Serial.println(op);
#endif
        break;
  }
}


void Set_HostName()
{
#if defined(ESP8266)
    //Set new hostname
  WiFi.hostname(BOARD_NAME.c_str());
#elif defined(ESP32)
  WiFi.setHostname(BOARD_NAME.c_str());
#endif
  //Get Current Hostname
#ifdef _WIFI_DEBUG
  #if defined(ESP8266)
    Serial.printf("New hostname: %s\n", WiFi.hostname().c_str());
  #elif defined(ESP32)
    Serial.printf("New hostname: %s\n", WiFi.getHostname());
  #endif
#endif
}


void Connect_WIFI(String ssid , String password , byte Re_try_count)
{
  Set_HostName();
  delay(100);
#ifdef _WIFI_DEBUG  
   // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
#endif
  WiFi.begin(ssid, password);

     for(byte j = 0 ; j < Re_try_count ; j ++)
     {
       if(WiFi.status() != WL_CONNECTED) 
       {
         delay(500);
#ifdef _WIFI_DEBUG         
         Serial.print(".");
#endif         
         delay(50);
       }
       else
       {
         WIFI_Status = CONNECTED;
#ifdef _WIFI_DEBUG         
         // Print local IP address and start web server
         Serial.println("");
         Serial.println("WiFi connected.");
         Serial.println("IP address: ");
         Serial.println(WiFi.localIP());
#endif         
         MY_IP = WiFi.localIP().toString();
         break;
       }
     }
}

#if defined(ESP32)

void default_hotspot_config_for_esp32()
{
  IPAddress local_ip(192,168,4,1);
  IPAddress gateway(192,168,4,1);
  IPAddress subnet(255,255,255,0);

  WiFi.persistent(false); // avoid flash writes
  WiFi.softAPConfig(local_ip, gateway, subnet);
  delay(500);
}

#endif /*Esp 32 only */

void Set_Hotspot(String hot, String pass) {
  // Set device as a Wi-Fi Station
  
 // WiFi.mode(WIFI_STA);
 // WiFi.disconnect();
#if defined(ESP32)
  default_hotspot_config_for_esp32();
#ifdef _WIFI_DEBUG  
  Serial.println("HOTSPOT config was Done....! ");
#endif  
#endif
  boolean conn = WiFi.softAP(hot, pass);
  delay(500);
#ifdef _WIFI_DEBUG  
  Serial.println("IP address: ");
  Serial.println( WiFi.softAPIP() );
#endif  
  MY_IP = WiFi.softAPIP().toString(); // esp32
}

void wifi_connectedd()
{
  if(WiFi.status() == WL_CONNECTED)
  {
    WIFI_Status = CONNECTED ;
  }
  else
  {
    WIFI_Status = DISCONNECTED ;
  }
}




void Wifi_and_Hotspot_Mode()
{
  Connect_WIFI( ssid , password , 20 );
  wifi_connectedd();
  if( WIFI_Status == CONNECTED )
  {
#ifdef _WIFI_DEBUG    
    Serial.println("WIFI Connected Successfully ");
#endif    
  }
  else
  {
    No_Static_IP();
    Set_Hotspot( AP_NameChar , WiFiPassword );
#ifdef _WIFI_DEBUG    
    Serial.println("HOT_SPOT Created Successfully ");
#endif    
  }
}

void Hotspot_Only_Mode()
{
  delay(500);
#ifdef _WIFI_DEBUG    
    Serial.println("try to create HOT_SPOT ");
    Serial.print("HotSpot_Name: ");
    Serial.println(AP_NameChar);
#endif 
  
    No_Static_IP();

    Set_Hotspot( AP_NameChar , WiFiPassword );
#ifdef _WIFI_DEBUG    
    Serial.println("HOT_SPOT Created Successfully ");
#endif    
}

void Wifi_Only_Mode()
{
  static int wifi_retry_counter = 20 ; // 60 * 10 sec = 10 min's

  Connect_WIFI( ssid , password , 20 );
  wifi_connectedd();
  if( WIFI_Status == CONNECTED )
  {
#ifdef _WIFI_DEBUG    
    Serial.println("WIFI Connected Successfully ");
#endif    
  }
  else
  {
    if(wifi_retry_counter)
    {
      WIFI_Setup();
      wifi_retry_counter-- ;
      delay(10000); // 10 sec
    }
    else
    {
      Hotspot_Only_Mode(); //for safety purpose , it will activate after 200 tries of wifi connect.
    }
  }
}



void print_wifi_details()
{
#ifdef _INO_DEBUG
  Serial.println("\n=== Welcome to ESP Board ===");
  if(OTA_flag)
   Serial.println("\nBOOTING OTA .....!");
 else
   Serial.println("\nBOOTING APPLICATION ....!");
  
  Serial.println("**** SW Versions *****");
  Serial.println(VERSION);

  Serial.print("\nWIFI_HOTSPOT_MODE = ");
  Serial.println(WIFI_HOTSPOT_MODE);

  Serial.print("\nHotspot Name : ");
  Serial.println(AP_NameChar);
  Serial.print("\nHotspot Password : ");
  Serial.println(WiFiPassword);
  Serial.print("\nWifi Name : ");
  Serial.println(ssid);
  Serial.print("\nWifi Password : ");
  Serial.println(password);

  Serial.print("\nIP address: ");
  if(WIFI_Status)
  {
  Serial.println(WiFi.localIP());
  }
  else
  {
   Serial.println(WiFi.softAPIP().toString());
  }
  if (STATIC_IP != "") Serial.println("Static IP Enabled...!");
  else Serial.println("Static IP Disabled...!");

#endif 
}

void wifi_ckeck_delay_update(int delay_sec)
{
  WIFI_CHECK_DELAY_SEC = delay_sec;
  init_timer_delay_sec( WIFI_CHECK_TIMER , WIFI_CHECK_DELAY_SEC );
  activate_timer( WIFI_CHECK_TIMER );
}

void WIFI_Setup() {
  init_timer_delay_sec( WIFI_CHECK_TIMER , WIFI_CHECK_DELAY_SEC ); // 20 min
  activate_timer( WIFI_CHECK_TIMER );

  if (STATIC_IP != "") 
  {
    Static_IP(); 
  } 
  
  if(WIFI_HOTSPOT_MODE == "BOTH")
  {
    Wifi_and_Hotspot_Mode();
  }

  else if(WIFI_HOTSPOT_MODE == "WIFI")
  {
    Wifi_Only_Mode(); 
  }

  else if(WIFI_HOTSPOT_MODE == "HOTSPOT")
  {
    Hotspot_Only_Mode(); // for ESP_NOW
  }

  print_wifi_details();

}



void wifi_check_loop()
{

  if (is_timer_timeout( WIFI_CHECK_TIMER ))   // every 20 min
  {
    if(WIFI_HOTSPOT_MODE != "HOTSPOT")
    {
       wifi_connectedd();
       if (WIFI_Status == DISCONNECTED)  // wifi not connected
       {
         WIFI_Setup();
         wifi_connectedd();
         if (WIFI_Status == CONNECTED) // if wifi reconnected update IP on G sheet
         {
           Update_IP_On_Google_Sheet();
         }
       }
    }
  }
}




#endif  //_WIFI_FUNCTIONS_H
