#include "aircraft_manager.hpp"

void AircraftManager::addAirCraft(Aircraft* aircraft)
{
    aircrafts.emplace(aircraft);
}

bool AircraftManager::move()
{
    for (auto iter = aircrafts.begin(); iter != aircrafts.end();)
    {
        if ((*iter)->move())
        {
            delete (*iter);
            iter = aircrafts.erase(iter);
        }
        else
        {
            ++iter;
        }
    }
    return false;
}