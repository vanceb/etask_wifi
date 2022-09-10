# etask_wifi

This package contains the code to perform setup and maintenance of wifi, as well as ntp updates.
It also provides a FreeRTOS task `etask_wifi()`, which can run as part of your project.

Include this repository as a submodule in your project, or just download as a library.

## Example excerpt

~~~c
#include <etask_wifi.h>

TaskHandle_t wifi_task;

void setup() {
  ...
  // Create a task to check and get OTA updates from S3
  xTaskCreate(
    etask_wifi,
    "WiFi_Task",
    5000,
    NULL,
    0,
    &wifi_task
  );
}
~~~
