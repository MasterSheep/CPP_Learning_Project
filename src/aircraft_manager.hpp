#include "GL/dynamic_object.hpp"
#include "aircraft.hpp"

class Aircraft;

class AircraftManager : public GL::DynamicObject
{
private:
    std::unordered_set<DynamicObject*> aircrafts;
    // const std::vector<Aircraft&> aircrafts;

public:
    AircraftManager() {}
    void addAirCraft(Aircraft* aircraft);
    bool move();
};