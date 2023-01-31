#include "script.hpp"
#include "natives.hpp"
#include "pointers.hpp"
#include "script_global.hpp"
#include "gui.hpp"
#include "backend/looped/looped.hpp"
#include "backend/backend.hpp"

namespace big
{
	void looped::vehicle_trail()
	{
		if (g.vehicle.vehicle_trail)
		{
			Vehicle myVeh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
			STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_rcbarry2");
			if (STREAMING::HAS_NAMED_PTFX_ASSET_LOADED("scr_rcbarry2"))
			{
				Vector3 pos = ENTITY::GET_WORLD_POSITION_OF_ENTITY_BONE(myVeh, ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(myVeh, "wheel_lf"));
				GRAPHICS::USE_PARTICLE_FX_ASSET("scr_rcbarry2");
				GRAPHICS::START_NETWORKED_PARTICLE_FX_NON_LOOPED_AT_COORD("scr_clown_appears", pos.x, pos.y, pos.z, 0.f, 0.f, 0.f, 0.4, false, false, false, false);
				Vector3 pos1 = ENTITY::GET_WORLD_POSITION_OF_ENTITY_BONE(myVeh, ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(myVeh, "wheel_lr"));
				GRAPHICS::USE_PARTICLE_FX_ASSET("scr_rcbarry2");
				GRAPHICS::START_NETWORKED_PARTICLE_FX_NON_LOOPED_AT_COORD("scr_clown_appears", pos1.x, pos1.y, pos1.z, 0.f, 0.f, 0.f, 0.4, false, false, false, false);
				Vector3 pos2 = ENTITY::GET_WORLD_POSITION_OF_ENTITY_BONE(myVeh, ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(myVeh, "wheel_rf"));
				GRAPHICS::USE_PARTICLE_FX_ASSET("scr_rcbarry2");
				GRAPHICS::START_NETWORKED_PARTICLE_FX_NON_LOOPED_AT_COORD("scr_clown_appears", pos2.x, pos2.y, pos2.z, 0.f, 0.f, 0.f, 0.4, false, false, false, false);
				Vector3 pos3 = ENTITY::GET_WORLD_POSITION_OF_ENTITY_BONE(myVeh, ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(myVeh, "wheel_rr"));
				GRAPHICS::USE_PARTICLE_FX_ASSET("scr_rcbarry2");
				GRAPHICS::START_NETWORKED_PARTICLE_FX_NON_LOOPED_AT_COORD("scr_clown_appears", pos3.x, pos3.y, pos3.z, 0.f, 0.f, 0.f, 0.4, false, false, false, false);
			}
			else STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_rcbarry2");
		}
	}
}