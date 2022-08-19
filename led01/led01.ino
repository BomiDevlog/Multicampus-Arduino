void setup() {
  pinMode(4,OUTPUT); //LED 출력
}

void loop() {
  digitalWrite(4, HIGH);  //pullup방식 OFF
  delay(500);             //0.001초 * 500 => 0.5초 유지
  digitalWrite(4, LOW);   //ON
  delay(500);
}
