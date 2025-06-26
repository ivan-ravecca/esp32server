#include "Ifttt.h"
#include "WiFiComp.h"
#include "TimeComp.h"
#include "CommandHandler.h"
#include <HTTPClient.h>
#include <ArduinoJson.h>

namespace Ifttt
{
    const char *ifttt_key = "xxxxxx";
    const char *event_data = "sensor_data";   // Excel updates
    const char *event_alert = "sensor_alert"; // Mobile notifications
    const String base_url = "https://maker.ifttt.com/trigger/";

    void sendToGoogleSheets(String sensorName, String status, String voltage, bool isRepeated, float duration)
    {
        if (WiFiComp::isConnected())
        {
            HTTPClient http;
            String url = base_url + String(event_data) + "/with/key/" + String(ifttt_key);

            http.begin(url);
            http.addHeader("Content-Type", "application/json");

            StaticJsonDocument<200> doc;

            doc["value1"] = "Bomba " + sensorName + " esta " + status;
            doc["value2"] = voltage;
            doc["value3"] = duration > 0 ? String(duration) : "0"; // Convert float to String

            String jsonString;
            serializeJson(doc, jsonString);

            int httpResponseCode = http.POST(jsonString);

            if (httpResponseCode > 0)
            {
                Serial.println("Datos enviados a Google Sheets: " + String(httpResponseCode));
            }
            else
            {
                Serial.println("Error enviando datos: " + String(httpResponseCode));
            }

            http.end();
        }
        if (isRepeated)
        {
            sendAlert("Sensor " + sensorName + " ha activado una alarma repetida, ya va corriendo " + String(duration) + " minutos.");
        }
    }

    void sendAlert(String message)
    {
        if (WiFiComp::isConnected())
        {
            HTTPClient http;
            String url = base_url + String(event_alert) + "/with/key/" + String(ifttt_key);

            http.begin(url);
            http.addHeader("Content-Type", "application/json");

            StaticJsonDocument<200> doc;
            doc["value1"] = message;
            doc["value2"] = TimeComp::getTimestamp();

            String jsonString;
            serializeJson(doc, jsonString);

            int httpResponseCode = http.POST(jsonString);

            if (httpResponseCode > 0)
            {
                Serial.println("Alerta enviada: " + String(httpResponseCode));
            }
            else
            {
                Serial.println("Error enviando alerta: " + String(httpResponseCode));
            }

            http.end();
        }
    }
}