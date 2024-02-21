#include <stdio.h>
#include "shared_task.h"
#include "ui.h"
#include "inventory.h"
#include "helper_func.h"
#include "driver.h"

static const char *TAG = "shared task";

TaskHandle_t RFID_TASK_HANDLE = NULL;
void reader_info_fetching_task(void *pVparameters)
{
    create_notif_panel("READER", "Fetching data, please wait", true);
    vTaskDelay(300 / portTICK_PERIOD_MS);
    GetSettings(&ri);

    uint32_t littleEndianValue = toLittleEndian((uint32_t)ri.Serial);

    lv_label_set_text(ui_device_id_labelx, intToString(littleEndianValue));
    lv_label_set_text(ui_version_labelx, charArrayToString(ri.VersionInfo, 2));
    lv_textarea_set_text(ui_scantime_txtarea, unsignedCharToString(ri.ScanTime));
    lv_textarea_set_one_line(ui_scantime_txtarea, true);
    lv_textarea_set_text(ui_power_txtarea, unsignedCharToString(ri.Power));
    lv_textarea_set_one_line(ui_power_txtarea, true);
    lv_label_set_text(ui_antenna_labelx, unsignedCharToString(ri.Antenna));
    lv_label_set_text(ui_protocol_labelx, unsignedCharToString(ri.Protocol));
    lv_label_set_text(ui_minf_labelx, intToString(ri.MinFreq));
    lv_label_set_text(ui_maxf_labelx, intToString(ri.MaxFreq));

    /* set the switch state */

    if (ri.BeepOn)
        lv_obj_add_state(ui_beepon_switch, LV_STATE_CHECKED);
    else
        lv_obj_clear_state(ui_beepon_switch, LV_STATE_CHECKED);

    /* LOG */
    ESP_LOGI(TAG, "device_id: %s", intToString(littleEndianValue));
    ESP_LOGI(TAG, "VersionInfo: %s", charArrayToString(ri.VersionInfo, 2));
    ESP_LOGI(TAG, "ScanTime: %s", unsignedCharToString(ri.ScanTime));
    ESP_LOGI(TAG, "Power: %s", unsignedCharToString(ri.Power));
    ESP_LOGI(TAG, "Antenna: %s", unsignedCharToString(ri.Antenna));
    ESP_LOGI(TAG, "Protocol: %s", unsignedCharToString(ri.Protocol));
    ESP_LOGI(TAG, "MinFreq: %s", intToString(ri.MinFreq));
    ESP_LOGI(TAG, "MaxFreq: %s", intToString(ri.MaxFreq));
    ESP_LOGI(TAG, "BeepOn: %s", unsignedCharToString(ri.BeepOn));

    notif_msg_update("Done");
    vTaskDelay(300 / portTICK_PERIOD_MS);
    system_status.reader_data_fetched = true;
    notif_panel_del();

    /* releasing write button  */
    lv_obj_add_flag(ui_reader_info_write, LV_OBJ_FLAG_CLICKABLE);

    RFID_TASK_HANDLE = NULL;
    vTaskDelete(RFID_TASK_HANDLE);
}

TaskHandle_t READER_WRITE_TASK_HANDLE = NULL;

void reader_info_write(void *pVparameters)
{
    create_notif_panel("READER", "Writing data, please wait", true);
    vTaskDelay(300 / portTICK_PERIOD_MS);

    char rfid_band_dd[20] = {0};
    /* currently not setting options for multiple baudrate*/
    // char rfid_baud_dd[20] = {0};
    uint32_t RFID_DD_BUFFER_SIZE = 20;

    /*getting scan time from textarea*/

    ri.ScanTime = charArrayToInt(lv_textarea_get_text(ui_scantime_txtarea));
    // ri.ScanTime = 3;

    // ESP_LOGI("TAG", "convertStringToUnsignedChar(lv_textarea_get_text(ui_scantime_txtarea)%s", convertStringToUnsignedChar(lv_textarea_get_text(ui_scantime_txtarea));
    ESP_LOGI("TAG", "%d", ri.ScanTime);

    ri.Power = charArrayToInt(lv_textarea_get_text(ui_power_txtarea));

    /*getting band dropdown*/
    lv_dropdown_get_selected_str(ui_bana_dd, rfid_band_dd, RFID_DD_BUFFER_SIZE);

    /*setting band*/
    ri.Band = toupper(rfid_band_dd[0]);

    ri.BeepOn = lv_obj_has_state(ui_beepon_switch, LV_STATE_CHECKED);

    /*getting and setting baudrate */

    // lv_dropdown_get_selected_str(ui_baud_dd, rfid_baud_dd, RFID_DD_BUFFER_SIZE);
    // ri.BaudRate = charArrayToInt(rfid_baud_dd);

    /*updating new settings*/
    SetSettings(&ri);
    vTaskDelay(100 / portTICK_PERIOD_MS);

    /* update rfid info tab */
    notif_panel_del();
    vTaskDelay(10 / portTICK_PERIOD_MS);
    update_rfid_tab();

    vTaskDelay(300 / portTICK_PERIOD_MS);

    READER_WRITE_TASK_HANDLE = NULL;
    vTaskDelete(READER_WRITE_TASK_HANDLE);
}

void update_rfid_tab()
{
    if (RFID_TASK_HANDLE == NULL)
    {
        if (system_status.reader)
        {
            xTaskCreatePinnedToCore(reader_info_fetching_task, "reader_info_fetching_task",
                                    RFID_TASK_STACK_SIZE, NULL,
                                    RFID_TASK_PRIORITY,
                                    &RFID_TASK_HANDLE,
                                    RFID_TASK_CORE);
            ESP_LOGI("update_rfid_tab", "start fetching reader info.");
        }
        else
        {
            ESP_LOGI("update_rfid_tab", "reader not found.");
        }
    }
    else
    {
        ESP_LOGI("update_rfid_tab", "rfid info task already running");
    }
}

/* sample task create
    xTaskCreatePinnedToCore(
        myTask,          // Task function
        "MyTask",        // Task name
        TASK_STACK_SIZE, // Stack size
        NULL,            // Task parameters (if any)
        TASK_PRIORITY,               // Task priority
        task_handle,            // Task handle (optional, can be NULL)
        TASK_CORE               // Core to pin the task to (0 or 1)
    );
    */

/* prints reader info on rfid tab */