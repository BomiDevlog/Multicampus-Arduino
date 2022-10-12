#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include "DHT.h"

#define DHTPIN D4
#define DHTTYPE DHT11

const char* ssid = "iptimeBM";
const char* password = "22022202";
const char* mqtt_server = "192.168.0.4";

DHT dht(DHTPIN, DHTTYPE);
StaticJsonDocument<200> doc; //RAM 할당

WiFiClient espClient;
PubSubClient client(espClient);

long lastMsg = 0;
char msg[50];
  
void setup() {

  Serial.begin(115200);
  while (!Serial) continue;

  pinMode(DHTPIN,INPUT);
  dht.begin();

  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  client.subscribe("Model");  
}

void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  // Switch on the LED if an 1 was received as first character
  if ((char)payload[0] == '1') {
    digitalWrite(BUILTIN_LED, LOW);   // Turn the LED on (Note that LOW is the voltage level
    // but actually the LED is on; this is because
    // it is acive low on the ESP-01)
  } else {
    digitalWrite(BUILTIN_LED, HIGH);  // Turn the LED off by making the voltage HIGH
  }

}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP8266Client")) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish("outTopic", "hello world");
      // ... and resubscribe
      client.subscribe("inTopic");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void makeJson(float temp, float humi){
  JsonObject root = doc.to<JsonObject>();
  root["Temp"] = temp;     
  root["Humi"] = humi;
    
  Serial.print("JsonData: ");
  serializeJson(root, Serial);  //시리얼 모니터창에 출력
  Serial.println();

  serializeJson(root, msg);  // MQTT msg array에 담기
}

void loop() {
  
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  Serial.print("SensorData: ");
  Serial.print("Temp: ");
  Serial.print(t);
  Serial.print(", Humi: ");
  Serial.println(h);

  
  makeJson(t,h);
  
  if (!client.connected()) {
    reconnect();
  }
  
  client.loop();

  long now = millis();
  if (now - lastMsg > 2000) {
    lastMsg = now;
    Serial.print("MQTT-Publish: ");
    Serial.println(msg);
    client.publish("Sensor", msg);
  }


  delay(2000);
}
