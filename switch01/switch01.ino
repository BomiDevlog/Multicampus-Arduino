#include <Led.h>
Led led(3);
const int BTN = 2;

void setup() {
  pinMode(BTN, INPUT); // 스위치는 INPUT
}

void loop() {
  int value = digitalRead(BTN);
  led.setValue(value); 
  
  //pull up방식이니 평상시에는 HIGH(1) 
  //그래서 led는 켜져있고 버튼을 누르며 꺼짐

}
