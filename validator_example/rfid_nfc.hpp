#ifndef RFID_NFC_HPP
#define RFID_NFC_HPP

#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 22
#define RST_PIN 4

MFRC522 mfrc522(SS_PIN, RST_PIN);

String getCardUID() {
    String uidStr = "";
    if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
        for (byte i = 0; i < mfrc522.uid.size; i++) {
            uidStr += String(mfrc522.uid.uidByte[i] < 0x10 ? "0" : "");
            uidStr += String(mfrc522.uid.uidByte[i], HEX);
        }
        mfrc522.PICC_HaltA();
    }
    return uidStr;
}

void initRFID() {
    SPI.begin();
    mfrc522.PCD_Init();
}

#endif
