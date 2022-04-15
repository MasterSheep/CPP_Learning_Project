#include "GL/dynamic_object.hpp"
#include "aircraft.hpp"

#include <algorithm>

class Aircraft;

class AircraftManager : public GL::DynamicObject
{
private:
    std::vector<std::unique_ptr<Aircraft>> aircrafts;

    void sortAircrafts();
    void printAircrafts();

public:
    AircraftManager() {}
    void addAirCraft(std::unique_ptr<Aircraft> aircraft);
    bool move();
    int countAirelineType(std::string type);
};