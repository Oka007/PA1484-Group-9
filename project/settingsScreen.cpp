#include "settingsScreen.h"
// #include "project.ino"
#include "secrets.h"
#include "saveSettings.h"
#include <ArduinoJson.h>
#include <LittleFS.h>
#include "departureScreen.h"
#include "api.hpp"

lv_obj_t *wifiStatus = nullptr;
static JsonDocument station_json;
JsonArray station_array;

//Global variable that shows what station is selected 
String station_alt = "";

String readStations() {
    Serial.println("Run readStations()");

    if (!LittleFS.begin(true)) {
        Serial.println("Could not begin LittleFS");
        return "";
    }

    File file = LittleFS.open("/karlskrona_stations.json", "r");

    if (!file) {
        Serial.println("Stations could not be opened");
        return "";
    }


    DeserializationError error = deserializeJson(station_json, file);
    file.close();

    if(error){
        Serial.print("Deserialisation failed: ");
        Serial.println(error.f_str());
        return "";
    }

    station_array = station_json["stopLocationOrCoordLocation"].as<JsonArray>();
    
    String station_options = "";

    for (JsonObject station : station_array) {
        String name = station["StopLocation"]["name"];

        if (station_options.length() > 0) {
            station_options += "\n";
        }

        station_options += name;
    }

    return station_options;
}

// Makes an event based on what changes with the stations drop box
static void event_handler_stops(lv_event_t *e)
{
    // Changes the former station to the one selected
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *obj = lv_event_get_target(e);
    if (code == LV_EVENT_VALUE_CHANGED)
    {
        char buf[64];
        lv_dropdown_get_selected_str(obj, buf, sizeof(buf));
        LV_LOG_USER("Option: %s", buf);

        //Changes the station that is chosen 
        station_alt = String(buf);

        // Change stored setting
        int selectedVal = lv_dropdown_get_selected(obj);
        preferences.putInt("selectedStop", selectedVal);
        Serial.println("STOP");

        update_departure_title(selectedVal);
    }
}
// Makes an event based on what changes with the transporttypes drop box
static void event_handler_transport(lv_event_t *e)
{
    // Changes the former tranporttype to the one selected
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *obj = lv_event_get_target(e);
    if (code == LV_EVENT_VALUE_CHANGED)
    {
        char buf[32];
        lv_dropdown_get_selected_str(obj, buf, sizeof(buf));
        LV_LOG_USER("Option: %s", buf);

        // Change stored setting
        int selectedVal = lv_dropdown_get_selected(obj);
        preferences.putInt("selectedTran", selectedVal);
        Serial.println("TRANSPORT");
    }
}

// Create the settings screen UI
void create_settings_screen(lv_obj_t *settingsTile)
{

    lv_obj_t *title = lv_label_create(settingsTile);

    lv_label_set_text(title, "settings");

    lv_obj_align(title, LV_ALIGN_TOP_MID, 0, 20);

    // Connection status area
    wifiStatus = lv_label_create(settingsTile);
    lv_label_set_text(wifiStatus, "WiFi Connection: 0%");
    lv_obj_align(wifiStatus, LV_ALIGN_TOP_RIGHT, -5, 5);

    // Create a drop down list for stations
    lv_obj_t *stop_list = lv_dropdown_create(settingsTile);
    lv_dropdown_set_options(stop_list, readStations().c_str());

    // Set selected stop to saved settings during startup
    int selectedStop = preferences.getInt("selectedStop");
    lv_dropdown_set_selected(stop_list, selectedStop);

    // Set the size and position of drop down list for stations
    lv_obj_set_size(stop_list, 300, 100);
    lv_obj_align(stop_list, LV_ALIGN_TOP_LEFT, 50, 70);

    // Makes an event happen every time a change happens in the list for stations
    lv_obj_add_event_cb(stop_list, event_handler_stops, LV_EVENT_ALL, NULL);
}

// "station 12\n "station 13"