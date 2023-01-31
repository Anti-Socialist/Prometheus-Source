#include "natives.hpp"
#include "backend/looped_command.hpp"
#include "util/math.hpp"
#include "gui.hpp"
#include "gta/enums.hpp"

namespace big
{
	class tiny_player : looped_command
	{
		using looped_command::looped_command;

		virtual void on_tick() override
		{
			{
				PED::SET_PED_CONFIG_FLAG(self::ped, 223, true);
			}
		}
		virtual void on_disable() override
		{
			PED::SET_PED_CONFIG_FLAG(self::ped, 223, false);
		}
	};
	tiny_player g_tiny_player("tinyplayer", "Tiny Player", "Makes Ped Tiny", g.self.tiny_player);
}