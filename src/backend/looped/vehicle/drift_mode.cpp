#include "backend/looped/looped.hpp"
#include "natives.hpp"
#include "util/vehicle.hpp"

namespace big
{
    void looped::drift_mode()
    {
        if (g.vehicle.drift_mode)
        {
            if (GetAsyncKeyState(0x10)) {

                VEHICLE::SET_VEHICLE_REDUCE_GRIP(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0), 1);
            }
            else
            {
                VEHICLE::SET_VEHICLE_REDUCE_GRIP(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0), 0);
            }
        }
    }
}