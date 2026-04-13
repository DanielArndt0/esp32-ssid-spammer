#include "spammer.hpp"

// List of SSIDs stored in flash memory to save RAM
// Max 32 characters per SSID, separated by \n
const char targetSSIDs[] PROGMEM = {
  "c6Xyu1%R%tBet4qFQ!66gTJbauEqtaw\n"
  "0el*HbYdS!e*7UlQDa*Th1VBWQ5ogHp\n"
  "$zE#*9zUeITOGxt!@rIDWMT4lQ5w4^!\n"
  "TSMU3rXHT#8WkeD8KwJ%e6KWp3MTvqt\n"
  "PS7dk7u8W1RXTf#pNdKDnJFUZNqT!pB\n"
  "50!xw27tJjl7RpsAYsVbiHC%VBByACL\n"
  "pmiwHrfdPj&s*zXVK3&j2R56JL&klXP\n"
  "pD2X!Sjaepp4riFsPW5LHccf*$3%GQz\n"
  "i2Rt1qFcjeQN@8PVLXlfVPSd^U3NVIm\n"
  "%E^we!aDmfikzR4Zq#%ug!ChSvE2ieD\n"
  "S!0HjrbWhPuCfAG1a%Fvgx6@^zVzpTy\n"
  "Fd7H&Yuao&@gxhvKbw8VlmSOWHafUzG\n"
  "rmNMYvJMd$*2j9!ob#X9QMP6EAv#Y6p\n"
  "ky3x0GNQhploIXSvAGF@ilrP$OB!jXY\n"
  "qJZ1jUz!0t*ctNR!0lQw40a$SvhhWV1\n"
  "tV#OSjg!PyOc!yGuvpD@sy1PuMW@eJD\n"
  "vsY$gRwC8ojh@6RC%gsLXT*SAxX4@%5\n"
  "7hRYJtXAmTRj!h2m6*VSoFf0tkGhJVu\n"
  "sUftTT#kkRtx3O&A3^bjDsX3tQRbPYX\n"
  "ijisdioahiofhasihe2i13ioh1as992\n"
  "EwzOHje*Z5s&ftDG2lf4w&pB2vDVI4u\n"
  "OVEAKltApxmz5ozj9#u^Asok*wYeTj8\n"
  "ZN5Z&@D68l%v5%@cxUv5tDEgRf4*n*k\n"
  "zu5xMAx5lK&*jstrX40#fp2jWdyzVox\n"
  "TTI5bSSk*xsws*#NN7oHhjHN^eiVa%M\n"
  "myow7acI%*hano9UjpG@Db!3#dKb7F&\n"
  "8agu!VIuUBEO2*EdfH4vDz@$rs4To*j\n"
  "U@C&lth@ZgO%*zB2AD0rdn$4B4bjV2z\n"
  "6$MLLGzrK%6RCk6%EQJ2rpIPLe@w^gI\n"
  "qXhW#Tz20HbljCy5nGcTWrhhln72kx4\n"
  "KBgldjuIs7jDiS@LIR!aaBOeyr4pc7J\n"
  "C0h@fmOiBhHZX&bk5b0Uc80O7@JVflx\n"
  "YfeEK4iCV^MqtDDC1^@#GMiLl!X2eyf\n"
  "S9kC*UKb$86jQi*ne!jLG6byYWC9X@O\n"
  "xmcjYNB18OtFScjdBnw9$yT%1GOpnbD\n"
  "y*0AjXud@E@pQEGD6dZq$0Vt4OxW$2f\n"
  "0bX%6l!SzmNjg9FYpgKgBQ4gfQRTWYU\n"
  "gozkYpnrRTuTTHXbJKl#flfmB*87EgD\n"
  "wpovP$C51sVS#PDxw56NKyAZZ!UPd$*\n"
  "pSN6YGvakIZwgUi#JNyx&FFaFq@W^%s\n"
  "LgVNK#&gE7sz2B1FGr0vBEguR%7Citw\n"
  "DaTGOj45NudUzMA^Rg0Q*eAOFuLh@f3\n"
  "YLyi9Cu7jHoK$#CIwXk8XCdVJEa^WS2\n"
};

