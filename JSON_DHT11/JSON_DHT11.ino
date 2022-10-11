#include <ArduinoJson.h>
#include "DHT.h"

#define DHTPIN D4
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
StaticJsonDocument<200> doc; //RAM 할당
  
void setup() {

  Serial.begin(9600);
  while (!Serial) continue;

  pinMode(DHTPIN,INPUT);
  dht.begin();
}

void makeJson(float temp, float humi){
    
  JsonObject root = doc.to<JsonObject>();
  
  root["Temp"] = temp;   
  root["Humi"] = humi; 
       
  serializeJson(root, Serial);  //시리얼 모니터창에 출력
  Serial.println();
}

void loop() {
  delay(2000);

  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  Serial.print(F("Temperature: "));
  Serial.print(t);
  Serial.print(F("°C Humidity: "));
  Serial.print(h);
  Serial.println(F("%"));  
  
  makeJson(t,h);
}
