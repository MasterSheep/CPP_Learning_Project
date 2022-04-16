#include "aircraft_manager.hpp"

#include <numeric>

void AircraftManager::addAirCraft(std::unique_ptr<Aircraft> aircraft)
{
    assert(aircraft);
    aircrafts.emplace_back(std::move(aircraft));
}

bool AircraftManager::move()
{
    sortAircrafts();

    const auto& pred = [this](const auto& item)
    {
        try
        {
            return item->move();
        } catch (const AircraftCrash& err)
        {
            std::cerr << err.what() << std::endl;
            crashs++;
            return true;
        }
    };
    aircrafts.erase(std::remove_if(aircrafts.begin(), aircrafts.end(), pred), aircrafts.end());
    return true;
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
                  [](std::unique_ptr<Aircraft>& aircraft) {
                      std::cout << aircraft->has_terminal() << " fuel level : " << aircraft->getFuel()
                                << std::endl;
                  });
}

int AircraftManager::get_required_fuel() const
{
    return accumulate(aircrafts.begin(), aircrafts.end(), 0,
                      [](unsigned int sum, const std::unique_ptr<Aircraft>& targ)
                      {
                          if (targ->is_low_on_fuel() && !targ->is_service_done)
                          {
                              return sum + (MAX_FUEL - targ->fuel);
                          }
                          return sum;
                      });
}

void AircraftManager::coutCrashed() const
{
    std::cout << crashs << " aircrafts crashed" << std::endl;
}