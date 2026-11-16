#include "journeySelectionScreen.h"

void create_journey_selections_screen(lv_obj_t* journeyTile)
{
    lv_obj_t* title = lv_label_create(journeyTile);

    lv_obj_align(title, LV_ALIGN_TOP_MID,1,60);

    lv_obj_t* info = lv_label_create(journeyTile);

    lv_label_set_text (info, "Choose a Starting stop, and a destination stop");
    
    lv_obj_set_width(info , lv_pct(90));
    lv_obj_set_style_text_align(info,LV_TEXT_ALIGN_CENTER,0);
    lv_obj_align(info, LV_ALIGN_CENTER,0,0);
}
