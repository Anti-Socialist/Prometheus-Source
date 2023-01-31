#include "backend/looped/looped.hpp"
#include "natives.hpp"
#include "util/entity.hpp"
#include "backend/looped_command.hpp"


namespace big
{
	class ride_deer : looped_command
	{


		using looped_command::looped_command;

		virtual void on_tick() override
		{

			Ped playerPed = self::ped;
			if (!ENTITY::DOES_ENTITY_EXIST(playerPed)) return;
			Vector3 pos = ENTITY::GET_ENTITY_COORDS(self::ped, 1);
			Hash stripper = MISC::GET_HASH_KEY("a_c_deer");
			STREAMING::REQUEST_MODEL(stripper);
			while (!STREAMING::HAS_MODEL_LOADED(stripper)) script::get_current()->yield();
			if (g.self.fire_breath)
			{
				static bool ran_once = []
				{
					Ped playerPed = self::ped;
					Vector3 pos = ENTITY::GET_ENTITY_COORDS(self::ped, 1);
					Hash stripper = MISC::GET_HASH_KEY("a_c_deer");
					STREAMING::REQUEST_MODEL(stripper);
					while (!STREAMING::HAS_MODEL_LOADED(stripper)) script::get_current()->yield();
					int createdPED = PED::CREATE_PED(26, stripper, pos.x, pos.y, pos.z, 1, 1, 0);
					ENTITY::SET_ENTITY_INVINCIBLE(createdPED, false);
					PED::SET_PED_COMBAT_ABILITY(createdPED, 100);
					PED::SET_PED_CAN_SWITCH_WEAPON(createdPED, true);
					ENTITY::ATTACH_ENTITY_TO_ENTITY(playerPed, createdPED, -1, 0.0f, 0.35f, 0.72f, 0.0f, 0.0f, 0.0f, 1, 0, 0, 2, 1, 1, false);
					char* anim = (char*)"creatures@deer@move";
					char* animID = (char*)"trot";
					TASK::TASK_PLAY_ANIM(createdPED, anim, animID, 8.0f, 0.0f, -1, 9, 0, 0, 0, 0);
					STREAMING::REQUEST_ANIM_DICT(anim);
					while (!STREAMING::HAS_ANIM_DICT_LOADED(anim))
						script::get_current()->yield();
					//charPose
					char* anim2 = (char*)"mp_safehouselost_table@";
					char* animID2 = (char*)"lost_table_negative_a";

					STREAMING::REQUEST_ANIM_DICT(anim2);
					while (!STREAMING::HAS_ANIM_DICT_LOADED(anim2))
						script::get_current()->yield();
					TASK::TASK_PLAY_ANIM(playerPed, anim2, animID2, 8.0f, 0.0f, -1, 9, 0, 0, 0, 0);
					return true;
				}();
			}

			//deer animation
		}
	};
	ride_deer g_ride_deer("ridedeer", "Ride Deer", "Rideable Deer", g.self.ride_deer);
}