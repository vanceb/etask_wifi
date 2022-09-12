#ifndef ETASK_WIFI_H
#define ETASK_WIFI_H

/*
 * Platformio Libraries needed

lib_deps = 
    khoih-prog/ESP_WifiManager @ ^1.11.0
;    khoih-prog/ESPAsync_WiFiManager @ ^1.14.0
    khoih-prog/ESP_DoubleResetDetector @ ^1.3.2

 * From the github repository https://github.com/khoih-prog/ESP_WiFiManager
 * take one of the examples and use it as a library.
 * In this case ConfigOnDoubleReset_Multi
 * I did have to force the use of SPIFFS to get it to run
 * The example code is modified with an SVB comment
 */

/* FreeRTOS Task to manage WiFi and keep time updated by NTP */
void etask_wifi(void * parameter);

/* Static functions */


#endif