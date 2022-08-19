#include <Led.h> 
// pullup방식 : pulldown 하드웨어 구성에서 10K저항 제거.
Led led(3);
const int BTN = 2;

void setup() {
  pinMode(BTN, INPUT_PULLUP); // 내부 저항 사용
}

void loop() {
  int value = !digitalRead(BTN); // 버튼 클릭 시 점등. 평상 시 소등상태로 변경.
  led.setValue(value); 
  
}

//누르는 순간에만 소등 상태가 되니 불편함. 누른상태에서 스위치 점등 ->level Triger

//떨어지는곳 혹은 올라가는 곳만 캐치해서 상태변화 -> Edge Triger
