//Switch 눌려질 때마다 LED on/off (Edge Triger)

#include <Led.h>

#define OFF 1   // OFF 표기는 1을 의미한다고 정의
#define ON 0    // const int ON = 0; 과 같은 의미

Led led(3);              //Led 연결핀 3번. 클래스 변수 선언

const int sw_pin = 2;    //스위치 연결핀 2번.

void setup() {
  Serial.begin(9600); //통신속도
  pinMode(sw_pin, INPUT_PULLUP);
}

void loop() {
  boolean o_sw, n_sw;
  o_sw = digitalRead(sw_pin);   // 첫 번째 상태
  delay(2);
  n_sw = digitalRead(sw_pin);   // 두 번째 상태

  if(o_sw == OFF && n_sw == ON){  // 하강 edge인가? 물어보는 조건식
    Serial.println("button pressed");
    led.toggle();    
  }
// 스위치를 누르면 led에 점등/소등
}
