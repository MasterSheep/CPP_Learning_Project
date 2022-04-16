#pragma once

#include "GL/dynamic_object.hpp"
#include "aircraft.hpp"

#include <algorithm>

class Aircraft;

class AircraftManager : public GL::DynamicObject
{
private:
    std::vector<std::unique_ptr<Aircraft>> aircrafts;
    long crashs = 0;

public:
    void addAirCraft(std::unique_ptr<Aircraft> aircraft);
    bool move() override;
    int countAirelineType(std::string type);

    void sortAircrafts();
    void printAircrafts();
    int get_required_fuel() const;
    void coutCrashed() const;
};