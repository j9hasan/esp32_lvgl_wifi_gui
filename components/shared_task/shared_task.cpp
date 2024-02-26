#include <stdio.h>
#include "shared_task.h"
#include "ui.h"
#include "inventory.h"
#include "helper_func.h"
#include "driver.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_event.h"
#include "esp_log.h"
#include "esp_ota_ops.h"
#include "esp_http_client.h"
#include "esp_https_ota.h"
#include "string.h"
#include <sys/socket.h>

TaskHandle_t RFID_TASK_HANDLE = NULL;
void reader_info_fetching_task(void *pVparameters)
{

    if (pdTRUE == xSemaphoreTake(xGuiSemaphore, portMAX_DELAY))
    {
        create_notif_panel("READER", "Fetching data, please wait", true, 0);
        xSemaphoreGive(xGuiSemaphore);
    }
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
    __log("device_id: %s", intToString(littleEndianValue));
    __log("VersionInfo: %s", charArrayToString(ri.VersionInfo, 2));
    __log("ScanTime: %s", unsignedCharToString(ri.ScanTime));
    __log("Power: %s", unsignedCharToString(ri.Power));
    __log("Antenna: %s", unsignedCharToString(ri.Antenna));
    __log("Protocol: %s", unsignedCharToString(ri.Protocol));
    __log("MinFreq: %s", intToString(ri.MinFreq));
    __log("MaxFreq: %s", intToString(ri.MaxFreq));
    __log("BeepOn: %s", unsignedCharToString(ri.BeepOn));

    notif_msg_update("Done");
    vTaskDelay(300 / portTICK_PERIOD_MS);
    system_status.reader_data_fetched = true;

    if (pdTRUE == xSemaphoreTake(xGuiSemaphore, portMAX_DELAY))
    {
        notif_panel_del();
        xSemaphoreGive(xGuiSemaphore);
    }

    /* releasing write button  */
    lv_obj_add_flag(ui_reader_info_write, LV_OBJ_FLAG_CLICKABLE);

    RFID_TASK_HANDLE = NULL;
    vTaskDelete(RFID_TASK_HANDLE);
}

TaskHandle_t READER_WRITE_TASK_HANDLE = NULL;

void reader_info_write(void *pVparameters)
{
    if (pdTRUE == xSemaphoreTake(xGuiSemaphore, portMAX_DELAY))
    {
        create_notif_panel("READER", "Writing data, please wait", true, 0);
        xSemaphoreGive(xGuiSemaphore);
    }

    vTaskDelay(300 / portTICK_PERIOD_MS);

    char rfid_band_dd[20] = {0};
    /* currently not setting options for multiple baudrate*/
    // char rfid_baud_dd[20] = {0};
    uint32_t RFID_DD_BUFFER_SIZE = 20;

    /*getting scan time from textarea*/
    ri.ScanTime = charArrayToInt(lv_textarea_get_text(ui_scantime_txtarea));

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

    if (pdTRUE == xSemaphoreTake(xGuiSemaphore, portMAX_DELAY))
    {
        notif_panel_del();
        xSemaphoreGive(xGuiSemaphore);
    }
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

        xTaskCreatePinnedToCore(reader_info_fetching_task, "reader_info_fetching_task",
                                RFID_TASK_STACK_SIZE, NULL,
                                RFID_TASK_PRIORITY,
                                &RFID_TASK_HANDLE,
                                RFID_TASK_CORE);
        ESP_LOGI("update_rfid_tab", "start fetching reader info.");
    }

    else
    {
        ESP_LOGI("update_rfid_tab", "rfid info task already running");
    }
}

#define FIRMWARE_UPGRADE_URL "http://192.168.0.105:8000/handheld.bin"
#define OTA_RECV_TIMEOUT 5000
#define KB_TO_BYTES 1024

// extern const uint8_t server_cert_pem_start[] asm("_binary_ca_cert_pem_start");
// extern const uint8_t server_cert_pem_end[] asm("_binary_ca_cert_pem_end");

