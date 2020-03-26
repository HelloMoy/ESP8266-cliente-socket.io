#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#include <SocketIoClient.h>

ESP8266WiFiMulti WiFiMulti;
SocketIoClient webSocket;

void event(const char * payload, size_t length) {
  Serial.println("Dato recibido: " + String((char*)payload));
  if(String((char*)payload)=="Hola"){
    Serial.println("Dato esperado");
  }
}

void setup() {
  Serial.begin(115200);
  Serial.println("Conectado");

    WiFiMulti.addAP("INFINITUMr7tf", "910c52701e");

    while(WiFiMulti.run() != WL_CONNECTED) {
        delay(100);
    }

    webSocket.on("saludo", event);
    webSocket.emit("alerta", "\"Alerta desde ESP8266\"");
    webSocket.begin("192.168.1.86", 5000);
}

void loop() {
    webSocket.loop();
}
