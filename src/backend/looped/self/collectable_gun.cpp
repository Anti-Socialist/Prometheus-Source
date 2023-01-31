#include "backend/looped/looped.hpp"
#include "natives.hpp"
#include "gta/joaat.hpp"
#include "gui.hpp"
#include "core/enums.hpp"
#include "util/vehicle.hpp"
#include "util/math.hpp"

namespace big
{
    void looped::collectable_gun()
    {
        if (g.weapons.collectable_gun)
        {
            static Hash prop_list[] = { 437412629, 1298470051, 1955543594, 446117594, 1025210927, 3644302825, 601745115, 2568981558 };
            Ped playerPed = self::ped;
            Vector3 pos;
            if (PAD::IS_DISABLED_CONTROL_PRESSED(0, 25))
            {
                if (WEAPON::GET_PED_LAST_WEAPON_IMPACT_COORD(playerPed, &pos))
                {
                    Vector3 coords;
                    if (WEAPON::GET_PED_LAST_WEAPON_IMPACT_COORD(playerPed, &coords))
                    {
                        STREAMING::REQUEST_MODEL(prop_list[rand() % 8]);
                        if (STREAMING::HAS_MODEL_LOADED(prop_list[rand() % 8])) { script::get_current()->yield();
                            OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 1.5, 0, 10, prop_list[rand() % 8], false, true);
                        }
                    }
                }
            }
        }
    }
}