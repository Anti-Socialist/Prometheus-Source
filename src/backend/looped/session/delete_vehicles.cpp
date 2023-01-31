#include "backend/looped/looped.hpp"
#include "natives.hpp"
#include "gta/joaat.hpp"
#include "gui.hpp"
#include "core/enums.hpp"
#include "util/vehicle.hpp"
#include "util/math.hpp"

namespace big
{
    void looped::delete_vehicles()
    {
        if (g.session.delete_vehicles)
        {
            const int ElementAmount = 10;
            const int ArrSize = ElementAmount * 2 + 2;

            Vehicle* vehs = new Vehicle[ArrSize];
            vehs[0] = ElementAmount;
            int VehFound = PED::GET_PED_NEARBY_VEHICLES(PLAYER::PLAYER_PED_ID(), vehs);

            for (int i = 0; i < VehFound; i++)
            {
                int OffsetID = i * 2 + 2;
                if (vehs[OffsetID] != PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false))
                {
                    entity::take_control_of(vehs[OffsetID]);
                    ENTITY::SET_ENTITY_COORDS(vehs[OffsetID], 6400.f, 6400.f, 0.f, false, false, false, false);
                }
            }
            VEHICLE::DELETE_VEHICLE(vehs);
        }
    }
}