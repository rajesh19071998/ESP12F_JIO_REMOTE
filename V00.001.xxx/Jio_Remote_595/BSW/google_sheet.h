#ifndef _GOOGLE_SHEETS_H
#define _GOOGLE_SHEETS_H

//https://script.google.com/macros/s/AKfycbzc0LEbZWeHH9As_Y2SULaFRaoMF0Oi35Hdi9cvN4cqZBNy8o8a6l7koztRl4dDDGyTBA/exec?Action=AddESP&ESPName=Rajesh_ESP&ESPNum=55&ESPIP=192.168.31.100

extern String APPL_VER; // from .ino
extern String SW_Compiled_Date; // from .ino
String G_data = "";

#define G_UPDATE_IP 0
#define G_UPDATE_LOGOUT 1

int G_UPDATE_SELECT = 0;
byte G_UPDATE_FLAG = 255; //invalid

//#define _G_DEBUG
 
String IP_Sheet = "AKfycbzc0LEbZWeHH9As_Y2SULaFRaoMF0Oi35Hdi9cvN4cqZBNy8o8a6l7koztRl4dDDGyTBA"; //--> spreadsheet Insert your script ID

//----------------------------------------Host & httpsPort don't edit
const char* host = "script.google.com";
const int httpsPort = 443;
//----------------------------------------
 
WiFiClientSecure client; //--> Create a WiFiClientSecure object.
  
void sendDataToGoogleSheet();

String Formate_date(String inputDate)
{
  char final_date[20] = {'\n'};
  String formattedDate = "";

  for(int i = 0; inputDate[i]; i++)
  {
    if(inputDate[i] == ' ')
    {
      final_date[i] = '-';
    }
    else
    {
      final_date[i] = inputDate[i];
    }
  }
   formattedDate = String(final_date);
  #ifdef _G_DEBUG 
    Serial.println("Original: " + inputDate);
    Serial.println("Formatted: " + formattedDate);
  #endif
  return formattedDate;
}


void Update_LogOutTime_On_Google_Sheet()
{
  // https://script.google.com/macros/s/AKfycbzc0LEbZWeHH9As_Y2SULaFRaoMF0Oi35Hdi9cvN4cqZBNy8o8a6l7koztRl4dDDGyTBA/exec?Action=LogOutESP&ESPName=JIO_REMOTE&ESPNum=1

  G_data = "Action=LogOutESP&ESPName=" + BOARD_NAME + "&ESPNum="+BOARD_NUMBER ;
#ifdef _G_DEBUG  
   Serial.println("G log Out called");
#endif    
}


void Update_IP_On_Google_Sheet()
{
    //https://script.google.com/macros/s/AKfycbzc0LEbZWeHH9As_Y2SULaFRaoMF0Oi35Hdi9cvN4cqZBNy8o8a6l7koztRl4dDDGyTBA/exec?Action=AddESP&ESPName=Rajesh_ESP&ESPNum=55&ESPIP=192.168.31.100&ESP_G_IP=http://sw1.rajeshv.in&ESP_TYPE=ESP12F&ESP_APPL_V=V00.000.005&ESP_BSW_V=V00.003.010&SW_DATE=13-02-2026&ESP_DNS=http://esp12f.local

   // String G_Data = "Action=AddESP&ESPName="+BOARD_NAME +"&ESPNum="+BOARD_NUMBER+"&ESPIP="+MY_IP+"&ESP_G_IP="+Global_IP+"&ESP_TYPE="+MODULE_TYPE+"&ESP_APPL_V="+APPL_VER+"&ESP_BSW_V="+BSW_VER+"&SW_DATE="+SW_Compiled_Date+"&ESP_DNS=https://"+Local_DNS_Name+".local" ;
    
   G_data = "Action=AddESP&ESPName=" + BOARD_NAME + "&ESPNum="+BOARD_NUMBER+"&ESPIP="+MY_IP+"&ESP_G_IP="+Global_IP+"&ESP_TYPE="+MODULE_TYPE+"&ESP_APPL_V="+APPL_VER+"&ESP_BSW_V="+BSW_VER+"&SW_DATE="+Formate_date(SW_Compiled_Date)+"&ESP_DNS=https://"+Local_DNS_Name+".local";

   #ifdef _G_DEBUG  
     Serial.println("Update IP called");
   #endif 

}



