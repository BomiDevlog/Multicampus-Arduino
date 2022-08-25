#include "Ultra.h"

    Ultra::Ultra(int echo, int trig) : echo(echo), trig(trig){
        pinMode(echo, INPUT);
        pinMode(trig, OUTPUT);
    }
    int Ultra::getDistance(){
        digitalWrite(trig, HIGH);
        delayMicroseconds(10);
        digitalWrite(trig, LOW);

        // echo 핀 입력으로부터 거리를 cm 단위로 계산
        // y = 0.034*x/2 = 0/017*x cm => 실수 계산
        int distance = pulseIn(echo, HIGH) / 58; 
        return distance;
    }