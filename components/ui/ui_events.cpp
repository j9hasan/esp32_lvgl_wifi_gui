
#include "ui.h"
#include "shared_task.h"
#include "inventory.h"
#include "stdio.h"
#include "esp_log.h"
#include <string.h>
#include "wifi_app.h"

// volatile bool merge_on = false;
TagInfo ti;
unsigned char EPCNUM_g[64];
int epclen_g = 0;
unsigned char mem_data[] = {0x00, 0x00};
unsigned char epc_data[] = {0x00, 0x00};
uint16_t row_ = 0, col_ = 0;

void mem_screen(lv_event_t *e)
{

	const char *st = lv_table_get_cell_value(epc_table, row_, col_);
	string epcFromTable = st;
	int n = Inventory(false);
	string tidString;
	/*refresh ui*/
	lv_label_set_text(ui_chip_type_label, "");
	lv_label_set_text(ui_epc_size_label, "");
	lv_label_set_text(ui_pwd_size_label, "");
	lv_label_set_text(ui_usr_size_label, "");
	lv_label_set_text(ui_tot_mem_label, "");

	for (uint8_t i = 0; i < n; i++)
	{
		ScanResult sd;
		GetResult((unsigned char *)&sd, i);
		unsigned char tid[16];
		unsigned char tidlen = 0;
		string epc = string((char *)sd.epc, sd.epclen);
		string epcFromScan = tohex(epc);
		if (epcFromTable == epcFromScan)
		{
			if (GetTID(sd.epc, sd.epclen, tid, &tidlen))
			{
				memcpy(EPCNUM_g, sd.epc, sizeof(sd.epc));
				// memcpy(epclen_g, sd->epclen, sizeof(sd->epclen));
				epclen_g = sd.epclen;
				// EPCNUM_g[sizeof(sd->EPCNUM) - 1] = '\0';
				__log("tid found\n");
				tidString = bytes2hex(tid, tidlen);
				GetTagInfo(tid, &ti);

				/*tid found, populate ui*/
				lv_label_set_text(ui_chip_type_label, ti.chip);
				lv_label_set_text(ui_epc_size_label, intToString(ti.epclen));
				lv_label_set_text(ui_pwd_size_label, intToString(ti.pwdlen));
				lv_label_set_text(ui_usr_size_label, intToString(ti.userlen));
				uint16_t totalmem = (ti.epclen) + (ti.userlen) + ti.tidlen + (ti.pwdlen * 2) + 4;
				lv_label_set_text(ui_tot_mem_label, intToString(totalmem));

				/*Wtie EPC & TID in UI*/
				std::string originalString(epcFromScan);
				std::string originalString_(tidString);
				const size_t substringSize = 4;
				size_t numSubstrings = originalString.length() / substringSize;
				std::string substrings[numSubstrings];
				std::string substrings_[numSubstrings];
				for (size_t i = 0; i < numSubstrings; ++i)
				{
					substrings[i] = originalString.substr(i * substringSize, substringSize);
					substrings_[i] = originalString_.substr(i * substringSize, substringSize);
					lv_table_set_cell_value_fmt(tag_data_table, 1, i + 1, "%s", substrings[i].c_str());
					lv_table_set_cell_value_fmt(tag_data_table, 2, i + 1, "%s", substrings_[i].c_str());
					// memset(substrings, 0x00, sizeof(substrings));
					// memset(substrings_, 0x00, sizeof(substrings_));
				}
				__log("usrlen : %d", ti.userlen);
				__log("usrlen/2 : %d", ti.userlen);

				/*SET USER COL*/
				if ((ti.userlen / 2) < 8)
				{
					__log("usrlen<8\n");
					lv_table_set_row_cnt(tag_data_table, 2 + 1);
					lv_table_set_cell_value(tag_data_table, 2 + 1, 0, "USR(7)");
				}
				else if ((ti.userlen / 2) >= 8 && (ti.userlen / 2) <= 32)
				{
					printf("usrlen 8-32\n");
					lv_table_set_row_cnt(tag_data_table, 2 + 4);
					lv_table_set_cell_value(tag_data_table, 2 + 1, 0, "USR(7)");
					lv_table_set_cell_value(tag_data_table, 2 + 2, 0, "(8-15)");
					lv_table_set_cell_value(tag_data_table, 2 + 3, 0, "(16-23)");
					lv_table_set_cell_value(tag_data_table, 2 + 4, 0, "(24-31)");
				}
				/*read user memory*/
				for (uint8_t j = 0; j < ti.userlen / 2; j++)
				{
					if (ReadMemWord(sd.epc, sd.epclen, mem_data, j))
					{
						if (j < 8)
						{
							lv_table_set_cell_value_fmt(tag_data_table, 2 + 1, j + 1, "% 02x % 02x", mem_data[0], mem_data[1]);
							printf("j : %d, userData %2x%2x\n", j, mem_data[0], mem_data[1]);
							/*create new user row TODO*/
							// lv_table_set_cell_value_fmt(tag_data_table, 4, j + 8, "% 02x % 02x", mem_data[0], mem_data[1]);
						}
						else if (j >= 8 && j < 16)
						{

							lv_table_set_cell_value_fmt(tag_data_table, 4, j - 7, "% 02x % 02x", mem_data[0], mem_data[1]);
						}
						else if (j >= 16 && j < 24)
						{

							lv_table_set_cell_value_fmt(tag_data_table, 5, j - 15, "% 02x % 02x", mem_data[0], mem_data[1]);
						}
						else if (j >= 24 && j < 32)
						{

							lv_table_set_cell_value_fmt(tag_data_table, 6, j - 23, "% 02x % 02x", mem_data[0], mem_data[1]);
						}

						memset(mem_data, 0x00, sizeof(mem_data));
					}
					else
					{
						__log("Failed to read user data");
						/*set user cells to null in UI*/
						// lv_table_set_cell_value_fmt(tag_data_table, 3, j + 1, "% s % s", NULL, "");
						break;
					}
				}
			}
			else
			{
				/*tid not found, handle accordingly*/
			}
		}
	} /*inv for loop*/
}

