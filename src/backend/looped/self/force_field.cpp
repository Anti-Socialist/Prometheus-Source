#include "natives.hpp"
#include "backend/looped_command.hpp"
#include "util/math.hpp"
#include "gui.hpp"
#include "gta/enums.hpp"

namespace big
{
    class force_field : looped_command
    {
        using looped_command::looped_command;

        virtual void on_tick() override
        {

            Ped ped = self::ped;
            {
                Vector3 pCoords = ENTITY::GET_ENTITY_COORDS(self::ped, 0);
                FIRE::ADD_EXPLOSION(pCoords.x, pCoords.y, pCoords.z, 7, 9.0f, false, true, 0.0f, true);
            }
        }
    };
    force_field g_force_field("forcefield", "Force Field", "Force field around self", g.self.force_field);
}