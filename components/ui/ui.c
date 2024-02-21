#include <stdio.h>
#include <esp_log.h>
#include "ui.h"
#include "ui_helpers.h"
#include "shared_task.h"
#include "wifi_app.h"

///////////////////// VARIABLES ////////////////////
/* only global objects are here */
// SCREEN: ui_mainScreen
void ui_mainScreen_screen_init(void);
lv_obj_t *ui_mainScreen;
/* containers */
lv_obj_t *ui_iconContainer;
lv_obj_t *ui_bottomContainer;
/* icons */
lv_obj_t *ui_wifiIcon;
lv_obj_t *ui_settingsIcon;
/* labels */
lv_obj_t *ui_label1;
/* buttons */
/* others */
lv_obj_t *ui____initial_actions0;

// SCREEN: ui_setupScreen
void ui_setupScreen_screen_init(void);
lv_obj_t *tabview;
/* wifi tab */
lv_obj_t *ui_setupScreen;
lv_obj_t *ui_wifi_ssid_label;
lv_obj_t *ui_wifi_ssid_dd;
lv_obj_t *ui_wifi_pass_label;
lv_obj_t *ui_wifi_pass_ta;
lv_obj_t *ui_wifi_conn_btn;
lv_obj_t *ui_wifi_conn_btn_label;
lv_obj_t *ui_wifi_scan_btn;
lv_obj_t *ui_wifi_scan_btn_label;
lv_obj_t *ui_wifi_e_conn_btn;
lv_obj_t *ui_wifi_e_conn_btn_label;
lv_obj_t *ui_wifi_tab_label;
lv_obj_t *ui_wifi_save_checkbox;
lv_obj_t *ui_available_network_label;
lv_obj_t *ui_av_network_container;
lv_obj_t *ui_wifi_setup;
lv_obj_t *wn_panel;
lv_obj_t *wnp_close_btn;
lv_obj_t *wnp_msg;
lv_obj_t *spinner;

/* rfid tab */
lv_obj_t *ui_bana_dd;
lv_obj_t *ui_baud_dd;
lv_obj_t *ui_power_txtarea;
lv_obj_t *ui_scantime_txtarea;
lv_obj_t *ui_beepon_switch;
lv_obj_t *ui_reader_info_write;
lv_obj_t *ui_device_id_labelx;
lv_obj_t *ui_version_labelx;
lv_obj_t *ui_protocol_labelx;
lv_obj_t *ui_antenna_labelx;
lv_obj_t *ui_maxf_labelx;
lv_obj_t *ui_minf_labelx;

// GLOB: resources
lv_obj_t *kb;
lv_obj_t *notif_panel;
lv_obj_t *notif_panel_title;
lv_obj_t *notif_close_btn;
lv_obj_t *notif_msg;
lv_obj_t *notif_cross_icon;
bool spin_flag = false;

#if LV_COLOR_DEPTH != 16
#error "LV_COLOR_DEPTH should be 16bit to match SquareLine Studio's settings"
#endif
#if LV_COLOR_16_SWAP != 1
#error "LV_COLOR_16_SWAP should be 1 to match SquareLine Studio's settings"
#endif

///////////////////////////////////////////////////// MAIN SCREEN ////////////////////////////////////////////////

/* go to setup screen */
void settings_icon_event_cb(lv_event_t *event)
{
    lv_scr_load_anim(ui_setupScreen, LV_SCR_LOAD_ANIM_MOVE_LEFT, 200, 0, false);
}

/* wifi icon set/del */
// void wifi_icon_event_cb(lv_event_t *event)
// {
//     ESP_LOGI("wifi_icon", "wifi icon clicked");
// }

///////////////////////////////////////////////////// SETUP SCREEN //////////////////////////////////////////////
////////////WIFI TAB//////////////
/* kb set to pass ta */
void ui_wifi_pass_ta_event_cb(lv_event_t *event)
{
    ESP_LOGI("PASS TA", "pass ta clicked");
    make_kb(ui_wifi_pass_ta);
}

/* initiate wifi scan task */
void ui_wifi_scan_event_cb(lv_event_t *event)
{
    if (wifi_scan_task_handle == NULL)
    {
        xTaskCreatePinnedToCore(wifi_scan_task,
                                "wifi_scan_task",
                                WIFI_SCAN_TASK_STACK_SIZE,
                                NULL, WIFI_TASK_PRIORITY,
                                &wifi_scan_task_handle,
                                WIFI_TASK_CORE);
    }
    else
    {
        ESP_LOGI("WIFI SCAN CB", "wifi scan task already running");
    }
}