bool WriteEpcWord_u(unsigned char *epc, unsigned char epclen, unsigned char *data, unsigned char windex)
{
	if (WriteEpcWord(epc, epclen, data, windex))
	{
		lv_label_set_text_fmt(ui_mem_scr_log, "EPC data written at word%u.", col_ - 1);
		vTaskDelay(2000 / portTICK_PERIOD_MS);
		lv_label_set_text(ui_mem_scr_log, "");
		return 1;
	}
	else
	{
		lv_label_set_text(ui_mem_scr_log, "Failed to write EPC.");
		vTaskDelay(2000 / portTICK_PERIOD_MS);
		lv_label_set_text(ui_mem_scr_log, "");
		return 0;
	}
}
bool WriteMemWord_u(unsigned char *epc, unsigned char epclen, unsigned char *data, unsigned char windex);

void mem_scr_write_task(void *pVparameters)
{
	const char *txtAreaData = lv_textarea_get_text(ui_tdwp_dat_ta);
	/*CONVErt to uppeRCASE*/
	/*
	 */
	unsigned char mem_data_[2];
	if (strlen(txtAreaData) == 4)
	{
		printf("row: %u, col %u\n", row_, col_);
		sscanf(txtAreaData, "%2hhx", &mem_data_[0]);
		sscanf(txtAreaData + 2, "%2hhx", &mem_data_[1]);
		switch (row_)
		{
		case 1:
			/*Handle EPC data*/
			if (WriteEpcWord_u(EPCNUM_g, epclen_g, mem_data_, col_ - 1))
			{
				lv_table_set_cell_value(tag_data_table, row_, col_, txtAreaData);
			}
			break;
		case 2:
			/*HANDLE TID DATA*/
			/*TID IS RED ONLY*/
			break;
		case 3:
			/*USR0-7*/
			if (WriteMemWord_u(EPCNUM_g, epclen_g, mem_data_, col_ - 1))
			{
				lv_table_set_cell_value(tag_data_table, row_, col_, txtAreaData);
			}
			break;
		case 4:
			/*USR8-15*/
			col_ = col_ + 8;
			if (WriteMemWord_u(EPCNUM_g, epclen_g, mem_data_, col_ - 1))
			{
				lv_table_set_cell_value(tag_data_table, row_, col_ - 8, txtAreaData);
			}
			break;
		case 5:
			/*USR16-24*/
			col_ = col_ + 8 * 2;
			if (WriteMemWord_u(EPCNUM_g, epclen_g, mem_data_, col_ - 1))
			{
				lv_table_set_cell_value(tag_data_table, row_, col_ - 8 * 2, txtAreaData);
			}
			break;
		case 6:
			/*USR25-31*/
			col_ = col_ + 8 * 3;
			if (WriteMemWord_u(EPCNUM_g, epclen_g, mem_data_, col_ - 1))
			{
				lv_table_set_cell_value(tag_data_table, row_, col_ - 8 * 3, txtAreaData);
			}
			break;
		default:
			/*INVALID ROW*/
			break;
		}
		lv_textarea_set_text(ui_tdwp_dat_ta, "");
	}
	else
	{
		printf("data size invalid %d\n", strlen(txtAreaData));

		lv_label_set_text(ui_mem_scr_log, "invalid data");
		vTaskDelay(2000 / portTICK_PERIOD_MS);
		lv_textarea_set_text(ui_tdwp_dat_ta, "");
		lv_label_set_text(ui_mem_scr_log, "");
	}
	mem_task_handle = NULL;
	vTaskDelete(mem_task_handle);
}
TaskHandle_t mem_task_handle = NULL;
void tdw_panel_write_cb(lv_event_t *e)
{

	if (mem_task_handle == NULL)
	{
		xTaskCreatePinnedToCore(
			mem_scr_write_task,	  // Task function
			"mem_scr_write_task", // Task name
			MEM_TASK_STACK_SIZE,  // Stack size
			NULL,				  // Task parameters (if any)
			MEM_TASK_PRIORITY,	  // Task priority
			&mem_task_handle,	  // Task handle (optional, can be NULL)
			MEM_TASK_CORE		  // Core to pin the task to (0 or 1)
		);
	}
	else
	{
		__log("TASK ALREADY RUNNING");
	}
}
bool onAciiTextarea = false;
bool onHexTextarea = false;
char *ascii2hex(const char *ascii);
void onChangeASCII(lv_event_t *e)
{
	if (!onHexTextarea)
	{
		onAciiTextarea = true;
		const char *passAscii;
		passAscii = lv_textarea_get_text(ui_tap_pass_ascii_ta);
		const char *passHex = ascii2hex(passAscii);
		lv_textarea_set_text(ui_tap_pass_hex_ta, passHex);
		onAciiTextarea = false;
		delete[] (passHex);
	}
}
char *hex2ascii(const char *hex);
void onChangeHEX(lv_event_t *e)
{

	if (!onAciiTextarea)
	{
		onHexTextarea = true;
		const char *passhex;
		passhex = lv_textarea_get_text(ui_tap_pass_hex_ta);
		const char *passascii = hex2ascii(passhex);
		lv_textarea_set_text(ui_tap_pass_ascii_ta, passascii);
		delete[] (passascii);
		onHexTextarea = false;
	}
}
void pass_write(lv_event_t *e)
{
	const char *passHex_;
	passHex_ = lv_textarea_get_text(ui_tap_pass_hex_ta);
	int passHexLen = (strlen(passHex_) + 1) / 2;
	printf(" passHexLen %d\n", passHexLen);
	if (SetPassword(EPCNUM_g, epclen_g, (unsigned char *)passHex_, 4))
	{
		lv_label_set_text(ui_mem_scr_log, "");
		lv_label_set_text_fmt(ui_mem_scr_log, "Pass set: %s", passHex_);
	}
	else
	{
		lv_label_set_text(ui_mem_scr_log, "");
		lv_label_set_text(ui_mem_scr_log, "Pass not set");
	}
}
void pass_use(lv_event_t *e)
{
	lv_label_set_text(ui_mem_scr_log, "");
	lv_label_set_text(ui_mem_scr_log, "Pass use pressed");
}
void pass_default(lv_event_t *e)
{
	lv_label_set_text(ui_mem_scr_log, "");
	lv_label_set_text(ui_mem_scr_log, "Pass default pressed");
}
void test_btn_pressed(lv_event_t *e)
{
	lv_label_set_text(ui_mem_scr_log, "");
	lv_label_set_text(ui_mem_scr_log, "Test btn pressed");
}
void test_btn1_pressed(lv_event_t *e)
{
	lv_label_set_text(ui_mem_scr_log, "");
	lv_label_set_text(ui_mem_scr_log, "Test btn1 pressed");
}

