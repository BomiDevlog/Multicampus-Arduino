//led 4개 순차점멸
#include <Led.h>
//#include "Led.h"만 쓰고 컴파일하니 에러남. 현재폴더에 없기때문!
//여러프로그램에서 사용할 수 있도록 라이브러리화
//문서-Arduino-libraries폴더에 클래스명과 같은 Led폴더를 만들어 헤더파일류를 이동시킴

Led leds[4] = { Led(6), Led(5),Led(4),Led(3) }; // 작동하는지 보려고 순서를 바꿈
//int로 핀번호를 표시하는 것이 아니라 Led객체를 배열의 element로 넣어줌. 

int out_no = 0; //현재 step : 출력 순서 번호 0~3

void setup() {
}

void loop() { // if문 쓰지말고 코드 수정 -> setValue사용

  for(int n=0; n<4; n++){
    leds[n].setValue(n == out_no); // 이게 true 면 켜지고 false면 꺼짐
  }
  out_no = (++out_no) % 4;
  delay(1000);

}
