#include "backend/looped/looped.hpp"
#include "natives.hpp"
#include "util/entity.hpp"
#include "services/players/player_service.hpp"

namespace big
{
    void looped::collectable_drop()
    {
        if (g.self.collectable_drop)
        {
            static Hash prop_list[] = { 437412629, 1298470051, 1955543594, 446117594, 1025210927, 3644302825, 601745115, 2568981558 };
            STREAMING::REQUEST_MODEL(prop_list[rand() % 8]);
            if (STREAMING::HAS_MODEL_LOADED(prop_list[rand() % 8])) { script::get_current()->yield();
                Vector3 coords = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_player_service->get_selected()->id()), false);
                OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 1.5, 0, 10, prop_list[rand() % 8], false, true);
            }
            script::get_current()->yield(1500ms);
        }
    }
}