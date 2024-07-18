#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <MFRC522.h>
#include "config.h"

MFRC522 mfrc522(SS_PIN, RST_PIN);

void setup() {
    Serial.begin(115200);
    pinMode(RED_LED, OUTPUT);
    pinMode(BLUE_LED, OUTPUT);
    pinMode(BUZZER_PIN, OUTPUT);

    connectToWiFi();

    SPI.begin();
    mfrc522.PCD_Init();
}

void loop() {
    if (checkRFIDCard()) {
        String rfidData = readRFIDData();
        if (!rfidData.isEmpty()) {
            if (sendRequestAndProcessResponse(rfidData)) {
                digitalWrite(BLUE_LED, HIGH);
                digitalWrite(RED_LED, LOW);
                tone(BUZZER_PIN, 1000, 1000);
                delay(5000);
                digitalWrite(BLUE_LED, LOW);
            } else {
                digitalWrite(BLUE_LED, LOW);
                for (int i = 0; i < 2; i++) {
                    digitalWrite(RED_LED, HIGH);
                    tone(BUZZER_PIN, 1000, 150);
                    delay(250);
                    noTone(BUZZER_PIN);
                    digitalWrite(RED_LED, LOW);
                    delay(250);
                }
            }
        }
    }
}

bool checkRFIDCard() {
    if ( ! mfrc522.PICC_IsNewCardPresent()) {
        return false;
    }
    return mfrc522.PICC_ReadCardSerial();
}

String readRFIDData() {
    String rfidData = "";
    for (byte i = 0; i < mfrc522.uid.size; i++) {
        rfidData += String(mfrc522.uid.uidByte[i] < 0x10 ? "0" : "");
        rfidData += String(mfrc522.uid.uidByte[i], HEX);
    }
    return rfidData;
}

bool sendRequestAndProcessResponse(String rfidData) {
    String url = "http://" + String(serverAddress) + ":" + String(serverPort) + "/auth?id=" + rfidData + "&lvl=" + String(LEVEL);

    HTTPClient http;
    if (WiFi.status() != WL_CONNECTED) {
        Serial.println("WiFi not connected");
        return false;
    }

    http.begin(url);
    int httpCode = http.GET();
    if (httpCode > 0) {
        DynamicJsonDocument doc(200);
        deserializeJson(doc, http.getString());
        bool access = doc["access"];
        http.end();
        if (access) {
            Serial.println("Access granted!");
        } else {
            Serial.println("Access denied!");
        }
        return access;
    } else {
        Serial.print("HTTP Request failed with error code: ");
        Serial.println(httpCode);
        http.end();
        return false;
    }
}

void connectToWiFi() {
    Serial.println("Connecting to WiFi...");
    WiFi.begin(SSID, PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting...");
    }
    Serial.println("Connected to WiFi");
}
