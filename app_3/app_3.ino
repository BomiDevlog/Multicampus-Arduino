#include <SimpleTimer.h>
#include <Led.h>
//3번LED는 1초간격 blink, 4번 LED는 0.5초간격 blink 동시에 진행

SimpleTimer timer;
Led led1(3), led2(4);

void blink_1000(){
  led1.toggle();
}

void blink_500(){ // 함수를 만들고 호출을 늘려주면 된다!
  led2.toggle();
}

void setup() {
  timer.setInterval(1000, blink_1000);
  timer.setInterval(500, blink_500);
}

void loop() {
  timer.run();
}
