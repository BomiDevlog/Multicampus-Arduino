#include <Led.h>
#include <Button.h>

Led led(4);
Button btn(2);

void pressed() {
  led.toggle();
  delay(3000); 
  //delay함수가 실행될동안 프로그램은 다른 동작을 할 수 없이 정지상태라서 문제.
  //그 시간동안 버튼을 눌러도 감지 못함.
  //그래서 delay는 여러작업이 동시에 일어날 수 있는 상황에서 사용하면 안됨

  //t1 = millis();
  // ... 작업내용
  //t2 = millis();
  //t2-t1 > 1000 

  //타이머를 사용 -> SimpleTimer
}

void setup() {
  btn.setCallback(pressed);
}

void loop() {
  btn.check(); 
}
