#include "inventory.h"
#include "driver.h"

// J4210U uhf(&UART2, 57600);
vector<ScanResult> sdVector;
bool merge_on = false;
bool sd_flag = false;
bool filterOn = false;
string str;
ReaderInfo ri;
TaskHandle_t inventory_task_handle = NULL;

using namespace std;

// Function to perform inventory scan
void inventoryScan(void *pvParameters)
{
    /*ALWAYS GO TO MAIN SCR ON SCAN EVENT*/
    if (lv_scr_act() != ui_mainScreen)
    {
        /*del active screen*/
        /*---------*/
        _ui_screen_change(&ui_mainScreen, LV_SCR_LOAD_ANIM_FADE_ON, 50, 0, &ui_mainScreen_screen_init);
    }

    while (gpio_get_level(BUTTON_PIN) == 0)
    {
        int n = Inventory(filterOn);
        if (!merge_on)
        {
            if (pdTRUE == xSemaphoreTake(xGuiSemaphore, portMAX_DELAY))
            {
                lv_table_set_cell_value_fmt(epc_table, 0, 0, "EPC(tag count: %d)", n);
                lv_table_set_row_cnt(epc_table, n);
                xSemaphoreGive(xGuiSemaphore);
            }
            vTaskDelay(1 / portTICK_PERIOD_MS);
        }
        for (int i = 0; i < n; i++)
        {
            ScanResult sd;
            GetResult((unsigned char *)&sd, i);
            string epc = string((char *)sd.epc, sd.epclen);
            string hex = tohex(epc);
            __log("Ant = %d, Len = %d, EPC = %s, RSSI = %d, Count = %d\n",
                  sd.ant, sd.epclen, hex.c_str(), sd.RSSI, sd.count);
            if (merge_on) /*merge check*/
            {
                if (!hasSameEPCNUM(sdVector, sd.epc, sd.epclen))
                {
                    sdVector.push_back(sd);
                }
                else
                {
                    /*not pushing*/
                }
            }
            else
            {
                str = bytes2hex(sd.epc, sd.epclen);
                if (pdTRUE == xSemaphoreTake(xGuiSemaphore, portMAX_DELAY))
                {
                    lv_table_set_cell_value(epc_table, i + 1, 0, str.c_str());
                    lv_table_set_cell_value(epc_table, i + 1, 1, signedCharToString(sd.RSSI));
                    xSemaphoreGive(xGuiSemaphore);
                }
                vTaskDelay(0.1 / portTICK_PERIOD_MS);
            }
        }
        if (merge_on)
        {
            if (pdTRUE == xSemaphoreTake(xGuiSemaphore, portMAX_DELAY))
            {
                lv_table_set_cell_value_fmt(epc_table, 0, 0, "EPC(tag count: %d)", sdVector.size());
                lv_table_set_row_cnt(epc_table, sdVector.size());
                xSemaphoreGive(xGuiSemaphore);
            }
            vTaskDelay(1 / portTICK_PERIOD_MS);
            /*vector print in tft*/
            for (size_t i = 0; i < sdVector.size(); ++i)
            {
                string str_;
                str_ = bytes2hex(sdVector[i].epc, sdVector[i].epclen);
                if (pdTRUE == xSemaphoreTake(xGuiSemaphore, portMAX_DELAY))
                {
                    lv_table_set_cell_value(epc_table, i + 1, 0, str_.c_str());
                    lv_table_set_cell_value(epc_table, i + 1, 1, signedCharToString(sdVector[i].RSSI));
                    xSemaphoreGive(xGuiSemaphore);
                }
                vTaskDelay(1 / portTICK_PERIOD_MS);
            }
        }
        // vTaskDelay(100 / portTICK_PERIOD_MS);
    }
    // printVector(sdVector);
    __log("bye!");
    inventory_task_handle = NULL;
    //	vTaskDelay(200/portTICK_PERIOD_MS);
    vTaskDelete(NULL);
    // __log( "bye!");
}
// GPIO ISR handler for the button press
void IRAM_ATTR button_isr_handler(void *arg)
{
    if (inventory_task_handle == NULL)
    {
        xTaskCreatePinnedToCore(
            inventoryScan,
            "inventory_task",
            INV_SCAN_TASK_STACK_SIZE,
            NULL, INV_TASK_PRIORITY,
            &inventory_task_handle,
            INV_TASK_CORE);
    }
    else
    {
        /*__log("inventory task already running");*/
    }
}
bool hasSameEPCNUM(const std::vector<ScanResult> &vector, const unsigned char *epcnum, int epclen)
{
    for (const auto &ScanResult : vector)
    {
        if (ScanResult.epclen == epclen && std::memcmp(ScanResult.epc, epcnum, epclen) == 0)
        {
            return true; // Found the same EPCNUM
        }
    }
    return false; // EPCNUM not found in the vector
}
int getInventory()
{
    // c__log("\n>>> getInventory() STARTED:\n");
    int n = Inventory(false);
    // c__log("Found %d tags.\n", n);
    for (int i = 0; i < n; i++)
    {
        printtag(i);
    }
    // c__log("getInventory() ENDED <<<\n");
    return n;
}

// __log("EPCNUM: ");
// for (int j = 0; j < sdVector[i].epclen; ++j)
// {
//     __log("%02X ", sdVector[i].EPCNUM[j]);
// }
// __log(" already exist in vector\n");

// Print the contents of the vector
// for (const auto &scanData : sdVector)
// {
//     __log("all EPCNUM in sdVector: ");
//     for (int i = 0; i < scanData.epclen; ++i)
//     {
//         __log("%02X ", scanData.EPCNUM[i]);
//     }
//     __log("\n");
// }