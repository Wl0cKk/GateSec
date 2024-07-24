#ifndef CALL_POINT_HPP
#define CALL_POINT_HPP

#define RED_LED 32
#define BLUE_LED 12
#define BUZZER_PIN 2
// access
void granted() {
    Serial.println("Granted");
    digitalWrite(BLUE_LED, HIGH);
    digitalWrite(RED_LED, LOW);
    tone(BUZZER_PIN, 1000, 1000);
    delay(5000);
    digitalWrite(BLUE_LED, LOW);
}

void denied() {
    Serial.println("Denied");
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
#endif