#include "backend/looped/looped.hpp"
#include "natives.hpp"
#include "gta/joaat.hpp"
#include "gui.hpp"
#include "core/enums.hpp"
#include "util/vehicle.hpp"
#include "util/math.hpp"

namespace big
{
    void looped::flame_thrower()
    {
        Ped playerPed = self::ped;
        Vector3 pos;

        if (g.weapons.flame_thrower)
        {
        }
    }
}



//            Hash weaponhash = NULL;
//            if (WEAPON::GET_CURRENT_PED_WEAPON(PLAYER::PLAYER_PED_ID(), &weaponhash, false))
//            {
//                PLAYER::DISABLE_PLAYER_FIRING(PLAYER::PLAYER_ID(), true);
//
//                if (PAD::IS_CONTROL_PRESSED(0, 25))
//                {
//                    static int timer;
//                    if ((GetTickCount() - timer) > 75) {
//                        STREAMING::REQUEST_NAMED_PTFX_ASSET("core");
//                        GRAPHICS::USE_PARTICLE_FX_ASSET("core");
//                        GRAPHICS::START_NETWORKED_PARTICLE_FX_NON_LOOPED_AT_COORD("ent_sht_flame", WEAPON::GET_CURRENT_PED_WEAPON_ENTITY_INDEX(self::ped, false), 0.4f, 0.0f, 0.02f, 89.5f, 0.0f, 90.0f, ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(WEAPON::GET_CURRENT_PED_WEAPON_ENTITY_INDEX(self::ped, false), "Gun_Nuzzle"), 0.85f, 0, 0);
//                        STREAMING::REMOVE_PTFX_ASSET();
//                        timer = GetTickCount();
//                    }
//                }
//            }
//        }
//    }
//}