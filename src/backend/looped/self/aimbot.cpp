#include "natives.hpp"
#include "backend/looped_command.hpp"
#include "util/math.hpp"
#include "gui.hpp"
#include "gta/enums.hpp"

namespace big
{
	class aimbot : looped_command
	{
		using looped_command::looped_command;

		virtual void on_tick() override
		{
			if (g_local_player == nullptr || g_local_player->m_player_info == nullptr) return;
			if (g.self.aimbot && !NETWORK::NETWORK_IS_IN_SPECTATOR_MODE() && !NETWORK::NETWORK_IS_ACTIVITY_SPECTATOR() &&
				!HUD::IS_PAUSE_MENU_ACTIVE() && !ENTITY::IS_ENTITY_DEAD(self::ped, false) && !g_gui->is_open())
			{
				for (auto& item : g_player_service->players())
				{
					if (auto const& plyr = item.second;
						plyr->id() != self::id && GetAsyncKeyState(VK_LBUTTON))
					{
						if (auto const targetPed = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(plyr->id());
							ENTITY::DOES_ENTITY_EXIST(targetPed) && ENTITY::GET_ENTITY_HEALTH(targetPed) > 0)
						{
							if (g.self.aimbot_exclude_friend && plyr->is_friend()) continue;

							auto const playerPos = ENTITY::GET_ENTITY_COORDS(self::ped, true);
							auto const targetPos = ENTITY::GET_ENTITY_COORDS(targetPed, true);

							float screenX, screenY;
							if (auto const distance = SYSTEM::VDIST(playerPos.x, playerPos.y, playerPos.z, targetPos.x, targetPos.y, targetPos.z);
								GRAPHICS::GET_SCREEN_COORD_FROM_WORLD_COORD(targetPos.x, targetPos.y, targetPos.z, &screenX, &screenY)
								&& ENTITY::IS_ENTITY_VISIBLE(targetPed)
								&& (distance < 500 && distance > 2)
								&& ENTITY::HAS_ENTITY_CLEAR_LOS_TO_ENTITY(self::ped, targetPed, 17))
							{
								Vector3 selfPed = ENTITY::GET_ENTITY_COORDS(self::ped, true);
								auto const targetCoords = PED::GET_PED_BONE_COORDS(targetPed, 31086, 0, 0, 0); //For Head ->31086, For Neck ->39317
								PED::SET_PED_SHOOTS_AT_COORD(self::ped, targetCoords.x, targetCoords.y, targetCoords.z, true);
							}
						}
					}
				}
			}
		}

	};
	aimbot g_aimbot("aimbot", "Aim Bot", "Headshot Players", g.self.aimbot);
}