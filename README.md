___
# GateSec
___
## Wi-Fi access control system, unlocking by NFC 13.56 MHz and reconciliation of records in remote SQLite
___
## SQLite sec.db 

| card_id       | user_info     |access_lvl|
| ------------- |:-------------:|:--------:|
| TEXT          | TEXT          |INTEGER   |

___

### Move examples into right destination
```bash
  mv sec_example.db sec.db
  mv config_example.rb config.rb
  mv validator_example/* validator/ 
```
#### Change parameters in _config.h_ _config.rb_ to yours.

#### Used requirements:
- **MFRC522.h** `v1.2.1`
- **WiFi.h**
- **ArduinoJson.h** `v7.1.0` 
- **HTTPClient.h** `v2.2.0`

#### Server requirements:
```ruby
bundle install
```
![image](https://github.com/user-attachments/assets/dc3a9e8c-ce4d-4ce4-823f-20b9c84ae469)

| RED LED       | NodeMCU ESP32 DEVKITv1  | 
|:-------------:|:-----------------------:|
| cathode        | GND                    |
| anode          | D12                    |

| BLUE LED       | NodeMCU ESP32 DEVKITv1 | 
|:--------------:|:----------------------:|
| cathode         | GND                   |
| anode           | D32                   |

| BUZZER        | NodeMCU ESP32 DEVKITv1  | 
|:-------------:|:-----------------------:|
| -             | GND                     |
| +             | D2                      |

| RFID-RC522    | NodeMCU ESP32 DEVKITv1  | 
|:-------------:|:-----------------------:|
| SDA           | D22                     |
| SCK           | D18                     |
| MOSI          | D23                     |
| MISO          | D19                     |
| IRQ           | empty                   |
| GND           | GND                     |
| RST           | D4                      |
| 3.3V          | 3V3                     |

| TP 4056       | NodeMCU ESP32 DEVKITv1  | 
|:-------------:|:-----------------------:|
| USB +         | VIN (5V)                |
| USB -         | GND                     |
