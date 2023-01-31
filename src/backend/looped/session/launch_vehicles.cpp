#include "backend/looped/looped.hpp"
#include "natives.hpp"
#include "gta/joaat.hpp"
#include "gui.hpp"
#include "core/enums.hpp"
#include "util/vehicle.hpp"
#include "util/math.hpp"

namespace big
{
    void looped::launch_vehicle()
    {
        if (g.session.launch_vehicles)
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
                    ENTITY::APPLY_FORCE_TO_ENTITY(vehs[OffsetID], 1, 0, 0, 20, 0, 0, 0, 1, false, true, true, true, true);
                }
            }
        }
    }
}