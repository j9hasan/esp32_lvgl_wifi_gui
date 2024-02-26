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

/* static prototypes */
static void kb_del();
static void make_kb(lv_obj_t *obj);

////////////////////////////////////////////////////////////// SCREEN: ui_mainScreen  //////////////////////////////////////////////////////////

/* filter panel global objects */
// global obj
lv_obj_t *ui____initial_actions0;
static lv_obj_t *ui_filter_panel; // this file only

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
        delFilterPanel(ui_filter_panel);
        // _ui_flag_modify(ui_main_scr_keyboard, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
    }
}

/* closes filter panel and disable any filter */
void ui_event_filter_panel_close(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    if (event_code == LV_EVENT_CLICKED)
    {
        delFilterPanel(ui_filter_panel);
    }
}

/* filter panel offset textarea */
void ui_event_filter_panel_offset_ta(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    if (event_code == LV_EVENT_CLICKED)
    {
        make_kb(ui_fp_offset_ta);
    }
}

/* filter panel data textarea */
void ui_event_filter_panel_data_ta(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    if (event_code == LV_EVENT_CLICKED)
    {
        lv_obj_move_background(epc_table);
        make_kb(ui_fp_data_ta);
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
            mem_screen(e);
            lv_scr_load_anim(ui_memScreen, LV_SCR_LOAD_ANIM_MOVE_LEFT, 100, 0, false);
            // mem_screen(e);
            // _ui_screen_delete(&ui_mainScreen);
            // _ui_screen_change(&ui_memScreen, LV_SCR_LOAD_ANIM_MOVE_LEFT, 50, 0, &ui_memScreen_screen_init);
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
        kb_del();

        // if (lv_obj_is_valid(ui_tag_data_write_panel))
        // {
        //     lv_obj_del(ui_tag_data_write_panel);
        //     ui_tag_data_write_panel = NULL;
        //     __log("obj 'ui_tag_data_write' deleted");
        // }
        // else
        // {
        //     __log("failed to del obj 'ui_tag_data_write' null");
        // }
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
        lv_obj_set_width(ui_tag_data_write_panel, lv_pct(55));
        lv_obj_set_height(ui_tag_data_write_panel, lv_pct(40));
        lv_obj_align(ui_tag_data_write_panel, LV_ALIGN_TOP_MID, 0, 10);
        lv_obj_clear_flag(ui_tag_data_write_panel, LV_OBJ_FLAG_SCROLLABLE); /// Flags
        lv_obj_set_style_shadow_color(ui_tag_data_write_panel, lv_color_hex(0x655151), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_shadow_opa(ui_tag_data_write_panel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_shadow_width(ui_tag_data_write_panel, 30, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_shadow_spread(ui_tag_data_write_panel, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_shadow_ofs_x(ui_tag_data_write_panel, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_shadow_ofs_y(ui_tag_data_write_panel, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_border_width(ui_tag_data_write_panel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_radius(ui_tag_data_write_panel, 10, LV_PART_MAIN | LV_STATE_DEFAULT);

        ui_tdwp_close = lv_btn_create(ui_tag_data_write_panel);
        lv_obj_set_height(ui_tdwp_close, 20);
        lv_obj_set_width(ui_tdwp_close, 20);
        lv_obj_align(ui_tdwp_close, LV_ALIGN_OUT_TOP_LEFT, 0, 0);
        lv_obj_set_ext_click_area(ui_tdwp_close, 10);

        ui_tdwp_close_label = lv_label_create(ui_tdwp_close);
        lv_obj_align(ui_tdwp_close_label, LV_ALIGN_CENTER, 0, 0);
        lv_label_set_text(ui_tdwp_close_label, LV_SYMBOL_CLOSE);

        ui_tdwp_label = lv_label_create(ui_tag_data_write_panel);
        lv_obj_set_width(ui_tdwp_label, LV_SIZE_CONTENT);
        lv_obj_set_height(ui_tdwp_label, LV_SIZE_CONTENT);
        lv_obj_set_x(ui_tdwp_label, -29);
        lv_obj_set_y(ui_tdwp_label, -7);
        lv_obj_set_align(ui_tdwp_label, LV_ALIGN_CENTER);
        lv_label_set_text(ui_tdwp_label, "Data: ");

        ui_tdwp_dat_ta = lv_textarea_create(ui_tag_data_write_panel);
        lv_obj_set_width(ui_tdwp_dat_ta, 80);
        lv_obj_set_height(ui_tdwp_dat_ta, 29);
        lv_obj_align(ui_tdwp_dat_ta, LV_ALIGN_CENTER, 32, -8);
        lv_textarea_set_accepted_chars(ui_tdwp_dat_ta, "abcdefABCDEF0123456789");
        lv_obj_clear_flag(ui_tdwp_dat_ta, LV_OBJ_FLAG_SCROLLABLE);

        ui_tdwp_data_write = lv_btn_create(ui_tag_data_write_panel);
        lv_obj_set_width(ui_tdwp_data_write, 40);
        lv_obj_set_height(ui_tdwp_data_write, 20);
        lv_obj_align(ui_tdwp_data_write, LV_ALIGN_BOTTOM_RIGHT, 0, 0);
        lv_obj_set_style_radius(ui_tdwp_data_write, 7, LV_PART_MAIN | LV_STATE_DEFAULT);

        ui_tdwp_data_write_label = lv_label_create(ui_tdwp_data_write);
        lv_obj_set_width(ui_tdwp_data_write_label, LV_SIZE_CONTENT);  /// 1
        lv_obj_set_height(ui_tdwp_data_write_label, LV_SIZE_CONTENT); /// 1
        lv_obj_center(ui_tdwp_data_write_label);
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
    // lv_obj_t *ui_pass_use_btn;
    // lv_obj_t *ui_passwrite_btn;
    if (!lv_obj_is_valid(ui_tag_auth_panel))
    {
        /*AUTH PANEL*/
        ui_tag_auth_panel = lv_obj_create(lv_scr_act());
        lv_obj_set_width(ui_tag_auth_panel, lv_pct(65));
        lv_obj_set_height(ui_tag_auth_panel, lv_pct(43));
        lv_obj_set_x(ui_tag_auth_panel, -1);
        lv_obj_set_y(ui_tag_auth_panel, -61);
        lv_obj_set_align(ui_tag_auth_panel, LV_ALIGN_CENTER);
        lv_obj_clear_flag(ui_tag_auth_panel, LV_OBJ_FLAG_SCROLLABLE); /// Flags
        lv_obj_set_style_shadow_color(ui_tag_auth_panel, lv_color_hex(0x655151), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_shadow_opa(ui_tag_auth_panel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_shadow_width(ui_tag_auth_panel, 30, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_shadow_spread(ui_tag_auth_panel, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_shadow_ofs_x(ui_tag_auth_panel, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_shadow_ofs_y(ui_tag_auth_panel, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_border_width(ui_tag_auth_panel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_radius(ui_tag_auth_panel, 10, LV_PART_MAIN | LV_STATE_DEFAULT);

        ui_tap_close = lv_btn_create(ui_tag_auth_panel);
        lv_obj_set_height(ui_tap_close, 20);
        lv_obj_set_width(ui_tap_close, 20);
        lv_obj_align(ui_tap_close, LV_ALIGN_OUT_TOP_LEFT, 0, -2);
        lv_obj_set_ext_click_area(ui_tap_close, 10);

        ui_tap_close_label = lv_label_create(ui_tap_close);
        lv_obj_align(ui_tap_close_label, LV_ALIGN_CENTER, 0, 0);
        lv_label_set_text(ui_tap_close_label, LV_SYMBOL_CLOSE);

        ui_tap_pass_ascii_label = lv_label_create(ui_tag_auth_panel);
        lv_obj_set_width(ui_tap_pass_ascii_label, LV_SIZE_CONTENT);  /// 1
        lv_obj_set_height(ui_tap_pass_ascii_label, LV_SIZE_CONTENT); /// 1
        lv_obj_align(ui_tap_pass_ascii_label, LV_ALIGN_CENTER, -41, -24);
        lv_label_set_text(ui_tap_pass_ascii_label, "ASCII");
        lv_obj_set_style_text_font(ui_tap_pass_ascii_label, &lv_font_montserrat_10, LV_PART_MAIN | LV_STATE_DEFAULT);

        ui_tap_pass_ascii_ta = lv_textarea_create(ui_tag_auth_panel);
        lv_obj_set_size(ui_tap_pass_ascii_ta, 80, 28);
        lv_obj_align(ui_tap_pass_ascii_ta, LV_ALIGN_CENTER, -42, 2);
        lv_textarea_set_accepted_chars(ui_tap_pass_ascii_ta, " ABCDEFGHIJKLMNOPQRSTUVWXYZ_-.@#");
        lv_obj_clear_flag(ui_tap_pass_ascii_ta,
                          LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE |
                              LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
        lv_obj_set_style_text_font(ui_tap_pass_ascii_ta, &lv_font_montserrat_10, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_textarea_set_max_length(ui_tap_pass_ascii_ta, 6);

        ui_tap_pass_hex_ta = lv_textarea_create(ui_tag_auth_panel);
        lv_obj_set_size(ui_tap_pass_hex_ta, 80, 28);
        lv_obj_align(ui_tap_pass_hex_ta, LV_ALIGN_CENTER, 47, 2);
        lv_textarea_set_accepted_chars(ui_tap_pass_hex_ta, "abcdefABCDEF0123456789");
        lv_obj_clear_flag(ui_tap_pass_hex_ta,
                          LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE |
                              LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
        lv_obj_set_style_text_font(ui_tap_pass_hex_ta, &lv_font_montserrat_10, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_textarea_set_max_length(ui_tap_pass_hex_ta, 8);

        ui_tap_pass_hex_label = lv_label_create(ui_tag_auth_panel);
        lv_obj_set_width(ui_tap_pass_hex_label, LV_SIZE_CONTENT);  /// 1
        lv_obj_set_height(ui_tap_pass_hex_label, LV_SIZE_CONTENT); /// 1
        lv_obj_align(ui_tap_pass_hex_label, LV_ALIGN_CENTER, 45, -24);
        lv_label_set_text(ui_tap_pass_hex_label, "Pass. HEX");
        lv_obj_set_style_text_font(ui_tap_pass_hex_label, &lv_font_montserrat_10, LV_PART_MAIN | LV_STATE_DEFAULT);

        lv_obj_t *ui_tap_write = lv_btn_create(ui_tag_auth_panel);
        lv_obj_set_width(ui_tap_write, 40);
        lv_obj_set_height(ui_tap_write, 20);
        lv_obj_set_x(ui_tap_write, 0);
        lv_obj_set_y(ui_tap_write, 2);
        lv_obj_set_align(ui_tap_write, LV_ALIGN_BOTTOM_RIGHT);
        lv_obj_add_flag(ui_tap_write, LV_OBJ_FLAG_SCROLL_ON_FOCUS); /// Flags
        lv_obj_clear_flag(ui_tap_write, LV_OBJ_FLAG_SCROLLABLE);    /// Flags

        lv_obj_t *ui_Label7 = lv_label_create(ui_tap_write);
        lv_obj_set_width(ui_Label7, LV_SIZE_CONTENT);  /// 1
        lv_obj_set_height(ui_Label7, LV_SIZE_CONTENT); /// 1
        lv_obj_set_align(ui_Label7, LV_ALIGN_CENTER);
        lv_label_set_text(ui_Label7, "Write");

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

/*---------------------------------------------------------------------WIFI TAB-----------------------------------------------------------*/

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
        if ((READER_WRITE_TASK_HANDLE == NULL))
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
                if (system_status.reader_data_fetched == false)
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

/* setup tab */
void ui_event_check_and_do_fw_update(lv_event_t *event)
{
    /* initiate fw_update_task, defined in shaared task.cpp*/
    if (fw_update_task_handle == NULL)
    {
        xTaskCreatePinnedToCore(fw_update_task, "fw update task",
                                FW_UPDATE_TASK_STACK_SIZE, NULL,
                                FW_UPDATE_TASK_PRIORITY,
                                &fw_update_task_handle,
                                FW_UPDATE_TASK_CORE);
        __log("fw update tsk initiated");
    }
    else
    {
        __log("fw update task already running");
    }
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

static void make_kb(lv_obj_t *obj)
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

static void kb_del()
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
/* glob obj */
/* fw update notif panel */
lv_obj_t *ui_b_1;
lv_obj_t *ui_n_1;
lv_obj_t *ui_i_1;
lv_obj_t *ui_i_2;
lv_obj_t *ui_i_3;

void create_notif_panel(const char *title, const char *msg, bool _spin, uint8_t cmd)
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
        lv_obj_set_style_shadow_color(notif_panel, lv_color_hex(0x655151), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_shadow_opa(notif_panel, 150, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_shadow_width(notif_panel, 30, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_shadow_spread(notif_panel, 500, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_border_width(notif_panel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_radius(notif_panel, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_clear_flag(notif_panel, LV_OBJ_FLAG_SCROLLABLE);

        notif_close_btn = lv_btn_create(notif_panel);
        lv_obj_set_height(notif_close_btn, 25);
        lv_obj_set_width(notif_close_btn, 25);
        lv_obj_align(notif_close_btn, LV_ALIGN_TOP_RIGHT, 0, 0);
        lv_obj_set_ext_click_area(notif_close_btn, 10);

        notif_cross_icon = lv_label_create(notif_close_btn);
        lv_obj_align(notif_cross_icon, LV_ALIGN_CENTER, 0, 0);
        lv_label_set_text(notif_cross_icon, LV_SYMBOL_CLOSE);

        if (cmd == 1)
        {
            /* fw update panel */
            lv_obj_t *ui_s_1;
            lv_obj_t *ui_t_1;
            // lv_obj_t *ui_b_1;
            // lv_obj_t *ui_n_1;
            // lv_obj_t *ui_i_1;
            // lv_obj_t *ui_i_2;
            // lv_obj_t *ui_i_3;
            // lv_obj_t *ui_n_2;
            ui_s_1 = lv_spinner_create(notif_panel, 1000, 90);
            lv_obj_set_width(ui_s_1, 28);
            lv_obj_set_height(ui_s_1, 28);
            lv_obj_align(ui_s_1, LV_ALIGN_TOP_LEFT, 0, 0);
            lv_obj_clear_flag(ui_s_1, LV_OBJ_FLAG_CLICKABLE); /// Flags
            lv_obj_set_style_arc_width(ui_s_1, 9, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_width(ui_s_1, 9, LV_PART_INDICATOR | LV_STATE_DEFAULT);

            ui_t_1 = lv_label_create(notif_panel);
            lv_obj_set_width(ui_t_1, LV_SIZE_CONTENT);  /// 1
            lv_obj_set_height(ui_t_1, LV_SIZE_CONTENT); /// 1
            lv_obj_align(ui_t_1, LV_ALIGN_TOP_LEFT, 34, 4);
            lv_label_set_text(ui_t_1, title);
            lv_obj_set_style_text_font(ui_t_1, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);

            ui_b_1 = lv_bar_create(notif_panel);
            lv_bar_set_value(ui_b_1, 25, LV_ANIM_OFF);
            lv_bar_set_start_value(ui_b_1, 0, LV_ANIM_OFF);
            lv_obj_set_width(ui_b_1, 162);
            lv_obj_set_height(ui_b_1, 10);
            lv_obj_set_x(ui_b_1, 0);
            lv_obj_set_y(ui_b_1, 44);
            lv_obj_set_align(ui_b_1, LV_ALIGN_CENTER);
            lv_obj_add_flag(ui_b_1, LV_OBJ_FLAG_HIDDEN);

            ui_n_1 = lv_label_create(notif_panel);
            lv_obj_set_width(ui_n_1, LV_SIZE_CONTENT);  /// 1
            lv_obj_set_height(ui_n_1, LV_SIZE_CONTENT); /// 1
            lv_obj_set_x(ui_n_1, 0);
            lv_obj_set_y(ui_n_1, 26);
            lv_obj_set_align(ui_n_1, LV_ALIGN_CENTER);
            lv_label_set_text(ui_n_1, "");
            lv_obj_set_style_text_font(ui_n_1, &lv_font_montserrat_10, LV_PART_MAIN | LV_STATE_DEFAULT);

            ui_i_1 = lv_label_create(notif_panel);
            lv_obj_set_width(ui_i_1, LV_SIZE_CONTENT);  /// 1
            lv_obj_set_height(ui_i_1, LV_SIZE_CONTENT); /// 1
            lv_obj_set_x(ui_i_1, 0);
            lv_obj_set_y(ui_i_1, -19);
            lv_obj_set_align(ui_i_1, LV_ALIGN_CENTER);
            lv_label_set_text(ui_i_1, "Current fw ...");
            lv_obj_set_style_text_font(ui_i_1, &lv_font_montserrat_10, LV_PART_MAIN | LV_STATE_DEFAULT);

            ui_i_2 = lv_label_create(notif_panel);
            lv_obj_set_width(ui_i_2, LV_SIZE_CONTENT);  /// 1
            lv_obj_set_height(ui_i_2, LV_SIZE_CONTENT); /// 1
            lv_obj_set_x(ui_i_2, 0);
            lv_obj_set_y(ui_i_2, -4);
            lv_obj_set_align(ui_i_2, LV_ALIGN_CENTER);
            lv_label_set_text(ui_i_2, "Remote fw ...");
            lv_obj_set_style_text_font(ui_i_2, &lv_font_montserrat_10, LV_PART_MAIN | LV_STATE_DEFAULT);

            ui_i_3 = lv_label_create(notif_panel);
            lv_obj_set_width(ui_i_3, LV_SIZE_CONTENT);  /// 1
            lv_obj_set_height(ui_i_3, LV_SIZE_CONTENT); /// 1
            lv_obj_set_x(ui_i_3, 0);
            lv_obj_set_y(ui_i_3, 11);
            lv_obj_set_align(ui_i_3, LV_ALIGN_CENTER);
            lv_label_set_text(ui_i_3, "App size: ...");
            lv_obj_set_style_text_font(ui_i_3, &lv_font_montserrat_10, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        else
        {
            notif_panel_title = lv_label_create(notif_panel);
            lv_label_set_text(notif_panel_title, title);
            lv_obj_align(notif_panel_title, LV_ALIGN_TOP_LEFT, 0, 0);

            notif_msg = lv_label_create(notif_panel);
            lv_label_set_text(notif_msg, msg);

            spin_flag = _spin;
            if (spin_flag == true)
            {
                lv_obj_t *spinner = lv_spinner_create(notif_panel, 1000, 60);
                lv_obj_set_height(spinner, 45);
                lv_obj_set_width(spinner, 45);
                lv_obj_align(spinner, LV_ALIGN_CENTER, 0, -13);
                lv_obj_align(notif_msg, LV_ALIGN_CENTER, 0, 27);
            }
            else
            {
                lv_obj_align(notif_msg, LV_ALIGN_CENTER, 0, 0);
            }
        }
        lv_obj_add_event_cb(notif_close_btn, notif_panel_close_event_cb, LV_EVENT_CLICKED, NULL);
        __log("n panel created cmd %d", cmd);
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
    if (!lv_obj_is_valid(ui_filter_panel))
    {
        lv_obj_t *ui_fp_close;
        lv_obj_t *ui_fpclabel;
        lv_obj_t *ui_fp_offset_label;
        lv_obj_t *ui_fp_data_label;
        lv_obj_t *ui_fp_data_write;
        lv_obj_t *ui_fpdwl;

        ui_filter_panel = lv_obj_create(lv_scr_act());
        lv_obj_set_width(ui_filter_panel, lv_pct(69));
        lv_obj_set_height(ui_filter_panel, lv_pct(41));
        lv_obj_align(ui_filter_panel, LV_ALIGN_CENTER, -3, -57);
        lv_obj_clear_flag(ui_filter_panel, LV_OBJ_FLAG_SCROLLABLE);
        lv_obj_set_style_shadow_color(ui_filter_panel, lv_color_hex(0x655151), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_shadow_opa(ui_filter_panel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_shadow_width(ui_filter_panel, 30, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_shadow_spread(ui_filter_panel, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_shadow_ofs_x(ui_filter_panel, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_shadow_ofs_y(ui_filter_panel, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_border_width(ui_filter_panel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_radius(ui_filter_panel, 10, LV_PART_MAIN | LV_STATE_DEFAULT);

        ui_fp_close = lv_btn_create(ui_filter_panel);
        lv_obj_set_width(ui_fp_close, 25);
        lv_obj_set_height(ui_fp_close, 25);
        lv_obj_align(ui_fp_close, LV_ALIGN_TOP_LEFT, 0, -5);
        lv_obj_add_flag(ui_fp_close, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
        lv_obj_clear_flag(ui_fp_close, LV_OBJ_FLAG_SCROLLABLE);
        lv_obj_set_style_radius(ui_fp_close, 7, LV_PART_MAIN | LV_STATE_DEFAULT);

        ui_fpclabel = lv_label_create(ui_fp_close);
        lv_obj_set_width(ui_fpclabel, LV_SIZE_CONTENT);  /// 1
        lv_obj_set_height(ui_fpclabel, LV_SIZE_CONTENT); /// 1
        lv_obj_set_align(ui_fpclabel, LV_ALIGN_CENTER);
        lv_label_set_text(ui_fpclabel, LV_SYMBOL_CLOSE);

        ui_fp_offset_label = lv_label_create(ui_filter_panel);
        lv_obj_set_width(ui_fp_offset_label, LV_SIZE_CONTENT);  /// 1
        lv_obj_set_height(ui_fp_offset_label, LV_SIZE_CONTENT); /// 1
        lv_obj_set_x(ui_fp_offset_label, -79);
        lv_obj_set_y(ui_fp_offset_label, -3);
        lv_obj_set_align(ui_fp_offset_label, LV_ALIGN_CENTER);
        lv_label_set_text(ui_fp_offset_label, "Offset");
        lv_obj_set_style_text_font(ui_fp_offset_label, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);

        ui_fp_offset_ta = lv_textarea_create(ui_filter_panel);
        lv_obj_set_width(ui_fp_offset_ta, 48);
        lv_obj_set_height(ui_fp_offset_ta, 30);
        lv_obj_set_x(ui_fp_offset_ta, -35);
        lv_obj_set_y(ui_fp_offset_ta, -2);
        lv_obj_set_align(ui_fp_offset_ta, LV_ALIGN_CENTER);
        lv_textarea_set_accepted_chars(ui_fp_offset_ta, "0123456789");
        lv_obj_clear_flag(ui_fp_offset_ta,
                          LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE |
                              LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
        lv_obj_set_style_text_font(ui_fp_offset_ta, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);

        ui_fp_data_ta = lv_textarea_create(ui_filter_panel);
        lv_obj_set_width(ui_fp_data_ta, 74);
        lv_obj_set_height(ui_fp_data_ta, 30);
        lv_obj_set_x(ui_fp_data_ta, 57);
        lv_obj_set_y(ui_fp_data_ta, -2);
        lv_obj_set_align(ui_fp_data_ta, LV_ALIGN_CENTER);

        lv_textarea_set_accepted_chars(ui_fp_data_ta, "abcdefABCDEF0123456789");
        lv_obj_clear_flag(ui_fp_data_ta,
                          LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE |
                              LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
        lv_obj_set_style_text_font(ui_fp_data_ta, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);

        ui_fp_data_label = lv_label_create(ui_filter_panel);
        lv_obj_set_width(ui_fp_data_label, LV_SIZE_CONTENT);  /// 1
        lv_obj_set_height(ui_fp_data_label, LV_SIZE_CONTENT); /// 1
        lv_obj_set_x(ui_fp_data_label, 6);
        lv_obj_set_y(ui_fp_data_label, -3);
        lv_obj_set_align(ui_fp_data_label, LV_ALIGN_CENTER);
        lv_label_set_text(ui_fp_data_label, "Data ");
        lv_obj_set_style_text_font(ui_fp_data_label, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);

        ui_fp_data_write = lv_btn_create(ui_filter_panel);
        lv_obj_set_width(ui_fp_data_write, lv_pct(27));
        lv_obj_set_height(ui_fp_data_write, lv_pct(34));
        lv_obj_align(ui_fp_data_write, LV_ALIGN_BOTTOM_RIGHT, 0, 5);
        lv_obj_add_flag(ui_fp_data_write, LV_OBJ_FLAG_SCROLL_ON_FOCUS); /// Flags
        lv_obj_clear_flag(ui_fp_data_write, LV_OBJ_FLAG_SCROLLABLE);    /// Flags
        lv_obj_set_style_radius(ui_fp_data_write, 7, LV_PART_MAIN | LV_STATE_DEFAULT);

        ui_fpdwl = lv_label_create(ui_fp_data_write);
        lv_obj_set_width(ui_fpdwl, LV_SIZE_CONTENT);  /// 1
        lv_obj_set_height(ui_fpdwl, LV_SIZE_CONTENT); /// 1
        lv_obj_set_x(ui_fpdwl, lv_pct(-5));
        lv_obj_set_y(ui_fpdwl, lv_pct(0));
        lv_obj_set_align(ui_fpdwl, LV_ALIGN_CENTER);
        lv_label_set_text(ui_fpdwl, "Write");
        lv_obj_set_style_text_font(ui_fpdwl, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);

        /* event cb */
        lv_obj_add_event_cb(ui_fp_close, ui_event_filter_panel_close, LV_EVENT_ALL, NULL);
        lv_obj_add_event_cb(ui_fp_offset_ta, ui_event_filter_panel_offset_ta, LV_EVENT_ALL, NULL);
        lv_obj_add_event_cb(ui_fp_data_ta, ui_event_filter_panel_data_ta, LV_EVENT_ALL, NULL);
        lv_obj_add_event_cb(ui_fp_data_write, ui_event_filter_panel_write, LV_EVENT_ALL, NULL);
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