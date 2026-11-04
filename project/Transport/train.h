#ifndef UNTITLED_TRAIN_H
#define UNTITLED_TRAIN_H
#include "transport.h"
#include <Arduino.h>

class Train : public Transport {
    public:
        Train(string des, string line , Start_Stations s, Time t, string status) : Transport(des, line, s, t, status) {}

       void Display() const {
            Serial.printf("Train: %s\n", line.c_str());
            Serial.printf("Destination: %s\n", destination.c_str());
            Serial.printf("Start_Station_ %s\n", station.getNamn().c_str());
            Serial.printf("Departure:  %02d:%02d\n", departureTime.getHours(), departureTime.getMinutes());
       }
    
    /*void Display() const {
            cout<<"Train : "<< line << endl;
            cout<<"Destination : " <<destination<<endl;
            cout <<"Station : "<<station.getNamn()<<endl;
            cout<<"Departure"<<departureTime.getHours()
            <<":"<<departureTime.getMinute()<<endl;*/



};

#endif //UNTITLED_TRAIN_H
