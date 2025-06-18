#include "TimeComp.h"
#include <Arduino.h>

namespace TimeComp
{
    // NTP Server settings
    const char *ntpServer = "pool.ntp.org";
    const long gmtOffset_sec = -10800; // GMT-3 (adjust for your timezone)
    const int daylightOffset_sec = 0;  // No DST offset (already included in GMT offset)

    void setup()
    {
        configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
        Serial.println("NTP time sync initialized");
    }

    bool getFormattedTime(char *buffer, size_t bufferSize)
    {
        struct tm timeinfo;
        if (!getLocalTime(&timeinfo))
        {
            Serial.println("Failed to obtain time");
            return false;
        }

        strftime(buffer, bufferSize, "%Y-%m-%d %H:%M:%S", &timeinfo);
        return true;
    }
}