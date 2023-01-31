#include "natives.hpp"
#include "backend/looped_command.hpp"
#include "util/math.hpp"
#include "gui.hpp"
#include "gta/enums.hpp"

namespace big
{
    class beast_jump : looped_command
    {
        using looped_command::looped_command;

        virtual void on_tick() override
        {

            Ped ped = self::ped;
            {


                if (PED::IS_PED_RAGDOLL(ped) || PED::IS_PED_IN_ANY_VEHICLE(ped, true))
                {

                }
                else
                    if (PAD::IS_CONTROL_JUST_PRESSED(0, (int)ControllerInputs::INPUT_JUMP))
                    {

                        TASK::TASK_JUMP(ped, true, true, true);


                    }
            }
        }
    };

    beast_jump g_beast_jump("beastjump", "Beast Jump", "Jump Very High", g.self.beast_jump);
}