#include "shared_task.h"
#include "lvgl.h"
#include "lvgl_helpers.h"
#include "ui.h"
#include "wifi_app.h"
#include "nvs_flash.h"
#include "inventory.h"
#include "system_status.h"
#include "sd_fat.h"
#include <esp_sleep.h>

/* Defines */
#define LV_TICK_PERIOD_MS 10
SemaphoreHandle_t xGuiSemaphore;
/* sleep timer */
#define SLEEP_TIME_MINUTES 20
#define TIMER_INTERVAL_MS (SLEEP_TIME_MINUTES * 60 * 1000)
// uint32_t timer_interval = SLEEP_TIME_MINUTES * 20 * 1000;

/* Prototypes */
static void sleep_timer_callback(TimerHandle_t xTimer);
static void init_sleep_timer();
static void lv_tick_task(void *arg);
static void ui_task(void *pvParameter);
static void gpioConfig();

/* Task handler */
TaskHandle_t GUI_TASK_HANDLE = NULL, sleep_timer_handler;

/* error handling */
esp_err_t err;

extern "C" void app_main()
{
  /* Initialize NVS */
  esp_err_t err = nvs_flash_init();
  if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND)
  {
    ESP_ERROR_CHECK(nvs_flash_erase());
    err = nvs_flash_init();
  }
  ESP_ERROR_CHECK(err);

  /* enable wake up sources */
  esp_sleep_enable_ext0_wakeup(GPIO_NUM_36, 0);
  esp_sleep_enable_ext1_wakeup((1ULL << GPIO_NUM_4), ESP_EXT1_WAKEUP_ALL_LOW);

  /* initialize sleep timer */
  init_sleep_timer();

  /* Start system status event */
  systemStatusEventGroup = xEventGroupCreate();
  xTaskCreatePinnedToCore(ui_task, "gui", GUI_TASK_STACK_SIZE, NULL, GUI_TASK_PRIORITY, &GUI_TASK_HANDLE, GUI_TASK_CORE);

  /* Wait for the UI to initialize using event groups */
  bits = xEventGroupWaitBits(systemStatusEventGroup, UI_INITIALIZED_BIT, pdTRUE, pdTRUE, portMAX_DELAY);

  /* Open com for reader, return false if reader is not connected */
  bool stat = OpenComPort("COMX", 57600);
  const char *bool_to_str;

  /* Create notification panel to show initialization status*/
  create_notif_panel("Init: reader", "", true);
  lv_label_set_text_fmt(notif_msg, "Com status: %s\nBaudrate: 57600", bool_to_str = (stat) ? "OK" : "FAILED");

  /* Init reader */
  stat = GetSettings(&ri);
  system_status.reader = stat;
  lv_label_set_text_fmt(notif_msg, "Reader status: %s", bool_to_str = (stat) ? "OK" : "FAILED");
  vTaskDelay(700 / portTICK_PERIOD_MS);

  /* init sd card */
  lv_label_set_text(notif_panel_title, "Init: SD card");
  lv_label_set_text(notif_msg, "Getting sd status...");
  initSD();
  vTaskDelay(700 / portTICK_PERIOD_MS);
  lv_label_set_text_fmt(notif_msg, "SD status: %s", esp_err_to_name(sd_card_error));
  vTaskDelay(1000 / portTICK_PERIOD_MS);

  /* Init wifi driver */
  lv_label_set_text(notif_panel_title, "Init: WiFi");
  lv_label_set_text(notif_msg, "Getting wifi status...");
  wifi_init_sta();

  /* Wait for wifistatus connected/disconnected */
  bits = xEventGroupWaitBits(systemStatusEventGroup, WIFI_FAIL_BIT | WIFI_CONNECTED_BIT, pdTRUE, pdFALSE, 5000 / portTICK_PERIOD_MS);
  if (bits & WIFI_CONNECTED_BIT)
  {
    lv_label_set_text_fmt(notif_msg, "Wifi status: %s", "Connected");
  }
  else if (bits & WIFI_FAIL_BIT)
  {
    lv_label_set_text_fmt(notif_msg, "Wifi status: %s", "Not connected");
  }
  else
  {
    lv_label_set_text_fmt(notif_msg, "Wifi status: %s", esp_err_to_name(wifi_connect_error));
    __log(" Conn stat: %s ", esp_err_to_name(wifi_connect_error));
  }

  /* Delete the event group when it's no longer needed  */
  // vEventGroupDelete(systemStatusEventGroup);

  vTaskDelay(1200 / portTICK_PERIOD_MS);

  notif_panel_del();

  /* config gpio for scn interrupt */
  gpioConfig();
}

