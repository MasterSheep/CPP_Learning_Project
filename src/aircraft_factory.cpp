#include "aircraft_factory.hpp"

#include "airport.hpp"

std::unique_ptr<Aircraft> AircraftFactory::create_aircraft(Airport* airport)
{
    const AircraftType* type = aircraft_types[rand() % 3];
    std::string flight_number;
    do
    {
        flight_number = airlines[std::rand() % 8] + std::to_string(1000 + (rand() % 9000));
    }
    while (names.insert(flight_number).second);
    const float angle       = (rand() % 1000) * 2 * 3.141592f / 1000.f; // random angle between 0 and 2pi
    const Point3D start     = Point3D { std::sin(angle), std::cos(angle), 0 } * 3 + Point3D { 0, 0, 2 };
    const Point3D direction = (-start).normalize();
    return std::move(
        std::make_unique<Aircraft>(*type, flight_number, start, direction, airport->get_tower()));
}

// note: textures have to be initialized after initializing glut, so we'll need
// our own init here
void AircraftFactory::init_aircraft_types()
{
    assert(airlines);
    aircraft_types[0] = new AircraftType { .02f, .05f, .02f, MediaPath { "l1011_48px.png" } };
    aircraft_types[1] = new AircraftType { .02f, .05f, .02f, MediaPath { "b707_jat.png" } };
    aircraft_types[2] = new AircraftType { .02f, .10f, .02f, MediaPath { "concorde_af.png" } };
}

std::string AircraftFactory::airline_type(int id)
{
    return airlines[id];
}