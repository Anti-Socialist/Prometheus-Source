#include "natives.hpp"
#include "backend/looped_command.hpp"
#include "util/math.hpp"
#include "gui.hpp"
#include "gta/enums.hpp"

namespace big
{
    class fire_breath : looped_command
    {
        using looped_command::looped_command;

        virtual void on_tick() override
        {

            if (g.self.fire_breath)
            {
                static bool ran_once = []
                {
                    g_notification_service->push("Instructions", "Press E to breathe fire.");
                    return true;
                }();
            }

            if (g.self.fire_breath)
            {
                Ped ped = PLAYER::PLAYER_PED_ID();
                static int timer = 0;

                if (GetAsyncKeyState(0x45)) {

                    float XPos = 0.02f, YPos = 0.2f, ZPos = 0.0f, XOff = 90.0f, YOff = -100.0f, ZOff = 90.0f;

                    STREAMING::REQUEST_NAMED_PTFX_ASSET("core");
                    GRAPHICS::USE_PARTICLE_FX_ASSET("core");
                    if (GetTickCount64() - timer >= 3)
                    {
                        int ptfx = GRAPHICS::START_NETWORKED_PARTICLE_FX_NON_LOOPED_ON_PED_BONE("ent_sht_flame", PLAYER::PLAYER_PED_ID(), XPos, YPos, ZPos, XOff, YOff, ZOff, 0x796E, 1, 1, 1, 1);
                        GRAPHICS::SET_PARTICLE_FX_NON_LOOPED_COLOUR(1.0, 0.0, 0.0);
                        timer = GetTickCount64(); //yurii is my cutie
                    }
                    STREAMING::REMOVE_PTFX_ASSET();
                }
            }
        }
    };
    fire_breath g_fire_breath("firebreath", "Fire Breath", "Breathe fire", g.self.fire_breath);
}