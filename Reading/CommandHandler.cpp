#include "CommandHandler.h"
#include "SerialComp.h"
#include "TimeComp.h"

namespace CommandHandler
{
    void processCommand(String command)
    {
        SerialComp::logMessage("Received command: " + command);

        if (command == CMD_GET_CURRENT_TIME)
        {
            handleTimeRequest();
        }
        else if (command.startsWith(CMD_SENSOR_UPDATE))
        {
            handleSensorUpdate(command);
        }
        else
        {
            SerialComp::logMessage("Unknown command: " + command);
        }
    }

    void handleTimeRequest()
    {
        char timeString[30];
        if (!TimeComp::getFormattedTime(timeString, sizeof(timeString)))
        {
            SerialComp::sendResponse("ERROR:Failed to obtain time");
            return;
        }

        SerialComp::logMessage("Sending current time to Arduino: " + String(timeString));
        SerialComp::sendResponse("TIME:" + String(timeString));
    }

    void handleSensorUpdate(String command)
    {
        // Expected format: SENSOR_UPDATE,ID,STATUS,VOLTAGE,REPEATED_ALARM,DURATION_MINUTES
        // Example: SENSOR_UPDATE,A,1,217.30,1,15

        int firstComma = command.indexOf(',');
        if (firstComma == -1)
        {
            SerialComp::logMessage("Invalid sensor update format");
            return;
        }

        String data = command.substring(firstComma + 1);

        // Parse sensor data
        int pos1 = data.indexOf(',');
        if (pos1 == -1)
            return;
        String sensorId = data.substring(0, pos1);

        int pos2 = data.indexOf(',', pos1 + 1);
        if (pos2 == -1)
            return;
        int sensorStatus = data.substring(pos1 + 1, pos2).toInt();

        int pos3 = data.indexOf(',', pos2 + 1);
        if (pos3 == -1)
            return;
        float voltage = data.substring(pos2 + 1, pos3).toFloat();

        int pos4 = data.indexOf(',', pos3 + 1);
        if (pos4 == -1)
        {
            // Old format without duration
            int isRepeatedAlarm = data.substring(pos3 + 1).toInt();
            logSensorData(sensorId, sensorStatus, voltage, isRepeatedAlarm, 0);
            return;
        }

        // New format with duration
        int isRepeatedAlarm = data.substring(pos3 + 1, pos4).toInt();
        int durationMinutes = data.substring(pos4 + 1).toInt();

        logSensorData(sensorId, sensorStatus, voltage, isRepeatedAlarm, durationMinutes);
    }

    // Helper function to log sensor data
    void logSensorData(String sensorId, int sensorStatus, float voltage, int isRepeatedAlarm, int durationMinutes)
    {
        // Log the received sensor data
        SerialComp::logMessage("Sensor Update Received:");
        SerialComp::logMessage("  Sensor ID: " + sensorId);
        SerialComp::logMessage("  Status: " + String(sensorStatus) +
                               (sensorStatus == 1 ? " (energized)" : " (de-energized)"));
        SerialComp::logMessage("  Voltage: " + String(voltage));
        SerialComp::logMessage("  Repeated Alarm: " + String(isRepeatedAlarm) +
                               (isRepeatedAlarm == 1 ? " (repeated)" : " (new)"));

        if (durationMinutes > 0)
        {
            SerialComp::logMessage("  Duration: " + String(durationMinutes) + " minutes");
        }

        // Send acknowledgment back to Arduino
        SerialComp::sendResponse("ACK," + sensorId);
    }
}