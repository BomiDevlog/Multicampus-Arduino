//Switch 누르면 4개순차점멸 LED on/off (Edge Triger)
//스위치를 누를때마다 다음 불이 켜지는 형식으로 순차점멸

#include <Led.h>

#define OFF 1   
#define ON 0    

Led leds [4]={ Led(6), Led(5), Led(4), Led(3)}; 
const int sw_pin = 2;   
int out_no = 0; //현재step // 다른부분 2

void setup() {
  Serial.begin(9600);              //통신속도
  pinMode(sw_pin, INPUT_PULLUP);
}

void shift(){
  Serial.println("button pressed");
  for(int n =0; n < 4; n++){
    leds[n].setValue(n == out_no);
  }
  out_no = (++out_no)% 4;
}

void loop() {
  boolean o_sw, n_sw;  // 같은 부분
  o_sw = digitalRead(sw_pin);   // 첫 번째 상태
  delay(10);
  n_sw = digitalRead(sw_pin);   // 두 번째 상태


    if(o_sw == OFF && n_sw == ON){ // 하강 edge인가? 물어보는 조건식 // 같은 부분
      shift();
    }
  }

  
//자바스크립트의 이벤트처리를 하는 콜백함수와 같은 원리로 
// 코드중복을 제거하기위해 콜백처리해 별도의 함수로 구성한 구조. 

//자바스크립트의 콜백함수 : 미리 메소드로 처리해둔 함수를 호출하여 사용이 필요한 함수에서 사용하는 이벤트 함수
