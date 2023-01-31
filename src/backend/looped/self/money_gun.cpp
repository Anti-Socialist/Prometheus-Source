#include "backend/looped/looped.hpp"
#include "natives.hpp"
#include "gta/joaat.hpp"
#include "gui.hpp"
#include "core/enums.hpp"
#include "util/vehicle.hpp"
#include "util/math.hpp"

namespace big
{
    void looped::money_gun()
    {
        if (g.self.money_gun)
        {
            Ped playerPed = self::ped;
            Vector3 pos;
            if (PAD::IS_DISABLED_CONTROL_PRESSED(0, 25))
            {
                if (WEAPON::GET_PED_LAST_WEAPON_IMPACT_COORD(playerPed, &pos))
                {
                    Vector3 coords;
                    if (WEAPON::GET_PED_LAST_WEAPON_IMPACT_COORD(playerPed, &coords))
                    {
                        STREAMING::REQUEST_MODEL(2628187989);
                        if (STREAMING::HAS_MODEL_LOADED(2628187989)) {
                            OBJECT::CREATE_AMBIENT_PICKUP(0x65948212, coords.x, coords.y, coords.z + 1.5, 0, 0xFFFF, 2628187989, 0, 1);
                        }
                    }
                }
            }
        }
    }
}