static esp_err_t _http_client_init_cb(esp_http_client_handle_t http_client)
{
    esp_err_t err = ESP_OK;
    /* Uncomment to add custom headers to HTTP request */
    // err = esp_http_client_set_header(http_client, "Custom-Header", "Value");
    return err;
}

TaskHandle_t fw_update_task_handle = NULL;

/* fuction to kill ota prcess on failure */
static void end_ota_process()
{
    __log("ESP_HTTP_OTA upgrade failed");
    lv_label_set_text(ui_n_1, "ESP_HTTP_OTA upgrade failed");
    vTaskDelay(1500 / portTICK_PERIOD_MS);
    if (pdTRUE == xSemaphoreTake(xGuiSemaphore, portMAX_DELAY))
    {
        notif_panel_del();
        xSemaphoreGive(xGuiSemaphore);
    }
    fw_update_task_handle = NULL;
    vTaskDelete(fw_update_task_handle);
}

static esp_err_t validate_image_header(esp_app_desc_t *new_app_info)
{
    if (new_app_info == NULL)
    {
        lv_label_set_text(ui_n_1, "image header NULL");
        vTaskDelay(1500 / portTICK_PERIOD_MS);
        return ESP_ERR_INVALID_ARG;
    }

    const esp_partition_t *running = esp_ota_get_running_partition();
    esp_app_desc_t running_app_info;

    if (esp_ota_get_partition_description(running, &running_app_info) == ESP_OK)
    {
        lv_label_set_text_fmt(ui_i_1, "Current fw v%s", running_app_info.version);
        if (memcmp(new_app_info->version, running_app_info.version, sizeof(new_app_info->version)) != 0)
        {
            lv_label_set_text_fmt(ui_i_2, "Remote fw v%s", new_app_info->version);
        }
        vTaskDelay(2000 / portTICK_PERIOD_MS);
        __log("Current firmware version: %s", running_app_info.version);
    }

    /* version check */
    if (memcmp(new_app_info->version, running_app_info.version, sizeof(new_app_info->version)) == 0)
    {
        lv_label_set_text(ui_n_1, "No update avilable aborting.");
        vTaskDelay(1500 / portTICK_PERIOD_MS);

        __log("Current running version is the same as a new. We will not continue the update.");
        return ESP_FAIL;
    }
    return ESP_OK;
}

