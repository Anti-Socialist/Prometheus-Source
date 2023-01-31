#include "backend/looped/looped.hpp"
#include "natives.hpp"
#include "gta/joaat.hpp"
#include "gui.hpp"
#include "core/enums.hpp"
#include "util/vehicle.hpp"
#include "util/math.hpp"

namespace big
{
    void looped::fly_gun()
    {
        Ped playerPed = self::ped;

        if (g.weapons.fly_gun)
        {
            Vector3 impact;
            Vector3 test = ENTITY::GET_ENTITY_COORDS(playerPed, 0);
            Vector3 shotfly;
            WEAPON::REMOVE_WEAPON_FROM_PED(playerPed, MISC::GET_HASH_KEY("GADGET_PARACHUTE"));
            if (WEAPON::GET_PED_LAST_WEAPON_IMPACT_COORD(playerPed, &impact))
            {
                shotfly = impact;
            }
            if (PAD::IS_DISABLED_CONTROL_PRESSED(0, 25))
            {
                if (PAD::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_ATTACK))
                {
                    Vector3 entity_velocity;
                    entity_velocity.x = (shotfly.x - test.x) * 3.0f;
                    entity_velocity.y = (shotfly.y - test.y) * 3.0f;
                    entity_velocity.z = (shotfly.z - test.z) * 3.0f;
                    TASK::TASK_SKY_DIVE(playerPed, 0);
                    ENTITY::SET_ENTITY_VELOCITY(playerPed, entity_velocity.x, entity_velocity.y, entity_velocity.z);

                }
                float distance = MISC::GET_DISTANCE_BETWEEN_COORDS(test.x, test.y, test.z, shotfly.x, shotfly.y, shotfly.z, 0);
                if (distance < 1.0f) {
                    TASK::CLEAR_PED_TASKS_IMMEDIATELY(playerPed);
                    TASK::CLEAR_PED_SECONDARY_TASK(playerPed);
                }
            }
        }
    }
}