static void ui_task(void *pvParameter)
{
  (void)pvParameter;
  xGuiSemaphore = xSemaphoreCreateMutex();

  /* init lvgl */
  lv_init();

  /* Initialize SPI or I2C bus used by the drivers */
  lvgl_driver_init();

  /* Initialize the working buffers. */
  static lv_color_t buf1[DISP_BUF_SIZE];
  static lv_color_t buf2[DISP_BUF_SIZE];

  /*register DISP driver*/
  static lv_disp_draw_buf_t disp_buf;
  uint32_t size_in_px = DISP_BUF_SIZE;

  lv_disp_draw_buf_init(&disp_buf, buf1, buf2, size_in_px);
  static lv_disp_drv_t disp_drv;
  lv_disp_drv_init(&disp_drv);
  disp_drv.draw_buf = &disp_buf;
  disp_drv.flush_cb = disp_driver_flush;
  disp_drv.hor_res = LV_HOR_RES_MAX;
  disp_drv.ver_res = LV_VER_RES_MAX;
  // disp_drv.rotated = 1;
  lv_disp_drv_register(&disp_drv);

  /*register TOUCH driver*/
  lv_indev_drv_t indev_drv;
  lv_indev_drv_init(&indev_drv);
  indev_drv.read_cb = touch_driver_read;
  indev_drv.type = LV_INDEV_TYPE_POINTER;
  lv_indev_drv_register(&indev_drv);

  /* Create and start a periodic timer interrupt to call lv_tick_inc */
  const esp_timer_create_args_t periodic_timer_args = {
      .callback = &lv_tick_task, .name = "periodic_gui"};
  esp_timer_handle_t periodic_timer;
  ESP_ERROR_CHECK(esp_timer_create(&periodic_timer_args, &periodic_timer));
  ESP_ERROR_CHECK(esp_timer_start_periodic(periodic_timer, LV_TICK_PERIOD_MS * 1000));

  /* initializr UI created with lvgl, squareline studo */
  ui_init();
  xEventGroupSetBits(systemStatusEventGroup, UI_INITIALIZED_BIT);

  while (1)
  {
    vTaskDelay(pdMS_TO_TICKS(10));
    /* Try to take the semaphore, call lvgl related function on success */
    if (pdTRUE == xSemaphoreTake(xGuiSemaphore, portMAX_DELAY))
    {
      lv_task_handler();
      xSemaphoreGive(xGuiSemaphore);
    }
  }
  vTaskDelete(GUI_TASK_HANDLE);
}

/* lvgl timer task */
static void lv_tick_task(void *arg)
{
  (void)arg;

  lv_tick_inc(LV_TICK_PERIOD_MS);
}
/* gpio and scan interrupt handler */
void gpioConfig()
{
  // Configure button GPIO as input
  gpio_config_t io_conf = {
      .pin_bit_mask = (1ULL << BUTTON_PIN),
      .mode = GPIO_MODE_INPUT,
      .pull_up_en = GPIO_PULLUP_ENABLE,
      .intr_type = GPIO_INTR_NEGEDGE,
  };
  gpio_config(&io_conf);

  // Install ISR service with default configuration
  gpio_install_isr_service(0);

  // Hook ISR handler to the button pin
  gpio_isr_handler_add(BUTTON_PIN, button_isr_handler, (void *)BUTTON_PIN);
}

/* sleep timer function definations */
static void sleep_timer_callback(TimerHandle_t xTimer)
{
  // Set GPIO 21 low
  // gpio_set_level(GPIO_NUM_21, 0);
  __log("Going to light sleep after %u minutes.", SLEEP_TIME_MINUTES);
  // xTimerChangePeriod(xTimer, pdMS_TO_TICKS(timer_interval), 100);
  // esp_light_sleep_start();
  esp_deep_sleep_start();
  // gpio_set_level(GPIO_NUM_21, 1);
}

static void init_sleep_timer()
{
  sleep_timer_handler = xTimerCreate("SleepTimer", pdMS_TO_TICKS(TIMER_INTERVAL_MS), pdTRUE, (void *)0, sleep_timer_callback);

  if (sleep_timer_handler != NULL)
  {
    xTimerStart(sleep_timer_handler, 0);
  }
}
// MUTEX
/*

    if (pdTRUE == xSemaphoreTake(xGuiSemaphore, portMAX_DELAY))
    {
      lv_task_handler();
      xSemaphoreGive(xGuiSemaphore);
    }


*/