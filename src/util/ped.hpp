#pragma once
#include "natives.hpp"
#include "script.hpp"
#include "pointers.hpp"
#include "entity.hpp"

namespace big::ped
{
	inline bool change_player_model(const Hash hash)
	{
		for (uint8_t i = 0; !STREAMING::HAS_MODEL_LOADED(hash) && i < 100; i++)
		{
			STREAMING::REQUEST_MODEL(hash);
			script::get_current()->yield();
		}
		if (!STREAMING::HAS_MODEL_LOADED(hash))
		{
			return false;
		}
		self::ped = PLAYER::PLAYER_PED_ID();
		script::get_current()->yield();
		STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(hash);

		return true;
	}

	inline int spawn_in_vehicle(std::string_view model, Vehicle veh, bool is_networked = true, bool clean_up = true)
	{
		if (const Hash hash = rage::joaat(model.data()); hash)
		{
			for (uint8_t i = 0; !STREAMING::HAS_MODEL_LOADED(hash) && i < 100; i++)
			{
				STREAMING::REQUEST_MODEL(hash);

				script::get_current()->yield();
			}
			if (!STREAMING::HAS_MODEL_LOADED(hash))
			{
				g_notification_service->push_warning("Spawn", "Failed to spawn model, did you give an incorrect model?");

				return -1;
			}

			Ped ped = PED::CREATE_PED_INSIDE_VEHICLE(veh, 0, hash, -1, is_networked, false);

			script::get_current()->yield();

			STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(hash);

			if (*g_pointers->m_is_session_started)
			{
				DECORATOR::DECOR_SET_INT(ped, "MPBitset", 0);
			}

			return ped;
		}

		return -1;
	}

	inline bool steal_outfit(const Ped target)
	{
		Ped ped = self::ped;

		if (ENTITY::GET_ENTITY_MODEL(ped) != ENTITY::GET_ENTITY_MODEL(target))
		{
			return false;
		}
		for (int i = 0; i < 12; i++)
		{
			PED::SET_PED_COMPONENT_VARIATION(
				ped,
				i,
				PED::GET_PED_DRAWABLE_VARIATION(target, i),
				PED::GET_PED_TEXTURE_VARIATION(target, i),
				PED::GET_PED_PALETTE_VARIATION(target, i));
		}

		return true;
	}

	inline void steal_identity(const Ped target)
	{
		const int max_health = ENTITY::GET_ENTITY_MAX_HEALTH(self::ped);
		const int current_health = ENTITY::GET_ENTITY_HEALTH(self::ped);
		const int current_armor = PED::GET_PED_ARMOUR(self::ped);

		PLAYER::SET_PLAYER_MODEL(self::id, ENTITY::GET_ENTITY_MODEL(target));
		script::get_current()->yield();
		PED::CLONE_PED_TO_TARGET(target, self::ped);
		ENTITY::SET_ENTITY_MAX_HEALTH(self::ped, max_health);
		ENTITY::SET_ENTITY_HEALTH(self::ped, current_health, 0);
		PED::SET_PED_ARMOUR(self::ped, current_armor);
	}

	inline Ped spawn(ePedType pedType, Hash hash, Hash clone, Vector3 location, float heading, bool is_networked = true)
	{
		for (uint8_t i = 0; !STREAMING::HAS_MODEL_LOADED(hash) && i < 100; i++)
		{
			STREAMING::REQUEST_MODEL(hash);
			script::get_current()->yield();
		}

		if (!STREAMING::HAS_MODEL_LOADED(hash))
		{
			return 0;
		}

		auto ped = PED::CREATE_PED(pedType, hash, location.x, location.y, location.z, heading, is_networked, false);

		script::get_current()->yield();

		if (clone)
		{
			PED::CLONE_PED_TO_TARGET(clone, ped);
		}

		STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(hash);

		return ped;
	}

	inline bool requestAnimClipset(const char *animName)
	{
		int tick = 0;
		while (!STREAMING::HAS_ANIM_SET_LOADED(animName) && tick <= 25)
		{
			STREAMING::REQUEST_ANIM_SET(animName);
			tick++;
		}
		if (STREAMING::HAS_ANIM_SET_LOADED(animName))
		{
			return true;
		}
		return false;
	}

	inline void setPlayerWalkingStyle(const char *animName)
	{
		bool isLoaded = requestAnimClipset(animName);
		if (isLoaded)
			PED::SET_PED_MOVEMENT_CLIPSET(PLAYER::PLAYER_PED_ID(), animName, 1.0f);
	}

	inline void play_animation(Ped target, const char *anim_dictionary, const char *anim_name, int flag = ANIM_FLAG_NORMAL)
	{
		if (!entity::take_control_of(target))
		{
			g_notification_service->push_warning("Animation", "Failed to take control of target.");
			return;
		}
		size_t count = 0;
		do
		{
			STREAMING::REQUEST_ANIM_DICT(anim_dictionary);
			if (count++ == 100)
			{
				g_notification_service->push_warning("Animation", "Failed to request anim dict.");
				return;
			}
			script::get_current()->yield();
		} while (!STREAMING::HAS_ANIM_DICT_LOADED(anim_dictionary));
		TASK::TASK_PLAY_ANIM(target, anim_dictionary, anim_name, 8.0f, 0.0f, -1, flag, 0, false, false, false);
		g_notification_service->push("Animation", "Play animation success.");
	}
}