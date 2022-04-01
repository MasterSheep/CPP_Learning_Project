#include "aircraft.hpp"

#include <set>
#include <string>

class AircraftFactory
{
private:
    std::set<std::string> names;
    AircraftType* aircraft_types[NUM_AIRCRAFT_TYPES] {};
    const std::string airlines[8] = { "AF", "LH", "EY", "DL", "KL", "BA", "AY", "EY" };

public:
    AircraftFactory() {};
    std::unique_ptr<Aircraft> create_aircraft(Airport* airport);
    void init_aircraft_types();
    std::string airline_type(int id);
};
