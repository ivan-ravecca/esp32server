# ESP32-Arduino AC Line Monitor

This project implements a dual AC line monitoring system using an Arduino UNO for sensing and an ESP32 for internet connectivity. The system reports AC line status (energized/de-energized) with timestamps, voltage readings, and alarm notifications.

## System Overview

The project consists of two main components:

Arduino UNO - Interfaces with AC voltage sensors and provides basic monitoring
ESP32 - Acts as a gateway with WiFi connectivity, NTP time sync, and communication with UNO

## Getting Started

### Prerequisites

- Arduino IDE installed
- ESP32 board support installed in Arduino IDE
- Arduino UNO board
- ESP32 development board
- USB cables for programming and debugging
- IFTTT account for notifications and data logging

### Required Components

- Arduino UNO microcontroller
- ESP32 development board
- Active buzzer module
- Jumper wires for connections

### Connections

The Arduino UNO uses Software Serial to communicate with the ESP32:

- UNO pin 2 (RX) → ESP32 TX (pin 17)
- UNO pin 3 (TX) → ESP32 RX (pin 16)
- Common ground between devices

### Installation

1. Clone or download this repository
2. Open each project in the Arduino IDE:

   - Upload the ESP32 code to your ESP32 board
   - Upload the UNO code to your Arduino UNO

3. Configure WiFi credentials in the ESP32 WiFiComp.cpp file
4. Set up IFTTT webhooks and update the key in Ifttt.cpp file
5. Connect the hardware according to the wiring diagrams

## Project Structure

```
/
├── Reading/
│   ├── Reading.ino          # Main ESP32 application
│   ├── WiFiComp.h/.cpp      # WiFi connection component
│   ├── TimeComp.h/.cpp      # NTP time synchronization component
│   ├── SerialComp.h/.cpp    # Serial communication component
│   ├── CommandHandler.h/.cpp # Command processing component
│   ├── Ifttt.h/.cpp          # IFTTT webhook integration component
│   └── README.md
└── docs/
    └── wiring_diagram.png TBD
```

## Communication Protocol

The system uses a simple text-based protocol over Serial:
Commands from UNO to ESP32:

1. GET_CURRENT_TIME - Request current time from ESP32
2. SENSOR_UPDATE,ID,STATUS,VOLTAGE,REPEATED_ALARM,DURATION_MINUTES
   - Examples:
     - SENSOR_UPDATE,A,1,217.30,0,0 (Sensor A, energized, 217.30V, new alarm, no duration)
     - SENSOR_UPDATE,B,0,0.25,1,15 (Sensor B, de-energized, 0.25V, repeated alarm, 15 minutes duration)

Responses from ESP32 to UNO:

1. TIME:[timestamp] - Current time in YYYY-MM-DD HH:MM:SS format
2. ACK,[sensorID] - Acknowledgment of sensor update
3. ERROR:[message] - Error message

## IFTTT Integration

The ESP32 sends data to IFTTT via webhooks in two ways:

1. **Data Logging** (event: `sensor_data`)

   - Sends all sensor updates to Google Sheets for logging
   - Format:
     - Value1: "Bomba [SensorID] esta [Status]"
     - Value2: Voltage reading
     - Value3: Duration in minutes (0 if not applicable)

2. **Alert Notifications** (event: `sensor_alert`)
   - Sends mobile notifications for repeated alarms
   - Format:
     - Value1: Alert message with sensor details
     - Value2: Current timestamp

### Setting up IFTTT

1. Create an IFTTT account at [ifttt.com](https://ifttt.com)
2. Create a new applet with webhook as the trigger
3. Set up two different webhook events:
   - "sensor_data" for Google Sheets logging
   - "sensor_alert" for mobile notifications
4. Get your webhook key from the IFTTT Webhooks service
5. Update the `ifttt_key` in the Ifttt.cpp file with your key

## Contributing

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/improvement`)
3. Commit your changes (`git commit -am 'Add new feature'`)
4. Push to the branch (`git push origin feature/improvement`)
5. Open a Pull Request with detailed description
