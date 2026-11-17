#include "departureScreen.h"
#include "saveSettings.h"
#include "settingsScreen.h"
#include "api.h"

LV_FONT_DECLARE(Swedish);

// Pointer to the departure table
lv_obj_t* departureTable = nullptr;
lv_obj_t* departure_title = nullptr;

static void refresh_departures(lv_event_t* event)
// Refreshbuttons actions while being pressed.
{
    refresh_departures();
}
void refresh_departures()
{
    JsonDocument api_json;
    api_json = getApiData(selected_stop_id);
    departures = readDepartures(api_json);
    update_departure_screen(departures, selected_transport);
}

// Create the departure screen UI
void create_departure_screen(lv_obj_t* departureTile)
{   
    
    lv_coord_t screenWidth = lv_obj_get_width(departureTile);
    
    // Creat title
    departure_title = lv_label_create(departureTile);
    lv_label_set_text(departure_title, "Departures");
    lv_obj_set_style_text_font(departure_title, &Swedish, LV_PART_MAIN);

    lv_obj_align(departure_title, LV_ALIGN_TOP_MID, 0, 20);
    
    // Create departure table
    departureTable = lv_table_create(departureTile);
    lv_obj_set_style_text_font(departureTable, &Swedish, LV_PART_MAIN);

    // Set table rows and columns
    lv_table_set_row_cnt(departureTable, 5);
    lv_table_set_col_cnt(departureTable, 4);
    
    // Column headers
    lv_table_set_cell_value(departureTable, 0, 0, "Destination");
    lv_table_set_cell_value(departureTable, 0, 1, "Line");
    lv_table_set_cell_value(departureTable, 0, 2, "Time");
    lv_table_set_cell_value(departureTable, 0, 3, "Status");

    // Width of differnt columns
    lv_coord_t tableWidth = screenWidth - 20;

    lv_table_set_col_width(departureTable, 0, tableWidth * 35 / 100);
    lv_table_set_col_width(departureTable, 1, tableWidth * 12 / 100);
    lv_table_set_col_width(departureTable, 2, tableWidth * 18 / 100);
    lv_table_set_col_width(departureTable, 3, tableWidth * 35 / 100);

    
    /*/ // Example departure 1
    lv_table_set_cell_value(departureTable, 1, 0, "Karlskrona C");
    lv_table_set_cell_value(departureTable, 1, 1, "1");
    lv_table_set_cell_value(departureTable, 1, 2, "10:26");
    lv_table_set_cell_value(departureTable, 1, 3, "On time");

    // Example departure 2
    lv_table_set_cell_value(departureTable, 2, 0, "Lyckeby");
    lv_table_set_cell_value(departureTable, 2, 1, "4");
    lv_table_set_cell_value(departureTable, 2, 2, "10:32");
    lv_table_set_cell_value(departureTable, 2, 3, "+5 min");

    // Example departure 3
    lv_table_set_cell_value(departureTable, 3, 0, "Salto");
    lv_table_set_cell_value(departureTable, 3, 1, "2");
    lv_table_set_cell_value(departureTable, 3, 2, "10:40");
    lv_table_set_cell_value(departureTable, 3, 3, "On time");

    // Example departure 4
    lv_table_set_cell_value(departureTable, 4, 0, "Nattraby");
    lv_table_set_cell_value(departureTable, 4, 1, "6");
    lv_table_set_cell_value(departureTable, 4, 2, "10:48");
    lv_table_set_cell_value(departureTable, 4, 3, "On time");/*/
    
    // Table alignment
    lv_obj_align(departureTable, LV_ALIGN_TOP_MID, 0, 70);

    // Creates button
    lv_obj_t* refreshButton = lv_btn_create(departureTile);

    //  Aligns button
    lv_obj_set_size(refreshButton, 110, 40);
    lv_obj_align(refreshButton, LV_ALIGN_BOTTOM_RIGHT, -10, -10);

    // Adds a click event to button
    lv_obj_add_event_cb(refreshButton, refresh_departures, LV_EVENT_CLICKED, NULL);
    
    // Adds a button label
    lv_obj_t* refreshLabel = lv_label_create(refreshButton);
    lv_label_set_text(refreshLabel, "Refresh");
    lv_obj_center(refreshLabel);
}


// Updates departurescreens UI
void update_departure_screen(const std::vector<std::shared_ptr<Transport>>& transports, string type) 
{
    // Check that table exists
    if (departureTable == nullptr)
    {
        return;
    } 

    const int tableSize = 4;
     int shownDepartures = 0;

    for (const auto& transport : transports) {
        if (!transport) {
            continue;
        }

        if (type != "ALL" && transport->getType() != type) {
            continue;
        }

        if (shownDepartures >= tableSize) {
            break;
        }

        const int row = shownDepartures + 1;

        lv_table_set_cell_value(departureTable, row, 0, transport->getDestination().c_str());

        // Gets Line
        lv_table_set_cell_value(departureTable, row, 1, transport->getLine().c_str());
        
        // Gets Time
        lv_table_set_cell_value(departureTable, row, 2, transport->getDepartureTime().c_str());
    
        
        //Gets Status and adds time if delayed
        if (transport->getStatus() == "Delayed") {
            lv_table_set_cell_value_fmt(departureTable, row, 3, "Delayed %d min", + transport->getDelay());
        } else {
            lv_table_set_cell_value(departureTable, row, 3, transport->getStatus().c_str());
        }

        
        shownDepartures++;
    } 

    

    // Clears lines with no new transport info
    for (int i = shownDepartures; i < tableSize; i++)
    {
        for (int column = 0; column < 4; column++ )
        {
            lv_table_set_cell_value(departureTable, i + 1, column, "");
        }
    }
    
}

void update_departure_title(int selectedStationIndex) {
    // Gets name from the json
    JsonObject stop = station_array[selectedStationIndex]["StopLocation"];
    String name = stop["name"].as<String>();
    lv_label_set_text(departure_title, name.c_str());
}