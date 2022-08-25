#include "MiniCom.h"

//생성자 초기화
MiniCom::MiniCom(long serial_bps, int lcd_addr)
    :serial_bps(serial_bps), lcd(lcd_addr, 16, 2) {
    no_lcd = false ;
}

// 초기화 관련
void MiniCom::init(){
    Serial.begin(serial_bps);
    if(!no_lcd){
        lcd.init();
        lcd.backlight();
    }
}

// 타이머 관련
int MiniCom::setInterval(unsigned long interval, timer_callback f) {
    return timer.setInterval(interval, f);
}

// 실행 관련
void MiniCom::run(){
    timer.run();
} 

//(출력행, 출력메시지)
//출력메시지 표현하는 방법2가지
//1) 문자열 포인터* (배열) : 포맷팅된 문자 출력
//2)String
void MiniCom::print(int row, const char *pMsg) {
    if(no_lcd) return;
    char buf[17];
    sprintf(buf, "%-16s", pMsg);
    lcd.setCursor(0, row);
    lcd.print(buf);
}

void MiniCom::print(int row, String title, int value) {
    if(no_lcd) return;
    String buf = title + value;
    print(row, buf.c_str());
}

//Java : String str = "abc" + 5 = "abc5"  // String으로 문자열 결합
//c++ : String str = "abc" + 5 [x] "abc"가 char*(문자에 대한 포인터)이기 때문.
// String str="abc" // 두줄나누면 가능
//str += 5 ; String으로 결합 가능.
//매개변수. char* -> String [o], String -> char* [x]
void MiniCom::print(int row, String title1, int value1, 
    String title2, int value2) {
    if(no_lcd) return;
    String buf = title1 + value1 + "," + title2 + value2;
    print(row, buf.c_str());
}

void MiniCom::print(int row, String title, double value) {
    if(no_lcd) return;
    String buf = title + value;
    print(row, buf.c_str());
}
void MiniCom::print(int row, String title1, double value1, 
String title2, double value2) {
    if(no_lcd) return;
    String buf = title1 + value1 + "," + title2 + value2;
    print(row, buf.c_str());
}



/*
사용시 간단하게 초기화 작업 가능
MiniCom com;

void setup(){
    com.init();
}
*/