#include <stdio.h>
#include <esp_log.h>
#include "ui.h"
#include "ui_helpers.h"
#include "shared_task.h"
#include "wifi_app.h"
#include "system_status.h"

#if LV_COLOR_DEPTH != 16
#error "LV_COLOR_DEPTH should be 16bit to match SquareLine Studio's settings"
#endif
#if LV_COLOR_16_SWAP != 1
#error "LV_COLOR_16_SWAP should be 1 to match SquareLine Studio's settings"
#endif

/* only global objects are here */

////////////////////////////////////////////////////////////// SCREEN: ui_mainScreen  //////////////////////////////////////////////////////////

/* filter panel global objects */
// global obj
lv_obj_t *ui____initial_actions0;
static lv_obj_t *ui_mainScrPanel; // this file only

/* go to setup screen */
void ui_event_settings_icon(lv_event_t *event)
{
    // ui_setupScreen_screen_init();
    /* currently not deleting main screen bcz */
    lv_scr_load_anim(ui_setupScreen, LV_SCR_LOAD_ANIM_MOVE_LEFT, 100, 0, false);
}
/* demo agent functionality */
void ui_event_agent_btn(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    if (event_code == LV_EVENT_CLICKED)
    {
        ui_checkin_checkoutScreen_screen_init();
        __log("ui_checkin_checkoutScreen_screen_init()");
        lv_scr_load_anim(ui_checkinOutScreen, LV_SCR_LOAD_ANIM_MOVE_LEFT, 50, 0, true);
    }
}

/* enable/disable scan filter */
void ui_event_filter_switch(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    if (event_code == LV_EVENT_CLICKED)
    {
        if (filterOn)
        {
            lv_label_set_text(ui_filterBtnLbl, "F:0");
            filterOn = false;
        }
        else
        {
            makeFilterPanel();
            lv_label_set_text(ui_filterBtnLbl, "F:1");
            filterOn = true;
        }
    }
}

/* write data and activate filter */
void ui_event_filter_panel_write(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    if (event_code == LV_EVENT_CLICKED)
    {
        set_scan_filter(e);
        kb_del();
        delFilterPanel(ui_mainScrPanel);
        // _ui_flag_modify(ui_main_scr_keyboard, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
    }
}

/* closes filter panel and disable any filter */
void ui_event_filter_panel_close(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    if (event_code == LV_EVENT_CLICKED)
    {
        delFilterPanel(ui_mainScrPanel);
    }
}

/* filter panel offset textarea */
void ui_event_filter_panel_offset_ta(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    if (event_code == LV_EVENT_CLICKED)
    {
        make_kb(ui_mainScrOffsetTextarea);
    }
}

/* filter panel data textarea */
void ui_event_filter_panel_data_ta(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    if (event_code == LV_EVENT_CLICKED)
    {
        lv_obj_move_background(epc_table);
        make_kb(ui_mainScrDataTextarea);
    }
}

/* enables/disables inventory merge */
void ui_event_merge_sw(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    if (event_code == LV_EVENT_CLICKED)
    {
        merge_switch_click(e);
    }
}

/* press and hold epc col to access its memory */
void ui_event_main_table_cb(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    if (event_code == LV_EVENT_LONG_PRESSED)
    {
        lv_table_get_selected_cell(epc_table, &row_, &col_);
        __log("row: %u, col %u\n", row_, col_);
        if (row_ > 0 && col_ < 1)
        {

            ui_memScreen_screen_init();
            lv_scr_load_anim(ui_memScreen, LV_SCR_LOAD_ANIM_MOVE_LEFT, 100, 0, false);
            mem_screen(e);
        }
        else
        {
            __log("Invalid cell");
        }
    }
}

///////////////////////////////////////////////////////////// SCREEN: ui_memScreen    ///////////////////////////////////////////////////////////
/* static prototypes */
static void make_tdw_panel();
static void make_ta_panel();

static lv_obj_t *ui_tag_data_write_panel;
lv_obj_t *ui_tdwp_dat_ta;

static lv_obj_t *ui_tag_auth_panel;
lv_obj_t *ui_tap_pass_ascii_ta;
lv_obj_t *ui_tap_pass_hex_ta;

