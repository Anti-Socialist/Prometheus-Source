#include "backend/looped/looped.hpp"
#include "util/entity.hpp"
#include "script_global.hpp"
#include "natives.hpp"
#include "gta/joaat.hpp"
#include "util/local_player.hpp"

namespace big
{
    void looped::nightclub_loop()
    {
        if (g.self.nightclub_loop)
        {
            std::string mpPrefix = local_player::get_mp_prefix();
            int player_Stuff = 1;
            //new std::uint8_t[4];
            int player_char = STATS::STAT_GET_INT(rage::joaat("MPPLY_LAST_MP_CHAR"), &player_Stuff, true);
            *script_global(262145).at(24045).as<int*>() = 300000;
            *script_global(262145).at(24041).as<int*>() = 300000;
            STATS::STAT_SET_INT(rage::joaat(mpPrefix + "CLUB_POPULARITY"), 10000, true);
            STATS::STAT_SET_INT(rage::joaat(mpPrefix + "CLUB_PAY_TIME_LEFT"), -1, true);
            STATS::STAT_SET_INT(rage::joaat(mpPrefix + "CLUB_POPULARITY"), 10000, true);
            STATS::STAT_SAVE(0, 0, 3, 0);
            script::get_current()->yield(10000ms);
        }

    }
}