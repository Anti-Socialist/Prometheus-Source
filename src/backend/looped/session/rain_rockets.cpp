#include "backend/looped/looped.hpp"
#include "natives.hpp"
#include "gta/joaat.hpp"
#include "gui.hpp"
#include "core/enums.hpp"
#include "util/vehicle.hpp"
#include "util/math.hpp"

namespace big
{
    void looped::rain_rockets()
    {
        if (g.session.rain_rockets)
        {
            Ped iPed = PLAYER::PLAYER_PED_ID();
            static int timer = 0;
            Vector3 kek = ENTITY::GET_ENTITY_COORDS(iPed, FALSE);
            if (GetTickCount64() - timer >= 600)
            {
                float ang = MISC::GET_RANDOM_FLOAT_IN_RANGE(0.0f, 10.0f) * 3.14159265359f;
                float rad = MISC::GET_RANDOM_FLOAT_IN_RANGE(0.0f, 10.0f) * 15.0f;
                float x = kek.x + rad * cos(ang);
                float y = kek.y + rad * sin(ang);
                Hash airStrike = MISC::GET_HASH_KEY("WEAPON_AIRSTRIKE_ROCKET");
                WEAPON::REQUEST_WEAPON_ASSET(airStrike, 31, false);
                while (!WEAPON::HAS_WEAPON_ASSET_LOADED(airStrike))
                    script::get_current()->yield();
                MISC::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(x, y, 200.0f, x, y, 0, 250, 1, airStrike, PLAYER::PLAYER_PED_ID(), 1, 0, -1.0);

                timer = GetTickCount64();
            }
        }
    }
}