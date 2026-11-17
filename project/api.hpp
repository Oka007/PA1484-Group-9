#include <ArduinoJson.h>
#include <HTTPClient.h>
#include "secrets.h"
 
//A function that takes a stations id and returns a jsondocument with departures and other info. 
JsonDocument getApiData(String loc_id){
    JsonDocument fail;
    
    if (WiFi.status() != WL_CONNECTED) {
        return fail;
    }

    String Key;
    Key = String(api_Key); 

    HTTPClient http; 
    String url = "https://realtime-api.trafiklab.se/v1/departures/" + loc_id + "?key=" + Key;

    http.begin(url);

    int httpResponseCode = http.GET();

    if(httpResponseCode == 200) {
    String payload = http.getString();

    JsonDocument doc; 

    DeserializationError error = deserializeJson(doc, payload);

        if(error){
            http.end();
            return fail; 
        }
    http.end();

    return doc; 
    }
    http.end();

    return fail;
}