#ifndef UNTITLED_BUSS_H
#define UNTITLED_BUSS_H
#include <Arduino.h>

#include "transport.h"
#include <istream>
class Bus : public Transport{
public:
    Bus(string des, string line , Start_Stations s, Time t, string status) : Transport(des, line, s, t, status) {}
    void Display() const {
        Serial.printf("Bus: %s\n", line.c_str());
        Serial.printf("Destination: %s\n", destination.c_str());
        Serial.printf("Start_Station_ %s\n", station.getNamn().c_str());
        Serial.printf("Departure: %02d:%02d\n", departureTime.getHours(), departureTime.getMinutes());
    }
};

#endif //UNTITLED_BUSS_H
