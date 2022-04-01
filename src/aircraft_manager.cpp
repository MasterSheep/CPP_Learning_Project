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
    return false;
}

int AircraftManager::countAirelineType(std::string type)
{
    return std::count_if(aircrafts.begin(), aircrafts.end(),
                         [type](auto const& i)
                         { return !i.get()->get_flight_num().compare(0, type.size(), type); });
}