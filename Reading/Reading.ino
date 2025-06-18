#include "WiFiComp.h"
#include "TimeComp.h"
#include "SerialComp.h"
#include "CommandHandler.h"

void setup()
{
    SerialComp::setup();
    Serial.println("ESP32 WiFi Gateway Starting...");
    WiFiComp::setup();
    TimeComp::setup();
    Serial.println("ESP32 ready to receive commands from Arduino UNO");
}

void loop()
{
    if (SerialComp::commandAvailable())
    {
        String command = SerialComp::readCommand();
        CommandHandler::processCommand(command);
    }
}