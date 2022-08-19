#include "Button.h"

Button::Button(int pin) : pin(pin){ //멤버초기화리스트로 초기화
  pinMode(pin, INPUT_PULLUP); //생성자에서 핀모드 설정
  callback = NULL; //콜백함수를 NULL로 초기화
}

void Button::setCallback(button_callback_t callback){
  this->callback = callback;
}

int Button::read(){ // 현재 버튼의 상태를 읽음
  return !digitalRead(pin); 
}     
//pullup연결이지만 논리적해석은 pulldown이 되도록 !논리부정. 
//즉 누르면 HIGH 떼면 LOW를 리턴 

void Button::check(){ // 클릭 검사하고, 클릭됐으면 처리
  boolean o_sw, n_sw;  
  o_sw = read();  // 첫 번째 상태
  delay(10);
  n_sw = read();  // 두 번째 상태   

  if(o_sw == 0 && n_sw == 1){ // 하강 edge인지 물어보는 조건식 ()
    //Serial.println("button pressed"); // 확인용.
    if(callback != NULL){
      callback();
    }//NULL 이면 NullPointerException발생하기에 안전하게 NULL 아닐때로 조건
  }
  
} 
