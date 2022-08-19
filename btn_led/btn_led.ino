#include <Led.h>
#include <Button.h>

Led led(4);
Button btn(2);

void pressed() {
  led.on();
  delay(1000); //delay함수가 실행될동안 프로그램은 다른 동작을 할 수 없이 정지상태라서 문제.
  led.off();
}

void setup() {
  btn.setCallback(pressed);
}

void loop() {
  btn.check();
}
