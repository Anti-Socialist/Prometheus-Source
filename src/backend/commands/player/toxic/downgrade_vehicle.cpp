#include "backend/player_command.hpp"
#include "natives.hpp"
#include "pointers.hpp"
#include "util/toxic.hpp"

namespace big
{
	class downgrade_vehicle : player_command
	{
		using player_command::player_command;

		virtual CommandAccessLevel get_access_level()
		{
			return CommandAccessLevel::AGGRESSIVE;
		}

		virtual void execute(player_ptr player, const std::vector<std::uint64_t>& _args, const std::shared_ptr<command_context> ctx)
		{
			toxic::downgrade_vehicle(player->id());
		}
	};

	downgrade_vehicle g_downgrade_vehicle("downgradevehicle", "Downgrade Vehicle", "Downgrades players vehicle.", 0);
}