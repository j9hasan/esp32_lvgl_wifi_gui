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

/* error handling */
extern esp_err_t wifi_connect_error;
extern esp_err_t sd_card_error;
// extern esp_err_t wifi_status_error;

/* debug log*/
#define DEBUG
#ifdef DEBUG
#define __log(format, ...)                                \
    do                                                    \
    {                                                     \
        printf("Debug Log: " format "\n", ##__VA_ARGS__); \
        fflush(stdout);                                   \
    } while (0)
#else
#define __log(format, ...) // Define an empty macro for release mode
#endif

#endif // SYSTEM_STATUS_H