
#include "../ui.h"

/* global objects */
lv_obj_t *ui_mainScreen;
lv_obj_t *ui_wifiIcon;
lv_obj_t *epc_table;
lv_obj_t *ui_timeLabel;
lv_obj_t *ui_sdLogo;
lv_obj_t *ui_mergeSwitch;
lv_obj_t *ui_filterSW;
lv_obj_t *ui_agentButton;
lv_obj_t *ui_filterBtnLbl;
lv_obj_t *ui_mergeButtonLabel;
lv_obj_t *ui_mainScrDataTextarea;
lv_obj_t *ui_mainScrOffsetTextarea;

void ui_mainScreen_screen_init(void)
{
    /* local */
    lv_obj_t *ui_iconContainer;
    lv_obj_t *ui_bottomContainer;
    lv_obj_t *ui_settingsIcon;
    lv_obj_t *ui_agentButtonLabel;
    ui_mainScreen = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_mainScreen, LV_OBJ_FLAG_SCROLLABLE);

    /* container for icons at top */
    ui_iconContainer = lv_obj_create(ui_mainScreen);
    lv_obj_set_align(ui_iconContainer, LV_ALIGN_TOP_MID);
    lv_obj_clear_flag(ui_iconContainer, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_width(ui_iconContainer, lv_pct(100));
    lv_obj_set_height(ui_iconContainer, lv_pct(10));
    lv_obj_set_style_bg_color(ui_iconContainer, lv_color_hex(0xB4E2FF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_iconContainer, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_all(ui_iconContainer, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui_iconContainer, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_iconContainer, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    /* icons */
    ui_wifiIcon = lv_label_create(ui_iconContainer);
    lv_label_set_text(ui_wifiIcon, "");
    lv_obj_align(ui_wifiIcon, LV_ALIGN_TOP_LEFT, 0, 0);
    lv_obj_add_flag(ui_wifiIcon, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_set_style_text_font(ui_wifiIcon, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_settingsIcon = lv_label_create(ui_iconContainer);
    lv_label_set_text(ui_settingsIcon, LV_SYMBOL_SETTINGS);
    lv_obj_align(ui_settingsIcon, LV_ALIGN_RIGHT_MID, -5, 0);
    lv_obj_add_flag(ui_settingsIcon, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_set_style_text_font(ui_settingsIcon, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);

    /* bottom container */
    ui_bottomContainer = lv_obj_create(ui_mainScreen);
    lv_obj_set_align(ui_bottomContainer, LV_ALIGN_BOTTOM_MID);
    lv_obj_clear_flag(ui_bottomContainer, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_width(ui_bottomContainer, lv_pct(100));
    lv_obj_set_height(ui_bottomContainer, lv_pct(9));
    lv_obj_set_style_bg_color(ui_bottomContainer, lv_color_hex(0xB4E2FF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_bottomContainer, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_all(ui_bottomContainer, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui_bottomContainer, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_bottomContainer, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_timeLabel = lv_label_create(ui_mainScreen);
    lv_obj_set_width(ui_timeLabel, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_timeLabel, LV_SIZE_CONTENT); /// 1
    lv_obj_set_align(ui_timeLabel, LV_ALIGN_CENTER);
    lv_obj_set_x(ui_timeLabel, -80);
    lv_obj_set_y(ui_timeLabel, -105);
    lv_label_set_text(ui_timeLabel, "");

    ui_filterSW = lv_btn_create(ui_mainScreen);
    lv_obj_set_width(ui_filterSW, lv_pct(11));
    lv_obj_set_height(ui_filterSW, lv_pct(9));
    lv_obj_set_x(ui_filterSW, lv_pct(-31));
    lv_obj_set_y(ui_filterSW, lv_pct(44));
    lv_obj_set_align(ui_filterSW, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_filterSW, LV_OBJ_FLAG_SCROLL_ON_FOCUS); /// Flags
    lv_obj_clear_flag(ui_filterSW, LV_OBJ_FLAG_SCROLLABLE);    /// Flags
    lv_obj_set_style_radius(ui_filterSW, 15, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_filterSW, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_filterSW, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_filterSW, lv_color_hex(0x81CCD5), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_filterSW, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_filterSW, 2, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_filterBtnLbl = lv_label_create(ui_filterSW);
    lv_obj_set_width(ui_filterBtnLbl, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_filterBtnLbl, LV_SIZE_CONTENT); /// 1
    lv_obj_set_align(ui_filterBtnLbl, LV_ALIGN_CENTER);
    lv_label_set_text(ui_filterBtnLbl, "F:0");
    lv_obj_set_style_text_color(ui_filterBtnLbl, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_filterBtnLbl, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_obj_set_style_text_font(ui_filterBtnLbl, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_mergeSwitch = lv_btn_create(ui_mainScreen);
    lv_obj_set_width(ui_mergeSwitch, lv_pct(11));
    lv_obj_set_height(ui_mergeSwitch, lv_pct(9));
    lv_obj_set_x(ui_mergeSwitch, lv_pct(-43));
    lv_obj_set_y(ui_mergeSwitch, lv_pct(44));
    lv_obj_set_align(ui_mergeSwitch, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_mergeSwitch, LV_OBJ_FLAG_SCROLL_ON_FOCUS); /// Flags
    lv_obj_clear_flag(ui_mergeSwitch, LV_OBJ_FLAG_SCROLLABLE);    /// Flags
    lv_obj_set_style_radius(ui_mergeSwitch, 15, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_mergeSwitch, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_mergeSwitch, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_mergeSwitch, lv_color_hex(0x81CCD5), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_mergeSwitch, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_mergeSwitch, 2, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_mergeButtonLabel = lv_label_create(ui_mergeSwitch);
    lv_obj_set_width(ui_mergeButtonLabel, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_mergeButtonLabel, LV_SIZE_CONTENT); /// 1
    lv_obj_set_align(ui_mergeButtonLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_mergeButtonLabel, "M:0");
    lv_obj_set_style_text_color(ui_mergeButtonLabel, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_mergeButtonLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_obj_set_style_text_font(ui_mergeButtonLabel, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_agentButton = lv_btn_create(ui_mainScreen);
    lv_obj_set_width(ui_agentButton, lv_pct(13));
    lv_obj_set_height(ui_agentButton, lv_pct(9));
    lv_obj_set_x(ui_agentButton, lv_pct(-18));
    lv_obj_set_y(ui_agentButton, lv_pct(44));
    lv_obj_set_align(ui_agentButton, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_agentButton, LV_OBJ_FLAG_SCROLL_ON_FOCUS); /// Flags
    lv_obj_clear_flag(ui_agentButton, LV_OBJ_FLAG_SCROLLABLE);    /// Flags
    lv_obj_set_style_radius(ui_agentButton, 15, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_agentButton, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_agentButton, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_agentButton, lv_color_hex(0x81CCD5), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_agentButton, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_agentButton, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    ui_agentButtonLabel = lv_label_create(ui_agentButton);
    lv_obj_set_width(ui_agentButtonLabel, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_agentButtonLabel, LV_SIZE_CONTENT); /// 1
    lv_obj_set_align(ui_agentButtonLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_agentButtonLabel, "agent");
    lv_obj_set_style_text_color(ui_agentButtonLabel, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);

    /* epc_table */
    epc_table = lv_table_create(ui_mainScreen);
    lv_table_set_col_cnt(epc_table, 2);
    lv_table_set_col_width(epc_table, 1, 80);
    lv_table_set_col_width(epc_table, 0, 240);
    lv_obj_set_height(epc_table, 200);
    lv_table_set_cell_value(epc_table, 0, 0, "EPC");
    lv_table_set_cell_value(epc_table, 0, 1, "RSSI");
    lv_obj_align(epc_table, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_pos(epc_table, 0, 0);
    lv_obj_set_scroll_dir(epc_table, LV_DIR_VER);
    lv_obj_set_style_pad_ver(epc_table, 3, LV_PART_ITEMS);
    lv_obj_move_background(epc_table);
    lv_obj_set_style_bg_color(epc_table, lv_color_hex(0xfffbe6), LV_PART_ITEMS);

    /* events */
    lv_obj_add_event_cb(ui_settingsIcon, ui_event_settings_icon, LV_EVENT_CLICKED, NULL); /*Settings event callback*/
    lv_obj_add_event_cb(ui_mergeSwitch, ui_event_merge_sw, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_filterSW, ui_event_filter_switch, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_agentButton, ui_event_agent_btn, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(epc_table, ui_event_main_table_cb, LV_EVENT_LONG_PRESSED, NULL);
}
