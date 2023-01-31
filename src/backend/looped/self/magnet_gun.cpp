#include "backend/looped/looped.hpp"
#include "core/enums.hpp"
#include "gta/enums.hpp"
#include "util/entity.hpp"
#include "util/math.hpp"
#include "util/toxic.hpp"

namespace big
{

	void looped::magnet_gun()
	{
		if (g.self.magnet_gun)
		{
			static float zoom = { 10.f };
			static Entity currEnt{ NULL };

			if (GetAsyncKeyState(VK_RBUTTON))
			{
				if (zoom < 40.f)
				{
					if (PAD::IS_DISABLED_CONTROL_PRESSED(2, 261))
					{
						zoom += 2.f;
					}
				}
				if (PAD::IS_DISABLED_CONTROL_PRESSED(2, 262))
				{
					zoom -= 2.f;

				}

				if (GetAsyncKeyState(VK_RBUTTON))
				{
					if (currEnt == NULL)
						PLAYER::GET_ENTITY_PLAYER_IS_FREE_AIMING_AT(PLAYER::PLAYER_ID(), &currEnt);
					else
					{
						if (ENTITY::IS_ENTITY_A_PED(currEnt) && PED::IS_PED_IN_ANY_VEHICLE(currEnt, true) && !PED::IS_PED_A_PLAYER(currEnt))
							currEnt = PED::GET_VEHICLE_PED_IS_IN(currEnt, 0);

						entity::take_control_of(currEnt);

						Vector3 rot = CAM::GET_GAMEPLAY_CAM_ROT(0);
						Vector3 dir = toxic::RotationToDirection(rot);
						Vector3 spawnPosition = toxic::Add(CAM::GET_GAMEPLAY_CAM_COORD(), toxic::Multiply(dir, zoom));

						Vector3 getcoords = ENTITY::GET_ENTITY_COORDS(currEnt, 0);
						float getaimcoordsX = toxic::GravityGunGoto(spawnPosition.x, getcoords.x);
						float getaimcoordsY = toxic::GravityGunGoto(spawnPosition.y, getcoords.y);
						float getaimcoordsZ = toxic::GravityGunGoto(spawnPosition.z, getcoords.z);
						ENTITY::SET_ENTITY_VELOCITY(currEnt, getaimcoordsX * 2.0, getaimcoordsY * 2.0, getaimcoordsZ * 2.0);
						GRAPHICS::DRAW_MARKER(28, spawnPosition.x, spawnPosition.y, spawnPosition.z, 0, 0, 0, 0, 180, 0, 2, 2, 2, 0, 0, 0, 255, 1, 1, 1, 0, 0, 0, 0);

						if (GetAsyncKeyState(VK_LBUTTON))
						{
							ENTITY::APPLY_FORCE_TO_ENTITY(currEnt, 1, dir.x * 250.0f, dir.y * 250.0f, dir.z * 250.0f, 0.0f, 0.0f, 0.0f, false, false, true, true, false, true);
							PLAYER::DISABLE_PLAYER_FIRING(PLAYER::PLAYER_ID(), false);
							currEnt = NULL;
						}

					}

				}
				else
					currEnt = NULL;

			}
		}
	}
}