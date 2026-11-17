#include <ArduinoJson.h>
#include <HTTPClient.h>
#include <lvgl.h>
#include "secrets.h"
#include "api.h"

#include "Transport/buss.h"
#include "Transport/train.h"
#include "Transport/ferry.h"

#include <string>
 
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

/*
void loop_api(){
    delay(60000);

    getApiData(loc_id);
}
*/

Time parseTime(const char* timestamp){
//Converts API timestamp into Time object    
    int hours = 0;
    int minutes = 0;

    if (timestamp == nullptr ||
        sscanf(timestamp, "%*10cT%d:%d", &hours, &minutes) != 2)
        {
            return Time(0,0);
        }

    return Time(minutes, hours);
    
}

TransportList readDepartures(const JsonDocument& json) {
    TransportList transports;
    
    JsonArrayConst departures = json["departures"].as<JsonArrayConst>();

    // Go through every departure
    for (JsonObjectConst departure : departures) {
        // Get route info
        JsonObjectConst route = departure["route"].as<JsonObjectConst>();

        std::string mode = route["transport_mode"] | "";
        std::string direction = route["direction"] | "";
        std::string line = route["designation"] | "";

        // Creates the start station for this particular departure
        Start_Stations station(
            departure["stop"]["name"] | "",
            departure["stop"]["id"] | ""
        );

        const char* timestamp = departure["scheduled"].as<const char*>();

        // Convert to Time class
        Time departureTime = parseTime(timestamp);

        bool canceled = departure["canceled"] | false;
        int delay = departure["delay"] | 0;     // Measured in seconds

        std::string status;

        if (canceled) {
            status = "Canceled";
        } else if (delay > 30) {
            status = "Delayed";
        } else {
            status = "On Time";
        }
        
        // Create the correct type of transport
        if (mode == "BUS") {
            transports.emplace_back(
                new Bus(direction, line, station, departureTime, status, delay)
            );
        } else if (mode == "TRAIN") {
            transports.emplace_back(
                new Train(direction, line, station, departureTime, status, delay)
            );
        } else if (mode == "FERRY") {
            transports.emplace_back(
                new Ferry(direction, line, station, departureTime, status, delay)
            );
        } 
    }
    
    return transports;
} 
/*

JsonDocument getJourneys(String fromId, String toId)
{
    JsonDocument fail;

    if (WiFi.status() != WL_CONNECTED) {
        return fail;
    }

    String Key = String();
    Key = String(api_Key); 

    HTTPClient http;

    String url = String("https://api.resrobot.se/v2.1/trip?format=json&originId=")
                 + fromId + "&destId=" + toId
                 + "&numF=5&accessId=" + Key;

    http.begin(url);

    int httpResponseCode = http.GET();

    if (httpResponseCode == 200) {
        String payload = http.getString();

        JsonDocument doc;

        DeserializationError error = deserializeJson(doc, payload);

        if (error) {
            http.end();
            return fail;
        }

        http.end();
        return doc;
    }

    http.end();
    return fail;
}


*/