// Standard Beacon Frame definition (109 bytes)
uint8_t spammer::_beaconPacket[109] = {
  /* 0 - 3  */ 0x80, 0x00, 0x00, 0x00,             // Type/Subtype: Management beacon frame
  /* 4 - 9  */ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // Destination: Broadcast
  /* 10 - 15 */ 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, // Source MAC Address
  /* 16 - 21 */ 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, // BSSID
  /* 22 - 23 */ 0x00, 0x00,                         // Sequence number (handled by SDK)
  /* 24 - 31 */ 0x83, 0x51, 0xf7, 0x8f, 0x0f, 0x00, 0x00, 0x00, // Timestamp
  /* 32 - 33 */ 0xe8, 0x03,                         // Beacon Interval (approx 1s)
  /* 34 - 35 */ 0x31, 0x00,                         // Capabilities Information
  /* 36 - 37 */ 0x00, 0x20,                         // Tag SSID: length 32
  /* 38 - 69 */ 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
                0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
                0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
                0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, // Blank space for SSID
  /* 70 - 71 */ 0x01, 0x08,                         // Supported Rates Tag
  /* 72 - 79 */ 0x82, 0x84, 0x8b, 0x96, 0x24, 0x30, 0x48, 0x6c, // Transmission rates
  /* 80 - 82 */ 0x03, 0x01, 0x01,                   // Current Channel Tag
  /* 83 - 108*/ 0x30, 0x18, 0x01, 0x00, 0x00, 0x0f, 0xac, 0x02, // RSN Info
                0x02, 0x00, 0x00, 0x0f, 0xac, 0x04, 0x00, 0x0f, 
                0xac, 0x04, 0x01, 0x00, 0x00, 0x0f, 0xac, 0x02, 
                0x00, 0x00 
};

spammer::spammer(bool useWpa2) {
    _useWpa2 = useWpa2;
    _channelIndex = 0;
    _currentWifiChannel = 1;
    _lastAttackTime = 0;
    _lastPacketRateTime = 0;
    _packetCounter = 0;
    _packetSize = sizeof(_beaconPacket);
    _channels[0] = 1; // Default to channel 1 initially
}

void spammer::begin() {
    // Seed the random generator
    randomSeed(analogRead(0) + 1);
    
    // Choose a random starting channel between 1 and 14
    _channels[0] = random(1, 14);

    // Initialize the empty SSID buffer with spaces
    for (int i = 0; i < 32; i++) {
        _emptySsidBuffer[i] = ' ';
    }

    // Adjust packet capabilities based on WPA2 setting
    if (_useWpa2) {
        _beaconPacket[34] = 0x31;
    } else {
        _beaconPacket[34] = 0x21;
        _packetSize -= 26; // Remove the RSN information from the end
    }

    generateRandomMac();

    // Set WiFi to Station mode
    WiFi.mode(WIFI_MODE_STA);
    
    // Set the initial WiFi channel
    esp_wifi_set_channel(_channels[0], WIFI_SECOND_CHAN_NONE);
}

void spammer::switchToNextChannel() {
    if (sizeof(_channels) < 2) return;

    uint8_t ch = _channels[_channelIndex];

    _channelIndex++;
    if (_channelIndex >= sizeof(_channels)) {
        _channelIndex = 0;
    }

    if (ch != _currentWifiChannel && ch >= 1 && ch <= 14) {
        _currentWifiChannel = ch;
        esp_wifi_set_channel(_currentWifiChannel, WIFI_SECOND_CHAN_NONE);
    }
}

void spammer::generateRandomMac() {
    for (int i = 0; i < 6; i++) {
        _macAddress[i] = random(256);
    }
}

void spammer::update() {
    uint32_t currentTime = millis();

    // Spam SSIDs every 100ms
    if (currentTime - _lastAttackTime > 100) {
        _lastAttackTime = currentTime;

        int i = 0;
        int j = 0;
        int currentSsidNumber = 1;
        char tempChar;
        int totalSsidsLength = strlen_P(targetSSIDs);

        switchToNextChannel();

        // Iterate over all SSIDs
        while (i < totalSsidsLength) {
            j = 0;
            do {
                tempChar = pgm_read_byte(targetSSIDs + i + j);
                j++;
            } while (tempChar != '\n' && j <= 32 && i + j < totalSsidsLength);

            uint8_t ssidLength = j - 1;

            // Incrementally change MAC address for each SSID
            _macAddress[5] = currentSsidNumber;
            currentSsidNumber++;

            // Inject the MAC address into the beacon frame (Source & BSSID)
            memcpy(&_beaconPacket[10], _macAddress, 6);
            memcpy(&_beaconPacket[16], _macAddress, 6);

            // Clear the SSID field
            memcpy(&_beaconPacket[38], _emptySsidBuffer, 32);

            // Copy the new SSID into the beacon frame
            memcpy_P(&_beaconPacket[38], &targetSSIDs[i], ssidLength);

            // Set the appropriate channel in the beacon frame
            _beaconPacket[82] = _currentWifiChannel;

            // Transmit the packet 3 times for better reliability
            for (int k = 0; k < 3; k++) {
                bool isSuccess = (esp_wifi_80211_tx(ESP_IF_WIFI_STA, _beaconPacket, _packetSize, 0) == 0);
                if (isSuccess) {
                    _packetCounter++;
                }
                delay(2);
            }

            i += j; // Move to the next SSID string
        }
    }

    // Print transmission rate every 3 seconds
    if (currentTime - _lastPacketRateTime > 3000) {
        _lastPacketRateTime = currentTime;
        Serial.print(_packetCounter);
        Serial.println(" packets/s");
        _packetCounter = 0;
    }
}
