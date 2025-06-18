#include "SerialComp.h"

namespace SerialComp
{
    void setup()
    {
        Serial.begin(SERIAL_BAUD);
        Serial2.begin(9600, SERIAL_8N1, RXp2, TXp2);

        // Wait for serial to initialize
        delay(1000);
        Serial.println("Serial communication initialized");
    }

    bool commandAvailable()
    {
        return Serial2.available();
    }

    String readCommand()
    {
        String command = Serial2.readStringUntil('\n');
        command.trim();
        return command;
    }

    void sendResponse(String response)
    {
        Serial2.println(response);
    }

    void logMessage(String message)
    {
        Serial.println(message);
    }
}