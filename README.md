# SSID Spammer for ESP32

A beacon frame generator firmware example for the `ESP32` using the `Arduino` framework and an object-oriented interface.

## Overview

This project implements a configurable `SSID` spammer capable of simulating multiple `Wi-Fi` networks simultaneously.

The firmware allows the user to:

- simulate open or `WPA2` protected networks
- transmit beacon frames continuously
- alternate automatically between `Wi-Fi` channels
- visualize the packet transmission rate on the serial monitor in real time

The codebase was reorganized into a small library-oriented structure to make the project easier to understand, maintain, and expand.

## Technical Details

| Category | Details |
| :-- | :-- |
| **Microcontroller** | `ESP32` |
| **Framework** | `Arduino / ESP-IDF` |
| **Language** | `C++` |
| **Compiler / IDE** | `Arduino IDE` |

## Features

- custom `SSID` transmission
- memory optimization using `PROGMEM` for string storage
- optional `WPA2` encryption simulation
- automatic channel hopping for broader visibility
- modular source organization with separate application logic and execution file

## Project Structure

```bash
├── examples/
│   └── usage.ino
├── include/
│   └── spammer.hpp
├── src/
│   └──spammer.cpp
└── README.md
```

## Modules

### [spammer.hpp](include/spammer.hpp)

Centralizes the library definitions and interface:

- class and attribute declarations
- parameter documentation
- encapsulation of internal variables

### [spammer.cpp](src/spammer.cpp)

Handles the application and `Wi-Fi` logic:

- hardware radio initialization
- `802.11` beacon frame construction and `MAC` address generation
- channel switching and timing control
- raw packet injection into the network

### [usage.ino](examples/usage.ino)

Handles the primary entry point:

- serial communication setup
- spammer object instantiation
- cyclic execution via the main loop

## Current Behavior

- the system chooses a random starting `Wi-Fi` channel
- beacon frames are broadcasted sequentially for each configured network
- the source `MAC` address is incrementally adjusted for each forged network
- the serial port outputs the amount of successfully sent packets per second

## Notes

This tool is intended strictly for educational and testing purposes. Utilizing this code to disrupt public networks or interfere with wireless communications without explicit authorization is illegal and unethical.

The default `SSID` list can be expanded or modified directly within the implementation file, provided each network name remains under the **32-character limit** and ends with a newline character.

## Author

[Daniel Arndt](https://github.com/DanielArndt0)