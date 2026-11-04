#ifndef UNTITLED_TRAIN_H
#define UNTITLED_TRAIN_H
#include "Transport.h"
class Train : public Transport {
    public:
    Train(string des, string line , Start_Stations s, Time t):Transport(des,line,s,t){
    {

     {   void Display() const {
            cout<<"Train : "<< line << endl;
            cout<<"Destination : " <<destination<<endl;
            cout <<"Station : "<<station.getNamn()<<endl;
            cout<<"Departure"<<departureTime.getHours()
            <<":"<<departureTime.getMinute()<<endl;

    };

};

#endif //UNTITLED_TRAIN_H
