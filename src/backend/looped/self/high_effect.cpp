#include "natives.hpp"
#include "backend/looped_command.hpp"
#include "util/math.hpp"
#include "gui.hpp"
#include "gta/enums.hpp"

namespace big
{
	class high_effect : looped_command
	{
		using looped_command::looped_command;

		virtual void on_tick() override
		{
			{
				static const char* modifiers[] = { "drug_flying_01", "drug_flying_02", "drug_flying_base" };
				GRAPHICS::SET_TIMECYCLE_MODIFIER("drug_flying_base");
			}
		}
		virtual void on_disable() override
		{
			GRAPHICS::CLEAR_TIMECYCLE_MODIFIER();
		}
	};
	high_effect g_high_effect("higheffect", "High Effect", "Makes Player High", g.self.high_effect);
}