#pragma once

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <SimpleTimer.h>

class MiniCom {
protected:
    long serial_bps;        // Serial 속도
    LiquidCrystal_I2C lcd;  // 16x2 LCD
    SimpleTimer timer;      // 타이머
    bool no_lcd;            // LCD 사용 여부

public:
    // 운영 관련
    MiniCom(long serial_bps=115200, int lcd_addr=0x27);
    void setNoLcd() { no_lcd = true;}; 
    void init(); // 초기화
    void run(); // 실행

    // 타이머 관련
    int setInterval(unsigned long interval, timer_callback f);
    SimpleTimer& getTimer() { return timer; }
    //반환타입 SimpleTimer& : & 참조변수

    // LCD 출력 지원 메서드 (helper 함수) -오버로드 (다중정의)
    void print(int row, const char *pMsg); //문자에 대한 포인터로 전달
    void print(int row, String title, int value);
    void print(int row, String title1, int value1, String title2, int value2);
    void print(int row, String title, double value);
    void print(int row, String title1, double value1, 
                String title2, double value2);
};