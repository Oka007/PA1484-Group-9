#include "settingsScreen.h"
#include <TFT_eSPI.h>      // Grafikkbibliotek för TFT
#include <XPT2046_Touchscreen.h> // Touchbibliotek   vet inte vilken det sak vara ska stå på boxen av aparaten 


// Gjorde vad internät säger att man ska göra 
TFT_eSPI tft = TFT_eSPI(); // Skapar ett TFT-objekt
XPT2046_Touchscreen ts(TOUCH_CS); // Skapar ett touch-objekt med CS-pin

// Dropdown-data. And the stops (not don)
const char* options[] = {"AWA vägen", "Af Chapmangymnasiet", "Afvelsgärdevägen","Alamedan","Allatorp","Allatorp norra", "Allatorps gård", "Allasjösmåla", "Allévägen","Almvägen", "Almöbron", "Alnaryd", "Amiralen", "Amiralitetstorget", "Angöringen"};
int selectedIndex = 0;
bool dropdownOpen = false;

void setup() {
  tft.init();           
  tft.setRotation(1);   
  ts.begin();           

  drawDropdown();       // Making the dropdown-desplay 
}

void loop() {
  if (ts.touched()) {
    TS_Point p = ts.getPoint();
    int x = p.x;
    int y = p.y;

    // if dopdown isent showing 
    if (!dropdownOpen && y > 20 && y < 50 && x > 20 && x < 200) {
      dropdownOpen = true;
      drawDropdown();
    }
    // if dropsown is showowing and an opten is prest 
    else if (dropdownOpen) {
      for (int i = 0; i < 3; i++) {
        if (y > (50 + i * 30) && y < (80 + i * 30) && x > 20 && x < 200) {
          selectedIndex = i;
          dropdownOpen = false;
          drawDropdown();
          Serial.printf("Selected: %s\n", options[selectedIndex]);
        }
      }
    }
  }
}

void drawDropdown() {
  tft.fillScreen(TFT_WHITE);
  tft.setTextColor(TFT_BLACK, TFT_WHITE);
  tft.setTextDatum(TL_DATUM);

  // Rita huvudfältet
  tft.fillRect(20, 20, 180, 30, TFT_WHITE);
  tft.drawString(options[selectedIndex], 25, 25);

  // if dopdown is open show the altenertivs 
  if (dropdownOpen) {
    for (int i = 0; i < 3; i++) {
      tft.fillRect(20, 50 + i * 30, 180, 30, TFT_WHITE);
      tft.drawString(options[i], 25, 55 + i * 30);
    }
  }
}

// for nowe it's set to all
int transportTyp = 0;
    





// Create the settings screen UI
void create_settings_screen(lv_obj_t* settingsTile)
{
    lv_obj_t* title = lv_label_create(settingsTile);
    lv_label_set_text(title, "Settings");

    


    
    lv_obj_align(title, LV_ALIGN_TOP_MID, 0, 20);

    
}