/* initiate wifi connection task */
void ui_wifi_conn_event_cb(lv_event_t *event)
{
    kb_del();
    if (wifi_scan_task_handle == NULL)
    {
        xTaskCreatePinnedToCore(wifi_conn_task,
                                "wifi_conn_task",
                                WIFI_CONNECT_TASK_STACK_SIZE,
                                NULL, WIFI_TASK_PRIORITY,
                                &wifi_connect_task_handle,
                                WIFI_TASK_CORE);
    }
    else
    {
        ESP_LOGI("WIFI CONN CB", "wifi conn task already running");
    }
}

void wnp_close_btn_cb(lv_event_t *event)
{
    lv_event_code_t event_code = lv_event_get_code(event);

    if (event_code == LV_EVENT_CLICKED)
    {
        wnp_del("del");
        // lv_obj_add_flag(wn_panel, LV_OBJ_FLAG_HIDDEN);
    }
}
/////////////////////////////////////////////////////////////RFID TAB////////////////////////////////////////////////////////

void ui_reader_power_txtarea_cb(lv_event_t *event)
{
    lv_event_code_t event_code = lv_event_get_code(event);

    if (event_code == LV_EVENT_CLICKED)
    {
        make_kb(ui_power_txtarea);
    }
}
void ui_reader_scantime_txtarea_cb(lv_event_t *event)
{
    lv_event_code_t event_code = lv_event_get_code(event);

    if (event_code == LV_EVENT_CLICKED)
    {
        make_kb(ui_scantime_txtarea);
    }
}
void ui_reader_info_write_cb(lv_event_t *event)
{
    lv_event_code_t event_code = lv_event_get_code(event);

    if (event_code == LV_EVENT_CLICKED)
    {
        if ((READER_WRITE_TASK_HANDLE == NULL) & system_status.reader)
        {
            lv_obj_clear_flag(ui_reader_info_write, LV_OBJ_FLAG_CLICKABLE);

            xTaskCreatePinnedToCore(reader_info_write, "reader_info_write",
                                    RFID_TASK_STACK_SIZE, NULL,
                                    RFID_TASK_PRIORITY,
                                    &READER_WRITE_TASK_HANDLE,
                                    RFID_TASK_CORE);
            ESP_LOGI("reader write", "writing reader info.");
        }
        else
        {
            ESP_LOGI("reader write", "reader write task already running.");
        }
    }
}
void tabview_slider_cb(lv_event_t *event)
{
    lv_event_code_t event_code = lv_event_get_code(event);

    if (event_code == LV_EVENT_VALUE_CHANGED)
    {
        // ESP_LOGI("tabview_slider_cb", "tab: %d", lv_tabview_get_tab_act(tabview));
        if (lv_tabview_get_tab_act(tabview) == 1)
        {
            if (RFID_TASK_HANDLE == NULL) /*if (RFID_TASK_HANDLE == NULL && reader status ok )*/
            {
                if (system_status.reader_data_fetched == false && system_status.reader)
                {
                    xTaskCreatePinnedToCore(reader_info_fetching_task, "reader_info_fetching_task",
                                            RFID_TASK_STACK_SIZE, NULL,
                                            RFID_TASK_PRIORITY,
                                            &RFID_TASK_HANDLE,
                                            RFID_TASK_CORE);
                    ESP_LOGI("tabview_slider_cb", "start fetching reader info.");
                }
                else
                {
                    ESP_LOGI("tabview_slider_cb", "reader info already fetched.");
                }
            }
            else
            {
                ESP_LOGI("tabview_slider_cb", "rfid info task already running");
            }
        }
    }
}

/* go to home */
void ui_home_btn_cb(lv_event_t *event)
{
    // ui_mainScreen_screen_init();
    lv_scr_load_anim(ui_mainScreen, LV_SCR_LOAD_ANIM_MOVE_RIGHT, 200, 0, false);
}

////////////////////////////////////////////////////////// SCREENS ////////////////////////////////////////////////////////////

void ui_init(void)
{
    lv_disp_t *dispp = lv_disp_get_default();
    lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED),
                                              false, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    ui_mainScreen_screen_init();
    ui_setupScreen_screen_init();
    ui____initial_actions0 = lv_obj_create(NULL);
    lv_disp_load_scr(ui_mainScreen);
}

////////////////////////////////////////////////////// GLOB METHODS AND RESOURCES////////////////////////////////////////////////
void make_kb(lv_obj_t *obj)
{
    if (lv_obj_is_valid(kb))
    {
        kb_del();
    }
    else
    {
        kb = lv_keyboard_create(lv_scr_act());
        lv_keyboard_set_textarea(kb, obj);
        lv_keyboard_set_popovers(kb, true);
        lv_obj_add_event_cb(kb, kb_event_cb, LV_EVENT_ALL, NULL);
    }
}
void kb_event_cb(lv_event_t *event)
{
    lv_event_code_t event_code = lv_event_get_code(event);
    if (event_code == LV_EVENT_CANCEL)
    {
        lv_obj_del(kb);
        kb = NULL;
    }
}

