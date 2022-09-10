#include <etask_wifi.h>

#include <TimeLib.h>
#include <time.h>
#include <Timezone.h>
#include <NTPClient.h>

#include <WiFiManager.h>
#include <WiFi.h>
#include <WiFiUdp.h>

/* United Kingdom (London, Belfast) */
TimeChangeRule BST = {"BST", Last, Sun, Mar, 1, 60}; // British Summer Time
TimeChangeRule GMT = {"GMT", Last, Sun, Oct, 2, 0};  // Standard Time
Timezone UK(BST, GMT);

void etask_wifi(void *parameter)
{
    // Set up Wifi - Using WiFi Manager
    // WiFiManager
    // Local intialization. Once its business is done, there is no need to keep it around
    WiFiManager wifiManager;
    // reset saved settings
    // wifiManager.resetSettings();

    // fetches ssid and pass from eeprom and tries to connect
    // if it does not connect it starts an access point with the specified name
    // here  "ESP Base"
    // and goes into a blocking loop awaiting configuration
    wifiManager.autoConnect("ESP Base");

    // if you get here you have connected to the WiFi
    Serial.println("connected...yeey :)");


    WiFiUDP ntpUDP;
    int UTCOffset = 0; // Set time to UTC - convert to local using Timezone
    NTPClient ntp(ntpUDP, NTP_SERVER, UTCOffset * 60 * 60, NTP_UPDATE_INTERVAL * 60 * 1000);

    ntp.begin();

    /* Variables for the loop */
    unsigned long currentMillis = 0;
    unsigned long previousMillis = 0;
    const unsigned long interval = 30000;
    uint8_t fails = 0;

    // Infinite loop - designed to run as an RTOS task
    for (;;)
    {
        // Make sure WiFi is connected
        currentMillis = millis();
        // if WiFi is down, try reconnecting
        if (WiFi.status() != WL_CONNECTED) {
            if (currentMillis - previousMillis >=interval) {
                Serial.print(millis());
                Serial.println("Reconnecting to WiFi...");
                WiFi.disconnect();
                if (WiFi.reconnect() != ESP_OK) {
                    fails += 1;
                    if (fails >= 5) {
                        Serial.println("Failed to reconnect to wifi - rebooting!");
                        delay(5000);
                        ESP.restart();
                    } 
                } else {
                    fails = 0;
                }
                previousMillis = currentMillis;
            }
        } else {
            if (ntp.update())
            {
                setTime(ntp.getEpochTime());
                Serial.print(getEpochStringByParams(UK.toLocal(now())));
                Serial.println(" Time updated from ntp");
            }
        }
        delay(NTP_LOOP_DELAY);
    }
}