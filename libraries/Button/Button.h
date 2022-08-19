#pragma once

#include <Arduino.h>

//매개변수 없는 void 함수에 대한 포인터를 button_callback_t로 정의
typedef void (*button_callback_t)();
// void 리턴타입. 즉 리턴없고 매개변수 없는 함수
//리턴타입 함수명 () -> 함수구조 //button_callback_t 가 타입명.
//*포인터: 주소 지정한 형태의 함수에 대해 포인터. 매개변수와 리턴타입이 일치해야함

class Button{
protected:
  int pin;
  button_callback_t callback; //callback 함수에 대한 포인터
  // callback 변수명
public:
  Button(int pin);
  void setCallback(button_callback_t callback);
  int read();     // 현재 버튼의 상태를 리턴
  void check(); // 클릭 검사하고, 클릭됐으면 처리
};
