#include <ESP8266WiFi.h>
#include <PubSubClient.h> // mqtt

#include <ArduinoJson.h>
#include "DHT.h"

#define DHTPIN D4 //온습도센서 연결핀번호
#define DHTTYPE DHT11

//mqtt: wifi연결을 위한 정보
const char* ssid = "iptimeBM";
const char* password = "22022202";
const char* mqtt_server = "192.168.0.4";

DHT dht(DHTPIN, DHTTYPE); //json
StaticJsonDocument<200> doc; //RAM 할당 //mqtt

WiFiClient espClient;
PubSubClient client(espClient); 

long lastMsg = 0;
char msg[50]; // MQTT에 보내는 메시지 배열. 
  
void setup() {

  Serial.begin(115200);
  while (!Serial) continue;

  pinMode(DHTPIN,INPUT);
  dht.begin();

  setup_wifi(); // wifi접속 관련
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);  
}
void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network. ㅣwifi연결관련부분
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

//NodeMCU가 MQTT로부터 subscribe할 때 불려지는 함수 : 어떤 topic으로 어떤 메시지가 오는지
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

void reconnect() { // 연결실패, 지연되었을때
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

void makeJson(float temp, float humi){ // 가공하는 영역
  JsonObject root = doc.to<JsonObject>(); // json으로 가공
  root["Temp"] = temp;     
  root["Humi"] = humi;
    
  Serial.print("JsonData: ");
  serializeJson(root, Serial);  //시리얼 모니터창에 출력
  Serial.println();

  serializeJson(root, msg);  // MQTT msg array에 담기 (msg공간에 root내용을 담음) 중요!
}

void loop() { // 센싱한 데이터를 시리얼모니터창에 출력하고 제이슨으로 가공. mqtt로 보내야해서 커넥션준비해서 pub으로 메시지 발송.
  
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
    client.publish("Sensor", msg); // 토픽이름 : Sensor, msg: 온습도 센서에서 센싱한 데이터
  }
  delay(2000);
}
