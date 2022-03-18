#include "GL/dynamic_object.hpp"
#include "aircraft.hpp"

class Aircraft;

class AircraftManager : public GL::DynamicObject
{
private:
    std::vector<std::unique_ptr<Aircraft>> aircrafts;
    // const std::vector<Aircraft&> aircrafts;

public:
    AircraftManager() {}
    void addAirCraft(std::unique_ptr<Aircraft> aircraft);
    bool move();
};