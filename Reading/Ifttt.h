#ifndef IFTTT_H
#define IFTTT_H

#include <Arduino.h>

namespace Ifttt
{
    // Function declarations for IFTTT integration
    void sendToGoogleSheets(String sensorName, String status, String voltage, bool isRepeated, float duration);
    void sendAlert(String message);
}

#endif // IFTTT_H
