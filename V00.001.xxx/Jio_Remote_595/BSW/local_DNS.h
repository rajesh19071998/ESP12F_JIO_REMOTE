#ifndef _LOCAL_DNS_H
#define _LOCAL_DNS_H

//#define _MDNS_DEBUG

void local_dns_setup()
{
    // Start mDNS with hostname "esp8266"
  if (MDNS.begin(Local_DNS_Name)) {  // Local_DNS_Name is available in WIFI_CONFIG.h
#ifdef _MDNS_DEBUG  
    Serial.print("mDNS started at : http://");
    Serial.print(Local_DNS_Name);
    Serial.println(".local");
#endif    
  }
  else 
  {
#ifdef _MDNS_DEBUG
   Serial.println("mDNS was failed to start......! ");
#endif
  }
}

void local_dns_loop()
{
#if defined(ESP8266)
  MDNS.update(); // only for esp8266
#endif  
}








#endif  //_LOCAL_DNS_H