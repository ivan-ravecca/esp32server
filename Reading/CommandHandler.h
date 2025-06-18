#ifndef COMMAND_HANDLER_H
#define COMMAND_HANDLER_H

#include <Arduino.h>

namespace CommandHandler
{
#define CMD_ERROR "ERROR"
#define CMD_GET_CURRENT_TIME "GET_CURRENT_TIME"
#define CMD_SENSOR_UPDATE "SENSOR_UPDATE"

    void processCommand(String command);
    void handleTimeRequest();
    void handleSensorUpdate(String command);
    void logSensorData(String sensorId, int sensorStatus, float voltage, int isRepeatedAlarm, int durationMinutes);
}

#endif