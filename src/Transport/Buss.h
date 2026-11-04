#ifndef UNTITLED_BUSS_H
#define UNTITLED_BUSS_H
#include <iostream>

#include "Transport.h"
#include <istream>
class Bus : public Transport{
public:
    Bus(string des, string line , Start_Stations s, Time t):Transport(des,line,s,t)
    {
    }
    void Display() const {
        cout<<"Bus : "<< line << endl;
        cout<<"Destination  : " <<destination<<endl;
        cout <<"Start_Station : "<<station.getNamn()<<endl;
        cout<<"Departure"<<departureTime.getHours()
        <<":"<<departureTime.getMinute()<<endl;
    }
};

#endif //UNTITLED_BUSS_H
