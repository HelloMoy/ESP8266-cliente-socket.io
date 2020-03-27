#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#include <SocketIoClient.h>

ESP8266WiFiMulti WiFiMulti;
SocketIoClient webSocket;

int periodo = 1000; //periodo del envio de datos
unsigned long TiempoAhora = 0;
int temp = 17;

void event(const char * payload, size_t length) {
  Serial.println("Dato recibido: " + String((char*)payload));
  if(String((char*)payload)=="Hola"){
    Serial.println("Dato esperado");
  }
}

void setup() {
  Serial.begin(115200);
  Serial.println("Iniciando");

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
    if(millis() > TiempoAhora + periodo){
      String dato = "{R:90, G:120, B:255}";                         //Dato a enviar
      String formato = "\"" + dato + "\"" ;
      const char *casteo = const_cast<char*>(formato.c_str());      //Casteo del dato a enviar
      webSocket.emit("alerta", casteo );                            //Envio de datos al servidor

      TiempoAhora = millis();
    }
}
