#ifndef BROADCAST_HPP
#define BROADCAST_HPP

#define PORT 10000
#define MESSAGE "for example where the validator is located"

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

#endif
