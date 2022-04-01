#include "aircraft_manager.hpp"

void AircraftManager::addAirCraft(std::unique_ptr<Aircraft> aircraft)
{
    aircrafts.emplace_back(std::move(aircraft));
}

bool AircraftManager::move()
{
    aircrafts.erase(
        std::remove_if(aircrafts.begin(), aircrafts.end(), [](auto const& i) { return i.get()->move(); }),
        aircrafts.end());
    /*
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
    */
    return false;
}