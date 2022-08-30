#pragma once

#include <WifiMiniCom.h>
#include <PubSubClient.h>


class MqttCom : public WifiMiniCom {
protected:
    const char *server; // MQTT 브로커 IP 주소
    String client_id;   // 클라이언트 (NodeMCU의 ID)
    WiFiClient espClient;
    PubSubClient client;


    const char *topic;  // subscribe 토픽명
    // void (*callback)(char*, unit8_t, unsigned int);
    MQTT_CALLBACK_SIGNATURE; // subscibe 콜백 함수 포인터, 변수명은 callback.
//MQTT_CALLBACK  =(broker주소, 토픽명, 콜백함수) 
//토픽명과 콜백함수는 subscribe할때만 설정. 디폴트는 NULL. 
//PubSubClient에서 define될때 변수명과 변수타입이 포함된 callback함수.(81번줄)

public:
    MqttCom(int serial_bps=115200, int lcd_addr=0x27); // 생성자
    void init(const char *ssid, const char *password, int no_lcd=false); // 초기
    void setServer(const char *server, const char *topic = NULL,
                    MQTT_CALLBACK_SIGNATURE = NULL); // 서버 설정
    void reconnect(); // 재접속 처리
    void run(); // 운영
    //publish(...) 오버로딩(다중정의) : 숫자->문자열 통신
    void publish(const char *topic, const char *value);
    void publish(const char *topic, int value);
    void publish(const char *topic, float value);
};