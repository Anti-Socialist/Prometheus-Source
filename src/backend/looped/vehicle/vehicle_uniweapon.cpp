#include "backend/looped/looped.hpp"
#include "natives.hpp"
#include "services/players/player_service.hpp"
#include "gta/enums.hpp"

namespace big
{
	void looped::vehicle_uniweap() {

		if (g.vehicle.vehicle_uniweap) {
			Hash wpnHash;
			Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
			Vector3 v0, v1;
			Vehicle VehicleHandle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);
			Vector3 getcoords1 = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(VehicleHandle, 0.6f, 0.6707f, 0.3711f);
			Vector3 getcoords2 = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(VehicleHandle, -0.6f, 0.6707f, 0.3711f);
			Vector3 getcoords3 = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(VehicleHandle, 0.6f, 25.0707f, 0.3711f);
			Vector3 getcoords4 = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(VehicleHandle, -0.6f, 25.0707f, 0.3711f);
			float StartCoords1[] = { getcoords1.x, getcoords1.y, getcoords1.z };
			float StartCoords2[] = { getcoords2.x, getcoords2.y, getcoords2.z };
			float EndCoords1[] = { getcoords3.x, getcoords3.y, getcoords3.z };
			float EndCoords2[] = { getcoords4.x, getcoords4.y, getcoords4.z };
			Vector3 coords0from = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, -(v1.x + 0.25f), v1.y + 1.25f, 0.1f);
			Vector3 coords1from = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, (v1.x + 0.25f), v1.y + 1.25f, 0.1f);
			Vector3 coords0to = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, -v1.x, v1.y + 100.0f, 0.1f);
			Vector3 coords1to = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, v1.x, v1.y + 100.0f, 0.1f);
			wpnHash = MISC::GET_HASH_KEY("VEHICLE_WEAPON_TANK");

			if (PAD::IS_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_PICKUP))
			{
				GRAPHICS::DRAW_LINE(getcoords1.x, getcoords1.y, getcoords1.z, getcoords3.x, getcoords3.y, getcoords3.z, 245, 51, 255, 200);
				GRAPHICS::DRAW_LINE(getcoords2.x, getcoords2.y, getcoords2.z, getcoords4.x, getcoords4.y, getcoords4.z, 245, 51, 255, 200);
				MISC::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(coords0from.x, coords0from.y, coords0from.z, coords0to.x, coords0to.y, coords0to.z, 250, 1, wpnHash, PLAYER::PLAYER_PED_ID(), 1, 0, 1.0);
				MISC::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(coords1from.x, coords1from.y, coords1from.z, coords1to.x, coords1to.y, coords1to.z, 250, 1, wpnHash, PLAYER::PLAYER_PED_ID(), 1, 0, 1.0);
			}
		}
	}
} 