#include "Led.h" 
//라이브러리화 시킨후에는 #include <Led.h> 해도됨
Led led(3); //클래스변수 제시
void setup() {
  // 이미 생성자에서 핀모드 설정해줌
}

void loop() {
  led.on();
  delay(500);
  led.off();
  delay(500);

}

//blink프로그램 완성!
