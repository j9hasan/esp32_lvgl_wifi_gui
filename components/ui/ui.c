#include <stdio.h>
#include <esp_log.h>
#include "ui.h"
#include "ui_helpers.h"
#include "shared_task.h"
#include "wifi_app.h"

#if LV_COLOR_DEPTH != 16
#error "LV_COLOR_DEPTH should be 16bit to match SquareLine Studio's settings"
#endif
#if LV_COLOR_16_SWAP != 1
#error "LV_COLOR_16_SWAP should be 1 to match SquareLine Studio's settings"
#endif

/* only global objects are here */

/////////////////////////////////////////////////////// SCREEN: ui_checkinOutScreen  //////////////////////////////////////

lv_obj_t *ui_checkinOutScreen;
lv_obj_t *ui_leftContainer;
lv_obj_t *ui_demoImg;
lv_obj_t *ui_checkinOutScreenImgContainer;
lv_obj_t *ui_timeLabelUiAgentCheckin;
lv_obj_t *ui_checkinOutStatusLabel;
lv_obj_t *ui_distributorContainer;
lv_obj_t *ui_distributorLabel;
lv_obj_t *ui_normalBtn2;

void ui_checkin_checkoutScreen_screen_init(void);

///////////////////////////////////////////////////// SCREEN: ui_memScreen ////////////////////////////////////////////////

void ui_memScreen_screen_init(void);
void ui_event_memScreen(lv_event_t *e);
lv_obj_t *table1;
lv_obj_t *ui_memScreen;
lv_obj_t *ui_Container4;
lv_obj_t *ui_chipType;
lv_obj_t *ui_chipTypeLabel;
lv_obj_t *ui_epcSize;
lv_obj_t *ui_epcSizeLabel;
lv_obj_t *ui_totalMem;
lv_obj_t *ui_totatMemoryLabel;
lv_obj_t *ui_tidSize;
lv_obj_t *ui_tidSizeLabel;
lv_obj_t *ui_pwdSize;
lv_obj_t *ui_userSize;
lv_obj_t *ui_userSizeLabel;
lv_obj_t *ui_pwdSizeLabel;

lv_obj_t *ui_TestBtn;

void ui_event_home2(lv_event_t *e);
lv_obj_t *ui_home2;
lv_obj_t *ui_memScreenNotifyLabel;
lv_obj_t *ui_memScrPanel;
void ui_event_memscrNotifypanelClose(lv_event_t *e);
lv_obj_t *ui_memscrNotifypanelClose;
lv_obj_t *ui_notifyPanelclosebuttonlabel2;
lv_obj_t *ui_memScrNotifyPanellabel;
void ui_event_memScrTextarea(lv_event_t *e);
lv_obj_t *ui_memScrTextarea;
void ui_event_memScrWriteData(lv_event_t *e);
lv_obj_t *ui_memScrWriteData;
lv_obj_t *ui_notifyPanelclosebuttonlabel1;
lv_obj_t *ui_authPanel;
void ui_event_memScrNotifypanelClose3(lv_event_t *e);
lv_obj_t *ui_mainScrNotifypanelClose3;
lv_obj_t *ui_notifyPanelclosebuttonlabel7;
lv_obj_t *ui_passASCIIlabel;
void ui_event_passASCIItxtarea(lv_event_t *e);
// void ui_event_passASCIItxtareaVC(lv_event_t *e);
lv_obj_t *ui_passASCIItxtarea;
void ui_event_passHEXtxtarea(lv_event_t *e);
// void ui_event_passHEXtxtareaVC(lv_event_t *e);
lv_obj_t *ui_passHEXtxtarea;
lv_obj_t *ui_passHEXlabel;
void ui_event_passUseBtn_normalBtn(lv_event_t *e);
lv_obj_t *ui_passUseBtn;
void ui_event_passWriteBtn_normalBtn(lv_event_t *e);
lv_obj_t *ui_passWriteBtn;
void ui_event_normalBtn1_normalBtn(lv_event_t *e);
lv_obj_t *ui_normalBtn1;

////////////////////////////////////////////////////////////// SCREEN: ui_mainScreen  //////////////////////////////////////////////////////////
void ui_mainScreen_screen_init(void);
lv_obj_t *ui_mainScreen;
lv_obj_t *ui_iconContainer;
lv_obj_t *ui_bottomContainer;
lv_obj_t *ui_wifiIcon;
lv_obj_t *ui_settingsIcon;
lv_obj_t *ui_label1;
lv_obj_t *table;

lv_obj_t *ui_timeLabel;
lv_obj_t *ui_sdLogo;
lv_obj_t *ui_mergeSwitch;
lv_obj_t *ui_mergeButtonLabel;
lv_obj_t *ui_filterSW;
lv_obj_t *ui_filterBtnLbl;
lv_obj_t *ui_main_scr_keyboard;
lv_obj_t *ui_agentButton;
lv_obj_t *ui_agentButtonLabel;
lv_obj_t *ui____initial_actions0;

void makeFilterPanel();
void delFilterPanel(lv_obj_t *obj);

void ui_event_mergeSwitch(lv_event_t *e);
void ui_event_scanFilterSwitch(lv_event_t *e);
void ui_event_mainScrNotifypanelClose2(lv_event_t *e);
void ui_event_mainScrOffsetTextarea(lv_event_t *e);
void ui_event_mainScrDataTextarea(lv_event_t *e);
void ui_event_mainScrWriteData(lv_event_t *e);
void ui_event_agentButton(lv_event_t *e);

/* go to setup screen */
void settings_icon_event_cb(lv_event_t *event)
{
    lv_scr_load_anim(ui_setupScreen, LV_SCR_LOAD_ANIM_MOVE_LEFT, 200, 0, false);
}

