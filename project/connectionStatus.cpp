#include "connectionStatus.h"
#include "settingsScreen.h" 

// Returns WiFi strength in 0-100 range
int get_wifi_strength() {
    if (WiFi.status() != WL_CONNECTED) {
        return 0;
    }

    int rssi = WiFi.RSSI();
    // This will give an rssi of -100dbm 0% and -50dbm 100%
    int strength = constrain(2 * (rssi + 100), 0, 100);

    return strength;
}

void update_wifi_display(int strength) {
    lv_label_set_text_fmt(wifiStatus, "WiFi Connection: %d%%", strength);
}