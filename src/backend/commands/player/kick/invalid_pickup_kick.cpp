#include "backend/player_command.hpp"
#include "natives.hpp"
#include "pointers.hpp"
#include "core/scr_globals.hpp"
#include "util/scripts.hpp"

namespace big
{
	class invalid_pickup_kick : player_command
	{
		using player_command::player_command;

		virtual CommandAccessLevel get_access_level()
		{
			return CommandAccessLevel::TOXIC;
		}

		virtual void execute(player_ptr player, const std::vector<std::uint64_t>& _args, const std::shared_ptr<command_context> ctx)
		{
			STREAMING::REQUEST_MODEL(MISC::GET_HASH_KEY("vw_prop_vw_colle_prbubble"));
			if (!STREAMING::HAS_MODEL_LOADED(MISC::GET_HASH_KEY("vw_prop_vw_colle_prbubble"))) {
				script::get_current()->yield();
				{
					Vector3 coords = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_player_service->get_selected()->id()), false);
					OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 1.5, 0, 0xFFFF, MISC::GET_HASH_KEY("vw_prop_vw_colle_prbubble"), 0, 1); //0xFFFF
					STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(MISC::GET_HASH_KEY("vw_prop_vw_colle_prbubble"));
				}
			}
		}
	};

	invalid_pickup_kick g_invalid_pickup_kick("invalidpickup", "Invalid Pickup", "Blocked by most menus!", 0, false);
}