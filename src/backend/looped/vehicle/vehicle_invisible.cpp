#include "backend/looped/looped.hpp"
#include "natives.hpp"

namespace big
{
	static bool bLastVehInvisibility = false;
	void looped::vehicle_invisible()
	{
		if (g.vehicle.vehicle_invisible)
		{
			ENTITY::SET_ENTITY_VISIBLE(PED::GET_VEHICLE_PED_IS_USING(self::ped), false, 0);
		}
		else 
		{
			ENTITY::SET_ENTITY_VISIBLE(PED::GET_VEHICLE_PED_IS_USING(self::ped), true, 0);
		}
	}
}