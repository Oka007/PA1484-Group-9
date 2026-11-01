#include "departureScreen.h"


// Create the departure screen UI
void create_departure_screen(lv_obj_t* departureTile)
{   
    lv_coord_t screenWidth = lv_obj_get_width(departureTile);
    
    // Creat title
    lv_obj_t* title = lv_label_create(departureTile);
    lv_label_set_text(title, "Departures");
    lv_obj_align(title, LV_ALIGN_TOP_MID, 0, 20);
    
    // Create departure table
    lv_obj_t* departureTable = lv_table_create(departureTile);
    
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

    
    // Example departure 1
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
    lv_table_set_cell_value(departureTable, 4, 3, "On time");

    // Table alignment
    lv_obj_align(departureTable, LV_ALIGN_TOP_MID, 0, 70);
}