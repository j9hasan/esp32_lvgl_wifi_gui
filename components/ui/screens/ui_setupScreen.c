
#include "../ui.h"
#include "shared_task.h"
#include "system_status.h"

/* button style */
lv_style_t btn_style;
lv_style_t btn_label_style;

void ui_setupScreen_screen_init(void)
{
    __log("ui_setupScreen_screen_init()");
    uint16_t btn_radius = 8;
    lv_obj_t *label;
    lv_obj_t *ui_home_btn;
    lv_obj_t *ui_home_btn_label;

    ui_setupScreen = lv_obj_create(NULL);

    tabview = lv_tabview_create(ui_setupScreen, LV_DIR_TOP, 30);

    /*Add 3 tabs (the tabs are page (lv_page) and can be scrolled*/
    lv_obj_t *tab1 = lv_tabview_add_tab(tabview, "Wifi");
    lv_obj_t *tab2 = lv_tabview_add_tab(tabview, "RFID");
    lv_obj_t *tab3 = lv_tabview_add_tab(tabview, "Setup");

    ///////////////////////////////////////////////// RFID TAB ///////////////////////////////////////////

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
    lv_obj_t *ui_offset;

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
    ///////////////////////////////////////////////////////////// WIFI TAB ///////////////////////////////////////////////////////

    ui_wifi_setup = lv_label_create(tab1);
    lv_obj_set_width(ui_wifi_setup, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_wifi_setup, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_wifi_setup, -112);
    lv_obj_set_y(ui_wifi_setup, -82);
    lv_obj_set_align(ui_wifi_setup, LV_ALIGN_CENTER);
    lv_label_set_text(ui_wifi_setup, "WiFi Setup");

    ui_wifi_ssid_dd = lv_dropdown_create(tab1);
    lv_dropdown_set_options(ui_wifi_ssid_dd, "SSID");
    lv_obj_set_width(ui_wifi_ssid_dd, 150);
    lv_obj_set_height(ui_wifi_ssid_dd, 40);
    lv_obj_set_x(ui_wifi_ssid_dd, -76);
    lv_obj_set_y(ui_wifi_ssid_dd, -48);
    lv_obj_set_align(ui_wifi_ssid_dd, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_wifi_ssid_dd, LV_OBJ_FLAG_SCROLL_ON_FOCUS); /// Flags
    lv_obj_set_style_radius(ui_wifi_ssid_dd, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_wifi_ssid_dd, lv_color_hex(0x2D2D2D), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_wifi_ssid_dd, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_wifi_ssid_dd, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui_wifi_ssid_dd, LV_BORDER_SIDE_FULL, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_radius(lv_dropdown_get_list(ui_wifi_ssid_dd), 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(lv_dropdown_get_list(ui_wifi_ssid_dd), lv_color_hex(0x000000),
                                  LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(lv_dropdown_get_list(ui_wifi_ssid_dd), 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(lv_dropdown_get_list(ui_wifi_ssid_dd), 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(lv_dropdown_get_list(ui_wifi_ssid_dd), LV_BORDER_SIDE_LEFT,
                                 LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_wifi_pass_ta = lv_textarea_create(tab1);
    lv_obj_set_width(ui_wifi_pass_ta, 150);
    lv_obj_set_height(ui_wifi_pass_ta, 40);
    lv_obj_set_x(ui_wifi_pass_ta, -76);
    lv_obj_set_y(ui_wifi_pass_ta, 0);
    lv_obj_set_align(ui_wifi_pass_ta, LV_ALIGN_CENTER);
    lv_textarea_set_placeholder_text(ui_wifi_pass_ta, "Password");
    lv_obj_clear_flag(ui_wifi_pass_ta, LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
                                           LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
    lv_obj_set_scrollbar_mode(ui_wifi_pass_ta, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_radius(ui_wifi_pass_ta, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_wifi_pass_ta, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_wifi_pass_ta, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_wifi_pass_ta, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui_wifi_pass_ta, LV_BORDER_SIDE_FULL, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_av_network_container = lv_obj_create(tab1);
    lv_obj_remove_style_all(ui_av_network_container);
    lv_obj_set_width(ui_av_network_container, 136);
    lv_obj_set_height(ui_av_network_container, 152);
    lv_obj_set_x(ui_av_network_container, 79);
    lv_obj_set_y(ui_av_network_container, 10);
    lv_obj_set_align(ui_av_network_container, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_av_network_container, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_obj_set_style_bg_color(ui_av_network_container, lv_color_hex(0xDFDEDE), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_av_network_container, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_available_network_label = lv_label_create(tab1);
    lv_obj_set_width(ui_available_network_label, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_available_network_label, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_available_network_label, 78);
    lv_obj_set_y(ui_available_network_label, -82);
    lv_obj_set_align(ui_available_network_label, LV_ALIGN_CENTER);
    lv_label_set_text(ui_available_network_label, "Available Networks");

    /* button style */
    lv_style_init(&btn_style);
    lv_style_set_radius(&btn_style, 0);
    lv_style_set_bg_color(&btn_style, lv_color_hex(0xFFFFFF));
    lv_style_set_bg_opa(&btn_style, 255);
    lv_style_set_border_color(&btn_style, lv_color_hex(0x000000));
    lv_style_set_border_opa(&btn_style, 255);
    lv_style_set_border_width(&btn_style, 1);
    lv_style_set_border_side(&btn_style, LV_BORDER_SIDE_FULL);
    lv_style_set_shadow_width(&btn_style, 0);
    lv_style_set_shadow_spread(&btn_style, 0);

    lv_style_init(&btn_label_style);
    lv_style_set_text_color(&btn_style, lv_color_hex(0x000000));
    lv_style_set_text_opa(&btn_style, 255);

    ui_wifi_scan_btn = lv_btn_create(tab1);
    lv_obj_set_width(ui_wifi_scan_btn, 45);
    lv_obj_set_height(ui_wifi_scan_btn, 25);
    lv_obj_set_x(ui_wifi_scan_btn, -107);
    lv_obj_set_y(ui_wifi_scan_btn, 44);
    lv_obj_set_align(ui_wifi_scan_btn, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_wifi_scan_btn, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_obj_clear_flag(ui_wifi_scan_btn, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_add_style(ui_wifi_scan_btn, &btn_style, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_wifi_scan_btn_label = lv_label_create(ui_wifi_scan_btn);
    lv_obj_set_width(ui_wifi_scan_btn_label, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_wifi_scan_btn_label, LV_SIZE_CONTENT); /// 1
    lv_obj_set_align(ui_wifi_scan_btn_label, LV_ALIGN_CENTER);
    lv_label_set_text(ui_wifi_scan_btn_label, "Scan");

    lv_obj_add_style(ui_wifi_scan_btn_label, &btn_label_style, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_wifi_conn_btn = lv_btn_create(tab1);
    lv_obj_set_width(ui_wifi_conn_btn, 45);
    lv_obj_set_height(ui_wifi_conn_btn, 25);
    lv_obj_set_x(ui_wifi_conn_btn, -41);
    lv_obj_set_y(ui_wifi_conn_btn, 44);
    lv_obj_set_align(ui_wifi_conn_btn, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_wifi_conn_btn, LV_OBJ_FLAG_SCROLL_ON_FOCUS); /// Flags
    lv_obj_clear_flag(ui_wifi_conn_btn, LV_OBJ_FLAG_SCROLLABLE);    /// Flags

    lv_obj_add_style(ui_wifi_conn_btn, &btn_style, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_wifi_conn_btn_label = lv_label_create(ui_wifi_conn_btn);
    lv_obj_set_width(ui_wifi_conn_btn_label, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_wifi_conn_btn_label, LV_SIZE_CONTENT); /// 1
    lv_obj_set_align(ui_wifi_conn_btn_label, LV_ALIGN_CENTER);
    lv_label_set_text(ui_wifi_conn_btn_label, "Conn");

    lv_obj_add_style(ui_wifi_conn_btn_label, &btn_label_style, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_wifi_save_checkbox = lv_checkbox_create(tab1);
    lv_checkbox_set_text(ui_wifi_save_checkbox, "Save Network");
    lv_obj_set_width(ui_wifi_save_checkbox, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_wifi_save_checkbox, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_wifi_save_checkbox, -65);
    lv_obj_set_y(ui_wifi_save_checkbox, 75);
    lv_obj_set_align(ui_wifi_save_checkbox, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_wifi_save_checkbox, LV_OBJ_FLAG_SCROLL_ON_FOCUS); /// Flags

    /* wnp notification panel */

    lv_obj_t *wnp_close_icon;
    lv_obj_t *wnp_title;

    wn_panel = lv_obj_create(ui_setupScreen);
    lv_obj_set_height(wn_panel, lv_pct(50));
    lv_obj_set_width(wn_panel, lv_pct(70));
    lv_obj_set_align(wn_panel, LV_ALIGN_CENTER);
    lv_obj_set_style_radius(wn_panel, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(wn_panel, lv_color_hex(0x655151), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(wn_panel, 150, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(wn_panel, 30, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(wn_panel, 500, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_flag(wn_panel, LV_OBJ_FLAG_HIDDEN);

    wnp_title = lv_label_create(wn_panel);
    lv_label_set_text(wnp_title, "WiFi");
    lv_obj_align(wnp_title, LV_ALIGN_TOP_LEFT, 0, 0);

    wnp_close_btn = lv_btn_create(wn_panel);
    lv_obj_set_height(wnp_close_btn, 25);
    lv_obj_set_width(wnp_close_btn, 25);
    lv_obj_align(wnp_close_btn, LV_ALIGN_TOP_RIGHT, 0, 0);
    lv_obj_set_ext_click_area(wnp_close_btn, 10);

    wnp_close_icon = lv_label_create(wnp_close_btn);
    lv_obj_align(wnp_close_icon, LV_ALIGN_CENTER, 0, 0);
    lv_label_set_text(wnp_close_icon, LV_SYMBOL_CLOSE);

    wnp_msg = lv_label_create(wn_panel);
    lv_label_set_text(wnp_msg, "");
    lv_obj_align(wnp_msg, LV_ALIGN_CENTER, 0, 27);

    spinner = lv_arc_create(wn_panel);
    lv_arc_set_rotation(spinner, 270);
    lv_arc_set_bg_angles(spinner, 0, 360);
    lv_obj_remove_style(spinner, NULL, LV_PART_KNOB);  /*Be sure the knob is not displayed*/
    lv_obj_clear_flag(spinner, LV_OBJ_FLAG_CLICKABLE); /*To not allow adjusting by click*/
    lv_obj_set_height(spinner, 45);
    lv_obj_set_width(spinner, 45);
    lv_obj_align(spinner, LV_ALIGN_CENTER, 0, -8);
    // lv_arc_set_value(spinner, 10);

    // lv_anim_t a;
    // lv_anim_init(&a);
    // lv_anim_set_var(&a, spinner);
    // lv_anim_set_exec_cb(&a, set_angle);
    // lv_anim_set_time(&a, 1000);
    // lv_anim_set_repeat_count(&a, LV_ANIM_REPEAT_INFINITE); /*Just for the demo*/
    // lv_anim_set_repeat_delay(&a, 500);
    // lv_anim_set_values(&a, 0, 100);
    // lv_anim_start(&a);

    // lv_obj_t *spinner = lv_spinner_create(wn_panel, 1000, 60);
    // lv_obj_set_height(spinner, 45);
    // lv_obj_set_width(spinner, 45);
    // lv_obj_align(spinner, LV_ALIGN_CENTER, 0, -8);
    // lv_obj_align(wnp_msg, LV_ALIGN_CENTER, 0, 27);

    ui_offset = lv_label_create(tab1);
    lv_obj_set_width(ui_offset, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_offset, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_offset, 3);
    lv_obj_set_y(ui_offset, 153);
    lv_obj_set_align(ui_offset, LV_ALIGN_CENTER);
    lv_label_set_text(ui_offset, "");

    //////////////////////////////////////////////////////////////////////SETUP TAB//////////////////////////////////////////////////////

    label = lv_label_create(tab3);
    lv_label_set_text(label, "Setup tab");
    lv_tabview_set_act(tabview, 0, LV_ANIM_ON);

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

    lv_obj_add_event_cb(ui_home_btn, ui_home_btn_cb, LV_EVENT_CLICKED, NULL); /*Home button callback*/

    /* events */
    // wifi tab//
    lv_obj_add_event_cb(ui_wifi_pass_ta, ui_wifi_pass_ta_event_cb, LV_EVENT_CLICKED, NULL); /*Settings event callback*/
    lv_obj_add_event_cb(ui_wifi_scan_btn, ui_wifi_scan_event_cb, LV_EVENT_CLICKED, NULL);   /*Settings event callback*/
    lv_obj_add_event_cb(ui_wifi_conn_btn, ui_wifi_conn_event_cb, LV_EVENT_CLICKED, NULL);   /*Settings event callback*/
    lv_obj_add_event_cb(wnp_close_btn, wnp_close_btn_cb, LV_EVENT_CLICKED, NULL);

    // rfid tab//
    lv_obj_add_event_cb(tabview, tabview_slider_cb, LV_EVENT_VALUE_CHANGED, NULL);
    lv_obj_add_event_cb(ui_reader_info_write, ui_reader_info_write_cb, LV_EVENT_CLICKED, NULL); /*Reader write task cb*/
    lv_obj_add_event_cb(ui_scantime_txtarea, ui_reader_scantime_txtarea_cb, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(ui_power_txtarea, ui_reader_power_txtarea_cb, LV_EVENT_CLICKED, NULL);
}

/* notification panel functionality
 * called from core 0, MUST LOCK THE MUTEX before
 * calling any lvgl related functions
 *************************************************/

void wnp_update(const char *msg)
{
    if (pdTRUE == xSemaphoreTake(xGuiSemaphore, portMAX_DELAY))
    {
        if (lv_obj_has_flag(wn_panel, LV_OBJ_FLAG_HIDDEN))
        {
            ESP_LOGI("wnp update", "wnp_has_flag %d clearing flag", lv_obj_has_flag(wn_panel, LV_OBJ_FLAG_HIDDEN));
            lv_obj_clear_flag(wn_panel, LV_OBJ_FLAG_HIDDEN);
        }
        else
        {
            ESP_LOGI("wnp update", "wnp_has_flag %d", lv_obj_has_flag(wn_panel, LV_OBJ_FLAG_HIDDEN));
        }
        lv_label_set_text(wnp_msg, msg);
        xSemaphoreGive(xGuiSemaphore);
    }
}
void wnp_del(const char *msg)
{

    if (pdTRUE == xSemaphoreTake(xGuiSemaphore, pdMS_TO_TICKS(400)))
    {
        if (!lv_obj_has_flag(wn_panel, LV_OBJ_FLAG_HIDDEN))
        {
            ESP_LOGI("wnp del", "deleted");
            lv_obj_add_flag(wn_panel, LV_OBJ_FLAG_HIDDEN);
            xSemaphoreGive(xGuiSemaphore);
        }
        else
        {
            ESP_LOGI("wnp del", "failed to delete");
        }

        lv_label_set_text(wnp_msg, "");
    }
    else
    {
        ESP_LOGI("wnp del", "cant acquire mutex");
    }
}

void set_angle(lv_obj_t *spinner, uint32_t v)
{
    if (pdTRUE == xSemaphoreTake(xGuiSemaphore, portMAX_DELAY))
    {
        lv_arc_set_value(spinner, v);
        xSemaphoreGive(xGuiSemaphore);
    }
    else
    {
        ESP_LOGI("wnp del", "cant acquire mutex");
    }
}
/*how to add styles*/
// static lv_style_t icon_style;
// lv_style_init(&icon_style);
// lv_style_set_bg_color(&icon_style, lv_color_hex(0xFF2400));
// lv_style_set_width(&icon_style, 20);
// lv_style_set_pad_right(&icon_style, 20);
// lv_obj_add_style(ui_settingsIcon, &icon_style, LV_PART_MAIN | LV_STATE_DEFAULT);

/*mutex


    if (pdTRUE == xSemaphoreTake(xGuiSemaphore, portMAX_DELAY))
    {
      lv_task_handler();
      xSemaphoreGive(xGuiSemaphore);
    }










*/