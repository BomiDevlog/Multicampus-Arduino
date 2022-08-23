
#include "PWMLed.h"

PWMLed::PWMLed(int pin, int value): Led(pin), value(value) { // 부모 생성자 호출 // int value 초기값은 헤더파일에서 지정하기때문에 여기선 지정하면 에러
    analogWrite(pin, value);
}

void PWMLed::setValue(int value) { // 오버라이딩(재정의)
    this->value = value;
    analogWrite(pin,value);	 //함수.
}

/* Java : 부모 생성자 호출 방법

자식클래스 생성자 
: 제일 먼저 할 일은 부모 생성자 호출 super()
생략하면 자동으로 들어감.

(cf) new 인스턴스 생성 extends 클래스 상속

c++ : 
부모생성자를 호출하는게 객체지향언어의 공통특징.
c++의 경우 부모생성자를 호출하려면
부모클래스명을 그대로 쓰고 매개변수를 입력해준다.

부모클래스에 의해 pin설정,pinMode가 이루어지고
자신의 멤버만 설정해준 상태.

*/