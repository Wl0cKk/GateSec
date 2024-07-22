#ifndef CONFIG_H
#define CONFIG_H

#define RED_LED 32
#define BLUE_LED 12
#define BUZZER_PIN 2

#define RST_PIN 4
#define SS_PIN 22

#define SSID "YOUR WIFI NAME"
#define PASSWORD "YOUR WIFI PASSWORD"
#define MAX_WIFI_RETRIES 30

const char* serverAddress = "SERVER ADDRESS SAME LIKE IN config.rb";
const int serverPort = 8000;

#define LEVEL 5

#endif