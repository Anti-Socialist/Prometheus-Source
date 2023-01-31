#include "backend/looped/looped.hpp"
#include "natives.hpp"
#include "gta/joaat.hpp"
#include "gui.hpp"
#include "core/enums.hpp"
#include "util/vehicle.hpp"
#include "util/math.hpp"

namespace big
{
    void looped::asteroid_shower()
    {
        if (g.session.asteroid_shower)
        {
            Hash ast = MISC::GET_HASH_KEY("prop_asteroid_01");
            bool force_thunder = true;
            static int timer = 0;
            auto handle = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), ast);
            auto handle1 = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), ast);
            Vector3 coords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true);
            if (GetTickCount64() - timer >= 600)
            {
                if (STREAMING::IS_MODEL_VALID(ast))
                {
                    STREAMING::REQUEST_MODEL(ast);
                    while (!STREAMING::HAS_MODEL_LOADED(ast)) script::get_current()->yield();
                    float ang = MISC::GET_RANDOM_FLOAT_IN_RANGE(0.0f, 20.0f) * 3.14159265359f, handle;
                    float rad = MISC::GET_RANDOM_FLOAT_IN_RANGE(0.0f, 20.0f) * 15.0f, handle1;
                    float x = coords.x + rad * cos(ang);
                    float y = coords.y + rad * sin(ang);
                    Object Asteroid = OBJECT::CREATE_OBJECT(ast, x, y, 200.0f, 1, 1, 1);
                    ENTITY::SET_ENTITY_COLLISION(Asteroid, 1, 1);
                    ENTITY::APPLY_FORCE_TO_ENTITY(Asteroid, 1, 150.0f, 180.0f, 200.0f, 20.0f, 20.0f, 50.0f, 0, 0, 1, 1, 0, 1);
                    timer = GetTickCount64();
                }
                STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(ast);
            }
            return;
        }
        else {
            bool force_thunder = false;
        }
    }
}