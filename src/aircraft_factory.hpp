#include "aircraft.hpp"

#include <string>

class AircraftFactory
{
private:
    AircraftType* aircraft_types[NUM_AIRCRAFT_TYPES] {};
    const std::string airlines[8] = { "AF", "LH", "EY", "DL", "KL", "BA", "AY", "EY" };

public:
    AircraftFactory() {};
    std::unique_ptr<Aircraft> create_aircraft(Airport* airport) const;
    void init_aircraft_types();
};
