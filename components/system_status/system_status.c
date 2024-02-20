#include <stdio.h>
#include "system_status.h"

/* ui init wait mechanism */
EventGroupHandle_t systemStatusEventGroup;
EventBits_t bits;
const int UI_INITIALIZED_BIT = BIT0;
const int WIFI_CONNECTED_BIT = BIT1;
const int WIFI_FAIL_BIT = BIT2;

/* system status data initialization */
Status system_status = {false, false, false, false /*, ... */};