/* firmware update routine */
void fw_update_task(void *pVparameters)
{
    uint32_t image_size = 0;
    __log("Starting Advanced OTA Sequence");

    if (pdTRUE == xSemaphoreTake(xGuiSemaphore, portMAX_DELAY))
    {
        create_notif_panel("FW update", "", false, 1);
        xSemaphoreGive(xGuiSemaphore);
    }
    lv_label_set_text(ui_n_1, "Starting Advanced OTA Sequence");
    vTaskDelay(1300 / portTICK_PERIOD_MS);

    esp_err_t ota_finish_err = ESP_OK;
    esp_http_client_config_t config = {
        .url = FIRMWARE_UPGRADE_URL,
        // .cert_pem = (char *)server_cert_pem_start,
        .timeout_ms = OTA_RECV_TIMEOUT,
        .keep_alive_enable = true,
    };

    config.skip_cert_common_name_check = true;

    esp_https_ota_config_t ota_config = {
        .http_config = &config,
        .http_client_init_cb = _http_client_init_cb,
    };

    esp_https_ota_handle_t https_ota_handle = NULL;
    esp_err_t err = esp_https_ota_begin(&ota_config, &https_ota_handle);
    if (err != ESP_OK)
    {
        __log("ESP HTTPS OTA Begin failed");

        lv_label_set_text_fmt(ui_n_1, "OTA Begin failed Err: %s", esp_err_to_name(err));

        vTaskDelay(1300 / portTICK_PERIOD_MS);

        esp_https_ota_abort(https_ota_handle);
        end_ota_process();
    }

    esp_app_desc_t app_desc;
    err = esp_https_ota_get_img_desc(https_ota_handle, &app_desc);
    if (err != ESP_OK)
    {
        __log("esp_https_ota_read_img_desc failed");

        lv_label_set_text(ui_n_1, "Image desc. read fails.");
        vTaskDelay(1500 / portTICK_PERIOD_MS);

        esp_https_ota_abort(https_ota_handle);
        end_ota_process();
    }
    err = validate_image_header(&app_desc);
    if (err != ESP_OK)
    {
        __log("Image Header verification failed.");

        esp_https_ota_abort(https_ota_handle);
        end_ota_process();
    }
    else
    {
        /* verify success, get image size */
        image_size = esp_https_ota_get_image_size(https_ota_handle) / 1000;

        lv_label_set_text_fmt(ui_i_3, "Remote fw size %d KB", image_size);
    }

    const TickType_t updateInterval = pdMS_TO_TICKS(1000);

    /* set download bar range */
    lv_bar_set_range(ui_b_1, 0, image_size);

    uint32_t lastImgBytesRead = 0;
    TickType_t lastUpdateTime = xTaskGetTickCount();

    while (1)
    {
        err = esp_https_ota_perform(https_ota_handle);
        if (err != ESP_ERR_HTTPS_OTA_IN_PROGRESS)
        {
            break;
        }

        uint32_t img_loaded_bytes = esp_https_ota_get_image_len_read(https_ota_handle);
        uint32_t img_loaded_kb = img_loaded_bytes / KB_TO_BYTES;

        TickType_t currentTime = xTaskGetTickCount();

        // update gui every 1 sec to reduce cpu load
        if ((currentTime - lastUpdateTime) >= updateInterval)
        {
            // Calculate increase in image bytes read
            uint32_t img_bytes_increase = img_loaded_bytes - lastImgBytesRead;
            lastImgBytesRead = img_loaded_bytes;

            // Calculate KBps
            __log("bytes inc %d", img_bytes_increase / 1024);

            uint32_t KBps = img_bytes_increase / (KB_TO_BYTES);
            __log("KBps: %d", KBps);
            __log("Image bytes read: %d", img_loaded_kb);

            // show and update bar value
            lv_obj_clear_flag(ui_b_1, LV_OBJ_FLAG_HIDDEN);
            lv_bar_set_value(ui_b_1, img_loaded_kb, LV_ANIM_OFF);

            // Update gui
            lv_label_set_text_fmt(ui_n_1, "Image read: %d KB (%d KB/s)", img_loaded_kb, KBps);

            lastUpdateTime = currentTime;
        }
    }

    if (esp_https_ota_is_complete_data_received(https_ota_handle) != true)
    {
        /* the OTA image was not completely received and user can customise the response to this situation. */
        __log("Complete data was not received.");

        lv_label_set_text(ui_n_1, "Complete data was not received.");

        vTaskDelay(1500 / portTICK_PERIOD_MS);
    }
    else
    {
        ota_finish_err = esp_https_ota_finish(https_ota_handle);

        if ((err == ESP_OK) && (ota_finish_err == ESP_OK))
        {
            __log("ESP_HTTPS_OTA upgrade successful. Rebooting ...");

            lv_label_set_text(ui_n_1, "OTA update successful.Rebooting ...");

            vTaskDelay(1200 / portTICK_PERIOD_MS);

            if (pdTRUE == xSemaphoreTake(xGuiSemaphore, portMAX_DELAY))
            {
                notif_panel_del();
                xSemaphoreGive(xGuiSemaphore);
            }
            esp_restart();
        }
        else
        {
            if (ota_finish_err == ESP_ERR_OTA_VALIDATE_FAILED)
            {
                __log("Image validation failed, image is corrupted");

                lv_label_set_text(ui_n_1, "Img corrupted");

                vTaskDelay(1300 / portTICK_PERIOD_MS);
            }
            esp_https_ota_abort(https_ota_handle);
            end_ota_process();
        }
    }
    fw_update_task_handle = NULL;
    vTaskDelete(fw_update_task_handle);
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