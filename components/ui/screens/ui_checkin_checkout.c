
#include "../ui.h"
#include "esp_system.h"
#include "esp_log.h"
#include "shared_task.h"
#include <stdio.h>
#include <string.h>
#include "sd_fat.h"
#include <ctype.h>
#include <sys/param.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_event.h"
#include "esp_netif.h"
#include "lwip/err.h"
#include "lwip/sockets.h"
#include "helper_func.h"
#include "cJSON.h"
#define MAX_PATH_LENGTH 20
#define USE_SEMAPHORE 0
#define FOLDERPATH "/S/folder1"
typedef struct
{
    int id;
    char name[20];
    float value;
} MyStruct1;

char *structToJson(const MyStruct1 *data)
{
    cJSON *root = cJSON_CreateObject();
    cJSON_AddItemToObject(root, "id", cJSON_CreateNumber(data->id));
    cJSON_AddItemToObject(root, "name", cJSON_CreateString(data->name));
    cJSON_AddItemToObject(root, "value", cJSON_CreateNumber(data->value));

    char *jsonString = cJSON_Print(root);
    cJSON_Delete(root);

    return jsonString;
}

MyStruct1 parseJson(const char *jsonString)
{
    cJSON *root = cJSON_Parse(jsonString);

    MyStruct1 result;
    if (root != NULL)
    {
        cJSON *id = cJSON_GetObjectItem(root, "id");
        cJSON *name = cJSON_GetObjectItem(root, "name");
        cJSON *value = cJSON_GetObjectItem(root, "value");

        if (id && id->type == cJSON_Number && name && name->type == cJSON_String && value && value->type == cJSON_Number)
        {
            result.id = id->valueint;
            snprintf(result.name, sizeof(result.name), "%s", name->valuestring);
            result.value = value->valuedouble;
        }
        else
        {
            ESP_LOGI("parser", "Handle error: JSON structure does not match expected format");
        }
        cJSON_Delete(root);
    }
    else
    {
        ESP_LOGI("parser", "Handle error: JSON parsing failed");
    }

    return result;
}
/*decoder status
 int decoderError_g;
 uint32_t png_w_g;
 uint32_t png_h_g;
 */
/*socket param*/
// #define HOST_IP_ADDR "192.168.1.8"
// #define PORT 801
#define HOST_IP_ADDR "192.168.1.20"
#define PORT "19991"
TaskHandle_t tcp_client_task_handler = NULL;

