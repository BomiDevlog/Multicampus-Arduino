#include <ArduinoJson.h>
//한번만 출력된다. nodeMCU에 리셋버튼 눌러서 확인
void setup() {
  Serial.begin(9600);
  while (!Serial) continue;

  StaticJsonDocument<200> doc; //RAM 할당
  JsonObject root = doc.to<JsonObject>();

  root["sensor"] = "gps";     //"sensor":"gps"  문자입력
  root["time"] = 123456789;  //"time":123456789 숫자입력

  JsonArray data = root.createNestedArray("data");  //배열로 추가할 수 있음.
  data.add(48.756080);
  data.add(2.302038);

  serializeJson(root, Serial);  //시리얼 모니터창에 출력
  Serial.println();

  serializeJsonPretty(root, Serial); //시리얼 모니터창에 출력(예쁘게)
}

void loop() {
  // not used in this example
}
