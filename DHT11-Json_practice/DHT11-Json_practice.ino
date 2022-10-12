//[실습] JSON.ino 와 DHT11.ino의 기능 합친 파일 생성
//1)각각의 블럭에 맞게 코드 조합
//2)시리얼넘버 등 충돌나는 부분에 대해 결정
//3)필요에 따라 위치 수정, 내용 변경 등 코드 정리 

#include <ArduinoJson.h>

#include "DHT.h"

#define DHTPIN D4     // 핀번호 수정
#define DHTTYPE DHT11   

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  Serial.println(F("DHTxx test!"));

  dht.begin();
  
}

void loop() {
  delay(2000);

  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);

  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  float hif = dht.computeHeatIndex(f, h);
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(f);
  Serial.print(F("°F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  Serial.print(hif);
  Serial.println(F("°F"));

//아래 내용을 독립된 내부함수로 정리한 것이 JSON_DHT11파일. 비교해서 코드 보기

//json형식으로 계속 출력 되어야함 => JSON의 setup에 있던 내용을 dht11의 loop자리로 합침
  StaticJsonDocument<200> doc; //RAM 할당 
  JsonObject root = doc.to<JsonObject>();

//key:value형태의 json형식으로 출력될 값을 지정해준다
  root["humi"] = h;     //"sensor":"gps"  문자입력
  root["temp"] = t;  //"time":123456789 숫자입력

//사용하지 않는 내용은 정리함 (주석 처리)
//  JsonArray data = root.createNestedArray("data");  //배열로 추가할 수 있음.
//  data.add(48.756080);
//  data.add(2.302038);

  serializeJson(root, Serial);  //시리얼 모니터창에 출력
  Serial.println();

  serializeJsonPretty(root, Serial); //시리얼 모니터창에 출력(예쁘게)
}
