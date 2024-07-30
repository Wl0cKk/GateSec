#ifndef BROADCAST_HPP
#define BROADCAST_HPP

#define PORT 10000 // port to listen and send
#define MESSAGE "Second floor" // place example
#define SECRET_HASH "57316fae0606a3caa46f1acd8163e74f1070f454" // secret.dat SHA1 key

WiFiUDP UDP;

void sendMessageToUDP() {
    DynamicJsonDocument doc(256);
    doc["ip"] = WiFi.localIP().toString();
    doc["note"] = MESSAGE;
    char buffer[256];
    size_t n = serializeJson(doc, buffer);
    uint8_t udpBuffer[256];
    memcpy(udpBuffer, buffer, n);
    UDP.beginPacket(IPAddress(255, 255, 255, 255), PORT);
    UDP.write(udpBuffer, n);
    UDP.endPacket();
    Serial.println("Message sent to UDP");
}

void listenForUDPMessageTask(void *pvParameters) {
    Serial.println("Listening for UDP packets on port 10000");
    UDP.begin(PORT);
    while (true) {
        int packetSize = UDP.parsePacket();
        if (packetSize) {
            char incomingPacket[256];
            int len = UDP.read(incomingPacket, 255);
            if (len > 0) {
                incomingPacket[len] = '\0';
            }
            Serial.printf("Received packet: %s\n", incomingPacket);
            StaticJsonDocument<256> doc;
            const char* auth = doc["auth"];
            if (strcmp(auth, SECRET_HASH) == 0) {
                Serial.println("Authorization request! Sending response...");
                sendMessageToUDP();
            } else {
                Serial.println("Auth failed");
            }
        }
        vTaskDelay(pdMS_TO_TICKS(80));
    }
}

#endif
