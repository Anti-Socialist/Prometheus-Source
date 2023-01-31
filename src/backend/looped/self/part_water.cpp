#include "backend/looped/looped.hpp"
#include "natives.hpp"
#include "backend/looped_command.hpp"

namespace big
{
	class move_water : looped_command
	{
		using looped_command::looped_command;

		virtual void on_tick() override
		{
			Vector3 coords = self::pos;
			float offset[] = { -4, 4 };

			for (int i = 0; i < 5; i++)
			{
				if (i < 2)
				{
					coords.x += offset[(i % 2 == 0)];
				}
				else if (i < 4)
				{
					coords.y += offset[(i % 2 == 0)];
				}
				WATER::MODIFY_WATER(coords.x, coords.y, -500000.0f, 0.2f);
			}
		}
	};

	move_water g_move_water("movewater", "Move Water", "Move water out of way.", g.self.move_water);
}