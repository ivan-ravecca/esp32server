#ifndef TIME_COMP_H
#define TIME_COMP_H

#include <time.h>

namespace TimeComp
{
    extern const char *ntpServer;
    extern const long gmtOffset_sec;
    extern const int daylightOffset_sec;

    void setup();
    bool getFormattedTime(char *buffer, size_t bufferSize);
}

#endif