void google_sheet_setup() {
 
  client.setInsecure();
  init_timer_delay_sec( G_SHEET_TIMER , G_SHEET_DELAY_SEC ); // 6 sec
}
 
 
// Subroutine for sending data to Google Sheets
void sendDataToGoogleSheet() 
{
#ifdef _G_DEBUG  
  Serial.println("==========");
  Serial.print("connecting to ");
  Serial.println(host);
#endif  
  //----------------------------------------Connect to Google host
  if (!client.connect(host, httpsPort)) 
  {
#ifdef _G_DEBUG     
    Serial.println("connection failed");
#endif    
    return;
  }
  //----------------------------------------
 
  //----------------------------------------Processing data and sending data

 // String url = "/macros/s/" + IP_Sheet + "/exec?temperature=" + string_temperature + "&humidity=" + string_humidity;

  String url = "/macros/s/" + IP_Sheet + "/exec?" + G_data;
#ifdef _G_DEBUG 
  Serial.print("requesting URL: ");
  Serial.println(url);
#endif 
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
         "Host: " + host + "\r\n" +
         "User-Agent: BuildFailureDetectorESP8266\r\n" +
         "Connection: close\r\n\r\n");
#ifdef _G_DEBUG  
  Serial.println("request sent");
#endif  
  //----------------------------------------
 
  //----------------------------------------Checking whether the data was sent successfully or not
  
  if (client.connected()) 
  {
    String line = client.readStringUntil('\n');
    if(G_UPDATE_FLAG != 255)
    {
      G_UPDATE_SELECT &= ~(1 << G_UPDATE_FLAG); // clear bit
     // Serial.print(G_UPDATE_FLAG); Serial.println(" G bit cleared");
    }
#ifdef _G_DEBUG     
    Serial.println("G Client Connected");
#endif    
    if (line == "\r") 
    {
#ifdef _G_DEBUG       
      Serial.println("headers received");
#endif      
    
    }

  }

  String line = client.readStringUntil('\n');
  if (line.startsWith("{\"state\":\"success\"")) 
  {
#ifdef _G_DEBUG     
    Serial.println("esp8266/Arduino CI successfull!");
#endif    
    
    if(G_UPDATE_FLAG != 255)
    {
      G_UPDATE_SELECT &= ~(1 << G_UPDATE_FLAG); // clear bit
      //Serial.print(G_UPDATE_FLAG); Serial.println(" G bit cleared");
    }
  }
   else 
   {
#ifdef _G_DEBUG     
    Serial.println("esp8266/Arduino CI has failed");
#endif    
  }
#ifdef _G_DEBUG   
  Serial.print("reply was : ");
  Serial.println(line);
  Serial.println("closing connection");
  Serial.println("==========");
  Serial.println();
#endif  
  //----------------------------------------
}







void Check_G_sheet_pending_send()
{
  G_UPDATE_FLAG = 255 ; // invalid flag
  if (G_UPDATE_SELECT & (1 << G_UPDATE_IP)) // check Bit is SET or NOT
  {
    G_UPDATE_FLAG = G_UPDATE_IP;
    Update_IP_On_Google_Sheet();
    //Serial.print(G_UPDATE_IP); Serial.println(" G bit checked");
    sendDataToGoogleSheet();
  }
  else if (G_UPDATE_SELECT & (1 << G_UPDATE_LOGOUT)) // check Bit is SET or NOT
  { 
    G_UPDATE_FLAG = G_UPDATE_LOGOUT;
    Update_LogOutTime_On_Google_Sheet();
    //Serial.print(G_UPDATE_LOGOUT); Serial.println(" G bit checked");
    sendDataToGoogleSheet();
  }

  if( G_UPDATE_SELECT == 0)
  {
    deactivate_timer(G_SHEET_TIMER);
  }
}

