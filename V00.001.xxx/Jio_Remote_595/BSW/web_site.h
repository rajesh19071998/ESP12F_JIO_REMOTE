/*********
  Rui Santos & Sara Santos - Random Nerd Tutorials
  Complete instructions at https://RandomNerdTutorials.com/build-web-servers-ebook/
  
  Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files.
  The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
*********/
#ifndef _WEB_SITE_H
#define _WEB_SITE_H

//#define _WEB_DEBUG

// Create a WebSocket object
AsyncWebSocket ws("/ws");

// Initialize LittleFS
void initFS() {
  if (!LittleFS.begin()) {
#ifdef _WEB_DEBUG    
    Serial.println("An error has occurred while mounting LittleFS");
#endif    
  }
  else 
  {
#ifdef _WEB_DEBUG    
    Serial.println("LittleFS mounted successfully");
#endif    
  }
}



String getOutputStates(){
  String jsonString = "";

#ifdef _RELAY_H  // Relay.h

  JSONVar myArray;
  for (int i =0; i< MAX_RELAY; i++){
    myArray["gpios"][i]["output"] = String(i);
    myArray["gpios"][i]["state"] = String(get_relay_state(i));
  }
   jsonString = JSON.stringify(myArray);
  
#endif  // Relay.h

return jsonString;
}


void notifyClients(String state) {
  ws.textAll(state);
}

void handleWebSocketMessage(void *arg, uint8_t *data, size_t len) {
    AwsFrameInfo *info = (AwsFrameInfo*)arg;
  if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) {
    data[len] = 0;
    if (strcmp((char*)data, "states") == 0) 
    {
#ifdef _WEB_DEBUG      
      Serial.print("Web_Data : ");
      Serial.println((char*)data);
#endif      
      notifyClients(getOutputStates());
    }
    else{
      int gpio = atoi((char*)data);
#ifdef _WEB_DEBUG      
      Serial.print("Web_Data : ");
      Serial.println((char*)data);
      /*
      Serial.print("Web_Site GPIO : ");
      Serial.println(gpio);
      */
#endif      
#ifdef _RELAY_H   // Relay.h    
      Update_relay_state_with_index((gpio - 1), !get_relay_state(gpio-1)); // Relay.h
#endif  // Relay.h
      notifyClients(getOutputStates());
    }
  }
}

void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client,AwsEventType type,
             void *arg, uint8_t *data, size_t len) {
  switch (type) {
    case WS_EVT_CONNECT:
#ifdef _WEB_DEBUG    
      Serial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
#endif     
      break;
    case WS_EVT_DISCONNECT:
#ifdef _WEB_DEBUG    
      Serial.printf("WebSocket client #%u disconnected\n", client->id());
#endif      
      break;
    case WS_EVT_DATA:
      handleWebSocketMessage(arg, data, len);

      break;
    case WS_EVT_PONG:
    case WS_EVT_ERROR:
      break;
  }
}

void initWebSocket() {
  ws.onEvent(onEvent);
  MIT_server.addHandler(&ws);
}

void web_site_setup(){
  
  initFS();
  
  initWebSocket();

}

void web_site_loop() {

  ws.cleanupClients();

}


#endif //_WEB_SITE_H