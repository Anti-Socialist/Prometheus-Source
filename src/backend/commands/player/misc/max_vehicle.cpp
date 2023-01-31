#include "backend/player_command.hpp"
#include "natives.hpp"
#include "pointers.hpp"
#include "util/globals.hpp"
#include "services/pickups/pickup_service.hpp"
#include "util/vehicle.hpp"

namespace big
{
	class max_vehicle : player_command
	{
		using player_command::player_command;

		virtual CommandAccessLevel get_access_level()
		{
			return CommandAccessLevel::FRIENDLY;
		}

		virtual void execute(player_ptr player, const std::vector<std::uint64_t>& _args, const std::shared_ptr<command_context> ctx)
		{
			Vehicle vechile = PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player->id()), false);
			vehicle::repair(vechile);
		}
	};

	max_vehicle g_max_vehicle("maxvehicle", "Max Vehicle", "Maxes player vehicle", 0);
}