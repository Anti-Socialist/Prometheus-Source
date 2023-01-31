#include "backend/player_command.hpp"
#include "natives.hpp"
#include "pointers.hpp"
#include "core/scr_globals.hpp"
#include "gta_util.hpp"
#include "util/entity.hpp"

#include <network/Network.hpp>
namespace big
{
	class money_drops : player_command
	{
		using player_command::player_command;

		virtual CommandAccessLevel get_access_level()
		{
			return CommandAccessLevel::FRIENDLY;
		}

		virtual void execute(player_ptr player, const std::vector<std::uint64_t>& _args, const std::shared_ptr<command_context> ctx)
		{
			{
				STREAMING::REQUEST_MODEL(2628187989);
				if (STREAMING::HAS_MODEL_LOADED(2628187989)) {
					Vector3 coords = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player->id()), false);
					OBJECT::CREATE_AMBIENT_PICKUP(0x65948212, coords.x, coords.y, coords.z + 1.5, 0, 0xFFFF, 2628187989, 0, 1);
				}
				script::get_current()->yield(1500ms);
			}
		}
	};

	money_drops g_money_drops("moneydrop", "Money Drop", "Drop player money", 0, false);
}