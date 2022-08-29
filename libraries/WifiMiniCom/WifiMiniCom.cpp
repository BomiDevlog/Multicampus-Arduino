#include "WifiMiniCom.h"

WifiMiniCom::WifiMiniCom(int serial_bps, int lcd_addr)
    : MiniCom(serial_bps, lcd_addr) {
}

/*
자식클래스에서 가장 먼저 해야할 일은  
부모클래스 호출.
java => super()
c++ => : MiniCom
*/

void WifiMiniCom::init(const char *ssid, const char *password) {
    MiniCom::init();
    WiFi.begin(ssid, password); // 비밀번호가 없는 경우 NULL
    print(0, "try to connect");
    Serial.println();
    while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    }
    print(0, "WiFi connected");
    print(1, WiFi.localIP().toString().c_str());
    Serial.println();
    Serial.println(WiFi.localIP());
}

