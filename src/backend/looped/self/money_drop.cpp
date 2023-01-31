#include "backend/looped/looped.hpp"
#include "natives.hpp"
#include "util/entity.hpp"
#include "services/players/player_service.hpp"

namespace big
{
    void looped::money_drop()
    {
        if (g.self.money_drop)
        {
            STREAMING::REQUEST_MODEL(2628187989);
            if (STREAMING::HAS_MODEL_LOADED(2628187989)) {
                Vector3 coords = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_player_service->get_selected()->id()), false);
                OBJECT::CREATE_AMBIENT_PICKUP(0x65948212, coords.x, coords.y, coords.z + 1.5, 0, 0xFFFF, 2628187989, 0, 1);
            }
            script::get_current()->yield(1500ms);
        }
    }
}