void G_sheet_send(int op)
{
  G_UPDATE_SELECT |= (1 << op); // SEt bit
  activate_timer(G_SHEET_TIMER);
  //Serial.print(op); Serial.println(" G bit set");
}






void google_sheet_loop()
{
    if(is_timer_timeout( G_SHEET_TIMER ))
    {
       Check_G_sheet_pending_send();
#ifdef _G_DEBUG        
       Serial.println(" Google Timer Time Out");
#endif           
    }
}







//==============================================================================

/******************************************* Sample code ****************************************************************************/
#if 0

#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include "DHT.h"
#define DHTTYPE DHT11 // type of the temperature sensor
const int DHTPin = 5; //--> The pin used for the DHT11 sensor is Pin D1 = GPIO5
DHT dht(DHTPin, DHTTYPE); //--> Initialize DHT sensor, DHT dht(Pin_used, Type_of_DHT_Sensor);
 
#define ON_Board_LED 2  //--> Defining an On Board LED, used for indicators when the process of connecting to a wifi router
 
const char* ssid = "AndroidAP3DEC"; //--> Your wifi name or SSID.
const char* password = "123456"; //--> Your wifi password.
 
 
//----------------------------------------Host & httpsPort
const char* host = "script.google.com";
const int httpsPort = 443;
//----------------------------------------
 
WiFiClientSecure client; //--> Create a WiFiClientSecure object.
 
String GAS_ID = "AKfycby8Lfzwu-5SBj9tHxbw3_j8ZPZy6P6_3e_BBISC0Jg7SstXLUed"; //--> spreadsheet script ID
 
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(500);
 
  dht.begin();  //--> Start reading DHT11 sensors
  delay(500);
  
  WiFi.begin(ssid, password); //--> Connect to your WiFi router
  Serial.println("");
    
  pinMode(ON_Board_LED,OUTPUT); //--> On Board LED port Direction output
  digitalWrite(ON_Board_LED, HIGH); //--> Turn off Led On Board
 
  //----------------------------------------Wait for connection
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    //----------------------------------------Make the On Board Flashing LED on the process of connecting to the wifi router.
    digitalWrite(ON_Board_LED, LOW);
    delay(250);
    digitalWrite(ON_Board_LED, HIGH);
    delay(250);
    //----------------------------------------
  }
  //----------------------------------------
  digitalWrite(ON_Board_LED, HIGH); //--> Turn off the On Board LED when it is connected to the wifi router.
  Serial.println("");
  Serial.print("Successfully connected to : ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println();
  //----------------------------------------
 
  client.setInsecure();
}
 
void loop() {
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  int h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  
  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor !");
    delay(500);
    return;
  }
  String Temp = "Temperature : " + String(t) + " °C";
  String Humi = "Humidity : " + String(h) + " %";
  Serial.println(Temp);
  Serial.println(Humi);
  
  sendData(t, h); //--> Calls the sendData Subroutine
}
 
// Subroutine for sending data to Google Sheets
void sendData(float tem, int hum) {
  Serial.println("==========");
  Serial.print("connecting to ");
  Serial.println(host);
  
  //----------------------------------------Connect to Google host
  if (!client.connect(host, httpsPort)) {
    Serial.println("connection failed");
    return;
  }
  //----------------------------------------
 
  //----------------------------------------Processing data and sending data
  String string_temperature =  String(tem);
  // String string_temperature =  String(tem, DEC); 
  String string_humidity =  String(hum, DEC); 
  String url = "/macros/s/" + GAS_ID + "/exec?temperature=" + string_temperature + "&humidity=" + string_humidity;
  Serial.print("requesting URL: ");
  Serial.println(url);
 
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
         "Host: " + host + "\r\n" +
         "User-Agent: BuildFailureDetectorESP8266\r\n" +
         "Connection: close\r\n\r\n");
 
  Serial.println("request sent");
  //----------------------------------------
 
  //----------------------------------------Checking whether the data was sent successfully or not
  while (client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") {
      Serial.println("headers received");
      break;
    }
  }
  String line = client.readStringUntil('\n');
  if (line.startsWith("{\"state\":\"success\"")) {
    Serial.println("esp8266/Arduino CI successfull!");
  } else {
    Serial.println("esp8266/Arduino CI has failed");
  }
  Serial.print("reply was : ");
  Serial.println(line);
  Serial.println("closing connection");
  Serial.println("==========");
  Serial.println();
  //----------------------------------------
} 
//==============================================================================
/******************************************************************************************************************/

