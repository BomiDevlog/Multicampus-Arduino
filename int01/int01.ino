//Switch 누를 때마다 LED on/off 점멸 (외부 Interrupt 사용)

void flash() {
  Serial.println("pressed"); // 확인용
}
void setup() {
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(2),
  flash, FALLING); 
  
  //외부 Interrupt 설정
  //2번pin에 Interrupt 붙임. FALLING감지되면 flash붙인다는 내용의 콜백함수
  //pinMode(INPUT)할 필요없음
  
  

}

void loop() {}
//기존에는 반복문에서 동작내용을 코드로 작성했지만  (소프트웨어적 방법)
//이번에는 Interrupt로 동작을 설정  (하드웨어적 방법)
