#include "ui.h"
#include "departureScreen.h"
#include "settingsScreen.h"

static lv_obj_t* tileview;
static lv_obj_t* t1;
static lv_obj_t* t2;
static lv_obj_t* t3;
static lv_obj_t* t1_label;
static lv_obj_t* t1_project_name;
static lv_obj_t* t2_label;
static bool t2_dark = false;  // start tile #2 in light mode

// Function: Tile #2 Color change
static void apply_tile_colors(lv_obj_t* tile, lv_obj_t* label, bool dark)
{
  // Background
  lv_obj_set_style_bg_opa(tile, LV_OPA_COVER, 0);
  lv_obj_set_style_bg_color(tile, dark ? lv_color_black() : lv_color_white(), 0);

  // Text
  lv_obj_set_style_text_color(label, dark ? lv_color_white() : lv_color_black(), 0);
}

static void on_tile2_clicked(lv_event_t* e)
{
  LV_UNUSED(e);
  t2_dark = !t2_dark;
  apply_tile_colors(t2, t2_label, t2_dark);
}


// Function: Creates UI
void create_ui()
{
  // Fullscreen Tileview
  tileview = lv_tileview_create(lv_scr_act());
  lv_obj_set_size(tileview, lv_disp_get_hor_res(NULL), lv_disp_get_ver_res(NULL));
  lv_obj_set_scrollbar_mode(tileview, LV_SCROLLBAR_MODE_OFF);

  // Settings above Departures
  t3 = lv_tileview_add_tile(tileview, 1, 0, LV_DIR_BOTTOM);

  // Main screens
  t1 = lv_tileview_add_tile(tileview, 0, 1, LV_DIR_RIGHT);
  t2 = lv_tileview_add_tile(tileview, 1, 1, LV_DIR_LEFT | LV_DIR_TOP);

  // Start on the Starting Screen
  lv_obj_set_tile(tileview, t1, LV_ANIM_OFF);
  
  // Tile #1
  {
    t1_project_name = lv_label_create(t1);
    t1_label = lv_label_create(t1);
    lv_obj_set_y(t1_label, 150);
    lv_obj_set_y(t1_project_name, 70);
    lv_label_set_text(t1_project_name, "Public transport information and \ninteraction on ESP32");
    lv_label_set_text(t1_label, "v.0.0\n Group 09\n Saga Lindqvist, Olle Andersson,\n Josefine Johnsson, Mahmmod Sulaiman, \nOlof Carlander");
    lv_obj_set_style_text_font(t1_label, &lv_font_montserrat_18, 0);
    lv_obj_set_style_text_font(t1_project_name, &lv_font_montserrat_28, 0);
    lv_obj_set_style_text_decor(t1_project_name, LV_TEXT_DECOR_UNDERLINE, 0);
    lv_obj_set_style_align(t1_label, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_set_style_align(t1_project_name, LV_TEXT_ALIGN_CENTER, 0);
    apply_tile_colors(t1, t1_label, /*dark=*/false);
  }

  // Tile #2
  {
    create_departure_screen(t2);
  }

  // Tile #3
  {
    create_settings_screen(t3);
  }
}