void ui_event_agentButton(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *target = lv_event_get_target(e);
    if (event_code == LV_EVENT_CLICKED)
    {
        _ui_screen_change(&ui_checkinOutScreen, LV_SCR_LOAD_ANIM_OVER_LEFT, 200, 0, &ui_checkin_checkoutScreen_screen_init);
        _ui_screen_delete(&ui_mainScreen);
    }
}

/* filter panel functionality */
// global obj
lv_obj_t *ui_mainScrPanel;
lv_obj_t *ui_mainScrDataTextarea;
lv_obj_t *ui_mainScrOffsetTextarea;

void ui_event_scanFilterSwitch(lv_event_t *e)
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
            // lv_obj_move_background(table);
            lv_label_set_text(ui_filterBtnLbl, "F:1");
            filterOn = true;
        }
    }
}
void ui_event_mainScrWriteData(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    if (event_code == LV_EVENT_CLICKED)
    {
        set_scan_filter(e);
        kb_del();
        // _ui_flag_modify(ui_main_scr_keyboard, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
    }
}

void ui_event_mainScrNotifypanelClose2(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    if (event_code == LV_EVENT_CLICKED)
    {
        delFilterPanel(ui_mainScrPanel);
    }
}
void ui_event_mainScrOffsetTextarea(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    if (event_code == LV_EVENT_CLICKED)
    {
        make_kb(ui_mainScrOffsetTextarea);
    }
}
void ui_event_mainScrDataTextarea(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    if (event_code == LV_EVENT_CLICKED)
    {
        lv_obj_move_background(table);
        // lv_obj_move_foreground(ui_main_scr_keyboard);
        make_kb(ui_mainScrDataTextarea);
    }
}
void ui_event_mergeSwitch(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    if (event_code == LV_EVENT_CLICKED)
    {
        merge_switch_click(e);
    }
}
void table_click_event(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    if (event_code == LV_EVENT_LONG_PRESSED)
    {
        lv_table_get_selected_cell(table, &row_, &col_);
        printf("row: %u, col %u\n", row_, col_);
        if (row_ > 0 && col_ < 1)
        {
            mem_screen(e);
            _ui_screen_delete(&ui_mainScreen);
            _ui_screen_change(&ui_memScreen, LV_SCR_LOAD_ANIM_MOVE_LEFT, 50, 0, &ui_memScreen_screen_init);
        }
    }
}
///////////////////////////////////////////////////////////// SCREEN: ui_memScreen    ////////////////////////////////////////////////////////////

////////////////////MEM SCREEN///////////////////////

void ui_event_memScrNotifypanelClose3(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    if (event_code == LV_EVENT_CLICKED)
    {
        _ui_flag_modify(ui_authPanel, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
        // del auth panel
    }
}
void ui_event_passASCIItxtarea(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    if (event_code == LV_EVENT_CLICKED)
    {
        make_kb(ui_passASCIItxtarea);
    }
}
void ui_event_passASCIItxtareaVC(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    // printf("target = %s\n", target->parent);
    fflush(stdout);
    if (event_code == LV_EVENT_VALUE_CHANGED)
    {
        onChangeASCII(e);
        // lv_event_send(ui_passHEXtxtarea, LV_EVENT_REFRESH, NULL);
    }
}
void ui_event_passHEXtxtarea(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if (event_code == LV_EVENT_CLICKED)
    {
        make_kb(ui_passHEXtxtarea);
    }
}
void ui_event_passHEXtxtareaVC(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    if (event_code == LV_EVENT_VALUE_CHANGED)
    {
        onChangeHEX(e);
    }
}

void table1_click_event(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    if (event_code == LV_EVENT_LONG_PRESSED)
    {
        lv_table_get_selected_cell(table1, &row_, &col_);
        _ui_flag_modify(ui_memScrPanel, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
        // make panel
    }
}
void ui_event_memscrNotifypanelClose(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    if (event_code == LV_EVENT_CLICKED)
    {
        _ui_flag_modify(ui_memScrPanel, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
        // panel del
    }
}
void ui_event_memScrTextarea(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    if (event_code == LV_EVENT_CLICKED)
    {
        make_kb(ui_memScrTextarea);
    }
}
void ui_event_memScrWriteData(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    if (event_code == LV_EVENT_CLICKED)
    {
        mem_scr_write(e);
    }
}

///////////////////////////////////////////////////////////// SCREEN: ui_setupScreen  ////////////////////////////////////////////////////////////
void ui_setupScreen_screen_init(void);
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
    lv_scr_load_anim(ui_mainScreen, LV_SCR_LOAD_ANIM_MOVE_RIGHT, 200, 0, false);
    __log("going home");
}

void ui_init(void)
{
    lv_disp_t *dispp = lv_disp_get_default();
    lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED),
                                              false, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    ui_mainScreen_screen_init();
    ui_setupScreen_screen_init();
    ui_memScreen_screen_init();
    ui____initial_actions0 = lv_obj_create(NULL);
    lv_disp_load_scr(ui_mainScreen);
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
        lv_obj_add_event_cb(ui_mainScrNotifypanelClose2, ui_event_mainScrNotifypanelClose2, LV_EVENT_ALL, NULL);
        lv_obj_add_event_cb(ui_mainScrOffsetTextarea, ui_event_mainScrOffsetTextarea, LV_EVENT_ALL, NULL);
        lv_obj_add_event_cb(ui_mainScrDataTextarea, ui_event_mainScrDataTextarea, LV_EVENT_ALL, NULL);
        lv_obj_add_event_cb(ui_mainScrWriteData, ui_event_mainScrWriteData, LV_EVENT_ALL, NULL);
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