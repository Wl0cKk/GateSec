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
