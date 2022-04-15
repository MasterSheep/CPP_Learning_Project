#include "aircraft_manager.hpp"

#include <numeric>

void AircraftManager::addAirCraft(std::unique_ptr<Aircraft> aircraft)
{
    aircrafts.emplace_back(std::move(aircraft));
}

bool AircraftManager::move()
{
    sortAircrafts();

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

void AircraftManager::sortAircrafts()
{
    std::sort(aircrafts.begin(), aircrafts.end(),
              [](std::unique_ptr<Aircraft>& a, std::unique_ptr<Aircraft>& b)
              {
                  if (a->has_terminal() == b->has_terminal())
                      return a->getFuel() <= b->getFuel();
                  return a->has_terminal();
              });
}

void AircraftManager::printAircrafts()
{
    std::for_each(aircrafts.begin(), aircrafts.end(),
                  [](std::unique_ptr<Aircraft>& aircft)
                  { std::cout << "fuel level :" << aircft->getFuel() << std::endl; });
}

int AircraftManager::get_required_fuel()
{
    return accumulate(aircrafts.begin(), aircrafts.end(), 0.0,
                      [](float sum, const std::unique_ptr<Aircraft>& aircraft)
                      {
                          if (aircraft->is_low_on_fuel() && aircraft->is_at_terminal)
                          {
                              return sum + (MAX_FUEL - aircraft->fuel);
                          }
                          return sum;
                      });
}