/* make auth panel */
void ui_event_tap_create(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    if (event_code == LV_EVENT_CLICKED)
    {
        make_ta_panel();
        // create auth panel
    }
}
/* del auth panel */
void ui_event_tap_close(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    if (event_code == LV_EVENT_CLICKED)
    {
        if (lv_obj_is_valid(ui_tag_auth_panel))
        {
            lv_obj_del(ui_tag_auth_panel);
            ui_tag_auth_panel = NULL;
            __log("obj 'ui_tag_auth_panel' deleted");
        }
        else
        {
            __log("failed to del obj 'ui_tag_auth_panel' null");
        }
    }
}
void ui_event_tap_pass_ascii_ta(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    if (event_code == LV_EVENT_CLICKED)
    {
        make_kb(ui_tap_pass_ascii_ta);
    }
}
void ui_event_tap_pass_ascii_ta_vc(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    if (event_code == LV_EVENT_VALUE_CHANGED)
    {
        onChangeASCII(e);
    }
}
void ui_event_tap_pass_hex_ta(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if (event_code == LV_EVENT_CLICKED)
    {
        make_kb(ui_tap_pass_hex_ta);
    }
}
void ui_event_tap_pass_hex_ta_vc(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    if (event_code == LV_EVENT_VALUE_CHANGED)
    {
        onChangeHEX(e);
    }
}

void ui_event_tag_data_table(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    if (event_code == LV_EVENT_LONG_PRESSED)
    {
        lv_table_get_selected_cell(tag_data_table, &row_, &col_);
        make_tdw_panel();
    }
}
void ui_event_tdwp_close(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    if (event_code == LV_EVENT_CLICKED)
    {
        if (lv_obj_is_valid(ui_tag_data_write_panel))
        {
            lv_obj_del(ui_tag_data_write_panel);
            ui_tag_data_write_panel = NULL;
            __log("obj 'ui_tag_data_write' deleted");
        }
        else
        {
            __log("failed to del obj 'ui_tag_data_write' null");
        }
    }
}
void ui_event_tdwp_data_ta(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    if (event_code == LV_EVENT_CLICKED)
    {
        make_kb(ui_tdwp_dat_ta);
    }
}
void ui_event_tdwp_write_btn(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    if (event_code == LV_EVENT_CLICKED)
    {
        /* starts write task in uievents.cpp */
        tdw_panel_write_cb(e);

        if (lv_obj_is_valid(ui_tag_data_write_panel))
        {
            lv_obj_del(ui_tag_data_write_panel);
            ui_tag_data_write_panel = NULL;
            __log("obj 'ui_tag_data_write' deleted");
        }
        else
        {
            __log("failed to del obj 'ui_tag_data_write' null");
        }
    }
}

void ui_home2_btn_cb(lv_event_t *event)
{
    // ui_mainScreen_screen_init();
    lv_scr_load_anim(ui_mainScreen, LV_SCR_LOAD_ANIM_MOVE_RIGHT, 100, 0, true);
}