void test_btn2_pressed(lv_event_t *e)
{
	// Your code here
	lv_label_set_text(ui_mem_scr_log, "");
	lv_label_set_text(ui_mem_scr_log, "Test btn2 pressed");
}
void merge_switch_click(lv_event_t *e)
{
	// Your code here
	if (merge_on)
	{
		merge_on = false;
		lv_label_set_text(ui_mergeButtonLabel, "M:0");
		sdVector.clear();
	}
	else
	{
		lv_label_set_text(ui_mergeButtonLabel, "M:1");
		merge_on = true;
	}
}
void set_scan_filter(lv_event_t *e)
{

	if (filterOn)
	{
		const char *str = lv_textarea_get_text(ui_mainScrDataTextarea);
		size_t str_len = strlen(str);
		// Allocate memory for the array
		unsigned char *maskData = (unsigned char *)malloc((str_len + 1) / 2);

		// Convert each pair of characters in the string to a byte in the array
		for (size_t i = 0; i < str_len; i += 2)
		{
			char byteStr[3] = {str[i], str[i + 1], '\0'};
			maskData[i / 2] = (unsigned char)strtol(byteStr, NULL, 16);
		}

#ifdef DEBUG
		// Print the array elements for verification
		__log("Array elements: ");
		for (size_t i = 0; i < (str_len + 1) / 2; i++)
		{
			__log("0x%02X ", maskData[i]);
		}
#endif
		// __log( "\n");
		size_t maskDataSize = (str_len + 1) / 2; // number of elements in the array
		__log("Size of maskData: %zu", maskDataSize);
		const char *maskOffset_ = lv_textarea_get_text(ui_mainScrOffsetTextarea);
		int maskOffset = atoi(maskOffset_);
		__log("mask offset %d: data ", maskOffset);
		if (SetFilter(maskOffset, maskDataSize, maskData))
		{
			__log("Filter set");
		}
		else
		{
			__log("Failed to set filter.");
		}
		// Don't forget to free the allocated memory
		free(maskData);
	}
}
void wifi_icon_clicked(lv_event_t *e)
{
	// Your code here
}

