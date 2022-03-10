#include "tower.hpp"

#include "airport.hpp"
#include "terminal.hpp"

#include <cassert>

WaypointQueue Tower::get_circle() const
{
    return { { Point3D { -1.5f, -1.5f, .5f }, wp_air },
             { Point3D { 1.5f, -1.5f, .5f }, wp_air },
             { Point3D { 1.5f, 1.5f, .5f }, wp_air },
             { Point3D { -1.5f, 1.5f, .5f }, wp_air } };
}

WaypointQueue Tower::get_instructions(Aircraft& aircraft)
{
    if (!aircraft.is_at_terminal)
    {
        // if the aircraft is far, then just guide it to the airport vicinity
        if (aircraft.distance_to(airport.pos) < 5)
        {
            // try and reserve a terminal for the craft to land
            const auto vp = airport.reserve_terminal(aircraft);
            if (!vp.first.empty())
            {
                reserved_terminals[&aircraft] = vp.second;
                return vp.first;
            }
            else
            {
                return get_circle();
            }
        }
        else
        {
            // GL::display_queue.erase(&aircraft);
            // GL::move_queue.erase(&aircraft);
            // std::cout << "Ici !" << std::endl;
            return {};
        }
    }
    else
    {
        // get a path for the craft to start
        /*
        const auto it = find_craft_and_terminal(aircraft);
        assert(it != reserved_terminals.end());
        */
        const auto terminal_num = reserved_terminals[&aircraft];
        Terminal& terminal      = airport.get_terminal(terminal_num);
        if (!terminal.is_servicing())
        {
            terminal.finish_service();
            reserved_terminals.erase(reserved_terminals.find(&aircraft));
            aircraft.is_at_terminal = false;
            return airport.start_path(terminal_num);
        }
        else
        {
            return {};
        }
    }
}

void Tower::arrived_at_terminal(const Aircraft& aircraft)
{
    // const auto it = reserved_terminals[&aircraft];
    //  assert(it != reserved_terminals.end());
    airport.get_terminal(reserved_terminals[&aircraft]).start_service(aircraft);
}
