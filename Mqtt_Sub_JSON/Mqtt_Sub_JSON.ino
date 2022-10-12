#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

// Update these with values suitable for your network.

const char* ssid = "iptimeBM";
const char* password = "22022202";
const char* mqtt_server = "192.168.0.4";

WiFiClient espClient;
PubSubClient client(espClient);

long lastMsg = 0;
char msg[50];
int value = 0;

void setup() {
  Serial.begin(115200);
  setup_wifi();
  
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

  //파이썬에서 이러한 형태로 데이터가 들어온다고 가정한다
  //{"model": "SmartPrediction", "time": "20221009 20:40:32", "predict": 1}
  client.subscribe("Model"); // topic명 Model을 구독
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

void subscribeToJSON(byte* input){ // 바이트가 들어오면 

  StaticJsonDocument <256> doc; // 제이슨 도큐먼트 타입으로 변환해줘
  deserializeJson(doc,input);
  
  // deserializeJson(doc,str); can use string instead of payload
  
  //{"model": "SmartPrediction", "time": "20221009 20:40:32", "predict": 1}
  //json구조에서 키를 이용해서 밸류를 추출. 딕셔너리 값 추출하듯이.
  String model = doc["model"];
  String timeClock = doc["time"];
  int predict  = doc["predict"];
  
  Serial.print("model = ");
  Serial.print(model);
  Serial.print(", time = ");
  Serial.print(timeClock);
  Serial.print(", predict = ");
  Serial.println(predict);  
}

void callback(char* topic, byte* payload, unsigned int length) {
    //페이로드로 바이트가 들어오면 
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  
  for (int i = 0; i < length; i++) { // 시리얼 모니터
    Serial.print((char)payload[i]);
  }
  Serial.println();

  subscribeToJSON(payload); // 내부함수 사용. 50번 라인 확인
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
      client.subscribe("Model");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  long now = millis();
  if (now - lastMsg > 2000) {
    lastMsg = now;
    ++value;
    snprintf (msg, 75, "hello world #%ld", value);
    Serial.print("Publish message: ");
    Serial.println(msg);
    
    client.publish("outTopic", msg);
  }
}
