// system_status.h

#ifndef SYSTEM_STATUS_H
#define SYSTEM_STATUS_H
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "freertos/event_groups.h"
#include "esp_system.h"
#include <esp_log.h>

/* ui init wait mechanism */
extern EventGroupHandle_t systemStatusEventGroup;
extern EventBits_t bits;
extern const int UI_INITIALIZED_BIT;
extern const int WIFI_CONNECTED_BIT;
extern const int WIFI_FAIL_BIT;

/* status struct */
typedef struct
{
    bool wifi;
    bool bluetooth;
    bool reader;
    bool reader_data_fetched;
} Status;

// Declare a global instance of the Status structure
extern Status system_status;

#endif // SYSTEM_STATUS_H