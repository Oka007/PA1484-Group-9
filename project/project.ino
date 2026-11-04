#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <TFT_eSPI.h>
#include <time.h>
#include <LilyGo_AMOLED.h>
#include <LV_Helper.h>
#include <lvgl.h>
#include <cstdio>

#include "secrets.h"
#include "saveSettings.h"


LilyGo_Class amoled;
Preferences preferences;

#include "ui.h"
#include "departureScreen.h"
#include "settingsScreen.h"
#include "connectionStatus.h"
#include "Transport/transport.h"
#include "Transport/buss.h"

// Function: Connects to WIFI
static void connect_wifi()
{
  Serial.printf("Connecting to WiFi SSID: %s\n", WIFI_SSID);
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  const uint32_t start = millis();
  while (WiFi.status() != WL_CONNECTED && (millis() - start) < 7000) {
    delay(250);
  }
  Serial.println();

  if (WiFi.status() == WL_CONNECTED) {
    Serial.print("WiFi connected.");
  } else {
    Serial.println("WiFi could not connect (timeout).");
  }
}

// Must have function: Setup is run once on startup
void setup()
{
  Serial.begin(115200);
  preferences.begin("settings", false);
  delay(200);

  if (!amoled.begin()) {
    Serial.println("Failed to init LilyGO AMOLED.");
    while (true) delay(1000);
  }

  beginLvglHelper(amoled);   // init LVGL for this board

  create_ui();
  connect_wifi();

  std::vector<std::shared_ptr<Transport>> departures;

  Start_Stations station("Karlskrona C", "1");

  departures.push_back(std::make_shared<Bus>("Saltö", "1", station, Time(40, 20), "On Time"));
  departures.push_back(std::make_shared<Bus>("Campus Gräsvik", "1", station, Time(30, 23), "Late 3min"));
  departures.push_back(std::make_shared<Bus>("Bergåsa", "123", station, Time(55, 20), "On Time"));
  departures.push_back(std::make_shared<Bus>("Kungsmarken", "4", station, Time(59, 20), "On Time"));

  update_departure_screen(departures);

  
}

// Must have function: Loop runs continously on device after setup
void loop()
{
  lv_timer_handler();
  delay(5);

  int wifiStrength = get_wifi_strength();
  update_wifi_display(wifiStrength);
}