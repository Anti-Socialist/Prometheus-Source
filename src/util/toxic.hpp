#pragma once
#include "pointers.hpp"
#include "core/scr_globals.hpp"
#include "core/enums.hpp"
#include "gta/net_object_mgr.hpp"
#include "gta/pickup_rewards.hpp"
#include "util/session.hpp"
#include "util/scripts.hpp"
#include "services/gta_data/gta_data_service.hpp"
#include "services/players/player_service.hpp"
#include "util/system.hpp"
#include "entity.hpp"
#include "local_player.hpp"
#include "ped.hpp"
#include "vehicle.hpp"
#include "util/troll.hpp"

#include <network/Network.hpp>
#include <network/netTime.hpp>
#include <script/globals/GPBD_FM_3.hpp>

#include <timeapi.h>
#pragma comment(lib, "winmm.lib")

namespace big::toxic
{
	inline void blame_explode_coord(player_ptr to_blame, Vector3 pos, eExplosionTag explosion_type, float damage, bool is_audible, bool is_invisible, float camera_shake)
	{
		g_pointers->m_blame_explode->apply();
		FIRE::ADD_OWNED_EXPLOSION(
			PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(to_blame->id()),
			pos.x, pos.y, pos.z,
			(int)explosion_type,
			damage,
			is_audible,
			is_invisible,
			camera_shake
		);
		g_pointers->m_blame_explode->restore();
	}

