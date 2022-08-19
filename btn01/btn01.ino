#include <Led.h> 
// 풀다운방식
Led led(3);
const int BTN = 2;

void setup() {
  pinMode(BTN, INPUT); // 스위치는 INPUT
}

void loop() {
  int value = !digitalRead(BTN); // 버튼 클릭 시 점등. 평상 시 소등상태로 변경.
  led.setValue(value); 
  
}
