/* SD card and FAT filesystem example.
   This example uses SPI peripheral to communicate with SD card.

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include "esp_system.h"
#include <esp_log.h>
#include "esp_event.h"
#include "driver/gpio.h"
#include <string.h>
#include <sys/unistd.h>
#include <sys/stat.h>
#include "esp_vfs_fat.h"
#include "sdmmc_cmd.h"
#include "lvgl.h"
#include <dirent.h>
#include <string.h>
#include "ui.h"
#include "system_status.h"

/* error status */
esp_err_t sd_card_error = -1;

#define MOUNT_POINT "/S"

// Pin assignments can be set in menuconfig, see "SD SPI Example Configuration" menu.
// You can also change the pin assignments here by changing the following 4 lines.
#define PIN_NUM_MISO 19
#define PIN_NUM_MOSI 23
#define PIN_NUM_CLK 18
#define PIN_NUM_CS 5

char **listFilesAndFolders(const char *path, int *numFiles)
{
    DIR *dir = opendir(path);
    struct dirent *entry;
    lv_obj_t *notif;
    notif = lv_label_create(ui_checkinOutScreen);
    lv_label_set_text(notif, "");
    // lv_obj_set_width(notif, 300);
    lv_obj_set_align(notif, LV_ALIGN_BOTTOM_LEFT);
    // lv_obj_set_y(notif, -30);
    // lv_label_set_long_mode(notif, LV_LABEL_LONG_SCROLL_CIRCULAR);

    if (dir == NULL)
    {
        __log("Dir is NULL");
        lv_label_set_text(notif, "DIR status: Dir is NULL");
        return NULL;
    }

    // Count the number of files in the directory
    *numFiles = 0;
    while ((entry = readdir(dir)) != NULL)
    {
        (*numFiles)++;
    }
    closedir(dir);

    // Open the directory again to read filenames
    dir = opendir(path);
    if (dir == NULL)
    {
        __log("Unable to open directory");
        lv_label_set_text(notif, "DIR status: Unable to open directory");
        return NULL;
    }

    // Allocate memory for the array of strings
    char **fileArray = (char **)malloc(*numFiles * sizeof(char *));
    if (fileArray == NULL)
    {
        __log("fileArray: Memory allocation error");
        lv_label_set_text(notif, "fileArray: Memory allocation error");
        closedir(dir);
        return NULL;
    }

    // Read filenames and copy them to the array
    int i = 0;
    while ((entry = readdir(dir)) != NULL)
    {
        fileArray[i] = strdup(entry->d_name);
        // ESP_LOGI(TAG, "%s", fileArray[i]);
        i++;
    }

    closedir(dir);
    lv_label_set_text(notif, "DIR status: OK");
    return fileArray;
}
void initSD()
{
    // Options for mounting the filesystem.
    // If format_if_mount_failed is set to true, SD card will be partitioned and
    // formatted in case when mounting fails.
    esp_vfs_fat_sdmmc_mount_config_t mount_config = {
#ifdef CONFIG_EXAMPLE_FORMAT_IF_MOUNT_FAILED
        .format_if_mount_failed = true,
#else
        .format_if_mount_failed = false,
#endif // EXAMPLE_FORMAT_IF_MOUNT_FAILED
        .max_files = 5,
        .allocation_unit_size = 16 * 1024};
    sdmmc_card_t *card;
    const char mount_point[] = MOUNT_POINT;
    __log("Initializing SD card");

    // Use settings defined above to initialize SD card and mount FAT filesystem.
    // Note: esp_vfs_fat_sdmmc/sdspi_mount is all-in-one convenience functions.
    // Please check its source code and implement error recovery when developing
    // production applications.
    __log("Using SPI peripheral");

    sdmmc_host_t host = SDSPI_HOST_DEFAULT();
    spi_bus_config_t bus_cfg = {
        .mosi_io_num = PIN_NUM_MOSI,
        .miso_io_num = PIN_NUM_MISO,
        .sclk_io_num = PIN_NUM_CLK,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
        .max_transfer_sz = 4000,
    };
    sd_card_error = spi_bus_initialize(host.slot, &bus_cfg, SDSPI_DEFAULT_DMA);
    if (sd_card_error != ESP_OK)
    {
        __log("Failed to initialize bus.");
        return;
    }

    // This initializes the slot without card detect (CD) and write protect (WP) signals.
    // Modify slot_config.gpio_cd and slot_config.gpio_wp if your board has these signals.
    sdspi_device_config_t slot_config = SDSPI_DEVICE_CONFIG_DEFAULT();
    slot_config.gpio_cs = PIN_NUM_CS;
    slot_config.host_id = host.slot;

    __log("Mounting filesystem");
    sd_card_error = esp_vfs_fat_sdspi_mount(mount_point, &host, &slot_config, &mount_config, &card);

    if (sd_card_error != ESP_OK)
    {
        if (sd_card_error == ESP_FAIL)
        {
            __log("Failed to mount filesystem. "
                  "If you want the card to be formatted, set the CONFIG_EXAMPLE_FORMAT_IF_MOUNT_FAILED menuconfig option.");
            return;
        }
        else
        {
            __log("Failed to initialize the card (%s). "
                  "Make sure SD card lines have pull-up resistors in place.",
                  esp_err_to_name(sd_card_error));
            return;
        }
    }
    __log("Filesystem mounted");

    // Card has been initialized, print its properties
    sdmmc_card_print_info(stdout, card);
    // deinitialize the bus after all devices are removed
    // spi_bus_free(host.slot);
}

/* file io example */
// Use POSIX and C standard library functions to work with files.
// First create a file.
// const char *file_hello = MOUNT_POINT "/hello.txt";

// ESP_LOGI(TAG, "Opening file %s", file_hello);
// FILE *f = fopen(file_hello, "w");
// if (f == NULL)
// {
//     ESP_LOGE(TAG, "Failed to open file for writing");
//     return;
// }
// fprintf(f, "Hello %s!\n", card->cid.name);
// fclose(f);
// ESP_LOGI(TAG, "File written");

// const char *file_foo = MOUNT_POINT "/foo.txt";

// // Check if destination file exists before renaming
// struct stat st;
// if (stat(file_foo, &st) == 0)
// {
//     // Delete it if it exists
//     unlink(file_foo);
// }

// // Rename original file
// ESP_LOGI(TAG, "Renaming file %s to %s", file_hello, file_foo);
// if (rename(file_hello, file_foo) != 0)
// {
//     ESP_LOGE(TAG, "Rename failed");
//     return;
// }

// // Open renamed file for reading
// ESP_LOGI(TAG, "Reading file %s", file_foo);
// f = fopen(file_foo, "r");
// if (f == NULL)
// {
//     ESP_LOGE(TAG, "Failed to open file for reading");
//     return;
// }

// // Read a line from file
// char line[64];
// fgets(line, sizeof(line), f);
// fclose(f);

// // Strip newline
// char *pos = strchr(line, '\n');
// if (pos)
// {
//     *pos = '\0';
// }
// ESP_LOGI(TAG, "Read from file: '%s'", line);

// All done, unmount partition and disable SPI peripheral
// esp_vfs_fat_sdcard_unmount(mount_point, card);
// ESP_LOGI(TAG, "Card unmounted");
