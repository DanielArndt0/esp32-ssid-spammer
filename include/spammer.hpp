#ifndef SPAMMER_HPP
#define SPAMMER_HPP

#include <Arduino.h>
#include <WiFi.h>

extern "C" {
  #include "esp_wifi.h"
}

class spammer {
public:
    /**
     * @brief Constructor for the spammer class.
     * @param useWpa2 Enable WPA2 simulation for the beacon frames (default is false).
     */
    spammer(bool useWpa2 = false);

    /**
     * @brief Initializes the spammer, setting up WiFi and generating the base MAC address.
     */
    void begin();

    /**
     * @brief Main loop update. Must be called repeatedly in the Arduino loop().
     * Handles channel hopping and sending beacon frames continuously.
     */
    void update();

private:
    bool _useWpa2;
    uint8_t _channels[1]; // Array of target channels
    uint8_t _channelIndex;
    uint8_t _currentWifiChannel;
    uint8_t _macAddress[6];
    char _emptySsidBuffer[32];

    uint32_t _lastAttackTime;
    uint32_t _lastPacketRateTime;
    uint32_t _packetCounter;
    uint32_t _packetSize;

    static uint8_t _beaconPacket[109];

    /**
     * @brief Switches the WiFi transmission to the next available channel.
     */
    void switchToNextChannel();

    /**
     * @brief Generates a random initial MAC address for the packets.
     */
    void generateRandomMac();
};

#endif // SPAMMER_HPP