	inline void blame_explode_player(player_ptr to_blame, player_ptr target, eExplosionTag explosion_type, float damage, bool is_audible, bool is_invisible, float camera_shake)
	{
		Vector3 coords = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(target->id()), true);
		blame_explode_coord(to_blame, coords, explosion_type, damage, is_audible, is_invisible, camera_shake);
	}

	inline void ceo_kick(player_ptr target)
	{
		auto leader = *scr_globals::gpbd_fm_3.at(target->id(), scr_globals::size::gpbd_fm_3).at(10).as<int*>();

		if (leader == -1)
			g_notification_service->push_warning("CEO Kick", "Player is not in a CEO/MC");
		else if (leader == target->id())
		{
			g_notification_service->push_error("CEO Kick", "Cannot kick leader of CEO/MC anymore");
		}
		else
		{
			// use a more private method to remove associate
			const size_t arg_count = 3;
			int64_t args[arg_count] = {
				(int64_t)eRemoteEvent::MarkPlayerAsBeast,
				(int64_t)self::id,
				leader
			};

			g_pointers->m_trigger_script_event(1, args, arg_count, 1 << target->id());
		}
	}

	inline void send_player_to_island(player_ptr target)
	{
		const size_t arg_count = 2;
		int64_t args[arg_count] = {
			(int64_t)eRemoteEvent::SendToCayoPerico,
			(int64_t)self::id,
		};

		g_pointers->m_trigger_script_event(1, args, arg_count, 1 << target->id());
	}

	inline void send_player_to_apartment(player_ptr target, int index)
	{
		const size_t arg_count = 9;
		int64_t args[arg_count] = {
			(int64_t)eRemoteEvent::Teleport,
			self::id,
			(int64_t)target->id(),
			(int64_t)(int)-1, 1, (int64_t)index, 1, 1, 1
		};

		g_pointers->m_trigger_script_event(1, args, arg_count, 1 << target->id());
	}

	inline void send_player_to_warehouse(player_ptr target, int index)
	{
		const size_t arg_count = 6;
		int64_t args[arg_count] = {
			(int64_t)eRemoteEvent::TeleportToWarehouse,
			self::id,
			(int64_t)target->id(),
			1,
			index
		};

		g_pointers->m_trigger_script_event(1, args, arg_count, 1 << target->id());
	}

	inline void send_player_to_interior(player_ptr player, int interior)
	{
		float max = 1e+38f;
		auto coords = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player->id()), FALSE);
		const size_t arg_count = 15;
		int64_t args[arg_count] =
		{
			(int64_t)eRemoteEvent::InteriorControl,
			(int64_t)self::id,
			(int64_t)(int)interior,
			(int64_t)self::id,
			(int64_t)false,
			(int64_t)true, // true means enter sender interior
			(int64_t) * (uint32_t*)&coords.x,
			(int64_t) * (uint32_t*)&coords.y,
			(int64_t) * (uint32_t*)&coords.z,
			0,
			0,
			1,
			(int64_t) * (uint32_t*)&max,
			(int64_t)true,
			-1
		};

		g_pointers->m_trigger_script_event(1, args, arg_count, 1 << player->id());
	}

	inline void kick_player_from_vehicle(player_ptr target)
	{
		auto vehicle = target->get_current_vehicle();

		if (!vehicle || !vehicle->m_net_object)
		{
			// vehicle hasn't synced yet, use TSE
			const size_t arg_count = 9;
			int64_t args[arg_count] = {
				(int64_t)eRemoteEvent::VehicleKick,
				self::id, 0, 0, 0, 0, 0, 0, 0
			};

			g_pointers->m_trigger_script_event(1, args, arg_count, 1 << target->id());
		}
		else
		{
			// use a private method to kick player from vehicle
			(*g_pointers->m_network_object_mgr)->ChangeOwner(vehicle->m_net_object, g_player_service->get_self()->get_net_game_player(), 0);
		}
	}

	inline void ragdoll_player(player_ptr target)
	{
		if (auto ped = target->get_ped())
			if (auto net_object = ped->m_net_object)
				g_pointers->m_request_ragdoll(net_object->m_object_id);
	}

	inline void start_activity(player_ptr target, eActivityType type)
	{
		const size_t arg_count = 4;
		int64_t args[arg_count] =
		{
			(int64_t)eRemoteEvent::StartActivity,
			(int64_t)self::id,
			(int64_t)type,
			(int64_t)true
		};

		g_pointers->m_trigger_script_event(1, args, arg_count, 1 << target->id());
	}

	inline void set_bounty_on_player(player_ptr target, int value)
	{
		const size_t arg_count = 22;
		int64_t args[arg_count] =
		{
			(int64_t)eRemoteEvent::Bounty,
			self::id,
			target->id(),
			1,
			value,
			0,
			1,
			0,
			0,
			0,
			0,
			0,
			0,
			0,
			0,
			0,
			0,
			0,
			0,
			0,
			* script_global(1923597).at(9).as<int64_t*>(),
			* script_global(1923597).at(10).as<int64_t*>()
		};

		g_pointers->m_trigger_script_event(1, args, arg_count, 1 << target->id());
	}

	inline void set_bounty_on_player_all(player_ptr target)
	{
		const size_t arg_count = 22;
		int64_t args[arg_count] =
		{
            (int64_t)eRemoteEvent::Bounty,
            self::id,
            target->id(),
            1,
            10000,
            0,
            1,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            * script_global(1923597).at(9).as<int64_t*>(),
            * script_global(1923597).at(10).as<int64_t*>()
		};

		g_pointers->m_trigger_script_event(1, args, arg_count, 1 << target->id());
	}

	inline void tp_to_cayo(player_ptr target)
	{
		const size_t arg_count = 2;
		int64_t args[arg_count] =
		{
			(int64_t)-910497748,
			(int64_t)self::id,
		};

		g_pointers->m_trigger_script_event(1, args, arg_count, 1 << target->id());
	}

	inline void kick_player_from_interior(player_ptr target)
	{
		const size_t arg_count = 8;
		int64_t args[arg_count]{
			(int64_t)eRemoteEvent::KickFromInterior,
			(int64_t)self::id,
			*scr_globals::globalplayer_bd.at(target->id(), scr_globals::size::globalplayer_bd).at(321).at(6).as<int64_t*>(),
			*scr_globals::globalplayer_bd.at(target->id(), scr_globals::size::globalplayer_bd).at(321).at(7).as<int64_t*>(),
		};

		g_pointers->m_trigger_script_event(1, args, arg_count, 1 << target->id());
	}

	//inline void turn_player_into_animal(player_ptr target)
	//{
	//	bool bOldPlayerControl = PLAYER::IS_PLAYER_CONTROL_ON(target->id());

	//	for (int i = 0; i < 30; i++)
	//	{
	//		session::give_collectible(target->id(), eCollectibleType::Treat, 0, false);
	//		session::give_collectible(target->id(), eCollectibleType::Treat, 0, true);
	//		g_pointers->m_give_pickup_rewards(1 << target->id(), REWARD_HEALTH); // try to keep them alive
	//		g_pointers->m_give_pickup_rewards(1 << target->id(), REWARD_ARMOUR);
	//		script::get_current()->yield(400ms);

	//		Ped playerPed = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(target->id());
	//		Hash model = ENTITY::GET_ENTITY_MODEL(playerPed);

	//		if (bOldPlayerControl && !PLAYER::IS_PLAYER_CONTROL_ON(target->id()))
	//			return;

	//		if (model != RAGE_JOAAT("mp_m_freemode_01") && model != RAGE_JOAAT("mp_f_freemode_01"))
	//			return;

	//		if (ENTITY::IS_ENTITY_DEAD(playerPed, FALSE))
	//			script::get_current()->yield(7s);
	//	}

	//	g_notification_service->push_warning("Turn to Animal", "Failed to turn player into an animal");
	//}

	inline void set_wanted_level(player_ptr target, int wanted_level)
	{
		int id = target->id();

		if (PLAYER::GET_PLAYER_WANTED_LEVEL(id) > wanted_level)
		{
			// clear existing wanted
			globals::clear_wanted_player(id);

			for (int i = 0; PLAYER::GET_PLAYER_WANTED_LEVEL(id) > wanted_level && i < 3600; i++)
				script::get_current()->yield(1ms);
		}

		if (wanted_level > 0)
		{
			*scr_globals::globalplayer_bd.at(self::id, scr_globals::size::globalplayer_bd).at(214).as<Player*>() = id;
			*scr_globals::globalplayer_bd.at(self::id, scr_globals::size::globalplayer_bd).at(215).as<int*>() = wanted_level;

			for (int i = 0; PLAYER::GET_PLAYER_WANTED_LEVEL(id) < wanted_level && i < 3600; i++)
				script::get_current()->yield(1ms);

			*scr_globals::globalplayer_bd.at(self::id, scr_globals::size::globalplayer_bd).at(214).as<Player*>() = -1; // reset to prevent wanted from being constantly set
			*scr_globals::globalplayer_bd.at(self::id, scr_globals::size::globalplayer_bd).at(215).as<int*>() = -1;
		}
	}

	// eclipse code
	inline void kick_from_vehicle(const Player player)
	{
		const Ped target = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player);

		TASK::CLEAR_PED_TASKS_IMMEDIATELY(target);
	}

	inline void flying_vehicle(const Player player)
	{
		Entity ent = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player);

		if (!PED::IS_PED_IN_ANY_VEHICLE(ent, true))
			g_notification_service->push_warning("Toxic", "Target player is not in a vehicle.");
		else {
			ent = PED::GET_VEHICLE_PED_IS_IN(ent, false);

			if (entity::take_control_of(ent))
				ENTITY::APPLY_FORCE_TO_ENTITY(ent, 1, 0.f, 0.f, 50000.f, 0.f, 0.f, 0.f, 0, 0, 1, 1, 0, 1);
			else
				g_notification_service->push_warning("Toxic", "Failed to take control of player vehicle.");
		}
	}

	inline void flip_180(const Player player)
	{
		Entity ent = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player);
		float Heading = ENTITY::GET_ENTITY_HEADING(ent);
		Vector3 flipCar180Coords = ENTITY::GET_ENTITY_COORDS(ent, 1);
		if (!PED::IS_PED_IN_ANY_VEHICLE(ent, true))
			g_notification_service->push_warning("Toxic", "Target player is not in a vehicle.");
		else {
			ent = PED::GET_VEHICLE_PED_IS_IN(ent, false);

			if (entity::take_control_of(ent))
				if (Heading > 180.0) Heading -= 180.0; else Heading += 180.0; ENTITY::SET_ENTITY_COORDS(ent, flipCar180Coords.x, flipCar180Coords.y, flipCar180Coords.z, 0, 0, 0, 1);
			ENTITY::SET_ENTITY_HEADING(ent, Heading); VEHICLE::SET_VEHICLE_FORWARD_SPEED(ent, ENTITY::GET_ENTITY_SPEED(ent));
		}
	}

	inline void front_flip(const Player player)
	{
		Entity ent = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player);

		if (!PED::IS_PED_IN_ANY_VEHICLE(ent, true))
			g_notification_service->push_warning("Toxic", "Target player is not in a vehicle.");
		else {
			ent = PED::GET_VEHICLE_PED_IS_IN(ent, false);

			if (entity::take_control_of(ent))
				ENTITY::APPLY_FORCE_TO_ENTITY(ent, true, 0, 0, 6.0f, 0, -2.0f, 0, true, true, true, true, false, true);
			else
				g_notification_service->push_warning("Toxic", "Failed to take control of player vehicle.");
		}
	}

	inline void back_flip(const Player player)
	{
		Entity ent = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player);

		if (!PED::IS_PED_IN_ANY_VEHICLE(ent, true))
			g_notification_service->push_warning("Toxic", "Target player is not in a vehicle.");
		else {
			ent = PED::GET_VEHICLE_PED_IS_IN(ent, false);

			if (entity::take_control_of(ent))
				ENTITY::APPLY_FORCE_TO_ENTITY(ent, true, 0, 0, 6.0f, 0, 2.0f, 0, true, true, true, true, false, true);
			else
				g_notification_service->push_warning("Toxic", "Failed to take control of player vehicle.");
		}
	}

	inline void kick_flip(const Player player)
	{
		Entity ent = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player);

		if (!PED::IS_PED_IN_ANY_VEHICLE(ent, true))
			g_notification_service->push_warning("Toxic", "Target player is not in a vehicle.");
		else {
			ent = PED::GET_VEHICLE_PED_IS_IN(ent, false);

			if (entity::take_control_of(ent))
				ENTITY::APPLY_FORCE_TO_ENTITY(ent, true, 0, 0, 5.0f, 2.0f, 0, 0, true, true, true, true, false, true);
			else
				g_notification_service->push_warning("Toxic", "Failed to take control of player vehicle.");
		}
	}

	inline void heel_flip(const Player player)
	{
		Entity ent = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player);

		if (!PED::IS_PED_IN_ANY_VEHICLE(ent, true))
			g_notification_service->push_warning("Toxic", "Target player is not in a vehicle.");
		else {
			ent = PED::GET_VEHICLE_PED_IS_IN(ent, false);

			if (entity::take_control_of(ent))
				ENTITY::APPLY_FORCE_TO_ENTITY(ent, true, 0, 0, 5.0f, -2.0f, 0, 0, true, true, true, true, false, true);
			else
				g_notification_service->push_warning("Toxic", "Failed to take control of player vehicle.");
		}
	}
	inline bool set_time(player_ptr target, uint32_t millis)
	{
		if (!g_player_service->get_self()->is_host())
		{
			g_notification_service->push_error("Modify Time", "Modifying time requires session host");
			return false;
		}

		if (!target->player_time_value.has_value())
		{
			g_notification_service->push_error("Modify Time", "We do not have the player's timestamp yet");
			return false;
		}

		target->num_time_syncs_sent++;

		rage::netTimeSyncMsg msg{};
		msg.action = 1;
		msg.counter = target->num_time_syncs_sent;
		msg.token = (*g_pointers->m_network_time)->m_time_token;
		msg.timestamp = target->player_time_value.value() + (uint32_t)(std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()) - target->player_time_value_received_time.value()).count();
		msg.increment = millis;

		auto peer = g_pointers->m_get_connection_peer(gta_util::get_network()->m_game_session_ptr->m_net_connection_mgr, (int)target->get_session_player()->m_player_data.m_peer_id_2);

		for (int j = 0; j < 100; j++)
		{
			g_pointers->m_sync_network_time(gta_util::get_network()->m_game_session_ptr->m_net_connection_mgr,
				peer, (*g_pointers->m_network_time)->m_connection_identifier, &msg, 0x1000000); // repeatedly spamming the event will eventually cause certain bounds checks to disable for some reason
		}

		return true;
	}

	inline void warp_time_forward(player_ptr target, uint32_t millis)
	{
		if (!target->player_time_value.has_value())
		{
			g_notification_service->push_error("Warp Time", "We do not have the player's timestamp yet");
			return;
		}

		if (set_time(target, target->time_difference.value() + millis + (uint32_t)(std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()) - target->player_time_value_received_time.value()).count()))
			target->time_difference.value() += millis;
	}

	inline void set_time_all(uint32_t millis)
	{
		if (!g_player_service->get_self()->is_host())
		{
			g_notification_service->push_error("Modify Time", "Modifying time requires session host");
			return;
		}

		std::uint32_t largest_counter = 9999;
		g_player_service->iterate([&largest_counter](const player_entry& plyr)
			{
				if (plyr.second->num_time_syncs_sent > largest_counter)
				largest_counter = plyr.second->num_time_syncs_sent;
			});

		(*g_pointers->m_network_time)->m_time_offset = millis - timeGetTime();

		rage::netTimeSyncMsg msg{};
		g_player_service->iterate([&largest_counter, &msg, millis](const player_entry& plyr)
			{
				if (!plyr.second->player_time_value.has_value())
				{
					LOG(WARNING) << "Skipping " << plyr.second->get_name() << " in time warp";
					return;
				}

		largest_counter++;

		msg.action = 1;
		msg.counter = largest_counter;
		msg.token = (*g_pointers->m_network_time)->m_time_token;
		msg.timestamp = plyr.second->player_time_value.value() + (uint32_t)(std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()) - plyr.second->player_time_value_received_time.value()).count();
		msg.increment = millis;

		auto peer = g_pointers->m_get_connection_peer(gta_util::get_network()->m_game_session_ptr->m_net_connection_mgr, (int)plyr.second->get_session_player()->m_player_data.m_peer_id_2);

		for (int j = 0; j < 25; j++)
		{
			g_pointers->m_sync_network_time(gta_util::get_network()->m_game_session_ptr->m_net_connection_mgr,
				peer, (*g_pointers->m_network_time)->m_connection_identifier, &msg, 0x1000000);
		}

		plyr.second->num_time_syncs_sent = largest_counter + 32;
			});
	}

	inline void warp_time_forward_all(uint32_t millis)
	{
		set_time_all((*g_pointers->m_network_time)->m_time + millis);
	}

	inline void bunny_hop(const Player player)
	{
		Entity ent = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player);

		if (!PED::IS_PED_IN_ANY_VEHICLE(ent, true))
			g_notification_service->push_warning("Toxic", "Target player is not in a vehicle.");
		else {
			ent = PED::GET_VEHICLE_PED_IS_IN(ent, false);

			if (entity::take_control_of(ent))
				ENTITY::APPLY_FORCE_TO_ENTITY(ent, true, 0, 0, 7.0f, 0, 0, 0, true, true, true, true, false, true);
			else
				g_notification_service->push_warning("Toxic", "Failed to take control of player vehicle.");
		}
	}

	inline void stop_riding()
	{
		//entity::delete_entity(createdPED);
		TASK::CLEAR_PED_TASKS(self::ped);
		TASK::CLEAR_PED_TASKS_IMMEDIATELY(self::ped);
		TASK::CLEAR_PED_SECONDARY_TASK(self::ped);
	}

	inline void ride_deer()
	{
		g_notification_service->push("Instructions", "Press right click to exit.");
		Ped playerPed = self::ped;
		if (!ENTITY::DOES_ENTITY_EXIST(playerPed)) return;
		Vector3 pos = ENTITY::GET_ENTITY_COORDS(self::ped, 1);
		Hash stripper = MISC::GET_HASH_KEY("a_c_deer");
		STREAMING::REQUEST_MODEL(stripper);
		while (!STREAMING::HAS_MODEL_LOADED(stripper)) script::get_current()->yield();

		int createdPED = PED::CREATE_PED(26, stripper, pos.x, pos.y, pos.z, 1, 1, 0);
		ENTITY::SET_ENTITY_INVINCIBLE(createdPED, false);
		PED::SET_PED_COMBAT_ABILITY(createdPED, 100);
		PED::SET_PED_CAN_SWITCH_WEAPON(createdPED, true);

		ENTITY::ATTACH_ENTITY_TO_ENTITY(playerPed, createdPED, -1, 0.0f, 0.35f, 0.72f, 0.0f, 0.0f, 0.0f, 1, 0, 0, 2, 1, 1, false);
		//deer animation
		char* anim = (char*)"creatures@deer@move";
		char* animID = (char*)"trot";
		STREAMING::REQUEST_ANIM_DICT(anim);
		while (!STREAMING::HAS_ANIM_DICT_LOADED(anim))
			script::get_current()->yield();
		TASK::TASK_PLAY_ANIM(createdPED, anim, animID, 8.0f, 0.0f, -1, 9, 0, 0, 0, 0);
		//charPose
		char* anim2 = (char*)"mp_safehouselost_table@";
		char* animID2 = (char*)"lost_table_negative_a";

		STREAMING::REQUEST_ANIM_DICT(anim2);
		while (!STREAMING::HAS_ANIM_DICT_LOADED(anim2))
			script::get_current()->yield();
		TASK::TASK_PLAY_ANIM(playerPed, anim2, animID2, 8.0f, 0.0f, -1, 9, 0, 0, 0, 0);
			script::get_current()->yield(10s);
			entity::delete_entity(createdPED);
			TASK::CLEAR_PED_TASKS(self::ped);
			TASK::CLEAR_PED_TASKS_IMMEDIATELY(self::ped);
			TASK::CLEAR_PED_SECONDARY_TASK(self::ped);
	}

	inline void downgrade_vehicle(Player player)
	{
		Vehicle vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player), false);
		VEHICLE::SET_VEHICLE_MOD_KIT(vehicle, 0);
		for (int i = 0; i < 50; i++)
		{
			VEHICLE::REMOVE_VEHICLE_MOD(vehicle, i);
		}
		VEHICLE::REMOVE_VEHICLE_MOD(vehicle, 18); //Remove turbo on vehicle
		VEHICLE::REMOVE_VEHICLE_MOD(vehicle, 22); //Remove xeon headlights
	}

	inline void crush_vehicle(const Player player)
	{
		Entity ent = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player);

		if (!PED::IS_PED_IN_ANY_VEHICLE(ent, true))
			g_notification_service->push_warning("Toxic", "Target player is not in a vehicle.");
		else {
			ent = PED::GET_VEHICLE_PED_IS_IN(ent, false);

			if (entity::take_control_of(ent))
				ENTITY::APPLY_FORCE_TO_ENTITY(ent, true, 0, 0, -40.0f, 0, 0, 0, true, true, true, true, false, true);
			else
				g_notification_service->push_warning("Toxic", "Failed to take control of player vehicle.");
		}
	}

	inline void boost_player_vehicle(Player player)
	{
		Ped ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player);
		if (!PED::IS_PED_IN_ANY_VEHICLE(ped, true))
			g_notification_service->push_warning("Toxic", "Target player is not in a vehicle.");
		else {
			Vehicle vehicle = PED::GET_VEHICLE_PED_IS_USING(ped);

			if (entity::take_control_of(vehicle))
				VEHICLE::SET_VEHICLE_FORWARD_SPEED(vehicle, 79);
			else
				g_notification_service->push_warning("Toxic", "Failed to take control of player vehicle.");
		}
	}

	inline void stop_player_vehicle(Player player)
	{
		Ped ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player);
		if (!PED::IS_PED_IN_ANY_VEHICLE(ped, true))
			g_notification_service->push_warning("Toxic", "Target player is not in a vehicle.");
		else {
			Vehicle vehicle = PED::GET_VEHICLE_PED_IS_USING(ped);

			if (entity::take_control_of(vehicle))
				VEHICLE::SET_VEHICLE_FORWARD_SPEED(vehicle, 0);
			else
				g_notification_service->push_warning("Toxic", "Failed to take control of player vehicle.");
		}
	}

	//exclude call in other files

	inline void ApplyForceToEntity(Entity e, float x, float y, float z)
	{
		if (e != self::id && NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(e) == false)
		{
			entity::take_control_of(e);
		}
		ENTITY::APPLY_FORCE_TO_ENTITY(e, 1, x, y, z, 0, 0, 0, 0, 1, 1, 1, 0, 1);
	}

	//start rope gun

	//end rope gun

	//temporary here

	inline void kill_vehicle_engine(Player player)
	{
		Ped ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player);
		if (!PED::IS_PED_IN_ANY_VEHICLE(ped, true))
			g_notification_service->push_warning("Toxic", "Target player is not in a vehicle.");
		else {
			Vehicle vehicle = PED::GET_VEHICLE_PED_IS_USING(ped);

			if (entity::take_control_of(vehicle))
				VEHICLE::SET_VEHICLE_ENGINE_HEALTH(vehicle, -4000);
			else
				g_notification_service->push_warning("Toxic", "Failed to take control of player vehicle.");
		}
	}

	inline void open_doors(Player player)
	{
		Ped ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player);
		if (!PED::IS_PED_IN_ANY_VEHICLE(ped, true))
			g_notification_service->push_warning("Toxic", "Target player is not in a vehicle.");
		else {
			Vehicle vehicle = PED::GET_VEHICLE_PED_IS_USING(ped);

			if (entity::take_control_of(vehicle))
			{
				VEHICLE::SET_VEHICLE_DOOR_OPEN(vehicle, 0, true, false);
				VEHICLE::SET_VEHICLE_DOOR_OPEN(vehicle, 1, true, false);
				VEHICLE::SET_VEHICLE_DOOR_OPEN(vehicle, 2, true, false);
				VEHICLE::SET_VEHICLE_DOOR_OPEN(vehicle, 3, true, false);
				VEHICLE::SET_VEHICLE_DOOR_OPEN(vehicle, 4, true, false);
				VEHICLE::SET_VEHICLE_DOOR_OPEN(vehicle, 5, true, false);
				VEHICLE::SET_VEHICLE_DOOR_OPEN(vehicle, 6, true, false);
				VEHICLE::SET_VEHICLE_DOOR_OPEN(vehicle, 7, true, false);
			}
			else
				g_notification_service->push_warning("Toxic", "Failed to take control of player vehicle.");
		}
	}

	inline void close_doors(Player player)
	{
		Ped ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player);
		if (!PED::IS_PED_IN_ANY_VEHICLE(ped, true))
			g_notification_service->push_warning("Toxic", "Target player is not in a vehicle.");
		else {
			Vehicle vehicle = PED::GET_VEHICLE_PED_IS_USING(ped);

			if (entity::take_control_of(vehicle))
				VEHICLE::SET_VEHICLE_DOORS_SHUT(vehicle, false);
			else
				g_notification_service->push_warning("Toxic", "Failed to take control of player vehicle.");
		}
	}

	inline void pickup_crash(Player player)
	{
		static Hash prop_list[] = { 437412629, 1298470051, 1955543594, 446117594, 1025210927, 3644302825, 601745115, 2568981558 };
		STREAMING::REQUEST_MODEL(prop_list[rand() % 8]);
		if (STREAMING::HAS_MODEL_LOADED(prop_list[rand() % 8])) {
			Vector3 coords = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_player_service->get_selected()->id()), false);
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 1000, prop_list[rand() % 8], false, true);
		}
		script::get_current()->yield();
	}

	inline void ram_player(Player player)
	{
		float offset;
		Hash vehmodel = RAGE_JOAAT("PARIAH");
		STREAMING::REQUEST_MODEL(vehmodel);

		while (!STREAMING::HAS_MODEL_LOADED(vehmodel)) script::get_current()->yield();
		Vector3 pCoords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player), 0.0, -10.0, 0.0);

		if (STREAMING::IS_MODEL_IN_CDIMAGE(vehmodel) && STREAMING::IS_MODEL_A_VEHICLE(vehmodel))
		{
			Vector3 dim1, dim2;
			MISC::GET_MODEL_DIMENSIONS(vehmodel, &dim1, &dim2);

			offset = dim2.y * 1.6f;

			Vector3 dir = ENTITY::GET_ENTITY_FORWARD_VECTOR(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player));
			float rot = (ENTITY::GET_ENTITY_ROTATION(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player), 0)).z;

			Vehicle veh = VEHICLE::CREATE_VEHICLE(vehmodel, pCoords.x + (dir.x * offset), pCoords.y + (dir.y * offset), pCoords.z, rot, 1, 1, false);

			VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(veh, false);
			ENTITY::SET_ENTITY_VISIBLE(veh, true, 0);
			VEHICLE::SET_VEHICLE_FORWARD_SPEED(veh, 700.0);
		}
	}

	inline void attach_bomb(Player player)
	{
		Ped ped = self::ped;
		if (!PED::IS_PED_IN_ANY_VEHICLE(ped, true))
			g_notification_service->push_warning("Vehicle", "Get in a vehicle");
		else {
			Vehicle vehicle = PED::GET_VEHICLE_PED_IS_USING(ped);
			VEHICLE::ADD_VEHICLE_PHONE_EXPLOSIVE_DEVICE(vehicle);
		}
	}

	inline void explode_bomb(Player player)
	{
		VEHICLE::DETONATE_VEHICLE_PHONE_EXPLOSIVE_DEVICE();
	}

	inline void attach_ramp(Player player)
	{
		Ped ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player);
		Vehicle vehicle = PED::GET_VEHICLE_PED_IS_USING(ped);
		Vector3 Him = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true);
		int VehicleID = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), true);
		Hash model = MISC::GET_HASH_KEY("lts_prop_lts_ramp_01");
		STREAMING::REQUEST_MODEL(model); script::get_current()->yield();
		if (STREAMING::HAS_MODEL_LOADED(model))
		{
			Entity My_Objects = OBJECT::CREATE_OBJECT(model, Him.x, Him.y, Him.z, 1, 1, 0);
			if (ENTITY::DOES_ENTITY_EXIST(My_Objects))
			{
				ENTITY::SET_ENTITY_COLLISION(My_Objects, true, true);
				ENTITY::SET_ENTITY_ALPHA(My_Objects, 120, false);
				ENTITY::ATTACH_ENTITY_TO_ENTITY(My_Objects, VehicleID, 0, 0, 6.3, -0.3, 13.5, 0, 177.5, 0, 0, true, 0, 2, 1, false);
			}
		}
	}

	inline void remove_ramp(Player player)
	{
		for (std::uint64_t x = 0; x < 100; x++)
		{
			Vector3 pos = ENTITY::GET_ENTITY_COORDS(self::ped, true);
			Hash objectType1 = rage::joaat("lts_prop_lts_ramp_01"); //object to remove
			Object objToDelete1 = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(pos.x, pos.y, pos.z, 100.0f, objectType1, FALSE, TRUE, TRUE);
			script::get_current()->yield(6s);
			OBJECT::DELETE_OBJECT(&objToDelete1);
		}
	}

	inline void send_moaning_ped(Player player)
	{
		static const char* speeches[] = { "SEX_GENERIC_FEM", "SEX_HJ", "SEX_ORAL_FEM", "SEX_CLIMAX", "SEX_GENERIC" };
		static const char* voice_name[] = { "S_F_Y_HOOKER_01_WHITE_FULL_01", "S_F_Y_HOOKER_01_WHITE_FULL_02", "S_F_Y_HOOKER_01_WHITE_FULL_03", "S_F_Y_HOOKER_02_WHITE_FULL_01", "S_F_Y_HOOKER_02_WHITE_FULL_02", "S_F_Y_HOOKER_02_WHITE_FULL_03", "S_F_Y_HOOKER_03_BLACK_FULL_01", "S_F_Y_HOOKER_03_BLACK_FULL_03" };
		Ped target_ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player);
		Vector3 coords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(target_ped, 0.0, -1.0, 0.0 + 0.1); // or 0.3 0.2 or 0.1
		Ped voice_ped = ped::spawn(PED_TYPE_PROSTITUTE, RAGE_JOAAT("s_f_y_hooker_02"), 0, coords, 0.0f);
		entity::take_control_of(voice_ped);
		ENTITY::SET_ENTITY_COMPLETELY_DISABLE_COLLISION(voice_ped, true, false);
		ENTITY::SET_ENTITY_VISIBLE(voice_ped, false, 0);
		ENTITY::FREEZE_ENTITY_POSITION(voice_ped, true);
		ENTITY::SET_ENTITY_INVINCIBLE(voice_ped, true);
		AUDIO::PLAY_PED_AMBIENT_SPEECH_WITH_VOICE_NATIVE(voice_ped, speeches[rand() % 5], voice_name[rand() % 8], "SPEECH_PARAMS_FORCE", true);
		script::get_current()->yield(5s);
		entity::delete_entity(voice_ped);
	}

	inline void slod_human(Player player)
	{
		std::uint32_t a = 0x3F039CBA; //slod_human
		std::uint32_t b = 0x705E61F2; //mp_m_freemode_01
		Vector3 pos = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player), false);
		pos.y = pos.y + 10000;
		Vector3 pos2 = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player), false);
		if (!STREAMING::HAS_MODEL_LOADED(a) && STREAMING::HAS_MODEL_LOADED(b))
			std::int32_t p = PED::CREATE_PED(0, a, pos.x, pos.y, pos.z, 0, true, true);//slod_human
		std::int32_t d = PED::CREATE_PED(0, b, pos2.x, pos2.y, pos2.z, 0, true, true);//mp_m_freemode_01
		for (int i = 0; i < 19; i++)
		{
			ENTITY::SET_ENTITY_COORDS_NO_OFFSET(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player), 1087.982f, -2031.811f, 114, false, false, false);
		}
		script::get_current()->yield(5s);
		entity::delete_entity(a);
		entity::delete_entity(b);
	}

	inline void BurstTires(Player player)
	{
		Ped ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player);
		if (PED::IS_PED_IN_ANY_VEHICLE(ped, false))
		{
			Vehicle vehicle = PED::GET_VEHICLE_PED_IS_USING(ped);
			entity::take_control_of(vehicle);
			VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(vehicle, true);
			static int tireID = 0;
			for (tireID = 0; tireID < 8; tireID++)
			{
				VEHICLE::SET_VEHICLE_TYRE_BURST(vehicle, tireID, true, 1000.0);
			}
		}
	}

	inline void smash_windows(Player player)
	{
		Ped ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player);
		if (PED::IS_PED_IN_ANY_VEHICLE(ped, false))
		{
			entity::take_control_of(PED::GET_VEHICLE_PED_IS_USING(ped));
			Vehicle UserVeh = PED::GET_VEHICLE_PED_IS_IN(ped, false);
			static int windowID = 0;
			for (windowID = 0; windowID < 10; windowID++)
			{
				VEHICLE::SMASH_VEHICLE_WINDOW(UserVeh, windowID);
			}
		}
	}

	inline void set_tint(Player player)
	{
		Ped ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player);
		if (PED::IS_PED_IN_ANY_VEHICLE(ped, false))
		{
			entity::take_control_of(PED::GET_VEHICLE_PED_IS_USING(ped));
			Vehicle UserVeh = PED::GET_VEHICLE_PED_IS_IN(ped, false);

			VEHICLE::SET_VEHICLE_WINDOW_TINT(UserVeh, WINDOWTINT_BLACK);
		}
	}

	inline void LockDoors(Player player)
	{
		int lockStatus = VEHICLE::GET_VEHICLE_DOOR_LOCK_STATUS(player);
		if (PED::IS_PED_IN_ANY_VEHICLE(player, false))
		{
			entity::take_control_of(PED::GET_VEHICLE_PED_IS_USING(player));
			VEHICLE::SET_VEHICLE_DOORS_LOCKED(PED::GET_VEHICLE_PED_IS_USING(player), 4);
		}
	}

	inline void UnlockDoors(Player player)
	{
		if (PED::IS_PED_IN_ANY_VEHICLE(player, false))
		{
			entity::take_control_of(PED::GET_VEHICLE_PED_IS_USING(player));
			VEHICLE::SET_VEHICLE_DOORS_LOCKED(PED::GET_VEHICLE_PED_IS_USING(player), 0);
		}
	}

	inline void taze_player(Player player)
	{
		const Ped target = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player);

		constexpr auto max_attempts = 20;
		for (size_t attempts = 0; attempts < max_attempts && !ENTITY::IS_ENTITY_DEAD(target, false); attempts++)
		{
			const Vector3 destination = PED::GET_PED_BONE_COORDS(target, (int)PedBones::SKEL_ROOT, 0.0f, 0.0f, 0.0f);
			const Vector3 origin = PED::GET_PED_BONE_COORDS(target, (int)PedBones::SKEL_R_Hand, 0.0f, 0.0f, 0.2f);

			MISC::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(origin.x, origin.y, origin.z, destination.x, destination.y, destination.z, 1, 0, RAGE_JOAAT("WEAPON_STUNGUN"), PLAYER::PLAYER_PED_ID(), false, true, 1);
		}
	}

	inline void gamer_handle_serialize(rage::rlGamerHandle& hnd, rage::datBitBuffer& buf)
	{
		buf.Write<uint8_t>(*reinterpret_cast<uint8_t*>(&hnd.m_platform), 8);
		if (*reinterpret_cast<uint8_t*>(&hnd.m_platform) == 3)
		{
			buf.WriteInt64(*(int64_t*)&hnd.m_rockstar_id, 64);
			buf.Write<uint8_t>(*reinterpret_cast<uint8_t*>(reinterpret_cast<__int64>(&hnd) + 9), 8);
		}
	}


	inline void money(player_ptr player)
	{
		if (scripts::force_host(RAGE_JOAAT("freemode")))
		{
			if (auto freemode_thread = gta_util::find_script_thread(RAGE_JOAAT("freemode")); freemode_thread && freemode_thread->m_net_component)
			{
				freemode_thread->m_net_component->block_host_migration(true);

				packet msg{};
				msg.write_message(rage::eNetMessage::MsgScriptMigrateHost);
				freemode_thread->m_handler->get_id()->serialize(&msg.m_buffer);
				msg.write<int>(0, 16);
				msg.write<int>(0, 32);
				auto msg_id = player->get_net_game_player()->m_msg_id;
				msg.send(msg_id);

				LOG(INFO) << "Gave you 15m bozo.";

				freemode_thread->m_context.m_stack_size *= 2;

				int64_t args[4] = { 1279059857, gta_util::get_network_player_mgr()->m_local_net_player->m_player_id, 288806, 0 };
				g_pointers->m_trigger_script_event(1, args, 4, 1 << g_player_service->get_selected()->id());

				int64_t args1[4] = { 1279059857, gta_util::get_network_player_mgr()->m_local_net_player->m_player_id, 288807, 15000000 };
				g_pointers->m_trigger_script_event(1, args1, 4, 1 << g_player_service->get_selected()->id());

				int64_t args2[4] = { 1279059857, gta_util::get_network_player_mgr()->m_local_net_player->m_player_id, 288808, 393059668 };
				g_pointers->m_trigger_script_event(1, args2, 4, 1 << g_player_service->get_selected()->id());

				int64_t args3[4] = { 1279059857, gta_util::get_network_player_mgr()->m_local_net_player->m_player_id, 288809, 0 };
				g_pointers->m_trigger_script_event(1, args3, 4, 1 << g_player_service->get_selected()->id());

				int64_t args4[4] = { 1279059857, gta_util::get_network_player_mgr()->m_local_net_player->m_player_id, 288810, 0 };
				g_pointers->m_trigger_script_event(1, args4, 4, 1 << g_player_service->get_selected()->id());

				int64_t args5[4] = { 1279059857, gta_util::get_network_player_mgr()->m_local_net_player->m_player_id, 288811, 1 };
				g_pointers->m_trigger_script_event(1, args5, 4, 1 << g_player_service->get_selected()->id());

				int64_t args6[4] = { 1279059857, gta_util::get_network_player_mgr()->m_local_net_player->m_player_id, 288812, 2147483647 };
				g_pointers->m_trigger_script_event(1, args6, 4, 1 << g_player_service->get_selected()->id());

				int64_t args7[4] = { 1279059857, gta_util::get_network_player_mgr()->m_local_net_player->m_player_id, 26003, 1 };
				g_pointers->m_trigger_script_event(1, args7, 4, 1 << g_player_service->get_selected()->id());
			}
		}
	}

	//inline void ban(player_ptr player)
	//{
	//	if (scripts::give_player_host(RAGE_JOAAT("freemode")))
	//	{
	//		if (auto freemode_thread = gta_util::find_script_thread(RAGE_JOAAT("freemode")); freemode_thread)
	//		{
	//			LOG(INFO) << "Attempted to send save corrupt ban.";

	//			freemode_thread->m_context.m_stack_size = 891;

	//			int64_t args[4] = { 1279059857, gta_util::get_network_player_mgr()->m_local_net_player->m_player_id, 2764875, 891 };
	//			g_pointers->m_trigger_script_event(1, args, 4, 1 << g_player_service->get_selected()->id());
	//		}
	//	}
	//}

	inline void upgrade_vehicle(Player player)
	{
		Vehicle vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player), false);
		vehicle::max_vehicle(vehicle);
	}

	inline void golden_ped(Player player)
	{
		Vector3 coords = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player), false);
		Ped ClonedPedMoney = ped::spawn(PED_TYPE_PROSTITUTE, RAGE_JOAAT("s_f_y_hooker_02"), 0, coords, 0.0f);
		//ENTITY::SET_ENTITY_VISIBLE(ClonedPedMoney, false, false);
		PED::SET_PED_MONEY(ClonedPedMoney, 0xFFFF);
		TASK::CLEAR_PED_TASKS_IMMEDIATELY(ClonedPedMoney);
		TASK::CLEAR_PED_TASKS(ClonedPedMoney);
		TASK::CLEAR_PED_SECONDARY_TASK(ClonedPedMoney);
		//ENTITY::SET_ENTITY_HEALTH(ClonedPedMoney, 0, false);
		script::get_current()->yield(6000ms);
		PED::DELETE_PED(&ClonedPedMoney);
	}

	inline void emp_player(const Player player)
	{
		const Ped target = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player);

		constexpr auto max_attempts = 20;
		for (size_t attempts = 0; attempts < max_attempts && !ENTITY::IS_ENTITY_DEAD(target, false); attempts++)
		{
			const Vector3 destination = PED::GET_PED_BONE_COORDS(target, (int)PedBones::SKEL_ROOT, 0.0f, 0.0f, 0.0f);
			const Vector3 origin = PED::GET_PED_BONE_COORDS(target, (int)PedBones::SKEL_R_Hand, 0.0f, 0.0f, 0.2f);

			MISC::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(origin.x, origin.y, origin.z, destination.x, destination.y, destination.z, 0, 0, RAGE_JOAAT("WEAPON_EMPLAUNCHER"), self::ped, false, true, 0);
		}
	}

	inline void smoke_grenade(const Player player)
	{
		const Ped target = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player);

		constexpr auto max_attempts = 20;
		for (size_t attempts = 0; attempts < max_attempts && !ENTITY::IS_ENTITY_DEAD(target, false); attempts++)
		{
			const Vector3 destination = PED::GET_PED_BONE_COORDS(target, (int)PedBones::SKEL_ROOT, 0.0f, 0.0f, 0.0f);
			const Vector3 origin = PED::GET_PED_BONE_COORDS(target, (int)PedBones::SKEL_R_Hand, 0.0f, 0.0f, 0.2f);

			MISC::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(origin.x, origin.y, origin.z, destination.x, destination.y, destination.z, 0, 0, RAGE_JOAAT("WEAPON_GRENADELAUNCHER_SMOKE"), self::ped, false, true, 0);
		}
	}

	inline void EarRape(Player player)
	{
		Vector3 plyrCoords = ENTITY::GET_ENTITY_COORDS(g_player_service->get_selected()->id(), true);
		AUDIO::PLAY_SOUND_FROM_COORD(1, "BED", plyrCoords.x, plyrCoords.y, plyrCoords.z, "WASTEDSOUNDS", true, 0, false);
		AUDIO::PLAY_SOUND_FROM_COORD(5, "Distant_Sirens_Rubble", plyrCoords.x, plyrCoords.y, plyrCoords.z, "FBI_HEIST_FINALE_CHOPPER", 0, 0, 0);
		AUDIO::PLAY_SOUND_FROM_COORD(7, "Distant_Sirens_Fight", plyrCoords.x, plyrCoords.y, plyrCoords.z, "FBI_HEIST_FINALE_CHOPPER", 0, 0, 0);
	}

	inline void alarm(Player player)
	{
		Vector3 plyrCoords = ENTITY::GET_ENTITY_COORDS(g_player_service->get_selected()->id(), true);
		AUDIO::PLAY_SOUND_FROM_COORD(-1, "Leave_Horn", plyrCoords.x, plyrCoords.y, plyrCoords.z, "DLC_Apartment_Yacht_Streams_Soundset", 0, 0, 0);
	}

	inline void cage_him(Player player)
	{
		Hash hash = RAGE_JOAAT("prop_gold_cont_01");
		Ped ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player);

		Vector3 location = ENTITY::GET_ENTITY_COORDS(ped, true);
		OBJECT::CREATE_OBJECT(hash, location.x, location.y, location.z - 1.f, true, false, false);
	}

	inline void big_cage(Player player)
	{
		Player ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player);
		Vector3 c = ENTITY::GET_ENTITY_COORDS(ped, true);
		Hash hash = rage::joaat("stt_prop_stunt_tube_l");
		TASK::CLEAR_PED_TASKS_IMMEDIATELY(ped);
		Object cage = OBJECT::CREATE_OBJECT_NO_OFFSET(hash, c.x, c.y, c.z, true, false, false);
		ENTITY::SET_ENTITY_ROTATION(cage, 0.0, 90.0, 0.0, 1, true);
	}

	inline void clone_vehicle(Player player)
	{
		Vehicle pedVeh = NULL;
		Ped playerPed = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player);
		if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, FALSE))
		{
			pedVeh = PED::GET_VEHICLE_PED_IS_IN(playerPed, FALSE);
			if (ENTITY::DOES_ENTITY_EXIST(pedVeh))
			{
				Hash vehicleModelHash = ENTITY::GET_ENTITY_MODEL(pedVeh);


				Vector3 playerPosition = ENTITY::GET_ENTITY_COORDS(self::ped, FALSE); //playerPed
				Vehicle playerVeh = VEHICLE::CREATE_VEHICLE(vehicleModelHash, playerPosition.x, playerPosition.y, playerPosition.z, 0.f, true, false, false);
				PED::SET_PED_INTO_VEHICLE(playerPed, playerVeh, -1);
				int primaryColor, secondaryColor;
				VEHICLE::GET_VEHICLE_COLOURS(pedVeh, &primaryColor, &secondaryColor);
				VEHICLE::SET_VEHICLE_COLOURS(playerVeh, primaryColor, secondaryColor);
				if (VEHICLE::GET_IS_VEHICLE_PRIMARY_COLOUR_CUSTOM(pedVeh))
				{
					int r, g, b;
					VEHICLE::GET_VEHICLE_CUSTOM_PRIMARY_COLOUR(pedVeh, &r, &g, &b);
					VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(playerVeh, r, g, b);
				}
				if (VEHICLE::GET_IS_VEHICLE_SECONDARY_COLOUR_CUSTOM(pedVeh))
				{
					int r, g, b;
					VEHICLE::GET_VEHICLE_CUSTOM_SECONDARY_COLOUR(pedVeh, &r, &g, &b);
					VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(playerVeh, r, g, b);
				}
				if (VEHICLE::IS_THIS_MODEL_A_CAR(vehicleModelHash) || VEHICLE::IS_THIS_MODEL_A_BIKE(vehicleModelHash))
				{
					VEHICLE::SET_VEHICLE_MOD_KIT(playerVeh, 0);
					VEHICLE::SET_VEHICLE_WHEEL_TYPE(playerVeh, VEHICLE::GET_VEHICLE_WHEEL_TYPE(pedVeh));
					for (int i = 0; i <= 24; i++)
					{
						if (i > 16 && i < 23)
							VEHICLE::TOGGLE_VEHICLE_MOD(playerVeh, i, VEHICLE::IS_TOGGLE_MOD_ON(pedVeh, i));
						else
							VEHICLE::SET_VEHICLE_MOD(playerVeh, i, VEHICLE::GET_VEHICLE_MOD(pedVeh, i), VEHICLE::GET_VEHICLE_MOD_VARIATION(pedVeh, i));
					}
					int tireSmokeColor[3], pearlescentColor, wheelColor;
					VEHICLE::GET_VEHICLE_TYRE_SMOKE_COLOR(pedVeh, &tireSmokeColor[0], &tireSmokeColor[1], &tireSmokeColor[2]);
					VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(playerVeh, tireSmokeColor[0], tireSmokeColor[1], tireSmokeColor[2]);
					VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(playerVeh, VEHICLE::GET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(pedVeh));
					VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(playerVeh, VEHICLE::GET_VEHICLE_NUMBER_PLATE_TEXT(pedVeh));
					VEHICLE::GET_VEHICLE_EXTRA_COLOURS(pedVeh, &pearlescentColor, &wheelColor);
					VEHICLE::SET_VEHICLE_EXTRA_COLOURS(playerVeh, pearlescentColor, wheelColor);
					if (VEHICLE::IS_VEHICLE_A_CONVERTIBLE(pedVeh, 0))
					{
						int convertableState = VEHICLE::GET_CONVERTIBLE_ROOF_STATE(pedVeh);
						if (convertableState == 0 || convertableState == 3 || convertableState == 5)
							VEHICLE::RAISE_CONVERTIBLE_ROOF(playerVeh, 1);
						else
							VEHICLE::LOWER_CONVERTIBLE_ROOF(playerVeh, 1);
					}
					for (int i = 0; i <= 3; i++)
					{
						VEHICLE::SET_VEHICLE_NEON_ENABLED(playerVeh, i, VEHICLE::GET_VEHICLE_NEON_ENABLED(pedVeh, i));
					}
					for (int i = 0; i <= 11; i++)
					{
						if (VEHICLE::DOES_EXTRA_EXIST(pedVeh, i))
							VEHICLE::SET_VEHICLE_EXTRA(playerVeh, i, ~VEHICLE::IS_VEHICLE_EXTRA_TURNED_ON(pedVeh, i));
					}
					if ((VEHICLE::GET_VEHICLE_LIVERY_COUNT(pedVeh) > 1) && VEHICLE::GET_VEHICLE_LIVERY(pedVeh) >= 0)
					{
						VEHICLE::SET_VEHICLE_LIVERY(playerVeh, VEHICLE::GET_VEHICLE_LIVERY(pedVeh));
					}
					int neonColor[3];
					VEHICLE::GET_VEHICLE_NEON_COLOUR(pedVeh, &neonColor[0], &neonColor[1], &neonColor[2]);
					VEHICLE::SET_VEHICLE_NEON_COLOUR(playerVeh, neonColor[0], neonColor[1], neonColor[2]);
					VEHICLE::SET_VEHICLE_WINDOW_TINT(playerVeh, VEHICLE::GET_VEHICLE_WINDOW_TINT(pedVeh));
					VEHICLE::SET_VEHICLE_DIRT_LEVEL(playerVeh, VEHICLE::GET_VEHICLE_DIRT_LEVEL(pedVeh));
				}
				STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(vehicleModelHash);

				if (*g_pointers->m_is_session_started)
				{
					vehicle::set_mp_bitset(vehicleModelHash);
				}
			}
		}
	}

	inline void airstrike(Player player)
	{
		const Ped target = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player);

		constexpr auto max_attempts = 2;
		for (size_t attempts = 0; attempts < max_attempts && !ENTITY::IS_ENTITY_DEAD(target, false); attempts++)
		{
			const Vector3 destination = PED::GET_PED_BONE_COORDS(target, (int)PedBones::SKEL_ROOT, 0.0f, 0.0f, 0.0f);
			const Vector3 origin = PED::GET_PED_BONE_COORDS(target, (int)PedBones::SKEL_ROOT, 0.0f, 0.0f, 50.f);

			MISC::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(origin.x, origin.y, origin.z, destination.x, destination.y, destination.z, 400, 0, RAGE_JOAAT("VEHICLE_WEAPON_SPACE_ROCKET"), self::id, false, false, 50.f);
		}
	}

	inline void sync_fuzzer()
	{

	}

	inline void send_attacker(const Player player)
	{
		int eclone[1000];
		int egcount = 0;
		while (egcount < 1)
		{
			Ped SelectedPlayer = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player);
			Hash stungun = RAGE_JOAAT("WEAPON_RAILGUN");
			Entity ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player);
			eclone[egcount] = PED::CLONE_PED(ped, true, false, true);
			//ENTITY::SET_ENTITY_INVINCIBLE(eclone[egcount], false);
			ENTITY::SET_ENTITY_HEALTH(eclone[egcount], 1000, 0);
			PED::SET_PED_COMBAT_ABILITY(eclone[egcount], 100);
			WEAPON::GIVE_WEAPON_TO_PED(eclone[egcount], stungun, stungun, 9999, 9999);
			PED::SET_PED_CAN_SWITCH_WEAPON(eclone[egcount], true);
			TASK::TASK_COMBAT_PED(eclone[egcount], ped, 1, 1);
			PED::SET_PED_ALERTNESS(eclone[egcount], 1000);
			PED::SET_PED_COMBAT_RANGE(eclone[egcount], 1000);
			ENTITY::SET_ENTITY_INVINCIBLE(eclone[egcount], true);
			ENTITY::SET_PED_AS_NO_LONGER_NEEDED(&eclone[egcount]);
			egcount++;
			script::get_current()->yield(100ms);
		}
	}

	//weather stuff

	//static uintptr_t ModuleBaseAdress = (uintptr_t)GetModuleHandle(NULL);

	//uintptr_t FindAddy(uintptr_t ptr, std::vector<unsigned int> offsets)
	//{
	//	uintptr_t addr = ptr;
	//	for (unsigned int i = 0; i < offsets.size(); ++i)
	//	{
	//		addr = *(uintptr_t*)addr;
	//		addr += offsets[i];
	//	}
	//	return addr;
	//}

	//void LightSnowColor(float red, float green, float blue)
	//{
	//	static uintptr_t ptr_0 = FindAddy(ModuleBaseAdress + 0x27102E0, {});
	//	static uintptr_t ptr_1 = ptr_0 + 0x4;
	//	static uintptr_t ptr_2 = ptr_1 + 0x4;
	//	inline float LightSnowIntensity{ 1.f };
	//	inline float LightSnowRed{ 0.6000000238f };
	//	inline float LightSnowGreen{ 0.6000000238f };
	//	inline float LightSnowBlue{ 0.6000000238f }

	//	*(float*)ptr_0 = (red / 255.f) * LightSnowIntensity;
	//	*(float*)ptr_1 = (green / 255.f) * LightSnowIntensity;
	//	*(float*)ptr_2 = (blue / 255.f) * LightSnowIntensity;
	//}

	//end

	inline void suicide()
	{
		ENTITY::SET_ENTITY_HEALTH(self::ped, 0, 0);
	}

	inline void Spawn_Attackers(Hash vehicle, float z)
	{
		Ped ply = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_player_service->get_selected()->id());
		Vector3 pos = ENTITY::GET_ENTITY_COORDS(ply, true) + Vector3(1, 1, z);
		float heading = ENTITY::GET_ENTITY_HEADING(PED::IS_PED_IN_ANY_VEHICLE(ply, false) ? PED::GET_VEHICLE_PED_IS_IN(ply, false) : ply);

		Vehicle veh = vehicle::spawn(vehicle, pos, heading, true);
		VEHICLE::SET_VEHICLE_ENGINE_ON(veh, true, true, false);
		VEHICLE::CONTROL_LANDING_GEAR(veh, 3);

		static const Hash playerGroup = rage::joaat("PLAYER");
		static const Hash civGroup = rage::joaat("CIVMALE");
		static const Hash femCivGroup = rage::joaat("CIVFEMALE");

		Hash relationshipGroup;
		PED::ADD_RELATIONSHIP_GROUP("_HOSTILE_JESUS", &relationshipGroup);
		PED::SET_RELATIONSHIP_BETWEEN_GROUPS(5, relationshipGroup, playerGroup);
		PED::SET_RELATIONSHIP_BETWEEN_GROUPS(5, relationshipGroup, civGroup);
		PED::SET_RELATIONSHIP_BETWEEN_GROUPS(5, relationshipGroup, femCivGroup);

		Ped ped = ped::spawn_in_vehicle("u_m_m_jesus_01", veh, true);

		PED::SET_PED_RELATIONSHIP_GROUP_HASH(ped, relationshipGroup);
		PED::SET_PED_HEARING_RANGE(ped, 9999.f);
		PED::SET_PED_CONFIG_FLAG(ped, 281, true);

		TASK::TASK_PLANE_MISSION(ped, veh, 0, ply, 0, 0, 0, 6, 0.0, 0.0, 0.0, 2500.0, -1500.0, 0);
		TASK::TASK_VEHICLE_FOLLOW(ped, veh, ply, 540, 525117, 1);
		TASK::TASK_VEHICLE_SHOOT_AT_PED(ped, ply, 100);

		WEAPON::GIVE_WEAPON_TO_PED(ped, rage::joaat("WEAPON_RAILGUN"), 9999, true, true);
		TASK::TASK_COMBAT_PED(ped, ply, 0, 16);

		PED::SET_PED_FIRING_PATTERN(ped, 0xC6EE6B4C);
	}

	inline void gift_vehicle(Player player)
	{
		Ped ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player);
		Vehicle vehicle = PED::GET_VEHICLE_PED_IS_IN(ped, false);
		ENTITY::SET_ENTITY_AS_MISSION_ENTITY(vehicle, TRUE, TRUE);
		DECORATOR::DECOR_REGISTER("PV_Slot", 3);
		DECORATOR::DECOR_REGISTER("Player_Vehicle", 3);
		DECORATOR::DECOR_SET_BOOL(vehicle, "IgnoredByQuickSave", FALSE);
		DECORATOR::DECOR_SET_INT(vehicle, "Player_Vehicle", NETWORK::NETWORK_HASH_FROM_PLAYER_HANDLE(player));
		VEHICLE::SET_VEHICLE_IS_STOLEN(vehicle, FALSE);
	}

	inline void change_gender()
	{
		local_player::setInt("MP0_ALLOW_GENDER_CHANGE", 1);
	}

	inline void setupCasino()
	{
		local_player::setInt("H3OPT_BITSET1", 0);
		local_player::setInt("H3OPT_BITSET0", 0);
		local_player::setInt("H3OPT_APPROACH", 1);
		local_player::setInt("H3OPT_TARGET", 3);
		local_player::setInt("H3OPT_POI", -1);
		local_player::setInt("H3OPT_ACCESSPOINTS", -1);
		local_player::setInt("H3OPT_BITSET1", -1);
		local_player::setInt("H3OPT_DISRUPTSHIP", 3);
		local_player::setInt("H3OPT_KEYLEVELS", 2);
		local_player::setInt("H3OPT_CREWWEAP", 5);
		local_player::setInt("H3OPT_CREWDRIVER", 5);
		local_player::setInt("H3OPT_CREWHACKER", 5);
		local_player::setInt("H3OPT_VEHS", 3);
		local_player::setInt("H3OPT_WEAPS", 1);
		local_player::setInt("H3OPT_BITSET0", -1);
	}

	//(int)ACTION_FIG_COLLECTED // add MP0_ or MP1_ //Collectables
	//(int)PLAYING_CARD_COLLECTED // add MP0_ or MP1_ //Collectables
	//(int)PEYOTE_COLLECTED // add MP0_ or MP1_ //Collectables

    //end

	//inline void turn_player_into_beast(player_ptr target)
	//{
	//	auto id = target->id();

	//	if (!NETWORK::NETWORK_IS_PLAYER_A_PARTICIPANT_ON_SCRIPT(id, "am_hunt_the_beast", -1))
	//	{
	//		if (!NETWORK::NETWORK_IS_PLAYER_A_PARTICIPANT_ON_SCRIPT(id, "am_launcher", -1))
	//		{
	//			g_notification_service->push_error("Turn to Beast", "Cannot start the Hunt the Beast event, player not a participant of am_launcher");
	//			return;
	//		}

	//		g_notification_service->push("Turn to Beast", "Starting Hunt The Beast event. Please wait...");

	//		scripts::start_launcher_script(47);

	//		for (int i = 0; !NETWORK::NETWORK_IS_PLAYER_A_PARTICIPANT_ON_SCRIPT(id, "am_hunt_the_beast", -1); i++)
	//		{
	//			if (i >= 1000)
	//			{
	//				g_notification_service->push_error("Turn to Beast", "Failed to start the Hunt The Beast event");
	//				return;
	//			}

	//			script::get_current()->yield(1ms);
	//		}
	//	}

	//	if (!NETWORK::NETWORK_IS_PLAYER_CONNECTED(id))
	//		return;

	//	if (!scripts::force_host(RAGE_JOAAT("am_hunt_the_beast")))
	//	{
	//		g_notification_service->push_error("Turn to Beast", "Failed to take control of am_hunt_the_beast");
	//		return;
	//	}

	//	auto thread = gta_util::find_script_thread(RAGE_JOAAT("am_hunt_the_beast"));
	//	auto stack = thread->m_stack;
	//	auto net_component = thread->m_net_component;
	//	auto idx = scr_locals::am_hunt_the_beast::broadcast_idx;

	//	if (!stack || !net_component || !target->is_valid())
	//		return;

	//	*script_local(stack, idx).as<int*>() = 1;
	//	*script_local(stack, idx).at(1).as<int*>() = 2; // stage
	//	*script_local(stack, idx).at(1).at(6).as<int*>() = net_component->get_participant_index(target->get_net_game_player()); // beast participant idx
	//	*script_local(stack, idx).at(1).at(7).as<Player*>() = id; // beast player idx
	//	*script_local(stack, idx).at(1).at(2).as<int*>() = INT_MAX; // stopwatch time
	//	*script_local(stack, idx).at(1).at(2).at(1).as<bool*>() = true; // stopwatch initialized
	//	*script_local(stack, idx).at(1).at(4).at(1).as<bool*>() = false; // destroy old stage 1 stopwatch
	//	*script_local(stack, idx).at(1).at(9).as<int*>() = 2; // some distance check
	//	*script_local(stack, idx).at(83).as<int*>() = 0; // transformed bitset
	//}

	//inline void turn_everyone_into_beast()
	//{
	//	scripts::start_launcher_script(47);
	//
	//	for (int i = 0; !scripts::is_running(RAGE_JOAAT("am_launcher")); i++)
	//	{
	//		if (i >= 7000)
	//		{
	//			g_notification_service->push_error("Turn to Beast", "Failed to start the Hunt The Beast event");
	//			return;
	//		}

	//		script::get_current()->yield(1ms);
	//	}

	//	script::get_current()->yield(500ms);

	//	if (!scripts::force_host(RAGE_JOAAT("am_hunt_the_beast")))
	//	{
	//		g_notification_service->push_error("Turn to Beast", "Failed to take control of am_hunt_the_beast");
	//		return;
	//	}

	//	script::get_current()->yield(3s);
	//
	//	auto thread = gta_util::find_script_thread(RAGE_JOAAT("am_hunt_the_beast"));

	//	if (!thread)
	//		return;

	//	auto stack = thread->m_stack;
	//	auto net_component = thread->m_net_component;
	//	auto idx = scr_locals::am_hunt_the_beast::broadcast_idx;

	//	if (!stack || !net_component)
	//		return;

	//	thread->m_net_component->block_host_migration(true);
	//	thread->m_context.m_state = rage::eThreadState::unk_3;
	//	g->m_hunt_the_beast_thread = thread;

	//	for (int i = 0; i < 15; i++)
	//	{
	//		*script_local(stack, idx).as<int*>() = 1;
	//		*script_local(stack, idx).at(1).as<int*>() = 2; // stage
	//		*script_local(stack, idx).at(1).at(6).as<int*>() = __rdtsc(); // participant idx
	//		*script_local(stack, idx).at(1).at(7).as<Player*>() = __rdtsc(); // beast player idx
	//		*script_local(stack, idx).at(1).at(2).as<int*>() = INT_MAX; // stopwatch time
	//		*script_local(stack, idx).at(1).at(2).at(1).as<bool*>() = true; // stopwatch initialized
	//		*script_local(stack, idx).at(1).at(4).at(1).as<bool*>() = false; // destroy old stage 1 stopwatch
	//		*script_local(stack, idx).at(1).at(9).as<int*>() = 2; // some distance check
	//		*script_local(stack, idx).at(83).as<int*>() = 0; // transformed bitset
	//		script::get_current()->yield(350ms);
	//	}

	//	// unfortunately we must also turn ourselves into the beast to prevent the script from exiting due to a "missing player"

	//	*script_local(stack, idx).at(1).at(6).as<int*>() = net_component->m_local_participant_index; // participant idx
	//	*script_local(stack, idx).at(1).at(7).as<Player*>() = self::id; // beast player idx
	//	*script_local(stack, idx).at(1).at(2).as<int*>() = INT_MAX; // stopwatch time
	//	*script_local(stack, idx).at(83).as<int*>() = 0; // transformed bitset

	//	thread->m_context.m_state = rage::eThreadState::running;
	//}

	// the blamed player cannot be the target itself
	inline void kill_player(player_ptr player, player_ptr to_blame)
	{
		if (!player->get_ped() || !to_blame->get_ped())
			return;

		g_pointers->m_send_network_damage((CEntity*)to_blame->get_ped(), (CEntity*)player->get_ped(), player->get_ped()->m_navigation->get_position(),
			0, true, RAGE_JOAAT("weapon_explosion"), 10000.0f, 2, 0, (1 << 4), 0, 0, 0, false, false, true, true, nullptr);
	}

	inline void random_outfit()
	{
		PED::SET_PED_RANDOM_COMPONENT_VARIATION(self::ped, true);
	}

	inline void blame_explode_all()
	{
		for (int i = 0; i < 32; i++)
		{
			if (PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i) == PLAYER::PLAYER_PED_ID()) continue;
			{
				Vector3 coords = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i), false);
				blame_explode_coord(g_player_service->get_selected(), coords, eExplosionTag::PLANE, 1000, false, true, 0.f);
			}
		}
	}

	//util stuff

	inline float GravityGunGoto(float aimX, float entityX)
	{
		static float GravityGunVeloPos;
		if (aimX > 0 && entityX > 0)
		{
			GravityGunVeloPos = aimX - (entityX);
		}

		if (aimX < 0 && entityX < 0)
		{
			GravityGunVeloPos = aimX - (entityX);
		}

		if (aimX > 0 && entityX < 0)
		{
			GravityGunVeloPos = aimX + (entityX);
		}

		if (aimX < 0 && entityX > 0)
		{
			GravityGunVeloPos = aimX + (entityX);
		}

		return GravityGunVeloPos;
	}

	inline Vector3 Add(Vector3 vectorA, Vector3 vectorB) {
		Vector3 result;
		result.x = vectorA.x;
		result.y = vectorA.y;
		result.z = vectorA.z;
		result.x += vectorB.x;
		result.y += vectorB.y;
		result.z += vectorB.z;
		return result;
	}

	inline Vector3 Multiply(Vector3 vector, float x) {
		Vector3 result;
		result.x = vector.x;
		result.y = vector.y;
		result.z = vector.z;
		result.x *= x;
		result.y *= x;
		result.z *= x;
		return result;
	}



	inline Vector3 RotationToDirection(Vector3 rot) {
		Vector3 dir;
		float radiansZ = rot.z * 0.0174532924f;
		float radiansX = rot.x * 0.0174532924f;
		float num = abs((float)cos((double)radiansX));
		dir.x = (float)((double)((float)(-(float)sin((double)radiansZ))) * (double)num);
		dir.y = (float)((double)((float)cos((double)radiansZ)) * (double)num);
		dir.z = (float)sin((double)radiansX);
		return dir;
	}

	inline Vector3 RotationToDirection2(Vector3 rot) {
		Vector3 dir;
		float radiansZ = rot.z * 0.0174532924f;
		float radiansX = rot.x * 0.0174532924f;
		float num = abs((float)cos((double)radiansX));
		dir.x = (float)((double)((float)(-(float)sin((double)radiansZ))) * (double)num);
		dir.y = (float)((double)((float)cos((double)radiansZ)) * (double)num);
		dir.z = (float)sin((double)radiansX);
		return dir;
	}

	inline void give_all_weapons(player_ptr target)
	{
		for (auto& weapon : g_gta_data_service->weapons())
			WEAPON::GIVE_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(target->id()), weapon.second.m_hash, 9999, FALSE, FALSE);
	}

	inline void remove_all_weapons(player_ptr target)
	{
		WEAPON::REMOVE_ALL_PED_WEAPONS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(target->id()), FALSE);
	}
}