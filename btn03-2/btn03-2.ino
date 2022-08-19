//Switch 누르면 4개순차점멸 LED on/off (Edge Triger)
//스위치를 누를때마다 다음 불이 켜지는 형식으로 순차점멸

#include <Led.h>

#define OFF 1   
#define ON 0    

// 점등하는 led개수가 1개일때와 여러개일 때의 공통점과 다른점을 찾아보면
//그래서 공통 부분은 라이브러리화시켜서 불러서 쓰는게 유용하다
Led leds [4]={ Led(6), Led(5), Led(4), Led(3)};   //다른 부분 1
         
const int sw_pin = 2;   
int out_no = 0; //현재step // 다른부분 2


void setup() {
  Serial.begin(9600);              //통신속도
  pinMode(sw_pin, INPUT_PULLUP);
}

void loop() {
  boolean o_sw, n_sw;  // 같은 부분
  o_sw = digitalRead(sw_pin);   // 첫 번째 상태
  delay(10);
  n_sw = digitalRead(sw_pin);   // 두 번째 상태


    if(o_sw == OFF && n_sw == ON){ // 하강 edge인가? 물어보는 조건식 // 같은 부분
      Serial.println("button pressed");
      for(int n=0; n<4; n++){ // 다른 부분 3 => 버튼 눌렀을 때 뭘해야하는 지 if문 내부가 달라짐
       leds[n].setValue (n == out_no);
      }
      out_no = (++out_no) %4;
    }
    
  }

  
