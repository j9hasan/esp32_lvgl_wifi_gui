#ifndef __INVENTORY_H__
#define __INVENTORY_H__

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "shared_task.h"
#include "ui.h"
#include "driver.h"

#define BUTTON_PIN GPIO_NUM_4
#ifdef __cplusplus
#include <vector>
#include <string.h>
#include <algorithm>
#include <cstring>
#include "helper_func.h"
using namespace std;
/*function prototypes of inventory cpp file*/
bool hasSameEPCNUM(const std::vector<ScanResult> &vector, const unsigned char *epcnum, int epclen);
int getInventory();
extern vector<ScanResult> sdVector;
extern ReaderInfo ri;
extern "C"
{
#endif
    /*function prototypes for using inside c file*/
    void IRAM_ATTR button_isr_handler(void *arg);
    void inventoryScan(void *pvParameters);
#ifdef __cplusplus
}
#endif
#endif