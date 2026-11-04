#ifndef UNTITLED_FERRY_H
#define UNTITLED_FERRY_H
#include "Transport.h"

class Ferry : public Transport {
    public:
    Ferry(string des, string line , Start_Stations s, Time t):Transport(des,line,s,t) ;
public:

{   void Display() const {
    cout<<" Ferry: "<< line << endl;
    cout<<"Destination : " <<destination<<endl;
    cout <<"Start_Station : "<<station.getNamn()<<endl;
    cout<<"Departure"<<departureTime.getHours()
    <<":"<<departureTime.getMinute()<<endl;

};

}
#endif //UNTITLED_FERRY_H
