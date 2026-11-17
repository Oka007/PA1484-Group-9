#pragma once

#include <ArduinoJson.h>
#include <lvgl.h>
#include <memory>
#include <vector>
#include "Transport/transport.h"

extern string selected_stop_id;
extern std::string selected_transport;

extern std::vector<std::shared_ptr<Transport>> departures;
// Declared globallt so other functions can update it
extern lv_obj_t* wifiStatus;
extern JsonArray station_array;
// Create the settings screen UI
void create_settings_screen(lv_obj_t* settingsTile);
