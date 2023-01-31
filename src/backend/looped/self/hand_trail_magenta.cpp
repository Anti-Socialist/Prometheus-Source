#include "script.hpp"
#include "natives.hpp"
#include "pointers.hpp"
#include "script_global.hpp"
#include "gui.hpp"
#include "backend/looped/looped.hpp"
#include "backend/backend.hpp"

//red = red (RGB: 1.0, 0.0, 0.0)
//green = green (RGB: 0.0, 1.0, 0.0)
//yellow = ellow (RGB: 1.0, 1.0, 0.0)

namespace big
{
    void looped::hand_trail_magenta()
    {
        if (g.self.hand_trail_magenta)
        {
            STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_rcpaparazzo1");
            if (STREAMING::HAS_NAMED_PTFX_ASSET_LOADED("scr_rcpaparazzo1"))
            {
                STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_rcpaparazzo1");
                GRAPHICS::USE_PARTICLE_FX_ASSET("scr_rcpaparazzo1");
                GRAPHICS::START_NETWORKED_PARTICLE_FX_NON_LOOPED_ON_PED_BONE("scr_mich4_firework_sparkle_spawn", self::ped, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0x49d9, 0.6, false, false, false);
                GRAPHICS::SET_PARTICLE_FX_NON_LOOPED_COLOUR(1.0, 0.0, 1.0);
                GRAPHICS::SET_PARTICLE_FX_NON_LOOPED_ALPHA(1.0f);

                STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_rcpaparazzo1");
                GRAPHICS::USE_PARTICLE_FX_ASSET("scr_rcpaparazzo1");
                GRAPHICS::START_NETWORKED_PARTICLE_FX_NON_LOOPED_ON_PED_BONE("scr_mich4_firework_sparkle_spawn", self::ped, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0xdead, 0.6, false, false, false);
                GRAPHICS::SET_PARTICLE_FX_NON_LOOPED_COLOUR(1.0, 0.0, 1.0);
                GRAPHICS::SET_PARTICLE_FX_NON_LOOPED_ALPHA(1.0f);
            }
        }
    }
}