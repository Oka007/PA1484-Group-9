
#ifndef UNTITLED_TRANSPORT_H
#define UNTITLED_TRANSPORT_H

#include <string>
#include "Time.h"
#include "Stations.h"

using namespace std;

class Transport {
protected:
    string line;
    string destination;
    Start_Stations station;
    Time departureTime;
    string status;

public:
    Transport(string des, string L, Start_Stations s,
              Time t, string status)
        : line(L), destination(des), station(s),
          departureTime(t), status(status) {}

    string getDestination() const {
        return destination;
    }

    string getLine() const {
        return line;
    }

    Start_Stations getStations() const {
        return station;
    }

    Time getDepartureTime() const {
        return departureTime;
    }

    string getStatus() const {
        return status;
    }

    virtual void Display() const = 0;

    virtual ~Transport() = default;
};

#endif
