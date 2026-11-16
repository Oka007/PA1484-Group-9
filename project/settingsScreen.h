#pragma once

#include <ArduinoJson.h>
#include <lvgl.h>

// Declared globallt so other functions can update it
extern lv_obj_t* wifiStatus;
extern JsonArray station_array;
// Create the settings screen UI
void create_settings_screen(lv_obj_t* settingsTile);
