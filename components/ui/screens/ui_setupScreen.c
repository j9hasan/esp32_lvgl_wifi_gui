
#include "../ui.h"

void ui_setupScreen_screen_init(void)
{
    uint16_t btn_radius = 8;
    lv_obj_t *label;
    lv_obj_t *ui_home_btn;
    lv_obj_t *ui_home_btn_label;

    void ui_event_ssid_dd(lv_event_t * e);
    void ui_event_pass_ta(lv_event_t * e);
    void ui_event_conn_btn(lv_event_t * e);
    void ui_event_econ_btn(lv_event_t * e);

    ui_setupScreen = lv_obj_create(NULL);

    tabview = lv_tabview_create(ui_setupScreen, LV_DIR_TOP, 50);

    /*Add 3 tabs (the tabs are page (lv_page) and can be scrolled*/
    lv_obj_t *tab1 = lv_tabview_add_tab(tabview, "Wifi");
    lv_obj_t *tab2 = lv_tabview_add_tab(tabview, "RFID");
    lv_obj_t *tab3 = lv_tabview_add_tab(tabview, "Setup");

    ///////////////////////////////////////////////// RFID TAB ///////////////////////////////////////////

    void ui_event_powerTextarea(lv_event_t * e);
    void ui_event_scantimeTextarea(lv_event_t * e);
    void ui_event_beeponSwitch(lv_event_t * e);
    void ui_event_writeButton(lv_event_t * e);

    /* non global obj */
    lv_obj_t *ui_device_id_label;
    lv_obj_t *ui_version_label;
    lv_obj_t *ui_minf_label;
    lv_obj_t *ui_protocol_label;
    lv_obj_t *ui_baud_label;
    lv_obj_t *ui_maxf_label;
    lv_obj_t *ui_antenna_label;
    lv_obj_t *ui_readertype_label;
    lv_obj_t *ui_band_label;
    lv_obj_t *ui_power_label;
    lv_obj_t *ui_scantime_label;
    lv_obj_t *ui_beepon_label;
    lv_obj_t *ui_reader_info_write_label;

    ui_device_id_label = lv_label_create(tab2);
    lv_obj_set_width(ui_device_id_label, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_device_id_label, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_device_id_label, lv_pct(-34));
    lv_obj_set_y(ui_device_id_label, lv_pct(-44));
    lv_obj_set_align(ui_device_id_label, LV_ALIGN_CENTER);
    lv_label_set_text(ui_device_id_label, "Dev. ID:");

    ui_device_id_labelx = lv_label_create(tab2);
    lv_obj_set_width(ui_device_id_labelx, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_device_id_labelx, LV_SIZE_CONTENT); /// 1
    lv_obj_align(ui_device_id_labelx, LV_ALIGN_TOP_LEFT, 80, 3);
    lv_label_set_text(ui_device_id_labelx, "");

    ui_minf_label = lv_label_create(tab2);
    lv_obj_set_width(ui_minf_label, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_minf_label, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_minf_label, lv_pct(11));
    lv_obj_set_y(ui_minf_label, lv_pct(8));
    lv_obj_set_align(ui_minf_label, LV_ALIGN_CENTER);
    lv_label_set_text(ui_minf_label, "Min f.");

    ui_protocol_label = lv_label_create(tab2);
    lv_obj_set_width(ui_protocol_label, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_protocol_label, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_protocol_label, lv_pct(-40));
    lv_obj_set_y(ui_protocol_label, lv_pct(21));
    lv_obj_set_align(ui_protocol_label, LV_ALIGN_CENTER);
    lv_label_set_text(ui_protocol_label, "Protocol:");

    ui_protocol_labelx = lv_label_create(tab2);
    lv_obj_set_width(ui_protocol_labelx, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_protocol_labelx, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_protocol_labelx, lv_pct(22));
    lv_obj_set_y(ui_protocol_labelx, lv_pct(21));
    lv_obj_set_align(ui_protocol_labelx, LV_ALIGN_LEFT_MID);
    lv_label_set_text(ui_protocol_labelx, "");

    ui_baud_label = lv_label_create(tab2);
    lv_obj_set_width(ui_baud_label, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_baud_label, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_baud_label, lv_pct(11));
    lv_obj_set_y(ui_baud_label, lv_pct(-28));
    lv_obj_set_align(ui_baud_label, LV_ALIGN_CENTER);
    lv_label_set_text(ui_baud_label, "Baud.");

    ui_baud_dd = lv_dropdown_create(tab2);
    lv_dropdown_set_options(ui_baud_dd, "115200");
    lv_obj_set_width(ui_baud_dd, lv_pct(26));
    lv_obj_set_height(ui_baud_dd, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_baud_dd, lv_pct(32));
    lv_obj_set_y(ui_baud_dd, lv_pct(-28));
    lv_obj_set_align(ui_baud_dd, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_baud_dd, LV_OBJ_FLAG_SCROLL_ON_FOCUS); /// Flags

    ui_maxf_label = lv_label_create(tab2);
    lv_obj_set_width(ui_maxf_label, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_maxf_label, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_maxf_label, lv_pct(11));
    lv_obj_set_y(ui_maxf_label, lv_pct(21));
    lv_obj_set_align(ui_maxf_label, LV_ALIGN_CENTER);
    lv_label_set_text(ui_maxf_label, "Max f.");

    ui_antenna_label = lv_label_create(tab2);
    lv_obj_set_width(ui_antenna_label, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_antenna_label, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_antenna_label, lv_pct(-40));
    lv_obj_set_y(ui_antenna_label, lv_pct(8));
    lv_obj_set_align(ui_antenna_label, LV_ALIGN_CENTER);
    lv_label_set_text(ui_antenna_label, "Antenna:");

    ui_readertype_label = lv_label_create(tab2);
    lv_obj_set_width(ui_readertype_label, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_readertype_label, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_readertype_label, lv_pct(-28));
    lv_obj_set_y(ui_readertype_label, lv_pct(67));
    lv_obj_set_align(ui_readertype_label, LV_ALIGN_CENTER);
    lv_label_set_text(ui_readertype_label, "");

    ui_band_label = lv_label_create(tab2);
    lv_obj_set_width(ui_band_label, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_band_label, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_band_label, lv_pct(11));
    lv_obj_set_y(ui_band_label, lv_pct(-10));
    lv_obj_set_align(ui_band_label, LV_ALIGN_CENTER);
    lv_label_set_text(ui_band_label, "Band.");

    ui_bana_dd = lv_dropdown_create(tab2);
    lv_dropdown_set_options(ui_bana_dd, "USA\nKorean\nEU\nChinese");
    lv_obj_set_width(ui_bana_dd, lv_pct(26));
    lv_obj_set_height(ui_bana_dd, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_bana_dd, lv_pct(32));
    lv_obj_set_y(ui_bana_dd, lv_pct(-9));
    lv_obj_set_align(ui_bana_dd, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_bana_dd, LV_OBJ_FLAG_SCROLL_ON_FOCUS); /// Flags

    ui_power_label = lv_label_create(tab2);
    lv_obj_set_width(ui_power_label, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_power_label, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_power_label, lv_pct(-38));
    lv_obj_set_y(ui_power_label, lv_pct(-10));
    lv_obj_set_align(ui_power_label, LV_ALIGN_CENTER);
    lv_label_set_text(ui_power_label, "Power(dB):");

    ui_power_txtarea = lv_textarea_create(tab2);
    lv_obj_set_width(ui_power_txtarea, lv_pct(25));
    lv_obj_set_height(ui_power_txtarea, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_power_txtarea, lv_pct(-11));
    lv_obj_set_y(ui_power_txtarea, lv_pct(-9));
    lv_obj_set_align(ui_power_txtarea, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_power_txtarea, LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC |
                                            LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
    lv_obj_set_scrollbar_mode(ui_power_txtarea, LV_SCROLLBAR_MODE_OFF);

    ui_scantime_label = lv_label_create(tab2);
    lv_obj_set_width(ui_scantime_label, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_scantime_label, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_scantime_label, lv_pct(-39));
    lv_obj_set_y(ui_scantime_label, lv_pct(-28));
    lv_obj_set_align(ui_scantime_label, LV_ALIGN_CENTER);
    lv_label_set_text(ui_scantime_label, "Scan t.(ms):");

    ui_scantime_txtarea = lv_textarea_create(tab2);
    lv_obj_set_width(ui_scantime_txtarea, lv_pct(25));
    lv_obj_set_height(ui_scantime_txtarea, lv_pct(12)); /// 1
    lv_obj_set_x(ui_scantime_txtarea, lv_pct(-11));
    lv_obj_set_y(ui_scantime_txtarea, lv_pct(-28));
    lv_obj_set_align(ui_scantime_txtarea, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_scantime_txtarea,
                      LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
                          LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
    lv_obj_set_scrollbar_mode(ui_scantime_txtarea, LV_SCROLLBAR_MODE_OFF);

    ui_beepon_switch = lv_switch_create(tab2);
    lv_obj_set_width(ui_beepon_switch, lv_pct(11));
    lv_obj_set_height(ui_beepon_switch, lv_pct(10));
    lv_obj_set_x(ui_beepon_switch, lv_pct(-21));
    lv_obj_set_y(ui_beepon_switch, lv_pct(36));
    lv_obj_set_align(ui_beepon_switch, LV_ALIGN_CENTER);
    lv_obj_set_style_bg_color(ui_beepon_switch, lv_color_hex(0xCE9F9F), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_beepon_switch, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_beepon_label = lv_label_create(tab2);
    lv_obj_set_width(ui_beepon_label, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_beepon_label, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_beepon_label, lv_pct(-40));
    lv_obj_set_y(ui_beepon_label, lv_pct(36));
    lv_obj_set_align(ui_beepon_label, LV_ALIGN_CENTER);
    lv_label_set_text(ui_beepon_label, "beep on");

    ui_reader_info_write = lv_btn_create(tab2);
    lv_obj_set_width(ui_reader_info_write, lv_pct(20));
    lv_obj_set_height(ui_reader_info_write, lv_pct(16));
    lv_obj_set_x(ui_reader_info_write, lv_pct(40));
    lv_obj_set_y(ui_reader_info_write, lv_pct(43));
    lv_obj_set_align(ui_reader_info_write, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_reader_info_write, LV_OBJ_FLAG_SCROLL_ON_FOCUS); /// Flags
    lv_obj_clear_flag(ui_reader_info_write, LV_OBJ_FLAG_SCROLLABLE);    /// Flags
    lv_obj_set_style_radius(ui_reader_info_write, btn_radius, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_reader_info_write_label = lv_label_create(ui_reader_info_write);
    lv_obj_set_width(ui_reader_info_write_label, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_reader_info_write_label, LV_SIZE_CONTENT); /// 1
    lv_obj_set_align(ui_reader_info_write_label, LV_ALIGN_CENTER);
    lv_label_set_text(ui_reader_info_write_label, "Write");

    ui_version_labelx = lv_label_create(tab2);
    lv_obj_set_width(ui_version_labelx, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_version_labelx, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_version_labelx, lv_pct(70));
    lv_obj_set_y(ui_version_labelx, lv_pct(3));
    lv_label_set_text(ui_version_labelx, "");

    ui_version_label = lv_label_create(tab2);
    lv_obj_set_width(ui_version_label, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_version_label, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_version_label, lv_pct(13));
    lv_obj_set_y(ui_version_label, lv_pct(-44));
    lv_obj_set_align(ui_version_label, LV_ALIGN_CENTER);
    lv_label_set_text(ui_version_label, "Ver:");

    ui_antenna_labelx = lv_label_create(tab2);
    lv_obj_set_width(ui_antenna_labelx, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_antenna_labelx, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_antenna_labelx, lv_pct(23));
    lv_obj_set_y(ui_antenna_labelx, lv_pct(53));
    lv_label_set_text(ui_antenna_labelx, "");

    ui_maxf_labelx = lv_label_create(tab2);
    lv_obj_set_width(ui_maxf_labelx, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_maxf_labelx, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_maxf_labelx, lv_pct(69));
    lv_obj_set_y(ui_maxf_labelx, lv_pct(21));
    lv_obj_set_align(ui_maxf_labelx, LV_ALIGN_LEFT_MID);
    lv_label_set_text(ui_maxf_labelx, "");

    ui_minf_labelx = lv_label_create(tab2);
    lv_obj_set_width(ui_minf_labelx, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_minf_labelx, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_minf_labelx, lv_pct(69));
    lv_obj_set_y(ui_minf_labelx, lv_pct(8));
    lv_obj_set_align(ui_minf_labelx, LV_ALIGN_LEFT_MID);
    lv_label_set_text(ui_minf_labelx, "");

    ui_protocol_label = lv_label_create(tab2);
    lv_obj_set_width(ui_protocol_label, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_protocol_label, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_protocol_label, lv_pct(22));
    lv_obj_set_y(ui_protocol_label, lv_pct(21));
    lv_obj_set_align(ui_protocol_label, LV_ALIGN_LEFT_MID);
    lv_label_set_text(ui_protocol_label, "");
    ///////////////////////////////////////////////// WIFI TAB ///////////////////////////////////////////
    ui_wifi_ssid_label = lv_label_create(tab1);
    lv_obj_set_width(ui_wifi_ssid_label, lv_pct(13));
    lv_obj_set_height(ui_wifi_ssid_label, lv_pct(10));
    lv_obj_set_x(ui_wifi_ssid_label, lv_pct(-42));
    lv_obj_set_y(ui_wifi_ssid_label, lv_pct(-45));
    lv_obj_set_align(ui_wifi_ssid_label, LV_ALIGN_CENTER);
    lv_label_set_text(ui_wifi_ssid_label, "SSID:");

    ui_wifi_ssid_dd = lv_dropdown_create(tab1);
    lv_dropdown_set_options(ui_wifi_ssid_dd, "not connected");
    lv_obj_set_width(ui_wifi_ssid_dd, lv_pct(49));
    lv_obj_set_height(ui_wifi_ssid_dd, lv_pct(20));
    lv_obj_set_x(ui_wifi_ssid_dd, lv_pct(-7));
    lv_obj_set_y(ui_wifi_ssid_dd, lv_pct(-45));
    lv_obj_set_align(ui_wifi_ssid_dd, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_wifi_ssid_dd, LV_OBJ_FLAG_SCROLL_ON_FOCUS); /// Flags

    ui_wifi_pass_label = lv_label_create(tab1);
    lv_obj_set_width(ui_wifi_pass_label, lv_pct(13));
    lv_obj_set_height(ui_wifi_pass_label, lv_pct(10));
    lv_obj_set_x(ui_wifi_pass_label, lv_pct(-42));
    lv_obj_set_y(ui_wifi_pass_label, lv_pct(-22));
    lv_obj_set_align(ui_wifi_pass_label, LV_ALIGN_CENTER);
    lv_label_set_text(ui_wifi_pass_label, "Pass:");

    ui_wifi_pass_ta = lv_textarea_create(tab1);
    lv_obj_set_width(ui_wifi_pass_ta, lv_pct(49));
    lv_obj_set_height(ui_wifi_pass_ta, lv_pct(20));
    lv_obj_set_x(ui_wifi_pass_ta, lv_pct(-7));
    lv_obj_set_y(ui_wifi_pass_ta, lv_pct(-22));
    lv_obj_set_align(ui_wifi_pass_ta, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_wifi_pass_ta, LV_OBJ_FLAG_SCROLLABLE);
    lv_textarea_set_placeholder_text(ui_wifi_pass_ta, "Placeholder...");

    ui_wifi_conn_btn = lv_btn_create(tab1);
    lv_obj_set_width(ui_wifi_conn_btn, lv_pct(18));
    lv_obj_set_height(ui_wifi_conn_btn, lv_pct(15));
    lv_obj_set_x(ui_wifi_conn_btn, lv_pct(32));
    lv_obj_set_y(ui_wifi_conn_btn, lv_pct(-22));
    lv_obj_set_align(ui_wifi_conn_btn, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_wifi_conn_btn, LV_OBJ_FLAG_CLICKABLE);    /// Flags
    lv_obj_clear_flag(ui_wifi_conn_btn, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_obj_set_style_radius(ui_wifi_conn_btn, btn_radius, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_wifi_conn_btn_label = lv_label_create(ui_wifi_conn_btn);
    lv_obj_set_width(ui_wifi_conn_btn_label, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_wifi_conn_btn_label, LV_SIZE_CONTENT); /// 1
    lv_obj_set_align(ui_wifi_conn_btn_label, LV_ALIGN_CENTER);
    lv_label_set_text(ui_wifi_conn_btn_label, "Conn");

    ui_wifi_scan_btn = lv_btn_create(tab1);
    lv_obj_set_width(ui_wifi_scan_btn, lv_pct(18));
    lv_obj_set_height(ui_wifi_scan_btn, lv_pct(15));
    lv_obj_set_x(ui_wifi_scan_btn, lv_pct(32));
    lv_obj_set_y(ui_wifi_scan_btn, lv_pct(-45));
    lv_obj_set_align(ui_wifi_scan_btn, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_wifi_scan_btn, LV_OBJ_FLAG_CLICKABLE);    /// Flags
    lv_obj_clear_flag(ui_wifi_scan_btn, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_obj_set_style_radius(ui_wifi_scan_btn, btn_radius, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_wifi_scan_btn_label = lv_label_create(ui_wifi_scan_btn);
    lv_obj_set_width(ui_wifi_scan_btn_label, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_wifi_scan_btn_label, LV_SIZE_CONTENT); /// 1
    lv_obj_set_align(ui_wifi_scan_btn_label, LV_ALIGN_CENTER);
    lv_label_set_text(ui_wifi_scan_btn_label, "Scan");

    ui_wifi_e_conn_btn = lv_btn_create(tab1);
    lv_obj_set_width(ui_wifi_e_conn_btn, lv_pct(18));
    lv_obj_set_height(ui_wifi_e_conn_btn, lv_pct(15));
    lv_obj_set_x(ui_wifi_e_conn_btn, lv_pct(0));
    lv_obj_set_y(ui_wifi_e_conn_btn, lv_pct(20));
    lv_obj_set_align(ui_wifi_e_conn_btn, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_wifi_e_conn_btn, LV_OBJ_FLAG_SCROLL_ON_FOCUS); /// Flags
    lv_obj_clear_flag(ui_wifi_e_conn_btn, LV_OBJ_FLAG_SCROLLABLE);    /// Flags
    lv_obj_set_style_radius(ui_wifi_e_conn_btn, btn_radius, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_wifi_e_conn_btn_label = lv_label_create(ui_wifi_e_conn_btn);
    lv_obj_set_width(ui_wifi_e_conn_btn_label, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_wifi_e_conn_btn_label, LV_SIZE_CONTENT); /// 1
    lv_obj_set_align(ui_wifi_e_conn_btn_label, LV_ALIGN_CENTER);
    lv_label_set_text(ui_wifi_e_conn_btn_label, "Econ");

    ui_wifi_tab_label = lv_label_create(tab1);
    lv_obj_set_width(ui_wifi_tab_label, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_wifi_tab_label, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_wifi_tab_label, lv_pct(0));
    lv_obj_set_y(ui_wifi_tab_label, lv_pct(2));
    lv_obj_set_align(ui_wifi_tab_label, LV_ALIGN_CENTER);
    lv_label_set_text(ui_wifi_tab_label, "Click to connect from EEPROM");

    // label = lv_label_create(tab2);
    // lv_label_set_text(label, "RFID tab");

    label = lv_label_create(tab3);
    lv_label_set_text(label, "Setup tab");
    lv_tabview_set_act(tabview, 0, LV_ANIM_ON);

    // lv_obj_scroll_to_view_recursive(label, LV_ANIM_ON);
    //////////////////////////////////////////////////////////// SETUP SCREEN: parent ////////////////////////////////////////////////

    /* home button */
    ui_home_btn = lv_btn_create(ui_setupScreen);
    lv_obj_set_width(ui_home_btn, 25);
    lv_obj_set_height(ui_home_btn, 25);
    lv_obj_align(ui_home_btn, LV_ALIGN_BOTTOM_LEFT, 3, -3);
    lv_obj_add_flag(ui_home_btn, LV_OBJ_FLAG_SCROLL_ON_FOCUS); /// Flags
    lv_obj_clear_flag(ui_home_btn, LV_OBJ_FLAG_SCROLLABLE);    /// Flags
    lv_obj_set_style_radius(ui_home_btn, btn_radius, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_home_btn_label = lv_label_create(ui_home_btn);
    lv_obj_set_align(ui_home_btn_label, LV_ALIGN_CENTER);
    lv_label_set_text(ui_home_btn_label, LV_SYMBOL_HOME);

    /* events */
    // wifi tab//
    lv_obj_add_event_cb(ui_wifi_pass_ta, ui_wifi_pass_ta_event_cb, LV_EVENT_CLICKED, NULL); /*Settings event callback*/
    lv_obj_add_event_cb(ui_wifi_scan_btn, ui_wifi_scan_event_cb, LV_EVENT_CLICKED, NULL);   /*Settings event callback*/
    lv_obj_add_event_cb(ui_wifi_conn_btn, ui_wifi_conn_event_cb, LV_EVENT_CLICKED, NULL);   /*Settings event callback*/
    lv_obj_add_event_cb(ui_home_btn, ui_home_btn_cb, LV_EVENT_CLICKED, NULL);               /*Home button callback*/

    // rfid tab//
    lv_obj_add_event_cb(tabview, tabview_slider_cb, LV_EVENT_VALUE_CHANGED, NULL);
    lv_obj_add_event_cb(ui_reader_info_write, ui_reader_info_write_cb, LV_EVENT_CLICKED, NULL); /*Reader write task cb*/
    lv_obj_add_event_cb(ui_scantime_txtarea, ui_reader_scantime_txtarea_cb, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(ui_power_txtarea, ui_reader_power_txtarea_cb, LV_EVENT_CLICKED, NULL);
}

/*how to add styles*/
// static lv_style_t icon_style;
// lv_style_init(&icon_style);
// lv_style_set_bg_color(&icon_style, lv_color_hex(0xFF2400));
// lv_style_set_width(&icon_style, 20);
// lv_style_set_pad_right(&icon_style, 20);
// lv_obj_add_style(ui_settingsIcon, &icon_style, LV_PART_MAIN | LV_STATE_DEFAULT);