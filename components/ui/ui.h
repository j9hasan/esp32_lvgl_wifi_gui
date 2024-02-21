
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
    // SCREEN: ui_mainScreen

    extern void ui_mainScreen_screen_init(void);
    extern lv_obj_t *ui_mainScreen;

    /* containers */
    extern lv_obj_t *ui_iconContainer;
    extern lv_obj_t *ui_bottomContainer;

    /* icons */
    extern lv_obj_t *ui_wifiIcon;
    extern lv_obj_t *ui_settingsIcon;

    /* labels */
    extern lv_obj_t *ui_label1;

    /* buttons */

    /* events */
    void settings_icon_event_cb(lv_event_t *event);
    // void wifi_icon_event_cb(lv_event_t *event);

    /* others */
    extern lv_obj_t *ui____initial_actions0;

    // SCREEN: ui_setupScreen

    /* event cb */
    void ui_home_btn_cb(lv_event_t *event);

    extern lv_obj_t *tabview;

    /* wifi tab */
    extern void ui_setupScreen_screen_init(void);
    extern lv_obj_t *ui_setupScreen;
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
