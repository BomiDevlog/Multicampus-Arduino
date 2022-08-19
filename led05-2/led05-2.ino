#include "Led.h" 
Led led(4); //클래스변수 제시
void setup() {
  // 이미 생성자에서 핀모드 설정해줌
}

void loop() {
  led.toggle();
  delay(1000);

}

//blink프로그램 완성!
