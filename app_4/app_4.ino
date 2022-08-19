#include <SimpleTimer.h>
#include <Led.h>
//3번LED는 1초간격 blink, 4번 LED는 0.5초간격, 5번 LED는 0.3초간격 blink 동시에 진행

//주기적으로 센서의 값을 읽음
//센서측정하는 함수만들고 시간을 setup에 걸어줌
//예로ㅡ 1분간격으로 온도측정하는 기계

SimpleTimer timer;
Led led1(3), led2(4), led3(5);

void blink_1000(){
  led1.toggle();
}

void blink_500(){ // 함수를 만들고 호출을 늘려주면 된다!
  led2.toggle();
}

void blink_300(){
  led3.toggle();
}

void setup() {
  timer.setInterval(1000, blink_1000);
  timer.setInterval(500, blink_500);
  timer.setInterval(300, blink_300);
}

void loop() {
  timer.run();
}
