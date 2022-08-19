//Switch 누르면 4개순차점멸 LED on/off (Edge Triger)
//스위치를 누를때마다 다음 불이 켜지는 형식으로 순차점멸

#include <Led.h>

#define OFF 1   
#define ON 0    

Led led (3); 
const int sw_pin = 2;   

void setup() {
  Serial.begin(9600);              //통신속도
  pinMode(sw_pin, INPUT_PULLUP);
}

void blink(){
  Serial.println("button pressed");
  led.toggle();
}

void loop() {
  boolean o_sw, n_sw;  // 같은 부분
  o_sw = digitalRead(sw_pin);   // 첫 번째 상태
  delay(10);
  n_sw = digitalRead(sw_pin);   // 두 번째 상태


    if(o_sw == OFF && n_sw == ON){ // 하강 edge인가? 물어보는 조건식 // 같은 부분
      blink();
    }
  }

  
