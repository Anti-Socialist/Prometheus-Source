#include "backend/player_command.hpp"
#include "natives.hpp"
#include "pointers.hpp"
#include "core/scr_globals.hpp"
#include "util/scripts.hpp"

namespace big
{
	class parachute_crash : player_command
	{
		using player_command::player_command;

		virtual CommandAccessLevel get_access_level()
		{
			return CommandAccessLevel::TOXIC;
		}

		virtual void execute(player_ptr player, const std::vector<std::uint64_t>& _args, const std::shared_ptr<command_context> ctx)
		{
			auto TargetCoords = ENTITY::GET_ENTITY_COORDS(g_player_service->get_selected()->id(), true);
			Ped pped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_player_service->get_selected()->id());
			Hash model = RAGE_JOAAT("prop_beach_parasol_10");
			Vector3 coord = ENTITY::GET_ENTITY_COORDS(g_player_service->get_selected()->id(), true);
			auto offset = Vector3(5.0, 6.0, 120.00);
			ENTITY::SET_ENTITY_COORDS_NO_OFFSET(pped, TargetCoords.x, TargetCoords.y, TargetCoords.z + offset.z, 0, 0, 0);
			if (STREAMING::HAS_MODEL_LOADED(model)) //
			{
				script::get_current()->yield(100ms);
				WEAPON::GIVE_WEAPON_TO_PED(pped, 4222310262, 1, false, true);
				script::get_current()->yield(10ms);
				PLAYER::SET_PLAYER_PARACHUTE_MODEL_OVERRIDE(g_player_service->get_selected()->id(), model);
				script::get_current()->yield(100ms);
				TASK::SET_PARACHUTE_TASK_TARGET(pped, coord.x, coord.y, coord.z);
				script::get_current()->yield(2000ms);
				TASK::CLEAR_PED_TASKS_IMMEDIATELY(pped);
				script::get_current()->yield(2500ms);
				script::get_current()->yield();
			}
		}
	};
parachute_crash g_parachute_crash("parachute", "Parachute Crash", "Blocked by most menus!", 0, false);
}