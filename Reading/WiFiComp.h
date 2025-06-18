#ifndef WIFI_COMP_H
#define WIFI_COMP_H

#include <WiFi.h>

namespace WiFiComp
{
    extern const char *ssid;
    extern const char *password;

    void setup();
    bool isConnected();
}

#endif