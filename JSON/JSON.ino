#include <ArduinoJson.h>

//setup에 코드가 있어서 시리얼 모니터를열기전에 한번 출력하고 끝남
//시리얼모니터를 연 상태에서 nodeMCU에 리셋버튼 눌러서 확인
//시리얼모니터에 json형식으로 key:value형태로 출력되는지 확인

void setup() {
  Serial.begin(9600); // 시리얼 모니터의 출력 보드레이트가 맞는지 확인
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

//json형식: {key:value}딕셔너리 형태
// doc-object타입
//              -"sensor":"gps" 
//              -"time":123456789
//              -data : 리스트타입으로 여러개 
