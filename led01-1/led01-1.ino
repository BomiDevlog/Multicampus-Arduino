const int pu_led = 13; //핀번호를 나타내는 전역상수를 지정해서 유용하게 조작.

//13번에 연결하니 빵판과 같은 반응으로 불빛이 들어옴. 13번에 자체적으로 연결된 led라서.
//13번은 풀다운방식의 내장led, built in led
//blink : 일정한 주기로 깜빡거림. (예) 경고등, 동작중알림, cctv나 카메라에 불빛들어옴. 
//거리센서에서 깜빡이는 간격이 짧아지면 가깝고 일점범위넘어서면 꺼지는 방식으로 응용되기도함 
//delay시간을 제어해서 빨리 깜빡이면 긴박한 위급상황을 알림.
//주로 디바이스의 상태를 나타낼 떄 쓰임

void setup() {
  pinMode(pu_led,OUTPUT); //LED 출력
}

void loop() {
  digitalWrite(pu_led, HIGH);  //pullup방식 OFF // pulldown방식 on
  delay(100);                  //0.001초 * 500 => 0.5초 유지
  
  digitalWrite(pu_led, LOW);   //pullup방식 ON  // pulldown방식 off
  delay(100);
}
