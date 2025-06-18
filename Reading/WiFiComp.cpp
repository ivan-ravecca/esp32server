#include "WiFiComp.h"

namespace WiFiComp
{
    // WiFi credentials
    const char *ssid = "";
    const char *password = "";

    void setup()
    {
        Serial.println("WiFi Component: Starting connection...");
        WiFi.begin(ssid, password);
        Serial.print("Connecting to WiFi");

        while (WiFi.status() != WL_CONNECTED)
        {
            delay(500);
            Serial.print(".");
        }

        Serial.println();
        Serial.println("WiFi connected!");
        Serial.print("IP address: ");
        Serial.println(WiFi.localIP());
    }

    bool isConnected()
    {
        return WiFi.status() == WL_CONNECTED;
    }
}