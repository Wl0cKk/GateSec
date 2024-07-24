#ifndef HTTP_SERVICE_HPP
#define HTTP_SERVICE_HPP

#include <HTTPClient.h>
#include <ArduinoJson.h>

#define SERVER_ADDRESS "YOUR SERVER IP (same as in config.rb)"
#define SERVER_PORT    8000 // YOUR SERVER PORT (same as in config.rb)

bool getResponse(String uid, int level) {
    String url = "http://" + String(SERVER_ADDRESS) + ":" + String(SERVER_PORT) + "/auth?id=" + uid + "&lvl=" + String(level);

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
        return access;
    } else {
        Serial.print("HTTP Request failed with error code: ");
        Serial.println(httpCode);
        http.end();
    }
    return false;
}

#endif