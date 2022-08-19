#include "Led.h" // 꺽쇄가 아니라 큰따옴표로 include
//파일을 어디서 찾을 것인지 경로가 달라짐
//<-->는 라이브러리 디렉토리에서 찾음 
//"--" 현재폴더에서 찾고 없으면 라이브러리 디렉터리에서 찾음

//컨트롤 f -> ;을 {}로 바꿈
//함수명앞에 정의된 위치를 ::스코프연산자로 표시해줌 헤더파일의 클래스명 Led를 붙여주어 메서드로 인식. 이걸안하면 그냥 함수가됨.
//생성자는 멤버변수 초기화가 역할. 멤버변수초기화리스트를 이용
  //setup에서 하던 초기화작업을 클래스의 생성자에서 진행한다.
  Led::Led(int pin): pin(pin){
    pinMode(pin, OUTPUT);  
  } 
  
  void Led::on(){
    digitalWrite(pin, HIGH); //멤버변수pin이니 몇번인지 신경쓸 필요 없다
  }
  
  void Led::off(){
    digitalWrite(pin, LOW);  //멤버변수pin이니 몇번인지 신경쓸 필요 없다
  }
  
  void Led::setValue(int value){
    digitalWrite(pin,value);
  } 
  
  int Led::toggle(){
    int v = !digitalRead(pin); // wirte권한(OUTPUT)있으면 read가능, 그러나 read권한이 write은 아님,  INPUT은 write불가.
    digitalWrite(pin, v);
    return v;  
  } 
