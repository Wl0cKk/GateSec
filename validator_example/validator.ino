#include <WiFi.h>

#include "rfid_nfc.hpp"
#include "call_point.hpp"
#include "http_service.hpp"
#include "config.h"

void setup() {
    Serial.begin(115200);
    pinMode(RED_LED, OUTPUT);
    pinMode(BLUE_LED, OUTPUT);
    pinMode(BUZZER_PIN, OUTPUT);
    initRFID();
    connectToWiFi();
}

void loop() {
    String uid = getCardUID();
    if (!uid.isEmpty()) {
        Serial.println(uid);
        ( getResponse(uid, LEVEL) ? granted : denied )();
    }
    delay(200);
}

void connectToWiFi() {
    Serial.println("Connecting to WiFi...");
    WiFi.begin(SSID, PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
        delay(3000);
        Serial.println("Connecting...");
    }
    Serial.println("Connected to WiFi");
}
