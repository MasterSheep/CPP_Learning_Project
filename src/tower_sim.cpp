#include "tower_sim.hpp"

#include "GL/opengl_interface.hpp"
#include "aircraft.hpp"
#include "aircraft_manager.hpp"
#include "airport.hpp"
#include "config.hpp"
#include "img/image.hpp"
#include "img/media_path.hpp"

#include <cassert>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std::string_literals;

TowerSimulation::TowerSimulation(int argc, char** argv) :
    help { (argc > 1) && (std::string { argv[1] } == "--help"s || std::string { argv[1] } == "-h"s) }
{
    MediaPath::initialize(argv[0]);
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    GL::init_gl(argc, argv, "Airport Tower Simulation");

    create_keystrokes();
}

TowerSimulation::~TowerSimulation()
{
    delete airport;
}

void TowerSimulation::create_random_aircraft()
{
    assert(airport); // make sure the airport is initialized before creating aircraft
    auto aircraft = aircraft_factory.create_aircraft(this->airport);
    // GL::display_queue.emplace_back(aircraft);
    aircraft_manager.addAirCraft(std::move(aircraft));
    // GL::move_queue.emplace(aircraft);
}

void TowerSimulation::create_keystrokes()
{
    GL::keystrokes.emplace('x', []() { GL::exit_loop(); });
    GL::keystrokes.emplace('q', []() { GL::exit_loop(); });
    GL::keystrokes.emplace('c', [this]() { create_random_aircraft(); });
    GL::keystrokes.emplace('+', []() { GL::change_zoom(0.95f); });
    GL::keystrokes.emplace('-', []() { GL::change_zoom(1.05f); });
    GL::keystrokes.emplace('f', []() { GL::toggle_fullscreen(); });
    //
    GL::keystrokes.emplace('o', []() { GL::ticks_per_sec = GL::ticks_per_sec + 1u; });
    GL::keystrokes.emplace('i', []()
                           { GL::ticks_per_sec = GL::ticks_per_sec - (GL::ticks_per_sec == 1u ? 0u : 1u); });
    GL::keystrokes.emplace('p', []() { GL::pause = (GL::pause == true ? false : true); });
    //
    for (int i = 1; i <= 8; i++)
    {
        GL::keystrokes.emplace('0' + i,
                               [this, i]()
                               {
                                   auto type = aircraft_factory.airline_type(i - 1);
                                   std::cout << type << " : " << aircraft_manager.countAirelineType(type)
                                             << std::endl;
                               });
    }
}

void TowerSimulation::display_help() const
{
    std::cout << "This is an airport tower simulator" << std::endl
              << "the following keysstrokes have meaning:" << std::endl;

    for (const auto& [key, value] : GL::keystrokes)
    {
        std::cout << key << ' ';
    }

    std::cout << std::endl;
}

void TowerSimulation::init_airport()
{
    airport =
        new Airport { one_lane_airport, Point3D { 0, 0, 0 },
                      new img::Image { one_lane_airport_sprite_path.get_full_path() }, aircraft_manager };

    GL::display_queue.emplace_back(airport);
    GL::move_queue.emplace(airport);
}

void TowerSimulation::launch()
{
    if (help)
    {
        display_help();
        return;
    }

    init_airport();
    GL::move_queue.emplace(&aircraft_manager);
    aircraft_factory.init_aircraft_types();

    GL::loop();
}
