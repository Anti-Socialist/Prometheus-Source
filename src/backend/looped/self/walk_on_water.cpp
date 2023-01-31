#include "script.hpp"
#include "natives.hpp"
#include "pointers.hpp"
#include "script_global.hpp"
#include "gui.hpp"
#include "backend/looped/looped.hpp"
#include "backend/backend.hpp"
#include "util/entity.hpp"

namespace big
{
    void looped::walk_on_water()
    {
        if (g.self.walk_on_water)
        {
            Hash ferris = MISC::GET_HASH_KEY("prop_container_ld_d");
            Vector3 me = self::pos;
            float water;
            static int timer = 0;
            static Object model;

            WATER::SET_DEEP_OCEAN_SCALER(-1.f);
            if (WATER::GET_WATER_HEIGHT(me.x, me.y, me.z, &water))
            {
                if (!PED::IS_PED_IN_ANY_VEHICLE(self::ped, 1))
                {
                    if (!STREAMING::HAS_MODEL_LOADED(ferris))
                        if (GetTickCount64() - timer >= 0)
                        {
                            model = OBJECT::CREATE_OBJECT(ferris, me.x, me.y, me.z, 1, 1, 1);
                            entity::take_control_of(model);
                            ENTITY::SET_ENTITY_VISIBLE(model, 0, 0);    
                            ENTITY::FREEZE_ENTITY_POSITION(model, 1);
                            ENTITY::SET_ENTITY_ROTATION(model, 0, 0, ENTITY::GET_ENTITY_HEADING(self::ped) , 0, 0);
                            ENTITY::SET_ENTITY_COORDS(model, me.x, me.y, water - 2.8f, 0, 0, 0, 1);
                            timer = GetTickCount64();
                        }
                    }
                }
            if (ENTITY::DOES_ENTITY_EXIST(model))
            {
                entity::take_control_of(model);
                OBJECT::DELETE_OBJECT(&model);
            }
        }
    }
}
