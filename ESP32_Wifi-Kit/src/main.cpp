#include <Arduino.h>
#include <WiFiMulti.h>
#include <WebSocketsClient.h>

#define LED_BUILTIN  2

#define WIFI_SSID         "Chez_Stonesifer"
#define WIFI_PASSWORD     ""

#define WS_HOST           ""
#define WS_PORT           ""
#define WS_URL            ""

WiFiMulti wifiMulti;
WebSocketsClient wsClient;

void handleMessage(uint8_t * payload){

}

void onWSEvent(WStype_t type, uint8_t * payload, size_t length){
  switch(type){
    case WStype_CONNECTED:
      Serial.println("WS Connected");
      break;
    case WStype_DISCONNECTED:
      Serial.println("WS Disonnected");
      break;
    case WStype_TEXT:
      Serial.println("WS Message: %s\n", paylaod);
      handleMessage(payload);
      break;
  }
    
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  wifiMulti.addAP(WIFI_SSID, WIFI_PASSWORD);

  while(wifiMulti.run() != WL_CONNECTED){
    delay(100);
  }
  Serial.println("Connected");

  wsClient.beginSSL(WS_HOST, WS_PORT, WS_URL, "", "wss");
  wsClient.onEvent(onWSEvent)
}

bool isConnected = false;

void loop() {
  digitalWrite(LED_BUILTIN, WiFi.status() == WL_CONNECTED);
  wsClient.loop();
}
