

#include "journeySelectionScreen.h"
#include "settingsScreen.h"
#include "Arduino.h"
#include "api.h"

String readStations();

static lv_obj_t* fromStop;
static lv_obj_t* toStop;
static lv_obj_t* resultLabel;


static void getSelectedStops(lv_event_t*)
{
    int from = lv_dropdown_get_selected(fromStop);
    int to = lv_dropdown_get_selected(toStop);

    if (from == to) {
        return;
    }

    String fromId = station_array[from]["StopLocation"]["extId"].as<String>();
    String toId = station_array[to]["StopLocation"]["extId"].as<String>();

    JsonDocument journeys = getJourneys(fromId, toId);

    String result = "";
    int count = 0;

    for (JsonObject trip : journeys["Trip"].as<JsonArray>()) {

        if (count == 5) break;

        count++;
        result += "Journey " + String(count) + "\n";

        int ride = 0;

        for (JsonObject leg : trip["LegList"]["Leg"].as<JsonArray>()) {

            if (leg["type"].as<String>() != "JNY") continue;

            String start = leg["Origin"]["name"].as<String>();
            String time = leg["Origin"]["time"].as<String>();

            if (ride == 0) {
                result += "Start: ";
            } else {
                result += "Change: ";
            }

            result += time + " " + start + "\n";
            ride++;
        }

        if (ride == 1) {
            result += "No changes\n";
        }

        result += "\n";
    }

    if (count == 0) {
        result = "No journeys found";
    }

    lv_label_set_text(resultLabel, result.c_str());
}


void create_journey_selection_screen(lv_obj_t* journeyTile)
{
    lv_obj_t* title = lv_label_create(journeyTile);
    lv_label_set_text(title, "Journey Selection");
    lv_obj_align(title, LV_ALIGN_TOP_MID, 0, 20);

    String stations = readStations();

    lv_obj_t* fromLabel = lv_label_create(journeyTile);
    lv_label_set_text(fromLabel, "From");
    lv_obj_align(fromLabel, LV_ALIGN_TOP_LEFT, 40, 50);

    fromStop = lv_dropdown_create(journeyTile);
    lv_dropdown_set_options(fromStop, stations.c_str());
    lv_obj_set_width(fromStop, 300);
    lv_obj_align(fromStop, LV_ALIGN_TOP_LEFT, 50, 70);

    lv_obj_t* toLabel = lv_label_create(journeyTile);
    lv_label_set_text(toLabel, "To");
    lv_obj_align(toLabel, LV_ALIGN_TOP_LEFT, 40, 120);

    toStop = lv_dropdown_create(journeyTile);
    lv_dropdown_set_options(toStop, stations.c_str());
    lv_obj_set_width(toStop, 300);
    lv_obj_align(toStop, LV_ALIGN_TOP_LEFT, 50, 140);


    lv_obj_t* resultBox = lv_obj_create(journeyTile);
    lv_obj_set_size(resultBox, 300, 130);
    lv_obj_align(resultBox, LV_ALIGN_TOP_LEFT, 40, 140);
    lv_obj_set_scroll_dir(resultBox, LV_DIR_VER);

    resultLabel = lv_label_create(resultBox);
    lv_obj_set_width(resultLabel, lv_pct(100));
    lv_label_set_long_mode(resultLabel, LV_LABEL_LONG_WRAP);
    lv_label_set_text(resultLabel, "No journeys yet");


    lv_obj_add_event_cb(fromStop, getSelectedStops, LV_EVENT_VALUE_CHANGED, NULL);
    lv_obj_add_event_cb(toStop, getSelectedStops, LV_EVENT_VALUE_CHANGED, NULL);
}

