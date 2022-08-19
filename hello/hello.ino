void setup() {
  Serial.begin(9600); // 시리얼 통신 시작(속도: 9600 bps)
  Serial.print("hello, Arduino"); //시리얼 모니터에 "hello, Arduino"를 출력
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("hello, Arduino ===================="); 

}
