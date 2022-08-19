#include <Button.h>
#include<Led.h>

Led led(3);
Button btn(2);

//누르면 켜고/끄고 반응

void toggle(){
  led.toggle();
}//콜백함수 


void setup() {
   Serial.begin(9600);
   btn.setCallback(toggle);
//매개변수 없고 리턴타입없는 구조가 같음 = button_callback_t함수를 포인터해서 콜백할 수 있음
//함수명은 주소값이다. 포인터변수 callback으로 함수명을 받아줌. 
//실제로는 toggle함수의 시작주소가 전달되는것
}

//함수를 별도로 만듬으로서 계속해서 재사용할수있고.  다른 용도로 전환할때 프로그램수정없이 함수만 바꿔주면된다

void loop() {
   btn.check();

}
