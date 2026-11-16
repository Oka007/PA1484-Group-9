#include "journeySelectionScreen.h"

void create_journey_selection_screen(lv_obj_t* journeyTile)
{
    lv_obj_t* title = lv_label_create(journeyTile);
    lv_label_set_text(title, "Journey Selection");
    lv_obj_center(title);
}