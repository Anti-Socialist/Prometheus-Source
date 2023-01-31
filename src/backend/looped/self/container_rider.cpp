#include "backend/looped/looped.hpp"
#include "natives.hpp"
#include "util/entity.hpp"
#include "services/players/player_service.hpp"

namespace big
{
    void looped::container_rider()
    {
        if (g.self.container_rider)
        {
            static Object container;
            auto selfVeh = PED::GET_VEHICLE_PED_IS_IN(self::ped, 0);
            Vector3 min, max;
            Vector3 cmin, cmax;
            auto c = ENTITY::GET_ENTITY_COORDS(selfVeh, 1);
            MISC::GET_MODEL_DIMENSIONS(ENTITY::GET_ENTITY_MODEL(selfVeh), &min, &max);
            MISC::GET_MODEL_DIMENSIONS(MISC::GET_HASH_KEY("prop_container_ld2"), &cmin, &cmax);

            if (!PED::IS_PED_ON_ANY_BIKE(self::ped)) {
                if (PED::IS_PED_IN_ANY_VEHICLE(self::ped, 0)) {
                    g_notification_service->push_warning("Self", "Container rider requires a bike.");
                    return;
                }
            }

            if (!STREAMING::HAS_MODEL_LOADED(MISC::GET_HASH_KEY("prop_container_ld2")))
                STREAMING::REQUEST_MODEL(MISC::GET_HASH_KEY("prop_container_ld2"));

            if (!ENTITY::DOES_ENTITY_EXIST(container) || !VEHICLE::IS_VEHICLE_ON_ALL_WHEELS(selfVeh)) {
                static auto tickeer = GetTickCount();
                if ((GetTickCount() - tickeer) >= 1000) {
                    if (PAD::IS_CONTROL_PRESSED(2, 111)) {
                        tickeer = GetTickCount();
                        ENTITY::APPLY_FORCE_TO_ENTITY(selfVeh, 0, 0, 0, 1.5, 0, 0, 0, 0, 1, 1, 1, 0, 1);
                    }
                }
                static auto ticker = GetTickCount();
                if (ENTITY::DOES_ENTITY_EXIST(container)) {
                    entity::take_control_of(container);
                    ENTITY::SET_ENTITY_COORDS(container, 0.f, 0.f, 0.f, 1, 1, 1, 0);
                    ENTITY::DELETE_ENTITY(&container);
                    OBJECT::DELETE_OBJECT(&container);
                }
                container = OBJECT::CREATE_OBJECT(MISC::GET_HASH_KEY("prop_container_ld2"), c.x, c.y, c.z - ((max.z / 2) + cmax.z), 1, 1, 0);
                STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(container);
                ENTITY::SET_ENTITY_ROTATION(container, ENTITY::GET_ENTITY_PITCH(selfVeh), 0.f, ENTITY::GET_ENTITY_HEADING(selfVeh), 0, 0);
            }
        }
    }
}