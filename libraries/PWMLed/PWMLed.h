#pragma ONCE

#include <Arduino.h>
#include <Led.h>

class PWMLed: public Led { //상속
protected:
    int value;

public: // 여기의 2개를 cpp로 복사해서 기본 골격
    PWMLed(int pin, int value=0); // 초기값 int value=0  설정은 헤더파일에서만  지정 : 디폴트값이라서 생략가능
    void setValue(int value); 
};

//int value 가변저항에서 조절하는 전압량