#include "backend/looped/looped.hpp"
#include "natives.hpp"
#include "gta/joaat.hpp"
#include "gui.hpp"
#include "core/enums.hpp"
#include "util/vehicle.hpp"
#include "util/math.hpp"
#include "util/toxic.hpp"

namespace big
{

	void looped::rope_gun()
	{
		if (g.weapons.rope_gun)
		{
			if (PAD::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_AIM))
			{
				if (PAD::IS_DISABLED_CONTROL_JUST_RELEASED(0, (int)ControllerInputs::INPUT_ATTACK))
				{

					Entity entity;

					if (entity::raycast(&entity))
					{
						if (ENTITY::IS_ENTITY_AN_OBJECT(entity) || ENTITY::IS_ENTITY_A_PED(entity) || ENTITY::IS_ENTITY_A_VEHICLE(entity)) {
							std::string get_model = std::format("Model: 0x{}", ENTITY::GET_ENTITY_MODEL(entity));
							LOG(INFO) << get_model;
						}
					}
				}
			}
		}
	}
}