#pragma once

#include "aircraft_factory.hpp"
#include "aircraft_manager.hpp"

class Airport;
class AircraftFactory;
struct AircraftType;

class TowerSimulation
{
private:
    bool help        = false;
    Airport* airport = nullptr;
    AircraftManager aircraft_manager;
    AircraftFactory aircraft_factory;

    TowerSimulation(const TowerSimulation&) = delete;
    TowerSimulation& operator=(const TowerSimulation&) = delete;

    void create_random_aircraft();

    void create_keystrokes();
    void display_help() const;

    void init_airport();
    void init_aircraft();

public:
    TowerSimulation(int argc, char** argv);
    ~TowerSimulation();

    void launch();
};
