#include "backend/looped/looped.hpp"
#include "natives.hpp"
#include "gta/joaat.hpp"
#include "gui.hpp"
#include "core/enums.hpp"
#include "util/vehicle.hpp"
#include "util/math.hpp"

namespace big
{
    void looped::paint_gun()
    {
        Ped playerPed = self::ped;
        Vector3 pos;

        if (g.weapons.paint_gun)
        {
            if (PAD::IS_DISABLED_CONTROL_PRESSED(0, 25))
            {
                Hash model = MISC::GET_HASH_KEY("prop_air_lights_02a"); //hei_prop_carrier_docklight_01
                if (STREAMING::IS_MODEL_IN_CDIMAGE(model) && STREAMING::IS_MODEL_VALID(model))
                {
                    STREAMING::REQUEST_MODEL(model);
                    while (!STREAMING::HAS_MODEL_LOADED(model)) script::get_current()->yield();
                    if (WEAPON::GET_PED_LAST_WEAPON_IMPACT_COORD(playerPed, &pos))
                    {
                        OBJECT::CREATE_OBJECT(model, pos.x, pos.y, pos.z, true, 1, 0);
                    }
                    STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(model);
                }
            }
        }
    }
}