//헤더파일
#pragma once
 // 1번만 include된다

#include <Arduino.h> //아두이노의 HIGH, LOW 등을 인식

class Led{
protected:
  int pin; // 연결할 핀 번호

public:
  Led(int pin);
  
  void on();
  void off();
  void setValue(int value); //변수에 의해 on/off가 되도록.
  int toggle(); //현재상태를 반전시키는 것 on <-> off
};