void no_wifi_icon_clicked(lv_event_t *e)
{
	// Your code here
}

void ssid_dropdown_vchanged(lv_event_t *e)
{
	// Your code here
}

void connect_function(lv_event_t *e)
{
	// if (wifi_connect_task_handle == NULL)
	// {
	// 	xTaskCreatePinnedToCore(connect_to_wifi, "wifi_connect_task", WIFI_CONNECT_TASK_STACK_SIZE, NULL, WIFI_TASK_PRIORITY, &wifi_connect_task_handle, WIFI_TASK_CORE);
	// }
	// else
	// {
	// 	printf("wifi connect task already running");
	// }
}

void scan_function(lv_event_t *e)
{
	// if (wifi_scan_task_handle == NULL)
	// {
	// 	xTaskCreatePinnedToCore(scan_wifi, "wifi_scan_task", WIFI_SCAN_TASK_STACK_SIZE, NULL, WIFI_TASK_PRIORITY, &wifi_scan_task_handle, WIFI_TASK_CORE);
	// }
	// else
	// {
	// 	printf("wifi scan task already running");
	// }
}

void eeprom_connect(lv_event_t *e)
{
	// Your code here
}

void bt_bitrate_dd_vchanged(lv_event_t *e)
{
	// Your code here
}

void save_bt_(lv_event_t *e)
{
	// Your code here
}

