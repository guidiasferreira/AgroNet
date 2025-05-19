#include <DHT.h>
#include <LoRa.h>
#include <SPI.h>

#define NSS D8
#define RST D3
#define DIO0 D2
#define MISO D6
#define SCK D5
#define MOSI D7
#define DHTPIN D1
#define DHTTYPE DHT11
#define LDR A0

#define temperaturaIdeal 30
#define umidadeIdeal 60

String dadosLora = "";

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  while (!Serial);

  Serial.println("Iniciando LoRa...");
  LoRa.setPins(NSS, RST, DIO0);

  if (!LoRa.begin(433E6)) {
    Serial.println("ERRO ao iniciar LoRa!");
    while (1);
  }

  dht.begin();

}

void loop() {

  int luminosidade = analogRead(A0);
  float lumen = 1023;
  float conversaoLumen = (luminosidade / lumen) * 100;

  if (isnan(luminosidade)) {
    Serial.println("ERRO NO SENSOR LDR!!");

  } else {
    delay(2000);
  }


  float temperatura = dht.readTemperature();
  float umidade = dht.readHumidity();

  if (isnan(temperatura) || isnan(umidade)) {
    Serial.println("ERRO NO SENSOR DHT11!!");

  } else {
    delay(2000);
  }


  dadosLora = "Temperatura: " + String(temperatura) + "C" + "\nUmidade: " + String(umidade) + "%" + "\nLuminosidade: " + String(conversaoLumen) + "%";

  Serial.print("Enviando Dados\n");
  LoRa.beginPacket();
  LoRa.print(dadosLora);
  LoRa.endPacket();
  delay(1000);  
}
