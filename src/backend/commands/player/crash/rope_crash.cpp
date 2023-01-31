#include "backend/player_command.hpp"
#include "natives.hpp"
#include "pointers.hpp"
#include "core/scr_globals.hpp"
#include "gta_util.hpp"
#include "util/toxic.hpp"

#include <network/Network.hpp>

namespace big
{
	class rope_crash : player_command
	{
		using player_command::player_command;

		virtual CommandAccessLevel get_access_level()
		{
			return CommandAccessLevel::TOXIC;
		}

		virtual void execute(player_ptr player, const std::vector<std::uint64_t>& _args, const std::shared_ptr<command_context> ctx)
		{
			static Object first_rope;
			Ped iPed = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_player_service->get_selected()->id());
			int ropetype = 0;
			float lenth = 0.09;
			float init_length = 0.0012;
			float min_length = 10;
			Vector3 playerPosition = ENTITY::GET_ENTITY_COORDS(iPed, FALSE);
			//PHYSICS::ROPE_LOAD_TEXTURES();
			first_rope = PHYSICS::ADD_ROPE(playerPosition.x, playerPosition.y, playerPosition.z, 0, 0, 0, lenth, ropetype, init_length, min_length, 0.5f, 0.5f, true, true, true, 1.0f, 0); // 1, 300, to 0 if no work
			PHYSICS::ATTACH_ROPE_TO_ENTITY(ropetype, iPed, playerPosition.x, playerPosition.y, playerPosition.z, true); // 1, 300, to 0 if no work
			//PHYSICS::ACTIVATE_PHYSICS(first_rope);
			//PHYSICS::ATTACH_ENTITIES_TO_ROPE(first_rope, iPed, iPed, playerPosition.x, playerPosition.y, playerPosition.z, 0, 0, 0, lenth, iPed + 40.f, 0, 0, NULL);
			AUDIO::PLAY_SOUND_FROM_COORD(-1, "Event_Message_Purple", playerPosition.x, playerPosition.y, playerPosition.z, "GTAO_FM_Events_Soundset", true, 1, true);
			AUDIO::PLAY_SOUND_FROM_COORD(-1, "5s", playerPosition.x, playerPosition.y, playerPosition.z, "MP_MISSION_COUNTDOWN_SOUNDSET", true, 1, true);
		}
	};
	rope_crash g_rope_crash("rope", "Rope Crash", "Crashes players game.", 0, false);
}