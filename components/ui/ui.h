
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

    /////////////////////////////////////////////////////// SCREEN: ui_checkinOutScreen  //////////////////////////////////////
    extern lv_obj_t *ui_checkinOutScreen;
    extern lv_obj_t *ui_leftContainer;
    extern lv_obj_t *ui_demoImg;
    extern lv_obj_t *ui_checkinOutScreenImgContainer;
    extern lv_obj_t *ui_timeLabelUiAgentCheckin;
    extern lv_obj_t *ui_checkinOutStatusLabel;
    extern lv_obj_t *ui_distributorContainer;
    extern lv_obj_t *ui_distributorLabel;
    extern lv_obj_t *ui_normalBtn2;

    void ui_checkin_checkoutScreen_screen_init(void);

    ////////////////////////////////////////////////////// SCREEN: ui_mainScreen  /////////////////////////////////////////////////

    extern void ui_mainScreen_screen_init(void);
    extern lv_obj_t *ui_mainScreen;
    extern lv_obj_t *ui_iconContainer;
    extern lv_obj_t *ui_bottomContainer;
    extern lv_obj_t *ui_wifiIcon;
    extern lv_obj_t *ui_settingsIcon;
    extern lv_obj_t *ui_label1;
    extern lv_obj_t *table;

    extern lv_obj_t *ui_timeLabel;
    extern lv_obj_t *ui_sdLogo;
    extern lv_obj_t *ui_mergeSwitch;
    extern lv_obj_t *ui_mergeButtonLabel;
    extern lv_obj_t *ui_filterSW;
    extern lv_obj_t *ui_filterBtnLbl;
    extern lv_obj_t *ui_main_scr_keyboard;
    extern lv_obj_t *ui_agentButton;
    extern lv_obj_t *ui_agentButtonLabel;
    extern lv_obj_t *ui_mainScrDataTextarea;
    extern lv_obj_t *ui_mainScrOffsetTextarea;

    void ui_event_mergeSwitch(lv_event_t *e);
    void ui_event_scanFilterSwitch(lv_event_t *e);
    void ui_event_mainScrNotifypanelClose2(lv_event_t *e);
    void ui_event_mainScrOffsetTextarea(lv_event_t *e);
    void ui_event_mainScrDataTextarea(lv_event_t *e);
    void ui_event_mainScrWriteData(lv_event_t *e);
    void ui_event_agentButton(lv_event_t *e);

    /* events */
    void settings_icon_event_cb(lv_event_t *event);
    void table_click_event(lv_event_t *event);
    // void wifi_icon_event_cb(lv_event_t *event);

    /////////////////////////////////////////////////////// SCREEN: ui_memScreen  ///////////////////////////////////////////////////
    void ui_memScreen_screen_init(void);
    void table1_click_event(lv_event_t *e);
    void mem_scr_write(lv_event_t *e);
    extern lv_obj_t *table1;
    extern lv_obj_t *ui_memScreen;
    extern lv_obj_t *ui_Container4;
    extern lv_obj_t *ui_chipType;
    extern lv_obj_t *ui_chipTypeLabel;
    extern lv_obj_t *ui_epcSize;
    extern lv_obj_t *ui_epcSizeLabel;
    extern lv_obj_t *ui_totalMem;
    extern lv_obj_t *ui_totatMemoryLabel;
    extern lv_obj_t *ui_tidSize;
    extern lv_obj_t *ui_tidSizeLabel;
    extern lv_obj_t *ui_pwdSize;
    extern lv_obj_t *ui_userSize;
    extern lv_obj_t *ui_userSizeLabel;
    extern lv_obj_t *ui_pwdSizeLabel;
    void ui_event_home2(lv_event_t *e);
    extern lv_obj_t *ui_home2;
    extern lv_obj_t *ui_TestBtn;
    extern lv_obj_t *ui_TestBtn1;
    extern lv_obj_t *ui_TestBtn2;
    extern lv_obj_t *ui____initial_actions0;
    extern lv_obj_t *ui_memScreenNotifyLabel;
    extern lv_obj_t *ui_memScrPanel;
    void ui_event_memscrNotifypanelClose(lv_event_t *e);
    extern lv_obj_t *ui_memscrNotifypanelClose;
    extern lv_obj_t *ui_notifyPanelclosebuttonlabel2;
    extern lv_obj_t *ui_memScrNotifyPanellabel;
    void ui_event_memScrTextarea(lv_event_t *e);
    extern lv_obj_t *ui_memScrTextarea;
    void ui_event_memScrWriteData(lv_event_t *e);
    extern lv_obj_t *ui_memScrWriteData;
    extern lv_obj_t *ui_notifyPanelclosebuttonlabel1;
    extern lv_obj_t *ui_authPanel;
    void ui_event_memScrNotifypanelClose3(lv_event_t *e);
    extern lv_obj_t *ui_mainScrNotifypanelClose3;
    extern lv_obj_t *ui_notifyPanelclosebuttonlabel7;
    extern lv_obj_t *ui_passASCIIlabel;
    void ui_event_passASCIItxtarea(lv_event_t *e);
    void ui_event_passASCIItxtareaVC(lv_event_t *e);
    extern lv_obj_t *ui_passASCIItxtarea;
    void ui_event_passHEXtxtareaVC(lv_event_t *e);
    void ui_event_passHEXtxtarea(lv_event_t *e);
    extern lv_obj_t *ui_passHEXtxtarea;
    extern lv_obj_t *ui_passHEXlabel;
    void ui_event_passUseBtn_normalBtn(lv_event_t *e);
    extern lv_obj_t *ui_passUseBtn;
    void ui_event_passWriteBtn_normalBtn(lv_event_t *e);
    extern lv_obj_t *ui_passWriteBtn;
    void ui_event_normalBtn1_normalBtn(lv_event_t *e);
    extern lv_obj_t *ui_normalBtn1;

    /////////////////////////////////////////////////////// SCREEN: ui_setupScreen  ////////////////////////////////////////////////
    extern void ui_setupScreen_screen_init(void);
    extern lv_obj_t *ui_setupScreen;
    extern lv_obj_t *tabview;

    /* event cb */
    void ui_home_btn_cb(lv_event_t *event);

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
