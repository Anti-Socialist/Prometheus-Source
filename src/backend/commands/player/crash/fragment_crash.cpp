#include "backend/player_command.hpp"
#include "natives.hpp"
#include "pointers.hpp"
#include "core/scr_globals.hpp"
#include "util/scripts.hpp"
#include "util/entity.hpp"
#include "util/ped.hpp"

namespace big
{
	class fragment_crash : player_command
	{
		using player_command::player_command;

		virtual CommandAccessLevel get_access_level()
		{
			return CommandAccessLevel::TOXIC;
		}

		virtual void execute(player_ptr player, const std::vector<std::uint64_t>& _args, const std::shared_ptr<command_context> ctx)
		{
			auto Ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_player_service->get_selected()->id());
			auto Coords = ENTITY::GET_ENTITY_COORDS(Ped, TRUE);
			auto CrashModel = rage::joaat("prop_fragtest_cnst_04");

			// Freeze them
			TASK::CLEAR_PED_TASKS_IMMEDIATELY(Ped);
			TASK::CLEAR_PED_SECONDARY_TASK(Ped);

			while (!STREAMING::HAS_MODEL_LOADED(CrashModel)) {
				STREAMING::REQUEST_MODEL(CrashModel);
				script::get_current()->yield(100ms);
			}

			auto Object = OBJECT::CREATE_OBJECT(CrashModel, Coords.x, Coords.y, Coords.z, TRUE, TRUE, FALSE);
			OBJECT::BREAK_OBJECT_FRAGMENT_CHILD(Object, NULL, NULL);

			script::get_current()->yield(1s);

			STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(CrashModel);
			entity::delete_entity(Object);
		}
	};
	fragment_crash g_fragment_crash("fragment", "Fragment Crash", "Blocked by most menus!", 0, false);
}