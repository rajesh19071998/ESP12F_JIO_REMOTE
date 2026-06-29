#ifndef _HTTP_URL_H
#define _HTTP_URL_H


// #define _HTTP_URL_DEBUG

// Replace with the URL you want to execute
//String url = "http://example.com/your-endpoint";

WiFiClient http_client;  // Create a WiFiClient object

String http_url(String url) 
{
  String Responce = "";
  if (WiFi.status() == WL_CONNECTED) 
  {
    HTTPClient http;

    // Updated API: pass WiFiClient and URL
 #if defined(ESP32)   
    http.setConnectTimeout(3000);  // 3 secs for connect url
 #endif   
    http.setTimeout(2000);         // 2 for reading response

    http.begin(http_client, url);  

    int httpCode = http.GET(); // Make the GET request

#ifdef _HTTP_URL_DEBUG    
    Serial.print("http Code = ");
    Serial.println(httpCode);
#endif

    if (httpCode > 0) 
    {
      String payload = http.getString();
      Responce = payload;

#ifdef _HTTP_URL_DEBUG
      Serial.println("http Response:");
      Serial.println(payload);
#endif

    } 
    else 
    {
#ifdef _HTTP_URL_DEBUG      
      Serial.printf("Error on HTTP request: %s\n", http.errorToString(httpCode).c_str());
#endif      
      Responce = "Error on HTTP url Request = " + url + "  \n Error is = ";
      Responce = Responce + http.errorToString(httpCode) ;
      Responce = Responce + "  \nHTTP error code = ";
      Responce = Responce + String(httpCode);
    }

    http.end(); // Close connection
  }
   else 
  {
#ifdef _HTTP_URL_DEBUG    
    Serial.println("WiFi not connected");
#endif
    Responce = "WIFI not connected";    
  }

  return Responce ;
}

#endif
