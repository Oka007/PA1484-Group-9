#ifndef UNTITLED_STATIONS_H
#define UNTITLED_STATIONS_H
#include <string>
using namespace std;
class Start_Stations {
private:
    string namn ;
    string id ;
public:
    Start_Stations(string nam, string i)
    :namn(nam), id(i)  {}
     string getNamn()  const {
        return namn;
    }
    string getId()  const {
        return id ;
    }

};
#endif //UNTITLED_STATIONS_H