#define MAX_PAYLOAD_SIZE 1024
static const char *TAG = "example";
// const char *payload = "{\"key\":\"1\",\"reserved\":\"strss\"}";
static void tcp_client_task(void *pvParameters);
void ui_checkin_checkoutScreen_screen_init(void)
{
    if (tcp_client_task_handler == NULL)
    {
        xTaskCreate(tcp_client_task, "tcp_client", 4096, NULL, 5, &tcp_client_task_handler);
    }
    else
    {
        ESP_LOGI(TAG, "tcp client task already running");
    }

    int numFiles;
    char **path = listFilesAndFolders(FOLDERPATH, &numFiles);
    const char *basePath = "S:folder1/";
    char concatenatedPath[MAX_PATH_LENGTH];
    strcpy(concatenatedPath, basePath); // Copy the base path to concatenatedPath
    strcat(concatenatedPath, path[5]);  // Concatenate the current filename to it
    char *fileExtension = strrchr(concatenatedPath, '.');
    if (fileExtension != NULL)
    {
        toLowerCase(fileExtension);
    }
    const char *TAG = "Checkin checkOut";
    ui_checkinOutScreen = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_checkinOutScreen, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_obj_set_style_bg_color(ui_checkinOutScreen, lv_color_hex(0xB4E2FF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_checkinOutScreen, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    ESP_LOGI(TAG, "path: %s", concatenatedPath);

    // ui_demoImg = lv_img_create(ui_checkinOutScreen);
    // lv_img_set_src(ui_demoImg, concatenatedPath);
    // lv_obj_set_align(ui_demoImg, LV_ALIGN_CENTER);

    ui_leftContainer = lv_obj_create(ui_checkinOutScreen);
    lv_obj_remove_style_all(ui_leftContainer);
    lv_obj_set_width(ui_leftContainer, lv_pct(30));
    lv_obj_set_height(ui_leftContainer, lv_pct(100));
    lv_obj_set_align(ui_leftContainer, LV_ALIGN_LEFT_MID);
    lv_obj_clear_flag(ui_leftContainer, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_obj_set_style_bg_color(ui_leftContainer, lv_color_hex(0xDEEAF2), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_leftContainer, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_checkinOutScreenImgContainer = lv_obj_create(ui_checkinOutScreen);
    lv_obj_remove_style_all(ui_checkinOutScreenImgContainer);
    lv_obj_set_width(ui_checkinOutScreenImgContainer, lv_pct(30));
    lv_obj_set_height(ui_checkinOutScreenImgContainer, lv_pct(40));
    lv_obj_set_x(ui_checkinOutScreenImgContainer, lv_pct(0));
    lv_obj_set_y(ui_checkinOutScreenImgContainer, lv_pct(8));
    lv_obj_clear_flag(ui_checkinOutScreenImgContainer, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_obj_set_style_bg_color(ui_checkinOutScreenImgContainer, lv_color_hex(0xD8E1E7), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_checkinOutScreenImgContainer, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_demoImg = lv_img_create(ui_checkinOutScreenImgContainer);
    lv_img_set_src(ui_demoImg, concatenatedPath);
    lv_obj_set_align(ui_demoImg, LV_ALIGN_CENTER);

    ui_timeLabelUiAgentCheckin = lv_label_create(ui_checkinOutScreen);
    lv_obj_set_width(ui_timeLabelUiAgentCheckin, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_timeLabelUiAgentCheckin, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_timeLabelUiAgentCheckin, lv_pct(9));
    lv_obj_set_y(ui_timeLabelUiAgentCheckin, lv_pct(2));
    lv_label_set_text(ui_timeLabelUiAgentCheckin, "11.00.32");
    lv_obj_set_style_text_font(ui_timeLabelUiAgentCheckin, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_checkinOutStatusLabel = lv_label_create(ui_checkinOutScreen);
    lv_obj_set_width(ui_checkinOutStatusLabel, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_checkinOutStatusLabel, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_checkinOutStatusLabel, lv_pct(3));
    lv_obj_set_y(ui_checkinOutStatusLabel, lv_pct(9));
    lv_obj_set_align(ui_checkinOutStatusLabel, LV_ALIGN_LEFT_MID);
    lv_label_set_text(ui_checkinOutStatusLabel, "");

    ui_distributorContainer = lv_obj_create(ui_checkinOutScreen);
    lv_obj_remove_style_all(ui_distributorContainer);
    lv_obj_set_width(ui_distributorContainer, lv_pct(69));
    lv_obj_set_height(ui_distributorContainer, lv_pct(5));
    lv_obj_set_x(ui_distributorContainer, 48);
    lv_obj_set_y(ui_distributorContainer, -3);
    lv_obj_set_align(ui_distributorContainer, LV_ALIGN_BOTTOM_MID);
    lv_obj_clear_flag(ui_distributorContainer, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_obj_set_style_bg_color(ui_distributorContainer, lv_color_hex(0xDEE2E6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_distributorContainer, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_distributorLabel = lv_label_create(ui_distributorContainer);
    lv_label_set_long_mode(ui_distributorLabel, LV_LABEL_LONG_SCROLL_CIRCULAR); /*Circular scroll*/
    lv_obj_set_width(ui_distributorLabel, lv_pct(100));
    // lv_obj_set_width(ui_distributorLabel, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_distributorLabel, LV_SIZE_CONTENT); /// 1
    lv_obj_set_align(ui_distributorLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_distributorLabel, "Distributed By: Jence Bangladesh.http://jence.com");
    lv_obj_set_style_text_font(ui_distributorLabel, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_normalBtn2 = ui_normalBtn_create(ui_checkinOutScreen);
    // lv_obj_set_x(ui_normalBtn2, lv_pct(-43));
    // lv_obj_set_y(ui_normalBtn2, lv_pct(44));
    // lv_label_set_text(ui_comp_get_child(ui_normalBtn2, UI_COMP_NORMALBTN_NORMALBTNLABEL), "Back");
}
/*
TODO: HANDLE SOCKET CONNECTION AND DELETION EFFICIENTLY
*/
static void tcp_client_task(void *pvParameters)
{
    char rx_buffer[320];
    char host_ip[] = HOST_IP_ADDR;
    int addr_family = 0;
    int ip_protocol = 0;

    struct sockaddr_in dest_addr;
    dest_addr.sin_addr.s_addr = inet_addr(host_ip);
    dest_addr.sin_family = AF_INET;
    dest_addr.sin_port = htons(PORT);
    addr_family = AF_INET;
    ip_protocol = IPPROTO_IP;
    int sock = socket(addr_family, SOCK_STREAM, ip_protocol);
    if (sock < 0)
    {
        ESP_LOGE(TAG, "Unable to create socket: errno %d", errno);
        tcp_client_task_handler = NULL;
        vTaskDelete(tcp_client_task_handler);
    }
    ESP_LOGI(TAG, "Socket created, connecting to %s:%s", host_ip, PORT);

    int err = connect(sock, (struct sockaddr *)&dest_addr, sizeof(struct sockaddr_in6));
    if (err != 0)
    {
        ESP_LOGE(TAG, "Socket unable to connect: errno %d", errno);
        tcp_client_task_handler = NULL;
        vTaskDelete(tcp_client_task_handler);
    }
    ESP_LOGI(TAG, "Successfully connected");
    /*ready the json string*/

    // MyStruct1 myData = {1, "John", 123.45};
    // char *jsonString = structToJson(&myData);

    while (1)
    {
        // int err = send(sock, jsonString, strlen(jsonString), 0);
        // if (err < 0)
        // {
        //     ESP_LOGE(TAG, "Error occurred during sending: errno %d", errno);
        //     break;
        // }
        ESP_LOGE(TAG, "receiving");
        int len = recv(sock, rx_buffer, sizeof(rx_buffer) - 1, 0);

        if (len < 0)
        {
            ESP_LOGE(TAG, "recv failed: errno %d", errno);
            break;
        }
        else if (len == 0)
        {
            ESP_LOGE(TAG, "Connection closed");
            break;
        }
        else
        {
            rx_buffer[len] = 0; // Null-terminate whatever we received and treat like a string
            ESP_LOGI(TAG, "Received %d bytes from %s:", len, host_ip);
            ESP_LOGI(TAG, "%s", rx_buffer);

            // Add more debug logs if needed to check the flow

            lv_label_set_text_fmt(ui_checkinOutStatusLabel, "%s", rx_buffer);
            lv_obj_set_width(ui_checkinOutStatusLabel, 250);
            lv_label_set_long_mode(ui_checkinOutStatusLabel, LV_LABEL_LONG_SCROLL_CIRCULAR);
            // MyStruct1 parsedData = parseJson(rx_buffer);
            // ESP_LOGI(TAG, "id: %d name: %s value: %f", parsedData.id, parsedData.name, parsedData.value);
            ESP_LOGI(TAG, "data: %s ", rx_buffer);
            // vTaskDelay(5000 / portTICK_PERIOD_MS);
        }
        vTaskDelay(20 / portTICK_PERIOD_MS);
    }
    if (sock != -1)
    {
        ESP_LOGE(TAG, "Shutting down socket and restarting...");
        shutdown(sock, 0);
        close(sock);
    }
    tcp_client_task_handler = NULL;
    vTaskDelete(tcp_client_task_handler);
}
