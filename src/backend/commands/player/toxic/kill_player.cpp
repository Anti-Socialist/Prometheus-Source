#include "backend/player_command.hpp"
#include "natives.hpp"
#include "pointers.hpp"
#include "util/toxic.hpp"

namespace big
{
	class kill_player : player_command
	{
		using player_command::player_command;

		virtual CommandAccessLevel get_access_level()
		{
			return CommandAccessLevel::AGGRESSIVE;
		}

		virtual void execute(player_ptr player, const std::vector<std::uint64_t>& _args, const std::shared_ptr<command_context> ctx)
		{
			toxic::blame_explode_player(
				player,
				player,
				eExplosionTag::PLANE, 1000, false, true, 0.f
			);
		}
	};

	kill_player g_kill_player("kill", "Kill Player", "Kills the player, bypassing most forms of interior godmode", 0);
}