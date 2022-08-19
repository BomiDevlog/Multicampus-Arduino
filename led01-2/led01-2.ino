//blink program, pulldown방식(풀다운이 더 직관적이라서 앞으로 풀다운으로 진행할 것)
const int led = 3; 
int state = 0; //0이면 false

void setup() {
  Serial.begin(115200);       // 통신 속도 설정
  Serial.print("state: ");    //print 제약 : 1개의 값만 출력. 콤마(,)로 연결불가
  Serial.println(state);       // 초기 상태 출력
  //파스칼표기법을 보고 Serial이 클래스명이구나- 파악할 수 있다.
  pinMode(led,OUTPUT);  // 1.핀번호 설정
}

//시리얼모니터는 개발자가 상태를 확인하기 위해서 사용. => 디버깅 용도.

void loop() {
  digitalWrite(led, state);  // 0 => false => 0v 
  delay(1000);           
  state = !state;            // true (1) => high(5v) // toggle : 현재의 반대값을 만드는 것.

  Serial.print("state: ");    // 상태 출력
  Serial.println(state); 
}