/*********************************************** Google Script **************************************************/

//how to use Example
//https://script.google.com/macros/s/AKfycbzc0LEbZWeHH9As_Y2SULaFRaoMF0Oi35Hdi9cvN4cqZBNy8o8a6l7koztRl4dDDGyTBA/exec?Action=AddESP&ESPName=Rajesh_ESP&ESPNum=55&ESPIP=192.168.31.100

var result = "";
var Data_pos = "";

function doGet(e) { 
var ss = SpreadsheetApp.openByUrl("https://docs.google.com/spreadsheets/d/1UNbi_AR6szoaBBUkKiyMhwXmqGe6pRnLv8FFL6BndKQ/edit?gid=0#gid=0");

var sheet = ss.getSheetByName("Sheet1");

 if(e.parameter.Action == "AddESP")
 {
   addUser(e,sheet);
 }

 return ContentService.createTextOutput(result); // Data send to user (MIT APP)
}

function doPost(e) { 

  var ss = SpreadsheetApp.openByUrl("https://docs.google.com/spreadsheets/d/1UNbi_AR6szoaBBUkKiyMhwXmqGe6pRnLv8FFL6BndKQ/edit?gid=0#gid=0");
  var sheet = ss.getSheetByName("Sheet1"); 
  
   if(e.parameter.Action == "AddESP")
 {
   addUser(e,sheet);
 }

  return ContentService.createTextOutput(result); // Data send to user (MIT APP)
}


function VerifyESP(e,sheet) {
  var ESPName = e.parameter.ESPName ; 
  var ESPNum = e.parameter.ESPNum ;

 var ESPName_Found = 0;
 var ESPNum_Found = 0;
 
 Data_pos = "";


 for(let i=2; i<100; i++)
  {
    var i_num = i.toString();
	
    var ESPName_Cell = "A"+i_num;
    var ESPNum_Cell = "B"+i_num;
    
    var ESPNameCellVal = sheet.getRange(ESPName_Cell).getValue();
    var ESPNumCellVal = sheet.getRange(ESPNum_Cell).getValue();
    

    if(ESPName_Found == 0)
    {
      if(ESPNameCellVal == ESPName)
      {
        ESPName_Found = 1;
        Data_pos = i_num;
      }
    }
    if(ESPNum_Found == 0)
    {
      if(ESPNumCellVal == ESPNum)
      {
        ESPNum_Found = 1;
      }
    }
    

    if(ESPNameCellVal == "")
    {
      break; // exit loop if cell is blank
    }

  }

}


function addUser(e,sheet) {
  var ESPName = e.parameter.ESPName ; 
  var ESPNum = e.parameter.ESPNum ;
  var ESPIP  = e.parameter.ESPIP;
  
  VerifyESP(e,sheet);


  var Curr_Date = Utilities.formatDate(new Date(), "Asia/Kolkata", 'dd-MM-yyyy');
  var Curr_Time = Utilities.formatDate(new Date(), "Asia/Kolkata", 'HH:mm:ss');

  var First_SignUp_Time = Curr_Date+" @ "+ Curr_Time ;
  
  if(Data_pos == "") // ESP not found so adding in new line
  {
    sheet.appendRow([ESPName,ESPNum,ESPIP,First_SignUp_Time ]);
    result = "New ESP BOARD Added ....!";
  }	
  else
  {
     var IPCellPos = "C"+Data_pos;
	 var TimeCellPos = "D"+Data_pos;

     sheet.getRange(IPCellPos).setValue(ESPIP);
	 sheet.getRange(TimeCellPos).setValue(First_SignUp_Time);
	 
	 result = "ESP IP Updated Successfully..!";
	 
  }
}



/********************************************************************************************************************/

#endif


/************************************************************************************************************************/


#endif //_GOOGLE_SHEETS_H
