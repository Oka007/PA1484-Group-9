
#ifndef UNTITLED_TRANSPORT_H
#define UNTITLED_TRANSPORT_H

#include <string>
#include "time.h"
#include "stations.h"

using namespace std;

class Transport {
protected:
    string line;
    string destination;
    Start_Stations station;
    Time departureTime;
    string status;
    int delay;

public:
    Transport(string des, string L, Start_Stations s,
              Time t, string status, int delay)
        : line(L), destination(des), station(s),
          departureTime(t), status(status), delay(delay) {}

    string getDestination() const {
        return destination;
    }

    string getLine() const {
        return line;
    }

    Start_Stations getStations() const {
        return station;
    }

    string getDepartureTime() const {
        string dTime = to_string(departureTime.getHours()) + ":" + to_string(departureTime.getMinutes());
        return dTime;
    }

    string getStatus() const {
        return status;
    }

    int getDelay() const {
        int delayMin = (delay/60) + 0.5;
        return delayMin;
    }

    virtual void Display() const = 0;

    virtual string getType() const = 0;

    virtual ~Transport() = default;
};

#endif