void stop_bt_(lv_event_t *e)
{
	// Your code here
}

void start_bt_(lv_event_t *e)
{
	// Your code here
}

void rfid_baud_dd_vchanged(lv_event_t *e)
{
	// Your code here
}

void rfid_band_dd_vchanged(lv_event_t *e)
{
	// Your code here
}

void write_rfid(lv_event_t *e)
{
	// Your code here
}

void audio_dd_value_changed(lv_event_t *e)
{
	// Your code here
}

void play_music(lv_event_t *e)
{
	// Your code here
}

void stop_music(lv_event_t *e)
{
	// Your code here
}

void kill_audio_task(lv_event_t *e)
{
	// Your code here
}

void search_music(lv_event_t *e)
{
	// Your code here
}

void save_to_sd_btn_clicked(lv_event_t *e)
{
	// Your code here
}

void write_setup(lv_event_t *e)
{
	// Your code here
}

void beepon_clicked(lv_event_t *e)
{
	// Your code here
}

void mem_test_btn_called(lv_event_t *e)
{
	// Your code here
}
/*ASCII to HEX*/
#include <iostream>
#include <cstring>
#define PASSWORD_CHARACTERS " ABCDEFGHIJKLMNOPQRSTUVWXYZ_-.@#"
char *ascii2hex(const char *ascii)
{
	long n = 0, d = 0;
	int N = std::strlen(ascii);
	// Limit the processing to the first 6 characters
	if (N > 6)
		N = 6;
	if (N < 3)
		d = 0;
	else
		d = N - 3;
	for (int i = 0; i < N; i++)
	{
		char c = ascii[i];
		const char *indexPtr = std::strchr(PASSWORD_CHARACTERS, c);
		if (indexPtr != nullptr)
		{
			int index = indexPtr - PASSWORD_CHARACTERS;
			long nc = index << (5 * i);
			n |= nc;
		}
	}
	n <<= 2;
	n |= d;
	char *hex = new char[9]; // 8 characters for the hex representation + 1 for the null terminator
	std::sprintf(hex, "%08lX", n);
	return hex;
}
/*HEX TO ASCII*/
char *hex2ascii(const char *hex)
{
	// Make the length even
	size_t hexLength = std::strlen(hex);
	char *modifiedHex = new char[hexLength + 2]; // +2 for the extra "0" and null terminator
	std::strcpy(modifiedHex, hex);
	if (hexLength % 2 != 0)
	{
		modifiedHex[hexLength] = '0';
		modifiedHex[hexLength + 1] = '\0';
	}
	// Convert hex to decimal
	unsigned long long n = std::strtoull(modifiedHex, nullptr, 16);
	delete[] modifiedHex;		// Free the dynamically allocated memory
	char *result = new char[8]; // Assuming the maximum output size is 8 characters
	int d = static_cast<int>(n & 0x03) + 3;
	n >>= 2;
	int index = 0;
	for (int i = 0; i < d; i++)
	{
		long long nn = (n >> (i * 5));
		int cindex = static_cast<int>(nn & 0x1F);
		result[index++] = PASSWORD_CHARACTERS[cindex];
	}
	result[index] = '\0'; // Null-terminate the result string
	return result;
}
bool WriteMemWord_u(unsigned char *epc, unsigned char epclen, unsigned char *data, unsigned char windex)
{
	if (WriteMemWord(epc, epclen, data, windex))
	{
		lv_label_set_text_fmt(ui_mem_scr_log, "User data written at word%u.", col_ - 1);
		vTaskDelay(2000 / portTICK_PERIOD_MS);
		lv_label_set_text(ui_mem_scr_log, "");
		return 1;
	}
	else
	{
		lv_label_set_text(ui_mem_scr_log, "Failed to write.");
		vTaskDelay(2000 / portTICK_PERIOD_MS);
		lv_label_set_text(ui_mem_scr_log, "");
		return 0;
	}
}