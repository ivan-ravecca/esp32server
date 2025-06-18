#ifndef SERIAL_COMP_H
#define SERIAL_COMP_H

#include <Arduino.h>

namespace SerialComp
{
#define SERIAL_BAUD 9600
#define RXp2 16
#define TXp2 17

    void setup();
    bool commandAvailable();
    String readCommand();
    void sendResponse(String response);
    void logMessage(String message);
}

#endif