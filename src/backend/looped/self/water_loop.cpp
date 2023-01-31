#include "backend/looped/looped.hpp"
#include "natives.hpp"
#include "util/entity.hpp"
#include "services/players/player_service.hpp"

namespace big
{
    void looped::water_loop()
    {
        if (g.self.water_loop)
        {
            Player selectedPlayer = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_player_service->get_selected()->id());
            Vector3 Pos = ENTITY::GET_ENTITY_COORDS(selectedPlayer, true);
            FIRE::ADD_EXPLOSION(Pos.x, Pos.y, Pos.z, 13, 5, true, 0, 0, false);
        }
    }
}