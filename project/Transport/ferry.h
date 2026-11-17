#ifndef UNTITLED_FERRY_H
#define UNTITLED_FERRY_H
#include "transport.h"
#include <Arduino.h>

class Ferry : public Transport {
public:
    Ferry(string des, string line, Start_Stations s, Time t, string status, int delay)
        : Transport(des, line, s, t, status, delay)
    {
    }
    
    void Display() const {
    
        Serial.printf("Ferry: %s\n", line.c_str());
        Serial.printf("Destination: %s\n", destination.c_str());
        Serial.printf("Start_Stations: %s\n", station.getNamn().c_str());
        Serial.printf("Departure: %02d:%02d\n",
                        departureTime.getHours(),
                        departureTime.getMinutes());

    }
    string getType() const override {
        return "FERRY";
    }

};
#endif // UNTITLED_FERRY_H