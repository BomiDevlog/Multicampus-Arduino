#include <Button.h>
#include<Led.h>
//버튼을 누르면 차례로 순차 점등 (소등기능없음)

Led leds[4]= {Led(6), Led(5), Led(4), Led(3)};
Button btn(2);

int out_no = 0;

void move_led() {
  for(int n= 0; n < 4; n++){
    leds[n].setValue(n==out_no);
  }
  out_no = (++out_no)%4; // 다음 출력 패턴 번호를 설정
}

void setup() {
   btn.setCallback(move_led);
}


void loop() {
   btn.check();  //polling

}
