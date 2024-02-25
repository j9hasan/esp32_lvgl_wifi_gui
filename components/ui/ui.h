
#ifndef _UI_H_
#define _UI_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "lvgl.h"
#include "ui_helpers.h"
#include "ui_events.h"
#include "system_status.h"

    /* global button styles */
    // square button, defined in setup screen
    extern lv_style_t btn_style;
    extern lv_style_t btn_label_style;

    /////////////////////////////////////////////////////// SCREEN: ui_checkinOutScreen  //////////////////////////////////////
    void ui_checkin_checkoutScreen_screen_init(void);
    /* global objects */
    extern lv_obj_t *ui_checkinOutScreen;
    extern lv_obj_t *ui_checkinOutStatusLabel;

    ////////////////////////////////////////////////////// SCREEN: ui_mainScreen  /////////////////////////////////////////////////
    void ui_mainScreen_screen_init(void);
    extern lv_obj_t *ui____initial_actions0;

    /* global objects */
    extern lv_obj_t *ui_mainScreen;
    extern lv_obj_t *ui_wifiIcon;
    extern lv_obj_t *ui_sd_icon;
    extern lv_obj_t *epc_table;
    extern lv_obj_t *ui_timeLabel;
    extern lv_obj_t *ui_sdLogo;
    extern lv_obj_t *ui_mergeSwitch;
    extern lv_obj_t *ui_filterSW;
    extern lv_obj_t *ui_agentButton;
    extern lv_obj_t *ui_filterBtnLbl;
    extern lv_obj_t *ui_mergeButtonLabel;
    /* filter panel global objects */
    extern lv_obj_t *ui_mainScrDataTextarea;
    extern lv_obj_t *ui_mainScrOffsetTextarea;

    /* functions */
    void makeFilterPanel();
    void delFilterPanel(lv_obj_t *obj);

    /* callbacks */
    void ui_event_merge_sw(lv_event_t *e);
    void ui_event_filter_switch(lv_event_t *e);
    void ui_event_filter_panel_close(lv_event_t *e);
    void ui_event_filter_panel_offset_ta(lv_event_t *e);
    void ui_event_filter_panel_data_ta(lv_event_t *e);
    void ui_event_filter_panel_write(lv_event_t *e);
    void ui_event_agent_btn(lv_event_t *e);
    void ui_event_settings_icon(lv_event_t *event);
    void ui_event_main_table_cb(lv_event_t *event);

    /////////////////////////////////////////////////////// SCREEN: ui_memScreen  ///////////////////////////////////////////////////
    void ui_memScreen_screen_init(void);

    /* global objects */
    extern lv_obj_t *tag_data_table;
    extern lv_obj_t *ui_memScreen;
    extern lv_obj_t *ui_chip_type_label;
    extern lv_obj_t *ui_epc_size_label;
    extern lv_obj_t *ui_tot_mem_label;
    extern lv_obj_t *ui_tid_size_label;
    extern lv_obj_t *ui_usr_size_label;
    extern lv_obj_t *ui_pwd_size_label;
    extern lv_obj_t *ui_mem_scr_log;
    /* panels glob obj */
    extern lv_obj_t *ui_tdwp_dat_ta;
    extern lv_obj_t *ui_tap_pass_ascii_ta;
    extern lv_obj_t *ui_tap_pass_hex_ta;

    /* callbacks */
    void ui_event_tap_create(lv_event_t *e);
    void ui_event_tap_close(lv_event_t *e);
    void ui_event_tag_data_table(lv_event_t *e);
    void tdw_panel_write_cb(lv_event_t *e);
    void ui_event_tdwp_close(lv_event_t *e);
    void ui_event_tdwp_data_ta(lv_event_t *e);
    void ui_event_tdwp_write_btn(lv_event_t *e);

    void ui_event_tap_pass_ascii_ta(lv_event_t *e);
    void ui_event_tap_pass_ascii_ta_vc(lv_event_t *e);
    void ui_event_tap_pass_hex_ta_vc(lv_event_t *e);
    void ui_event_tap_pass_hex_ta(lv_event_t *e);
    void ui_home2_btn_cb(lv_event_t *event);

    /////////////////////////////////////////////////////// SCREEN: ui_setupScreen  ////////////////////////////////////////////////
    extern void ui_setupScreen_screen_init(void);
    extern lv_obj_t *ui_setupScreen;
    extern lv_obj_t *tabview;

    /* event cb */
    void ui_home_btn_cb(lv_event_t *event);
    void ui_event_check_and_do_fw_update(lv_event_t *event);

    ////////////////////////////////////////////////////////////// WIFI TAB /////////////////////////////////////////////////////////
    extern lv_obj_t *ui_wifi_ssid_label;
    extern lv_obj_t *ui_wifi_ssid_dd;
    extern lv_obj_t *ui_wifi_pass_label;
    extern lv_obj_t *ui_wifi_pass_ta;
    extern lv_obj_t *ui_wifi_conn_btn;
    extern lv_obj_t *ui_wifi_conn_btn_label;
    extern lv_obj_t *ui_wifi_scan_btn;
    extern lv_obj_t *ui_wifi_scan_btn_label;
    extern lv_obj_t *ui_wifi_e_conn_btn;
    extern lv_obj_t *ui_wifi_e_conn_btn_label;
    extern lv_obj_t *ui_wifi_tab_label;
    extern lv_obj_t *ui_wifi_save_checkbox;
    extern lv_obj_t *ui_available_network_label;
    extern lv_obj_t *ui_av_network_container;
    extern lv_obj_t *ui_wifi_setup;
    extern lv_obj_t *wn_panel;
    extern lv_obj_t *wnp_close_btn;
    extern lv_obj_t *wnp_msg;
    extern lv_obj_t *spinner;

    /* event cb */
    void ui_wifi_scan_event_cb(lv_event_t *event);
    void ui_wifi_pass_ta_event_cb(lv_event_t *event);
    void ui_wifi_conn_event_cb(lv_event_t *event);
    void wnp_close_btn_cb(lv_event_t *event);
    void wnp_update(const char *msg);
    void wnp_del(const char *msg);
    void set_angle(lv_obj_t *spinner, uint32_t v);

    ////////////////////////////////////////////////////////////// RFID TAB /////////////////////////////////////////////////////////
    extern lv_obj_t *ui_bana_dd;
    extern lv_obj_t *ui_power_txtarea;
    extern lv_obj_t *ui_scantime_txtarea;
    extern lv_obj_t *ui_beepon_switch;
    extern lv_obj_t *ui_reader_info_write;
    extern lv_obj_t *ui_device_id_labelx;
    extern lv_obj_t *ui_version_labelx;
    extern lv_obj_t *ui_protocol_labelx;
    extern lv_obj_t *ui_antenna_labelx;
    extern lv_obj_t *ui_maxf_labelx;
    extern lv_obj_t *ui_minf_labelx;
    extern lv_obj_t *ui_baud_dd;

    /* event cb */
    void tabview_slider_cb(lv_event_t *event);
    void ui_reader_info_write_cb(lv_event_t *event);
    void ui_reader_power_txtarea_cb(lv_event_t *event);
    void ui_reader_scantime_txtarea_cb(lv_event_t *event);

    ////////////////////////////////////////////////////////////////////// GLOBAL /////////////////////////////////////////////////////////
    void create_notif_panel(const char *title, const char *msg, bool _spin);
    void notif_msg_update(const char *msg);
    void notif_panel_del();

    extern lv_obj_t *notif_panel;
    extern lv_obj_t *notif_panel_title;
    extern lv_obj_t *notif_close_btn;
    extern lv_obj_t *notif_msg;
    extern lv_obj_t *notif_cross_icon;

    extern void kb_event_cb(lv_event_t *event);
    void make_kb();
    void kb_del();
    extern lv_obj_t *kb;

    void
    ui_init(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
