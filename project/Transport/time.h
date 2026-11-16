#ifndef UNTITLED_TIME_H
#define UNTITLED_TIME_H
#include <chrono>

class Time {
private:
    int hours;
    int minutes;
    
public:
    Time (int min, int h) 
        : hours(h),minutes (min) {}

   int getHours() const {
        return hours;
    }
    int getMinutes() const {
        return minutes;
    }
    bool operator==(const Time& t) const {
        return hours == t.hours &&
            minutes == t.minutes;
    }
};

#endif //UNTITLED_TIME_H