void kb_del()
{
    if (lv_obj_is_valid(kb))
    {
        lv_obj_del(kb);
        kb = NULL;
    }
}

void notif_panel_close_event_cb(lv_event_t *event)
{
    // ESP_LOGI("PANEL DEL CB", "CALLED");
    lv_event_code_t event_code = lv_event_get_code(event);
    if (event_code == LV_EVENT_CLICKED)
    {
        if (lv_obj_is_valid(notif_panel))
        {
            ESP_LOGI("PANEL DEL CB", "PANEL NOT NULL");
            lv_obj_add_flag(notif_panel, LV_OBJ_FLAG_HIDDEN);
            lv_obj_del_async(notif_panel);
            notif_panel = NULL;
        }
        else
        {
            ESP_LOGI("PANEL DEL CB", "PANEL IS NULL");
            lv_obj_add_flag(notif_panel, LV_OBJ_FLAG_HIDDEN);
        }
    }
}

void notif_panel_del()
{
    const char *TAG = "notif panel del";
    if (lv_obj_is_valid(notif_panel))
    {
        // lv_obj_add_flag(notif_panel, LV_OBJ_FLAG_HIDDEN);
        lv_obj_del(notif_panel);
        notif_panel = NULL;
        ESP_LOGI(TAG, "notification panel deleted.");
    }
    else
    {
        ESP_LOGI(TAG, "PANEL IS NULL");
        lv_obj_add_flag(notif_panel, LV_OBJ_FLAG_HIDDEN);
    }
}

void create_notif_panel(const char *title, const char *msg, bool _spin)
{
    if (lv_obj_is_valid(notif_panel))
    {
        ESP_LOGI("PANEL CREATE", "PANEL ALREADY EXIST");
    }
    {
        notif_panel = lv_obj_create(lv_scr_act());
        lv_obj_set_height(notif_panel, lv_pct(50));
        lv_obj_set_width(notif_panel, lv_pct(70));
        lv_obj_set_align(notif_panel, LV_ALIGN_CENTER);
        lv_obj_set_style_radius(notif_panel, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_shadow_color(notif_panel, lv_color_hex(0x655151), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_shadow_opa(notif_panel, 150, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_shadow_width(notif_panel, 30, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_shadow_spread(notif_panel, 500, LV_PART_MAIN | LV_STATE_DEFAULT);

        notif_panel_title = lv_label_create(notif_panel);
        lv_label_set_text(notif_panel_title, title);
        lv_obj_align(notif_panel_title, LV_ALIGN_TOP_LEFT, 0, 0);

        notif_close_btn = lv_btn_create(notif_panel);
        lv_obj_set_height(notif_close_btn, 25);
        lv_obj_set_width(notif_close_btn, 25);
        lv_obj_align(notif_close_btn, LV_ALIGN_TOP_RIGHT, 0, 0);
        lv_obj_set_ext_click_area(notif_close_btn, 10);
        // lv_obj_clear_flag(notif_close_btn, LV_OBJ_FLAG_CLICKABLE);

        notif_cross_icon = lv_label_create(notif_close_btn);
        lv_obj_align(notif_cross_icon, LV_ALIGN_CENTER, 0, 0);
        lv_label_set_text(notif_cross_icon, LV_SYMBOL_CLOSE);

        notif_msg = lv_label_create(notif_panel);
        lv_label_set_text(notif_msg, msg);

        spin_flag = _spin;
        if (spin_flag == true)
        {
            lv_obj_t *spinner = lv_spinner_create(notif_panel, 1000, 60);
            lv_obj_set_height(spinner, 45);
            lv_obj_set_width(spinner, 45);
            lv_obj_align(spinner, LV_ALIGN_CENTER, 0, -8);
            lv_obj_align(notif_msg, LV_ALIGN_CENTER, 0, 27);
        }
        else
        {
            lv_obj_align(notif_msg, LV_ALIGN_CENTER, 0, 0);
        }
        ESP_LOGI("PANEL CREATE", "PANEL CREATED");
        lv_obj_add_event_cb(notif_close_btn, notif_panel_close_event_cb, LV_EVENT_CLICKED, NULL);
    }
}

void notif_msg_update(const char *msg)
{
    if (lv_obj_is_valid(notif_panel))
    {
        lv_label_set_text(notif_msg, msg);
    }
}
