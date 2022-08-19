#include <SimpleTimer.h>

SimpleTimer timer;

//callback함수
void repeatMe(){
  Serial.print("Uptime (s): ");
  Serial.println(millis() / 1000);
}

void setup() {
  Serial.begin(9600);
  timer.setInterval(1000, repeatMe);
}

void loop() {
  timer.run();
}

//시리얼 모니터로 확인해보면, 아두이노 우노의 reset버튼을 누르면 시간이 다시 흐른다.
