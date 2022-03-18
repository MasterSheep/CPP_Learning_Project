#include "aircraft_manager.hpp"

void AircraftManager::addAirCraft(std::unique_ptr<Aircraft> aircraft)
{
    aircrafts.emplace_back(std::move(aircraft));
}

bool AircraftManager::move()
{
    for (auto iter = aircrafts.begin(); iter != aircrafts.end();)
    {
        if ((*iter)->move())
        {
            iter = aircrafts.erase(iter);
        }
        else
        {
            ++iter;
        }
    }
    return false;
}