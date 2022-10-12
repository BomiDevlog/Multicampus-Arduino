#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// Update these with values suitable for your network.


const char* ssid = "iptimeBM";  //와이파이 SSID
const char* password = "22022202";  //와이파이 pwd
const char* mqtt_server = "192.168.0.4"; //MQTT 브로커의 주소

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;

void setup() {
  pinMode(BUILTIN_LED, OUTPUT);     // Initialize the BUILTIN_LED pin as an output
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

  
  //{"model": "SmartPrediction", "time": "20221009 20:40:32", "predict": 1}
  client.subscribe("Model"); //Model 이라는 토픽을 구독하기로 설정
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
//subscribe 해온 메시지를 문자열로 만듬(byte -> 문자열)
void callback(char* topic, byte* payload, unsigned int length) {
  char str[length+1];
  
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  int i;
  for (i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
    str[i] = (char)payload[i];    
  }
  str[i] = 0; //Null termination
  Serial.println();

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
