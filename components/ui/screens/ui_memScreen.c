

#include "../ui.h"

/* global objects */
lv_obj_t *tag_data_table;
lv_obj_t *ui_memScreen;
lv_obj_t *ui_chip_type_label;
lv_obj_t *ui_epc_size_label;
lv_obj_t *ui_tot_mem_label;
lv_obj_t *ui_tid_size_label;
lv_obj_t *ui_usr_size_label;
lv_obj_t *ui_pwd_size_label;
lv_obj_t *ui_mem_scr_log;

void ui_memScreen_screen_init(void)
{
    /* vars */
    uint16_t btn_radius = 8;
    /* local objects */
    lv_obj_t *ui_tag_info_container;
    lv_obj_t *ui_chipType;
    lv_obj_t *ui_epcSize;
    lv_obj_t *ui_totalMem;
    lv_obj_t *ui_tidSize;
    lv_obj_t *ui_pwdSize;
    lv_obj_t *ui_userSize;
    lv_obj_t *ui_home2;

    ui_memScreen = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_memScreen, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_obj_set_style_bg_color(ui_memScreen, lv_color_hex(0xB4E2FF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_memScreen, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_memScreen, &lv_font_montserrat_10, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_tag_info_container = lv_obj_create(ui_memScreen);
    lv_obj_remove_style_all(ui_tag_info_container);
    lv_obj_set_width(ui_tag_info_container, lv_pct(96));
    lv_obj_set_height(ui_tag_info_container, lv_pct(20));
    lv_obj_set_x(ui_tag_info_container, lv_pct(0));
    lv_obj_set_y(ui_tag_info_container, lv_pct(-24));
    lv_obj_set_align(ui_tag_info_container, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_tag_info_container, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_obj_set_style_radius(ui_tag_info_container, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_tag_info_container, lv_color_hex(0xF5F1F4), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_tag_info_container, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_chipType = lv_label_create(ui_tag_info_container);
    lv_obj_set_width(ui_chipType, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_chipType, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_chipType, lv_pct(3));
    lv_obj_set_y(ui_chipType, lv_pct(19));
    lv_label_set_text(ui_chipType, "Chip type");
    lv_obj_set_style_text_font(ui_chipType, &lv_font_montserrat_10, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_chip_type_label = lv_label_create(ui_tag_info_container);
    lv_obj_set_width(ui_chip_type_label, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_chip_type_label, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_chip_type_label, lv_pct(21));
    lv_obj_set_y(ui_chip_type_label, lv_pct(20));
    lv_label_set_text(ui_chip_type_label, "XXXXXXXXXXX");
    lv_obj_set_style_text_font(ui_chip_type_label, &lv_font_montserrat_10, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_epcSize = lv_label_create(ui_tag_info_container);
    lv_obj_set_width(ui_epcSize, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_epcSize, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_epcSize, lv_pct(3));
    lv_obj_set_y(ui_epcSize, lv_pct(53));
    lv_label_set_text(ui_epcSize, "EPC size ");
    lv_obj_set_style_text_font(ui_epcSize, &lv_font_montserrat_10, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_epc_size_label = lv_label_create(ui_tag_info_container);
    lv_obj_set_width(ui_epc_size_label, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_epc_size_label, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_epc_size_label, lv_pct(21));
    lv_obj_set_y(ui_epc_size_label, lv_pct(53));
    lv_label_set_text(ui_epc_size_label, "XX");
    lv_obj_set_style_text_font(ui_epc_size_label, &lv_font_montserrat_10, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_totalMem = lv_label_create(ui_tag_info_container);
    lv_obj_set_width(ui_totalMem, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_totalMem, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_totalMem, lv_pct(50));
    lv_obj_set_y(ui_totalMem, lv_pct(19));
    lv_label_set_text(ui_totalMem, "Total memory");
    lv_obj_set_style_text_font(ui_totalMem, &lv_font_montserrat_10, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_tot_mem_label = lv_label_create(ui_tag_info_container);
    lv_obj_set_width(ui_tot_mem_label, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_tot_mem_label, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_tot_mem_label, lv_pct(77));
    lv_obj_set_y(ui_tot_mem_label, lv_pct(20));
    lv_label_set_text(ui_tot_mem_label, "XX");
    lv_obj_set_style_text_font(ui_tot_mem_label, &lv_font_montserrat_10, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_tidSize = lv_label_create(ui_tag_info_container);
    lv_obj_set_width(ui_tidSize, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_tidSize, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_tidSize, lv_pct(27));
    lv_obj_set_y(ui_tidSize, lv_pct(53));
    lv_label_set_text(ui_tidSize, "TID size");
    lv_obj_set_style_text_font(ui_tidSize, &lv_font_montserrat_10, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_tid_size_label = lv_label_create(ui_tag_info_container);
    lv_obj_set_width(ui_tid_size_label, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_tid_size_label, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_tid_size_label, lv_pct(43));
    lv_obj_set_y(ui_tid_size_label, lv_pct(53));
    lv_label_set_text(ui_tid_size_label, "XX");
    lv_obj_set_style_text_font(ui_tid_size_label, &lv_font_montserrat_10, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_pwdSize = lv_label_create(ui_tag_info_container);
    lv_obj_set_width(ui_pwdSize, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_pwdSize, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_pwdSize, lv_pct(75));
    lv_obj_set_y(ui_pwdSize, lv_pct(52));
    lv_label_set_text(ui_pwdSize, "PWD size");
    lv_obj_set_style_text_font(ui_pwdSize, &lv_font_montserrat_10, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_userSize = lv_label_create(ui_tag_info_container);
    lv_obj_set_width(ui_userSize, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_userSize, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_userSize, lv_pct(50));
    lv_obj_set_y(ui_userSize, lv_pct(53));
    lv_label_set_text(ui_userSize, "User size");
    lv_obj_set_style_text_font(ui_userSize, &lv_font_montserrat_10, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_usr_size_label = lv_label_create(ui_tag_info_container);
    lv_obj_set_width(ui_usr_size_label, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_usr_size_label, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_usr_size_label, lv_pct(68));
    lv_obj_set_y(ui_usr_size_label, lv_pct(53));
    lv_label_set_text(ui_usr_size_label, "XX");
    lv_obj_set_style_text_font(ui_usr_size_label, &lv_font_montserrat_10, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_pwd_size_label = lv_label_create(ui_tag_info_container);
    lv_obj_set_width(ui_pwd_size_label, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_pwd_size_label, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_pwd_size_label, lv_pct(94));
    lv_obj_set_y(ui_pwd_size_label, lv_pct(50));
    lv_label_set_text(ui_pwd_size_label, "XX");
    lv_obj_set_style_text_font(ui_pwd_size_label, &lv_font_montserrat_10, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *ui_tap_create_btn = lv_btn_create(ui_memScreen);
    lv_obj_align(ui_tap_create_btn, LV_ALIGN_TOP_MID, 0, 5);

    lv_obj_add_style(ui_tap_create_btn, &btn_style, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *ui_tap_create_btn_label = lv_label_create(ui_tap_create_btn);
    lv_label_set_text(ui_tap_create_btn_label, "Auth");

    lv_obj_add_style(ui_tap_create_btn_label, &btn_label_style, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_home2 = lv_btn_create(ui_memScreen);
    lv_obj_set_width(ui_home2, 25);
    lv_obj_set_height(ui_home2, 25);
    lv_obj_align(ui_home2, LV_ALIGN_BOTTOM_LEFT, 3, -3);
    lv_obj_set_style_radius(ui_home2, btn_radius, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *ui_home_btn_label = lv_label_create(ui_home2);
    lv_obj_set_align(ui_home_btn_label, LV_ALIGN_CENTER);
    lv_label_set_text(ui_home_btn_label, LV_SYMBOL_HOME);

    /*table*/
    tag_data_table = lv_table_create(ui_memScreen);
    // col
    lv_table_set_col_cnt(tag_data_table, 9);
    lv_table_set_col_width(tag_data_table, 0, 35.55);
    lv_table_set_col_width(tag_data_table, 1, 35.55);
    lv_table_set_col_width(tag_data_table, 2, 35.55);
    lv_table_set_col_width(tag_data_table, 3, 35.55);
    lv_table_set_col_width(tag_data_table, 4, 35.55);
    lv_table_set_col_width(tag_data_table, 5, 35.55);
    lv_table_set_col_width(tag_data_table, 6, 35.55);
    lv_table_set_col_width(tag_data_table, 7, 35.55);
    lv_table_set_col_width(tag_data_table, 8, 35.55);
    // row
    lv_table_set_row_cnt(tag_data_table, 2);
    // lv_obj_set_height(tag_data_table, 60);
    lv_table_set_cell_value(tag_data_table, 0, 0, "MEM.");
    lv_table_set_cell_value(tag_data_table, 1, 0, "EPC");
    lv_table_set_cell_value(tag_data_table, 2, 0, "TID");
    lv_table_set_cell_value(tag_data_table, 3, 0, "USR.");
    lv_table_set_cell_value(tag_data_table, 0, 1, "word0");
    lv_table_set_cell_value(tag_data_table, 0, 2, "word1");
    lv_table_set_cell_value(tag_data_table, 0, 3, "word2");
    lv_table_set_cell_value(tag_data_table, 0, 4, "word3");
    lv_table_set_cell_value(tag_data_table, 0, 5, "word4");
    lv_table_set_cell_value(tag_data_table, 0, 6, "word5");
    lv_table_set_cell_value(tag_data_table, 0, 7, "word6");
    lv_table_set_cell_value(tag_data_table, 0, 8, "word7");
    lv_obj_align(tag_data_table, LV_ALIGN_TOP_MID, 0, 0);
    lv_obj_set_pos(tag_data_table, 0, lv_pct(38));
    lv_obj_set_scroll_dir(tag_data_table, LV_DIR_VER);
    lv_obj_set_style_pad_ver(tag_data_table, 3, LV_PART_ITEMS);
    lv_obj_set_style_pad_hor(tag_data_table, 0, LV_PART_ITEMS);
    lv_obj_set_style_bg_color(tag_data_table, lv_color_hex(0xfffbe6), LV_PART_ITEMS);

    /*NOTIFY LABEL*/
    ui_mem_scr_log = lv_label_create(ui_memScreen);
    lv_obj_set_width(ui_mem_scr_log, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_mem_scr_log, LV_SIZE_CONTENT); /// 1
    lv_obj_set_y(ui_mem_scr_log, -5);
    lv_obj_set_x(ui_mem_scr_log, lv_pct(-2));
    lv_obj_set_align(ui_mem_scr_log, LV_ALIGN_BOTTOM_MID);
    lv_label_set_text(ui_mem_scr_log, "");

    /* events */
    lv_obj_add_event_cb(tag_data_table, ui_event_tag_data_table, LV_EVENT_LONG_PRESSED, NULL);
    lv_obj_add_event_cb(ui_home2, ui_home_btn_cb, LV_EVENT_CLICKED, NULL);               /*Home button callback*/
    lv_obj_add_event_cb(ui_tap_create_btn, ui_event_tap_create, LV_EVENT_CLICKED, NULL); /*Home button callback*/
}
