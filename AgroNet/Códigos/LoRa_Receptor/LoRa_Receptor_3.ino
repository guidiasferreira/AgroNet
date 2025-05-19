#include <LoRa.h> 
#include <SPI.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <ArduinoJson.h>

#define NSS D8
#define RST D3
#define DIO0 D2
#define MISO D6
#define SCK D5
#define MOSI D7


String recebendo = "";
String ip = "";
String temperatura = "";
String umidade = "";
String luminosidade = "";
String json = "";

const char* ssid = "Guilherme_2";
const char* password = "josecarlos";

ESP8266WebServer server(80);

void handleDados() {
  temperatura = recebendo.substring(recebendo.indexOf("Temperatura:") + 12, recebendo.indexOf("C", recebendo.indexOf("Temperatura:")));
  umidade = recebendo.substring(recebendo.indexOf("Umidade:") + 8, recebendo.indexOf("%", recebendo.indexOf("Umidade:")));
  luminosidade = recebendo.substring(recebendo.indexOf("Luminosidade:") + 13, recebendo.indexOf("%", recebendo.indexOf("Luminosidade:")));
  ip = WiFi.localIP().toString();

  json = "{";
  json += "\"temperatura\":\"" + temperatura + "\","; 
  json += "\"umidade\":\"" + umidade + "\","; 
  json += "\"luminosidade\":\"" + luminosidade + "\",";
  json += "\"ip\":\"" + ip + "\"";
  json += "}";

 
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.sendHeader("Access-Control-Allow-Methods", "GET, POST, OPTIONS");
  server.sendHeader("Access-Control-Allow-Headers", "Content-Type");

  server.send(200, "application/json", json);
}

void handleOptions() {
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.sendHeader("Access-Control-Allow-Methods", "GET, POST, OPTIONS");
  server.sendHeader("Access-Control-Allow-Headers", "Content-Type");
  server.send(200);
}

void handleNotFound() {
  server.send(404, "text/plain", "Página não encontrada");
}

void setup() {
  Serial.begin(115200);
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("Conectando ao WiFi...");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConectado!");
  Serial.print("Endereço IP: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("ESP8266")) {
    Serial.println("MDNS iniciado");
  }

  server.on("/dados", HTTP_GET, handleDados);
  server.on("/dados", HTTP_OPTIONS, handleOptions);
  server.onNotFound(handleNotFound);
  
  server.begin();
  Serial.println("Servidor HTTP iniciado");

  LoRa.setPins(NSS, RST, DIO0);

  if (!LoRa.begin(433E6)) {
    Serial.println("ERRO NO LORA!");
    while (1);
  }
}

void loop() {
  server.handleClient();
  
  int packetSize = LoRa.parsePacket();

  if (packetSize) {
    recebendo = "";

    while (LoRa.available()) {
      recebendo += (char)LoRa.read();
    }

    Serial.println("Recebendo Dados");
  }

  delay(10);
}
