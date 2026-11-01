#include "settingsScreen.h"


// Create the settings screen UI
void create_settings_screen(lv_obj_t* settingsTile)
{
    lv_obj_t* title = lv_label_create(settingsTile);
    lv_label_set_text(title, "Settings");
    
    lv_obj_align(title, LV_ALIGN_TOP_MID, 0, 20);
}