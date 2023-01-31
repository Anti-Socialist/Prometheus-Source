#include "backend/looped/looped.hpp"
#include "natives.hpp"
#include "gta/joaat.hpp"
#include "gui.hpp"
#include "core/enums.hpp"
#include "util/vehicle.hpp"
#include "util/math.hpp"

namespace big
{
    void looped::explode_peds()
    {
        if (g.session.explode_peds)
        {
            const int ElementAmount = 10;
            const int ArrSize = ElementAmount * 2 + 2;

            Ped* peds = new Ped[ArrSize];
            peds[0] = ElementAmount;

            int PedFound = PED::GET_PED_NEARBY_PEDS(PLAYER::PLAYER_PED_ID(), peds, -1);

            for (int i = 0; i < PedFound; i++)
            {
                int OffsetID = i * 2 + 2;
                entity::take_control_of(peds[OffsetID]);
                if (ENTITY::DOES_ENTITY_EXIST(peds[OffsetID]) && PLAYER::PLAYER_PED_ID() != peds[OffsetID])
                {
                    Vector3 pos = ENTITY::GET_ENTITY_COORDS(peds[OffsetID], false);
                    FIRE::ADD_EXPLOSION(pos.x, pos.y, pos.z, 0, 1000.0f, true, false, 0.f, 0);
                }
            }
        }
    }
}