static void make_tdw_panel()
{
    lv_obj_t *ui_tdwp_close;
    lv_obj_t *ui_tdwp_close_label;
    lv_obj_t *ui_tdwp_label;
    lv_obj_t *ui_tdwp_data_write;
    lv_obj_t *ui_tdwp_data_write_label;

    if (!lv_obj_is_valid(ui_tag_data_write_panel))
    {
        ui_tag_data_write_panel = lv_obj_create(lv_scr_act());
        lv_obj_set_width(ui_tag_data_write_panel, lv_pct(50));
        lv_obj_set_height(ui_tag_data_write_panel, lv_pct(33));
        lv_obj_set_x(ui_tag_data_write_panel, -3);
        lv_obj_set_y(ui_tag_data_write_panel, -56);
        lv_obj_set_align(ui_tag_data_write_panel, LV_ALIGN_CENTER);
        // lv_obj_add_flag(ui_tag_data_write_panel, LV_OBJ_FLAG_HIDDEN);       /// Flags
        lv_obj_clear_flag(ui_tag_data_write_panel, LV_OBJ_FLAG_SCROLLABLE); /// Flags
        lv_obj_set_style_shadow_color(ui_tag_data_write_panel, lv_color_hex(0x655151), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_shadow_opa(ui_tag_data_write_panel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_shadow_width(ui_tag_data_write_panel, 30, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_shadow_spread(ui_tag_data_write_panel, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_shadow_ofs_x(ui_tag_data_write_panel, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_shadow_ofs_y(ui_tag_data_write_panel, 5, LV_PART_MAIN | LV_STATE_DEFAULT);

        ui_tdwp_close = lv_btn_create(ui_tag_data_write_panel);
        lv_obj_set_height(ui_tdwp_close, 25);
        lv_obj_set_width(ui_tdwp_close, 25);
        lv_obj_align(ui_tdwp_close, LV_ALIGN_OUT_TOP_LEFT, 0, 0);
        lv_obj_set_ext_click_area(ui_tdwp_close, 10);

        ui_tdwp_close_label = lv_label_create(ui_tdwp_close);
        lv_obj_align(ui_tdwp_close_label, LV_ALIGN_CENTER, 0, 0);
        lv_label_set_text(ui_tdwp_close_label, LV_SYMBOL_CLOSE);

        ui_tdwp_label = lv_label_create(ui_tag_data_write_panel);
        lv_obj_set_width(ui_tdwp_label, LV_SIZE_CONTENT);  /// 1
        lv_obj_set_height(ui_tdwp_label, LV_SIZE_CONTENT); /// 1
        lv_obj_set_x(ui_tdwp_label, -43);
        lv_obj_set_y(ui_tdwp_label, -7);
        lv_obj_set_align(ui_tdwp_label, LV_ALIGN_CENTER);
        lv_label_set_text(ui_tdwp_label, "Enter data :");

        ui_tdwp_dat_ta = lv_textarea_create(ui_tag_data_write_panel);
        lv_obj_set_width(ui_tdwp_dat_ta, 80);
        lv_obj_set_height(ui_tdwp_dat_ta, 29);
        lv_obj_set_x(ui_tdwp_dat_ta, 30);
        lv_obj_set_y(ui_tdwp_dat_ta, -6);
        lv_obj_set_align(ui_tdwp_dat_ta, LV_ALIGN_CENTER);
        lv_textarea_set_accepted_chars(ui_tdwp_dat_ta, "abcdefABCDEF0123456789");
        lv_obj_clear_flag(ui_tdwp_dat_ta,
                          LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC |
                              LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags

        ui_tdwp_data_write = lv_btn_create(ui_tag_data_write_panel);
        lv_obj_set_width(ui_tdwp_data_write, lv_pct(30));
        lv_obj_set_height(ui_tdwp_data_write, lv_pct(40));
        lv_obj_set_x(ui_tdwp_data_write, lv_pct(38));
        lv_obj_set_y(ui_tdwp_data_write, lv_pct(47));
        lv_obj_set_align(ui_tdwp_data_write, LV_ALIGN_CENTER);
        lv_obj_add_flag(ui_tdwp_data_write, LV_OBJ_FLAG_SCROLL_ON_FOCUS); /// Flags
        lv_obj_clear_flag(ui_tdwp_data_write, LV_OBJ_FLAG_SCROLLABLE);    /// Flags
        lv_obj_set_style_radius(ui_tdwp_data_write, 1, LV_PART_MAIN | LV_STATE_DEFAULT);

        ui_tdwp_data_write_label = lv_label_create(ui_tdwp_data_write);
        lv_obj_set_width(ui_tdwp_data_write_label, LV_SIZE_CONTENT);  /// 1
        lv_obj_set_height(ui_tdwp_data_write_label, LV_SIZE_CONTENT); /// 1
        lv_obj_set_x(ui_tdwp_data_write_label, lv_pct(-5));
        lv_obj_set_y(ui_tdwp_data_write_label, lv_pct(0));
        lv_obj_set_align(ui_tdwp_data_write_label, LV_ALIGN_CENTER);
        lv_label_set_text(ui_tdwp_data_write_label, "Write");
        lv_obj_set_style_text_font(ui_tdwp_data_write_label, &lv_font_montserrat_10, LV_PART_MAIN | LV_STATE_DEFAULT);

        /* tag data write panel cb*/
        lv_obj_add_event_cb(ui_tdwp_close, ui_event_tdwp_close, LV_EVENT_ALL, NULL);
        lv_obj_add_event_cb(ui_tdwp_dat_ta, ui_event_tdwp_data_ta, LV_EVENT_ALL, NULL);
        lv_obj_add_event_cb(ui_tdwp_data_write, ui_event_tdwp_write_btn, LV_EVENT_ALL, NULL);
        __log("obj 'ui_tag_data_write_panel' created");
    }
    else
    {
        __log("obj 'ui_tag_data_write_panel' already exist");
    }
}

static void make_ta_panel()
{

    lv_obj_t *ui_tap_close;
    lv_obj_t *ui_tap_close_label;
    lv_obj_t *ui_tap_pass_ascii_label;

    lv_obj_t *ui_tap_pass_hex_label;
    lv_obj_t *ui_pass_use_btn;
    lv_obj_t *ui_passwrite_btn;
    if (!lv_obj_is_valid(ui_tag_auth_panel))
    {
        /*AUTH PANEL*/
        ui_tag_auth_panel = lv_obj_create(lv_scr_act());
        lv_obj_set_width(ui_tag_auth_panel, lv_pct(65));
        lv_obj_set_height(ui_tag_auth_panel, lv_pct(43));
        lv_obj_set_x(ui_tag_auth_panel, -1);
        lv_obj_set_y(ui_tag_auth_panel, -61);
        lv_obj_set_align(ui_tag_auth_panel, LV_ALIGN_CENTER);
        // lv_obj_add_flag(ui_tag_auth_panel, LV_OBJ_FLAG_HIDDEN);       /// Flags
        lv_obj_clear_flag(ui_tag_auth_panel, LV_OBJ_FLAG_SCROLLABLE); /// Flags
        lv_obj_set_style_radius(ui_tag_auth_panel, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_shadow_color(ui_tag_auth_panel, lv_color_hex(0x655151), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_shadow_opa(ui_tag_auth_panel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_shadow_width(ui_tag_auth_panel, 30, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_shadow_spread(ui_tag_auth_panel, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_shadow_ofs_x(ui_tag_auth_panel, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_shadow_ofs_y(ui_tag_auth_panel, 5, LV_PART_MAIN | LV_STATE_DEFAULT);

        ui_tap_close = lv_btn_create(ui_tag_auth_panel);
        lv_obj_set_height(ui_tap_close, 25);
        lv_obj_set_width(ui_tap_close, 25);
        lv_obj_align(ui_tap_close, LV_ALIGN_OUT_TOP_LEFT, 0, 0);
        lv_obj_set_ext_click_area(ui_tap_close, 10);

        ui_tap_close_label = lv_label_create(ui_tap_close);
        lv_obj_align(ui_tap_close_label, LV_ALIGN_CENTER, 0, 0);
        lv_label_set_text(ui_tap_close_label, LV_SYMBOL_CLOSE);

        ui_tap_pass_ascii_label = lv_label_create(ui_tag_auth_panel);
        lv_obj_set_width(ui_tap_pass_ascii_label, LV_SIZE_CONTENT);  /// 1
        lv_obj_set_height(ui_tap_pass_ascii_label, LV_SIZE_CONTENT); /// 1
        lv_obj_set_x(ui_tap_pass_ascii_label, -55);
        lv_obj_set_y(ui_tap_pass_ascii_label, -26);
        lv_obj_set_align(ui_tap_pass_ascii_label, LV_ALIGN_CENTER);
        lv_label_set_text(ui_tap_pass_ascii_label, "Pass. ASCII");
        lv_obj_set_style_text_font(ui_tap_pass_ascii_label, &lv_font_montserrat_10, LV_PART_MAIN | LV_STATE_DEFAULT);

        ui_tap_pass_ascii_ta = lv_textarea_create(ui_tag_auth_panel);
        lv_obj_set_width(ui_tap_pass_ascii_ta, 100);
        lv_obj_set_height(ui_tap_pass_ascii_ta, 28);
        lv_obj_set_x(ui_tap_pass_ascii_ta, lv_pct(17));
        lv_obj_set_y(ui_tap_pass_ascii_ta, lv_pct(-40));
        lv_obj_set_align(ui_tap_pass_ascii_ta, LV_ALIGN_CENTER);
        lv_textarea_set_accepted_chars(ui_tap_pass_ascii_ta, " ABCDEFGHIJKLMNOPQRSTUVWXYZ_-.@#");
        lv_obj_clear_flag(ui_tap_pass_ascii_ta,
                          LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE |
                              LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
        lv_obj_set_style_text_font(ui_tap_pass_ascii_ta, &lv_font_montserrat_10, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_radius(ui_tap_pass_ascii_ta, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_textarea_set_max_length(ui_tap_pass_ascii_ta, 6);

        ui_tap_pass_hex_ta = lv_textarea_create(ui_tag_auth_panel);
        lv_obj_set_width(ui_tap_pass_hex_ta, 100);
        lv_obj_set_height(ui_tap_pass_hex_ta, 28);
        lv_obj_set_x(ui_tap_pass_hex_ta, lv_pct(17));
        lv_obj_set_y(ui_tap_pass_hex_ta, lv_pct(4));
        lv_obj_set_align(ui_tap_pass_hex_ta, LV_ALIGN_CENTER);
        lv_textarea_set_accepted_chars(ui_tap_pass_hex_ta, "abcdefABCDEF0123456789");
        lv_obj_clear_flag(ui_tap_pass_hex_ta,
                          LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE |
                              LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
        lv_obj_set_style_text_font(ui_tap_pass_hex_ta, &lv_font_montserrat_10, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_radius(ui_tap_pass_hex_ta, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_textarea_set_max_length(ui_tap_pass_hex_ta, 8);

        ui_tap_pass_hex_label = lv_label_create(ui_tag_auth_panel);
        lv_obj_set_width(ui_tap_pass_hex_label, LV_SIZE_CONTENT);  /// 1
        lv_obj_set_height(ui_tap_pass_hex_label, LV_SIZE_CONTENT); /// 1
        lv_obj_set_x(ui_tap_pass_hex_label, -57);
        lv_obj_set_y(ui_tap_pass_hex_label, 1);
        lv_obj_set_align(ui_tap_pass_hex_label, LV_ALIGN_CENTER);
        lv_label_set_text(ui_tap_pass_hex_label, "Pass. HEX");
        lv_obj_set_style_text_font(ui_tap_pass_hex_label, &lv_font_montserrat_10, LV_PART_MAIN | LV_STATE_DEFAULT);

        /* tag auth panel cb*/

        lv_obj_add_event_cb(ui_tap_close, ui_event_tap_close, LV_EVENT_ALL, NULL);
        lv_obj_add_event_cb(ui_tap_pass_ascii_ta, ui_event_tap_pass_ascii_ta, LV_EVENT_ALL, NULL);
        lv_obj_add_event_cb(ui_tap_pass_ascii_ta, ui_event_tap_pass_ascii_ta_vc, LV_EVENT_ALL, "asciiTextarea");
        lv_obj_add_event_cb(ui_tap_pass_hex_ta, ui_event_tap_pass_hex_ta, LV_EVENT_ALL, NULL);
        lv_obj_add_event_cb(ui_tap_pass_hex_ta, ui_event_tap_pass_hex_ta_vc, LV_EVENT_ALL, "hexTextarea");
        __log("object 'ui_tag_auth_panel' is created");
    }
    else
    {
        __log("object 'ui_tag_auth_panel' already exist");
    }
}
///////////////////////////////////////////////////////////// SCREEN: ui_setupScreen  ////////////////////////////////////////////////////////////
// void ui_setupScreen_screen_init(void);
lv_obj_t *tabview;
/*---------------------------------------------------------------------WIFI TAB-----------------------------------------------------------*/
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
/* kb set to pass ta */
void ui_wifi_pass_ta_event_cb(lv_event_t *event)
{
    __log("pass ta clicked");
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
        __log("wifi scan task already running");
    }
}

/* initiate wifi connection task */
void ui_wifi_conn_event_cb(lv_event_t *event)
{
    // kb_del();
    if (wifi_connect_task_handle == NULL)
    {
        xTaskCreatePinnedToCore(wifi_conn_task,
                                "wifi_conn_task",
                                WIFI_CONNECT_TASK_STACK_SIZE,
                                NULL, WIFI_TASK_PRIORITY,
                                &wifi_connect_task_handle,
                                WIFI_TASK_CORE);
        __log("initiating wifi conn task");
    }
    else
    {
        __log("wifi conn task already running");
    }
}

void wnp_close_btn_cb(lv_event_t *event)
{
    lv_event_code_t event_code = lv_event_get_code(event);

    if (event_code == LV_EVENT_CLICKED)
    {
        wnp_del("del");
    }
}
/*----------------------------------------------------------------------------RFID TAB-----------------------------------------------------------*/
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
            __log("writing reader info.");
        }
        else
        {
            __log("reader write task already running.");
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
                    __log("start fetching reader info.");
                }
                else
                {
                    __log("reader info already fetched.");
                }
            }
            else
            {
                __log("rfid info task already running");
            }
        }
    }
}

/* go to home */
void ui_home_btn_cb(lv_event_t *event)
{
    // ui_mainScreen_screen_init();
    lv_scr_load_anim(ui_mainScreen, LV_SCR_LOAD_ANIM_MOVE_RIGHT, 200, 0, false);
    // __log("ui_mainScreen_screen_init(), prev screen deleted");
}

void ui_init(void)
{
    lv_disp_t *dispp = lv_disp_get_default();
    lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED),
                                              false, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    ui_mainScreen_screen_init();
    ui_setupScreen_screen_init();
    // ui_memScreen_screen_init();
    ui____initial_actions0 = lv_obj_create(NULL);
    lv_disp_load_scr(ui_mainScreen);
    __log("ui_mainScreen loaded.");
}

////////////////////////////////////////////////////// GLOB METHODS AND RESOURCES////////////////////////////////////////////////
// GLOB: resources
lv_obj_t *kb;
lv_obj_t *notif_panel;
lv_obj_t *notif_panel_title;
lv_obj_t *notif_close_btn;
lv_obj_t *notif_msg;
lv_obj_t *notif_cross_icon;
bool spin_flag = false;

void make_kb(lv_obj_t *obj)
{

    if (!lv_obj_is_valid(kb))
    {
        kb = lv_keyboard_create(lv_scr_act());
        lv_keyboard_set_popovers(kb, true);
        lv_obj_add_event_cb(kb, kb_event_cb, LV_EVENT_ALL, NULL);
        __log("keyboard created.");
    }
    lv_keyboard_set_textarea(kb, obj);
    __log("cursos set");
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
        __log("object 'kb' deleted");
    }
    else
    {
        __log("object 'kb' is null");
    }
}

void notif_panel_close_event_cb(lv_event_t *event)
{
    lv_event_code_t event_code = lv_event_get_code(event);
    if (event_code == LV_EVENT_CLICKED)
    {
        if (lv_obj_is_valid(notif_panel))
        {
            __log("closing n panel");
            lv_obj_add_flag(notif_panel, LV_OBJ_FLAG_HIDDEN);
            lv_obj_del_async(notif_panel);
            notif_panel = NULL;
        }
        else
        {
            __log("obj 'notif_panel' is null");
            lv_obj_add_flag(notif_panel, LV_OBJ_FLAG_HIDDEN);
        }
    }
}

void notif_panel_del()
{
    if (lv_obj_is_valid(notif_panel))
    {
        lv_obj_del(notif_panel);
        notif_panel = NULL;
        __log("obj 'notif_panel' deleted.");
    }
    else
    {
        __log("object 'notif_panel' is null");
        lv_obj_add_flag(notif_panel, LV_OBJ_FLAG_HIDDEN);
    }
}

void create_notif_panel(const char *title, const char *msg, bool _spin)
{
    if (lv_obj_is_valid(notif_panel))
    {
        __log("object 'notif_panel' already exist");
    }
    else
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

        notif_cross_icon = lv_label_create(notif_close_btn);
        lv_obj_align(notif_cross_icon, LV_ALIGN_CENTER, 0, 0);
        lv_label_set_text(notif_cross_icon, LV_SYMBOL_CLOSE);

        notif_msg = lv_label_create(notif_panel);
        lv_label_set_text(notif_msg, msg);

        spin_flag = _spin;
        if (spin_flag == true)
        {
            lv_obj_t *spinner = lv_spinner_create(notif_panel, 1500, 60);
            lv_obj_set_height(spinner, 45);
            lv_obj_set_width(spinner, 45);
            lv_obj_align(spinner, LV_ALIGN_CENTER, 0, -8);
            lv_obj_align(notif_msg, LV_ALIGN_CENTER, 0, 27);
        }
        else
        {
            lv_obj_align(notif_msg, LV_ALIGN_CENTER, 0, 0);
        }
        lv_obj_add_event_cb(notif_close_btn, notif_panel_close_event_cb, LV_EVENT_CLICKED, NULL);
        __log("n panel created");
    }
}

void notif_msg_update(const char *msg)
{
    if (lv_obj_is_valid(notif_panel))
    {
        __log("msg updated");
        lv_label_set_text(notif_msg, msg);
    }
    else
    {
        __log("obj 'notif_msg' is null is null");
    }
}

/* main screen filter panel */
void makeFilterPanel()
{
    if (!lv_obj_is_valid(ui_mainScrPanel))
    {
        lv_obj_t *ui_mainScrNotifypanelClose2;
        lv_obj_t *ui_notifyPanelclosebuttonlabel5;
        lv_obj_t *ui_offsetLabel;
        lv_obj_t *ui_dataLabel;
        lv_obj_t *ui_mainScrWriteData;
        lv_obj_t *ui_notifyPanelclosebuttonlabel3;

        ui_mainScrPanel = lv_obj_create(lv_scr_act());
        lv_obj_set_width(ui_mainScrPanel, lv_pct(64));
        lv_obj_set_height(ui_mainScrPanel, lv_pct(41));
        lv_obj_set_x(ui_mainScrPanel, -3);
        lv_obj_set_y(ui_mainScrPanel, -57);
        lv_obj_set_align(ui_mainScrPanel, LV_ALIGN_CENTER);
        lv_obj_clear_flag(ui_mainScrPanel, LV_OBJ_FLAG_SCROLLABLE); /// Flags
        lv_obj_set_style_shadow_color(ui_mainScrPanel, lv_color_hex(0x655151), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_shadow_opa(ui_mainScrPanel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_shadow_width(ui_mainScrPanel, 30, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_shadow_spread(ui_mainScrPanel, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_shadow_ofs_x(ui_mainScrPanel, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_shadow_ofs_y(ui_mainScrPanel, 5, LV_PART_MAIN | LV_STATE_DEFAULT);

        ui_mainScrNotifypanelClose2 = lv_btn_create(ui_mainScrPanel);
        lv_obj_set_width(ui_mainScrNotifypanelClose2, lv_pct(27));
        lv_obj_set_height(ui_mainScrNotifypanelClose2, lv_pct(28));
        lv_obj_set_x(ui_mainScrNotifypanelClose2, lv_pct(-41));
        lv_obj_set_y(ui_mainScrNotifypanelClose2, lv_pct(-49));
        lv_obj_set_align(ui_mainScrNotifypanelClose2, LV_ALIGN_CENTER);
        lv_obj_add_flag(ui_mainScrNotifypanelClose2, LV_OBJ_FLAG_SCROLL_ON_FOCUS); /// Flags
        lv_obj_clear_flag(ui_mainScrNotifypanelClose2, LV_OBJ_FLAG_SCROLLABLE);    /// Flags
        lv_obj_set_style_radius(ui_mainScrNotifypanelClose2, 1, LV_PART_MAIN | LV_STATE_DEFAULT);

        ui_notifyPanelclosebuttonlabel5 = lv_label_create(ui_mainScrNotifypanelClose2);
        lv_obj_set_width(ui_notifyPanelclosebuttonlabel5, LV_SIZE_CONTENT);  /// 1
        lv_obj_set_height(ui_notifyPanelclosebuttonlabel5, LV_SIZE_CONTENT); /// 1
        lv_obj_set_x(ui_notifyPanelclosebuttonlabel5, lv_pct(-5));
        lv_obj_set_y(ui_notifyPanelclosebuttonlabel5, lv_pct(0));
        lv_obj_set_align(ui_notifyPanelclosebuttonlabel5, LV_ALIGN_CENTER);
        lv_label_set_text(ui_notifyPanelclosebuttonlabel5, "close");
        lv_obj_set_style_text_font(ui_notifyPanelclosebuttonlabel5, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);

        ui_offsetLabel = lv_label_create(ui_mainScrPanel);
        lv_obj_set_width(ui_offsetLabel, LV_SIZE_CONTENT);  /// 1
        lv_obj_set_height(ui_offsetLabel, LV_SIZE_CONTENT); /// 1
        lv_obj_set_x(ui_offsetLabel, -79);
        lv_obj_set_y(ui_offsetLabel, -3);
        lv_obj_set_align(ui_offsetLabel, LV_ALIGN_CENTER);
        lv_label_set_text(ui_offsetLabel, "Offset");
        lv_obj_set_style_text_font(ui_offsetLabel, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);

        ui_mainScrOffsetTextarea = lv_textarea_create(ui_mainScrPanel);
        lv_obj_set_width(ui_mainScrOffsetTextarea, 48);
        lv_obj_set_height(ui_mainScrOffsetTextarea, 30);
        lv_obj_set_x(ui_mainScrOffsetTextarea, -35);
        lv_obj_set_y(ui_mainScrOffsetTextarea, -2);
        lv_obj_set_align(ui_mainScrOffsetTextarea, LV_ALIGN_CENTER);
        lv_textarea_set_accepted_chars(ui_mainScrOffsetTextarea, "0123456789");
        lv_obj_clear_flag(ui_mainScrOffsetTextarea,
                          LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE |
                              LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
        lv_obj_set_style_text_font(ui_mainScrOffsetTextarea, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_radius(ui_mainScrOffsetTextarea, 1, LV_PART_MAIN | LV_STATE_DEFAULT);

        ui_mainScrDataTextarea = lv_textarea_create(ui_mainScrPanel);
        lv_obj_set_width(ui_mainScrDataTextarea, 74);
        lv_obj_set_height(ui_mainScrDataTextarea, 30);
        lv_obj_set_x(ui_mainScrDataTextarea, 57);
        lv_obj_set_y(ui_mainScrDataTextarea, -2);
        lv_obj_set_align(ui_mainScrDataTextarea, LV_ALIGN_CENTER);

        lv_textarea_set_accepted_chars(ui_mainScrDataTextarea, "abcdefABCDEF0123456789");
        lv_obj_clear_flag(ui_mainScrDataTextarea,
                          LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE |
                              LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
        lv_obj_set_style_text_font(ui_mainScrDataTextarea, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_radius(ui_mainScrDataTextarea, 1, LV_PART_MAIN | LV_STATE_DEFAULT);

        ui_dataLabel = lv_label_create(ui_mainScrPanel);
        lv_obj_set_width(ui_dataLabel, LV_SIZE_CONTENT);  /// 1
        lv_obj_set_height(ui_dataLabel, LV_SIZE_CONTENT); /// 1
        lv_obj_set_x(ui_dataLabel, 6);
        lv_obj_set_y(ui_dataLabel, -3);
        lv_obj_set_align(ui_dataLabel, LV_ALIGN_CENTER);
        lv_label_set_text(ui_dataLabel, "Data ");
        lv_obj_set_style_text_font(ui_dataLabel, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);

        ui_mainScrWriteData = lv_btn_create(ui_mainScrPanel);
        lv_obj_set_width(ui_mainScrWriteData, lv_pct(27));
        lv_obj_set_height(ui_mainScrWriteData, lv_pct(34));
        lv_obj_set_x(ui_mainScrWriteData, lv_pct(40));
        lv_obj_set_y(ui_mainScrWriteData, lv_pct(47));
        lv_obj_set_align(ui_mainScrWriteData, LV_ALIGN_CENTER);
        lv_obj_add_flag(ui_mainScrWriteData, LV_OBJ_FLAG_SCROLL_ON_FOCUS); /// Flags
        lv_obj_clear_flag(ui_mainScrWriteData, LV_OBJ_FLAG_SCROLLABLE);    /// Flags
        lv_obj_set_style_radius(ui_mainScrWriteData, 1, LV_PART_MAIN | LV_STATE_DEFAULT);

        ui_notifyPanelclosebuttonlabel3 = lv_label_create(ui_mainScrWriteData);
        lv_obj_set_width(ui_notifyPanelclosebuttonlabel3, LV_SIZE_CONTENT);  /// 1
        lv_obj_set_height(ui_notifyPanelclosebuttonlabel3, LV_SIZE_CONTENT); /// 1
        lv_obj_set_x(ui_notifyPanelclosebuttonlabel3, lv_pct(-5));
        lv_obj_set_y(ui_notifyPanelclosebuttonlabel3, lv_pct(0));
        lv_obj_set_align(ui_notifyPanelclosebuttonlabel3, LV_ALIGN_CENTER);
        lv_label_set_text(ui_notifyPanelclosebuttonlabel3, "Write");
        lv_obj_set_style_text_font(ui_notifyPanelclosebuttonlabel3, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);

        /* event cb */
        lv_obj_add_event_cb(ui_mainScrNotifypanelClose2, ui_event_filter_panel_close, LV_EVENT_ALL, NULL);
        lv_obj_add_event_cb(ui_mainScrOffsetTextarea, ui_event_filter_panel_offset_ta, LV_EVENT_ALL, NULL);
        lv_obj_add_event_cb(ui_mainScrDataTextarea, ui_event_filter_panel_data_ta, LV_EVENT_ALL, NULL);
        lv_obj_add_event_cb(ui_mainScrWriteData, ui_event_filter_panel_write, LV_EVENT_ALL, NULL);
        __log("obj mainScrPanel is created.");
    }
    else
    {
        __log("obj mainScrPanel already exist.");
    }
}
void delFilterPanel(lv_obj_t *obj)
{
    lv_obj_del(obj);
    obj = NULL;
    __log("obj mainScrPanel deleted.");
}