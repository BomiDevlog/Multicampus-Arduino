#include "MqttCom.h"

// 생성자 - 가장 먼저 부모클래스 생성자(WifiMiniCom) 호출
MqttCom::MqttCom(int serial_bps, int lcd_addr) : 
    WifiMiniCom(serial_bps, lcd_addr), client(espClient) {
    topic = NULL;
    callback = NULL;
    server = NULL;

//랜덤하게 클라이언트 ID 배정
    randomSeed(analogRead(0));
    int r = random(300); // 0~300 사이의 랜덤한 정수값
    client_id = String("ESP8266Client") + r;
} 

// 초기화 메서드. 
void MqttCom::init(const char *ssid, const char *password, int no_lcd){
    WifiMiniCom::init(ssid, password); //부모클래스의 init호출-> wifi 연결 준비위해 아이디, 패스워드.
    if(no_lcd){
        WifiMiniCom::setNoLcd(); // LCD사용을 막아둠
    }
} 

// 서버 설정
void MqttCom::setServer(const char *server, const char *topic,
                    MQTT_CALLBACK_SIGNATURE){
    this->server = server;
    this->callback = callback; // MQTT_CALLBACK_SIGNATURE의 변수명 callback을 멤버변수로 지정.
    this->topic = topic;

    client.setServer(server, 1883);
    if(callback != NULL) {
        client.setCallback(callback);
    }
} 

// 재접속 처리
void MqttCom::reconnect(){
    while(!client.connected()){
        Serial.print("Attempting MQTT connecteion...");
        print(0, "try MQTT con...");
        if(client.connect(client_id.c_str())){ // 클라이언트 ID 중복 주의 // client_id.c_str() :  Sting -> char*
            Serial.println("connected");
            print(0, "MQTT connected");
            if(topic != NULL){ // 접속 성공하면 수신 신청
                client.subscribe(topic);
            }
        } else {
            char buf[17];
            sprintf(buf, "failed, rc=%d", client.state());
            Serial.print(buf);
            print(0, buf);
            Serial.println("try again in 5 seconds");
            print(1, "try again in 5 sec");
            delay(5000);
        }
    }
} 

// 운영
void MqttCom::run(){
    MiniCom::run(); // timer로 interval처리됨
    if (!client.connected()) {
        reconnect();
    }
    client.loop();
} //문자열 변환.
 
//publish(...) 오버로딩(다중정의) : 숫자->문자열 통신
void MqttCom::publish(const char *topic, const char *value){
    client.publish(topic, value);
}
void MqttCom::publish(const char *topic, int value){
    char msg[10];
    sprintf(msg, "%d", value); // 아두이노에서 실수%f 지원안됨. String타입으로 문자열.
    client.publish(topic, msg);
}
void MqttCom::publish(const char *topic, float value){
    String msg = "";
    msg += value;
    client.publish(topic, msg.c_str());
}