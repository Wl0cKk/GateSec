#include <SPI.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#include <MFRC522.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

#include "rfid_nfc.hpp"
#include "broadcast.hpp"
#include "call_point.hpp"
#include "http_service.hpp"

#include "config.h"

TaskHandle_t udpTask = NULL;

void setup() {
    Serial.begin(115200);
    pinMode(RED_LED, OUTPUT);
    pinMode(BLUE_LED, OUTPUT);
    pinMode(BUZZER_PIN, OUTPUT);
    initRFID();
    connectToWiFi();
    xTaskCreatePinnedToCore(listenForUDPMessageTask, "UDP Listener", 10000, NULL, 1, &udpTask, 1);
}

void loop() {
    if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()){
        String uid = getCardUID();
        mfrc522.PICC_HaltA();
        Serial.println(uid);
        ( getResponse(uid, LEVEL) ? granted : denied )();
    }
    vTaskDelay(pdMS_TO_TICKS(200));
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
