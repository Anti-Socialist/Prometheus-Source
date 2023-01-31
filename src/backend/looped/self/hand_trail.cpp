#include "natives.hpp"
#include "backend/looped_command.hpp"
#include "util/math.hpp"
#include "gui.hpp"
#include "gta/enums.hpp"

namespace big
{
    class hand_trail : looped_command
    {
        using looped_command::looped_command;

        virtual void on_tick() override
        {
            STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_rcpaparazzo1");
            if (STREAMING::HAS_NAMED_PTFX_ASSET_LOADED("scr_rcpaparazzo1"))
            {
                STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_rcpaparazzo1");
                GRAPHICS::USE_PARTICLE_FX_ASSET("scr_rcpaparazzo1");
                GRAPHICS::START_NETWORKED_PARTICLE_FX_NON_LOOPED_ON_PED_BONE("scr_mich4_firework_sparkle_spawn", self::ped, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0x49d9, 0.6, false, false, false);
                GRAPHICS::SET_PARTICLE_FX_NON_LOOPED_COLOUR(1.0, 0.0, 0.0);
                GRAPHICS::SET_PARTICLE_FX_NON_LOOPED_ALPHA(1.0f);

                STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_rcpaparazzo1");
                GRAPHICS::USE_PARTICLE_FX_ASSET("scr_rcpaparazzo1");
                GRAPHICS::START_NETWORKED_PARTICLE_FX_NON_LOOPED_ON_PED_BONE("scr_mich4_firework_sparkle_spawn", self::ped, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0xdead, 0.6, false, false, false);
                GRAPHICS::SET_PARTICLE_FX_NON_LOOPED_COLOUR(1.0, 0.0, 0.0);
                GRAPHICS::SET_PARTICLE_FX_NON_LOOPED_ALPHA(1.0f);
            }
        }
    };
    hand_trail g_hand_trail("handtrail", "Hand Trails", "Effects On Hands", g.self.hand_trail_red);
}