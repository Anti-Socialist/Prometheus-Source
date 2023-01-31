#include "backend.hpp"
#include "script.hpp"
#include "thread_pool.hpp"
#include "looped/looped.hpp"
#include "services/context_menu/context_menu_service.hpp"
#include "script_patches.hpp"
#include "looped_command.hpp"
#include "services/anti_cheat/anti_cheat_service.hpp"

namespace big
{
	void backend::loop()
	{
		for (auto& command : g_looped_commands)
			command->refresh();

		register_script_patches();

		while (g_running) 
		{
			looped::system_self_globals();
			looped::system_update_pointers();
			looped::system_desync_kick_protection();
			looped::system_spoofing();
			looped::system_mission_creator();
			looped::system_auto_tp();

			for (auto command : g_looped_commands)
				if (command->is_enabled())
					command->on_tick();

			script::get_current()->yield();
		}
	}

	void backend::anti_cheat()
	{
		LOG(INFO) << "Starting Anti-Cheat";
		while (g_running) {
			looped::anti_cheat();

			script::get_current()->yield(20s);
		}
	}

	void backend::self_loop()
	{
		LOG(INFO) << "Starting script: Self";

		while (g_running)
		{
			looped::self_godmode();
			looped::self_police();
			looped::self_hud();
			looped::self_dance_mode();
			looped::money_drop();
			looped::collectable_drop();
			//looped::aimbot();
			looped::money_loop();
			looped::nightclub_loop();
			looped::fire_loop();
			looped::water_loop();
			//looped::super_man();
			//looped::force_field();
			//looped::hand_trail_red();
			looped::hand_trail_green();
			looped::hand_trail_blue();
			looped::hand_trail_midnight();
			looped::hand_trail_magenta();
			//looped::move_water();
			looped::container_rider();
			//looped::tiny_player();
			looped::walk_on_water();
			//looped::fire_breath();
			looped::magnet_gun();
			//looped::beast_jump();
			looped::flying_axe();

			script::get_current()->yield();
		}
	}



	void backend::weapons_loop()
	{
		LOG(INFO) << "Starting script: Weapons";

		while (g_running)
		{
			looped::weapons_ammo_special_type();
			looped::weapons_cage_gun();
			looped::weapons_delete_gun();
			looped::weapons_gravity_gun();
			looped::weapons_increased_damage();
			looped::weapons_repair_gun();
			looped::weapons_steal_vehicle_gun();
			looped::weapons_vehicle_gun();
			looped::paint_gun();
			looped::money_gun();
			looped::fly_gun();
			looped::valkery_gun();
			looped::flame_thrower();
			looped::rope_gun();
			looped::collectable_gun();

			script::get_current()->yield();
		}
	}

	void backend::vehicles_loop()
	{
		LOG(INFO) << "Starting script: Vehicles";

		while (g_running)
		{
			looped::vehicle_auto_drive();
			looped::vehicle_boost_behavior();
			looped::vehicle_god_mode();
			looped::vehicle_speedo_meter();
			looped::vehicle_trail();
			looped::vehicle_uniweap();
			looped::vehicle_invisible();
			looped::drift_mode();

			script::get_current()->yield();
		}
	}

	void backend::turnsignal_loop()
	{
		LOG(INFO) << "Starting script: turnsignal";

		while (g_running)
		{
			looped::vehicle_turn_signals();

			script::get_current()->yield();
		}
	}

	void backend::misc_loop()
	{
		LOG(INFO) << "Starting script: Miscellaneous";

		while (g_running)
		{
			looped::hud_transition_state();
			looped::session_local_time();
			looped::session_pop_multiplier_areas();
			looped::session_force_thunder();
			looped::session_randomize_ceo_colors();
			looped::session_auto_kick_host();
			looped::delete_vehicles();
			looped::burst_vehicle_tires();
			looped::launch_vehicle();
			looped::horn_vehicles();
			looped::repair_vehicles();
			looped::upgrade_vehicles();
			looped::explode_peds();
			looped::rain_rockets();
			looped::asteroid_shower();
			looped::session_block_jobs();

			script::get_current()->yield();
		}
	}

	void backend::remote_loop()
	{
		LOG(INFO) << "Starting script: Remote";

		while (g_running)
		{
			looped::player_good_options();
			looped::player_toxic_options();
			looped::player_spectate();
			looped::player_remote_control_vehicle();

			script::get_current()->yield();
		}
	}

	void backend::lscustoms_loop()
	{
		LOG(INFO) << "Starting script: Ls customs";

		while (g_running)
		{
			looped::vehicle_ls_customs();

			script::get_current()->yield();
		}
	}

	void backend::rainbowpaint_loop()
	{
		LOG(INFO) << "Starting script: Rainbow paint";

		while (g_running)
		{
			looped::vehicle_rainbow_paint();

			script::get_current()->yield();
		}
	}

	void backend::vehiclefly_loop()
	{
		LOG(INFO) << "Starting script: Vehicle fly";

		while (g_running)
		{
			looped::vehicle_fly();

			script::get_current()->yield();
		}
	}

	void backend::disable_control_action_loop()
	{
		LOG(INFO) << "Starting script: Disable Control Action";

		while (g_running)
		{

			looped::custom_gun_disable_control_action();
			context_menu_service::disable_control_action_loop();

			script::get_current()->yield();
		}
	}
	void backend::world_loop()
	{
		LOG(INFO) << "Starting script: World";

		while (g_running)
		{

			looped::world_spawn_ped();
			script::get_current()->yield();
		}
	}
}
