#include <SimpleTimer.h>
#include <Led.h>


///SimpleTimer를 사용해 1초 간격으로 LED on/off 반복 설정

SimpleTimer timer;
Led led(3);

void blink_1000(){
  led.toggle();
}

void setup() {
  timer.setInterval(1000, blink_1000);
}

void loop() {
  timer.run();
}
