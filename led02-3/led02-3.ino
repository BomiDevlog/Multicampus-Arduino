//4개의 순차점멸 (LED pull up 연결)
//1초간격으로 불이 켜지는 과정을 
//배열을 통해 반복코드를 간소화해줌

const int led_pin [4] = {6,5,4,3} ; //LED 연결 핀 번호 
// {6,5,4,3} ,  {3,4,5,6} 할때 처리 방향이 다르다
const int led_out [4][4] = {
  {1, 0, 0, 0}, //led1만 on
  {0, 1, 0, 0}, //led2만 on
  {0, 0, 1, 0},  //led3만 on
  {0, 0, 0, 1}    //led4만 on
}; 
// 이차원 배열로 [step][각 step별 led의 값]

int out_no = 0; //현재 step : 출력값 출력 순서 번호 (0~3)


void setup() {
 for(int n=0; n < 4 ; n++ ){ //led4개에 대해 범위설정
  pinMode(led_pin[n], OUTPUT); //led_pin[n]번 핀모드 출력 설정
 }
}

void loop() { 
    
  for(int n=0; n<4; n++){
   digitalWrite(led_pin[n], led_out[out_no][n]);
  }

//여기를 개선 -> if문 안쓰고 똑같은 값을 가지도록 1줄로 바꾸기. (힌트: 나머지 연산자)
 //(out_no == 4)?  out_no =0 : out_no++;삼항연산자로 접근했었음. 지식인묻기
 out_no = (out_no +1) % 4;
  delay(1000);
}

//소프트웨어는 잘 짰는데 하드웨서에서 자주 하는 실수 -> 전선 연결 확인 특히 전원선 점검
