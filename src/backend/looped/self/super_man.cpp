#include "natives.hpp"
#include "backend/looped_command.hpp"
#include "util/math.hpp"
#include "gui.hpp"
#include "gta/enums.hpp"
#include "util/toxic.hpp"

namespace big
{
	class super_man : looped_command
	{
		using looped_command::looped_command;

		virtual void on_tick() override
		{
			g.self.no_ragdoll = true;
			g.vehicle.seatbelt = true;
			Hash parachute = RAGE_JOAAT("GADGET_PARACHUTE");
			WEAPON::GIVE_WEAPON_TO_PED(self::ped, parachute, 1, false, true);
			//ENTITY::SET_ENTITY_INVINCIBLE(self::ped, true);
			PED::SET_PED_TO_RAGDOLL_WITH_FALL(self::ped, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0);

			if (ENTITY::IS_ENTITY_IN_AIR(self::ped) && !PED::IS_PED_RAGDOLL(self::ped))
			{
				if (PAD::IS_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_VEH_ACCELERATE)) { toxic::ApplyForceToEntity(self::ped, 0, 2, 0); }
				if (PAD::IS_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_VEH_BRAKE)) { toxic::ApplyForceToEntity(self::ped, 0, -2, 0); }
				if (PAD::IS_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_VEH_HANDBRAKE)) { toxic::ApplyForceToEntity(self::ped, 0, 0, 2); }
			}
		}
	};
	super_man g_super_man("superman", "Super Man", "Fly through sky.", g.self.super_man);
}