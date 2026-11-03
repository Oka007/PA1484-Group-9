#pragma once

#include <lvgl.h>

// Declared globallt so other functions can update it
extern lv_obj_t* wifiStatus;
// Create the settings screen UI
void create_settings_screen(lv_obj_t* settingsTile);
