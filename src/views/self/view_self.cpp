#include "fiber_pool.hpp"
#include "util/entity.hpp"
#include "util/local_player.hpp"
#include "views/view.hpp"
#include "core/data/hud_component_names.hpp"
#include "util/scripts.hpp"
#include "util/toxic.hpp"
#include <iostream>

namespace big
{
	void view::self()
	{
		components::command_button<"suicide">();
		ImGui::SameLine();
		components::command_button<"heal">();
		ImGui::SameLine();
		components::command_button<"fillsnacks">();
		ImGui::SameLine();
		components::command_button<"skipcutscene">();
		ImGui::SameLine();
		components::command_button<"clean">();

		ImGui::SameLine();

		components::button("Skydive", [] {
			Vector3 me = ENTITY::GET_ENTITY_COORDS(self::ped, 0);
		WEAPON::GIVE_DELAYED_WEAPON_TO_PED(self::ped, MISC::GET_HASH_KEY("gadget_parachute"), 1, 0);
		ENTITY::SET_ENTITY_COORDS(self::ped, me.x, me.y, me.z + 1000, 0, 0, 0, 0);
			});

		components::button("Give dunce hat", [] {
			*script_global(1577881).as<int*>() = 1;
			*script_global(1577844).as<int*>() = 0;
		});

		ImGui::Separator();

		components::sub_title("General");

		ImGui::BeginGroup();

		ImGui::Checkbox("God Mode", &g.self.god_mode);
		components::command_checkbox<"otr">();
		components::command_checkbox<"freecam">();
		components::command_checkbox<"nophone">();
		components::command_checkbox<"infoxy">();
		components::command_checkbox<"fastrespawn">();
		components::command_checkbox<"tinyplayer">();
		ImGui::Checkbox("Container Rider", &g.self.container_rider);
		components::command_checkbox<"forcefield">();

		ImGui::EndGroup();
		ImGui::SameLine();
		ImGui::BeginGroup();

		components::command_checkbox<"noclip">();
		components::command_checkbox<"noragdoll">();
		components::command_checkbox<"fastrun">();
		ImGui::Checkbox("No Idle Kick", &g.tunables.no_idle_kick);
		components::command_checkbox<"walkunder">();
		components::command_checkbox<"superman">();
		components::command_checkbox<"higheffect">();
		components::command_checkbox<"firebreath">();
        ImGui::Checkbox("Flying Axe", &g.self.flying_axe);

		ImGui::EndGroup();
		ImGui::SameLine();
		ImGui::BeginGroup();

		components::command_checkbox<"invis">();
		if (g.self.invisibility)
			components::command_checkbox<"localvis">();
		components::command_checkbox<"cleanloop">();
		components::command_checkbox<"nocollision">();
		components::command_checkbox<"mobileradio">();

		ImGui::Checkbox("Dance Mode", &g.self.dance_mode);
		components::command_checkbox<"movewater">();
		components::command_checkbox<"beastjump">();
		components::command_checkbox<"airswim">();

		ImGui::EndGroup();

		ImGui::Separator();

		components::sub_title("Proofs");

		if (ImGui::Button("Check all"))
		{
			g.self.proof_bullet = true;
			g.self.proof_fire = true;
			g.self.proof_collision = true;
			g.self.proof_melee = true;
			g.self.proof_explosion = true;
			g.self.proof_steam = true;
			g.self.proof_drown = true;
			g.self.proof_water = true;
		}

		ImGui::SameLine();

		if (ImGui::Button("Uncheck all"))
		{
			g.self.proof_bullet = false;
			g.self.proof_fire = false;
			g.self.proof_collision = false;
			g.self.proof_melee = false;
			g.self.proof_explosion = false;
			g.self.proof_steam = false;
			g.self.proof_drown = false;
			g.self.proof_water = false;
		}

		ImGui::BeginGroup();

		ImGui::Checkbox("Bullet", &g.self.proof_bullet);
		ImGui::Checkbox("Fire", &g.self.proof_fire);

		ImGui::EndGroup();
		ImGui::SameLine();
		ImGui::BeginGroup();

		ImGui::Checkbox("Collision", &g.self.proof_collision);
		ImGui::Checkbox("Melee", &g.self.proof_melee);

		ImGui::EndGroup();
		ImGui::SameLine();
		ImGui::BeginGroup();

		ImGui::Checkbox("Explosion", &g.self.proof_explosion);
		ImGui::Checkbox("Steam", &g.self.proof_steam);

		ImGui::EndGroup();
		ImGui::SameLine();
		ImGui::BeginGroup();

		ImGui::Checkbox("Drown", &g.self.proof_drown);
		ImGui::Checkbox("Water", &g.self.proof_water);

		ImGui::EndGroup();

		ImGui::Separator();

		components::sub_title("Hand Trail");

		ImGui::BeginGroup();
		components::command_checkbox<"handtrail">();
		ImGui::Checkbox("Midnight", &g.self.hand_trail_midnight);

		ImGui::EndGroup();
		ImGui::SameLine();
		ImGui::BeginGroup();

		ImGui::Checkbox("Green", &g.self.hand_trail_green);
		ImGui::SameLine();
		ImGui::Checkbox("Blue", &g.self.hand_trail_blue);
		ImGui::Checkbox("Magenta", &g.self.hand_trail_magenta);

		//ImGui::EndGroup();
		//ImGui::SameLine();
		//ImGui::BeginGroup();

		ImGui::EndGroup();

		ImGui::Separator();

		components::small_text("Asi stuff");

		components::button("Load scripthookv", [] {
			LOG(INFO) << (std::string(getenv("appdata")) + "\\PromeTheus\\ScriptHookV.dll").c_str();
		LoadLibraryA((std::string(getenv("appdata")) + "\\PromeTheus\\ScriptHookV.dll").c_str());
			});

		components::button("Load scripthookvdotnet", [] {
			LOG(INFO) << (std::string(getenv("appdata")) + "\\PromeTheus\\ScriptHookV.dll").c_str();
		LoadLibraryA((std::string(getenv("appdata")) + "\\PromeTheus\\ScriptHookV.dll").c_str());
		LOG(INFO) << (std::string(getenv("appdata")) + "\\PromeTheus\\ScriptHookVDotNet2.dll").c_str();
		LoadLibraryA((std::string(getenv("appdata")) + "\\PromeTheus\\ScriptHookVDotNet2.dll").c_str());
		LOG(INFO) << (std::string(getenv("appdata")) + "\\PromeTheus\\ScriptHookVDotNet3.dll").c_str();
		LoadLibraryA((std::string(getenv("appdata")) + "\\PromeTheus\\ScriptHookVDotNet3.dll").c_str());
			});

		components::button("Load Menyoo", [] {
		LOG(INFO) << (std::string(getenv("appdata")) + "\\PromeTheus\\scripts\\Menyoo.asi").c_str();
		LoadLibraryA((std::string(getenv("appdata")) + "\\PromeTheus\\scripts\\Menyoo.asi").c_str());
			});

		ImGui::Separator();

		components::small_text("Recovery (risky)"); //line 167

		ImGui::BeginGroup();

		components::button("2k Good Behaviour", [] { toxic::warp_time_forward_all(200 * 60 * 1000); });

		ImGui::Checkbox("Casino rig", &g.self.money_loop);

		ImGui::Checkbox("Nightclub 300k Safe Loop", &g.self.nightclub_loop);

		components::button("Change gender", [] {
			toxic::change_gender();
			});

		// components::button("Give 15 Million!", [] {
		// 	//toxic::money();
		// 	});

		if (ImGui::TreeNode("Set stat")) {

			components::button("Max snacks", [] {
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_NO_BOUGHT_YUM_SNACKS"), 1000000, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_NO_BOUGHT_HEALTH_SNACKS"), 1000000, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_NO_BOUGHT_EPIC_SNACKS"), 1000000, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CIGARETTES_BOUGHT"), 1000000, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_NUMBER_OF_ORANGE_BOUGHT"), 1000000, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_NUMBER_OF_BOURGE_BOUGHT"), 1000000, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_NUMBER_OF_CHAMP_BOUGHT"), 1000000, 0);
			});
			
			components::button("Max armour", [] {
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_MP_CHAR_ARMOUR_1_COUNT"), 1000000, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_MP_CHAR_ARMOUR_2_COUNT"), 1000000, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_MP_CHAR_ARMOUR_3_COUNT"), 1000000, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_MP_CHAR_ARMOUR_4_COUNT"), 1000000, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_MP_CHAR_ARMOUR_5_COUNT"), 1000000, 0);
			});

			components::button("Max stats", [] {
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_SCRIPT_INCREASE_STAM"), 100, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_SCRIPT_INCREASE_STRN"), 100, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_SCRIPT_INCREASE_LUNG"), 100, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_SCRIPT_INCREASE_DRIV"), 100, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_SCRIPT_INCREASE_FLY"), 100, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_SCRIPT_INCREASE_SHO"), 100, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_SCRIPT_INCREASE_STL"), 100, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_SCRIPT_INCREASE_MECH"), 0, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CAR_CLUB_REP"), 100000, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MPPLY_TOTAL_RACES_WON"), 450, 0);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MPPLY_TOTAL_RACES_LOST"), 100, 0);
			});

			components::button("Add 21 days playtime", [] {
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_MP_PLAYING_TIME"), 21 * 86400000, true);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_LEADERBOARD_PLAYING_TIME"), 21 * 86400000, true);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_TOTAL_PLAYING_TIME"), 21 * 86400000, true);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_MP_PLAYING_TIME"), 21 * 86400000, true);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_LEADERBOARD_PLAYING_TIME"), 21 * 86400000, true);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_TOTAL_PLAYING_TIME"), 21 * 86400000, true);
			});

			components::button("Zero To Hero", [] {
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_RACES_WON"), 50, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_RACES_WON"), 50, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_NUMBER_SLIPSTREAMS_IN_RACE"), 110, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_NUMBER_TURBO_STARTS_IN_RACE"), 90, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_FMWINSEARACE"), 10, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_FMWINAIRRACE"), 1, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_FM_RACES_FASTEST_LAP"), 50, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_USJS_FOUND"), 50, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_USJS_COMPLETED"), 50, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_FMRALLYWONDRIVE"), 10, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_NUMBER_SLIPSTREAMS_IN_RACE"), 110, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_NUMBER_TURBO_STARTS_IN_RACE"), 90, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_AWD_FMWINSEARACE"), 10, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_AWD_FMWINAIRRACE"), 1, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_AWD_FM_RACES_FASTEST_LAP"), 50, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_USJS_FOUND"), 50, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_USJS_COMPLETED"), 50, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MPPLY_TIMES_RACE_BEST_LAP"), 120, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_AWD_FMRALLYWONDRIVE"), 10, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_SAWNOFF_ENEMY_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_SAWNOFF_ENEMY_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP2_SAWNOFF_ENEMY_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CHAR_XP_FM"), 2165850, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CHAR_XP_FM"), 2165850, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP2_CHAR_XP_FM"), 2165850, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_SCRIPT_INCREASE_STAM"), 100, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_SCRIPT_INCREASE_STRN"), 100, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_SCRIPT_INCREASE_LUNG"), 100, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_SCRIPT_INCREASE_DRIV"), 100, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_SCRIPT_INCREASE_FLY"), 100, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_SCRIPT_INCREASE_SHO"), 100, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_SCRIPT_INCREASE_STL"), 100, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_RACES_WON"), 100, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_PISTOL_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CMBTPISTOL_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_APPISTOL_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_MICROSMG_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_SMG_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_ASLTSMG_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_ASLTRIFLE_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CRBNRIFLE_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_ADVRIFLE_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_HVYSNIPER_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_SNIPERRFL_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_ASLTSHTGN_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_PUMP_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_GRNLAUNCH_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_RPG_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_MINIGUNS_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_ASLTSMG_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_ASLTRIFLE_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CRBNRIFLE_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_ADVRIFLE_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_HVYSNIPER_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_SNIPERRFL_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_MG_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CMBTMG_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_PISTOL_ENEMY_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CMBTPISTOL_ENEMY_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_APPISTOL_ENEMY_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_MICROSMG_ENEMY_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_SMG_ENEMY_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_ASLTSMG_ENEMY_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_ASLTRIFLE_ENEMY_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CRBNRIFLE_ENEMY_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_ADVRIFLE_ENEMY_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_HVYSNIPER_ENEMY_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_SNIPERRFL_ENEMY_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_ASLTSHTGN_ENEMY_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_PUMP_ENEMY_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_GRNLAUNCH_ENEMY_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_RPG_ENEMY_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_MINIGUNS_ENEMY_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_ASLTSMG_ENEMY_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_ASLTRIFLE_ENEMY_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CRBNRIFLE_ENEMY_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_ADVRIFLE_ENEMY_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_HVYSNIPER_ENEMY_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_SNIPERRFL_ENEMY_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_MG_ENEMY_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CMBTMG_ENEMY_KILLS"), 600, true);
            STATS::STAT_SET_BOOL(MISC::GET_HASH_KEY("MP0_AWD_FMRACEWORLDRECHOLDER"), true, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_ENEMYDRIVEBYKILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_USJS_COMPLETED"), 50, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_USJS_FOUND"), 50, true);
            STATS::STAT_SET_BOOL(MISC::GET_HASH_KEY("MP0_AWD_FMWINALLRACEMODES"), true, true);
            STATS::STAT_SET_BOOL(MISC::GET_HASH_KEY("MP0_AWD_FMWINEVERYGAMEMODE"), true, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_DB_PLAYER_KILLS"), 1000, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_KILLS_PLAYERS"), 1000, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_FMHORDWAVESSURVIVE"), 21, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_CAR_BOMBS_ENEMY_KILLS"), 25, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_FM_TDM_MVP"), 60, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_HOLD_UP_SHOPS"), 20, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_RACES_WON"), 101, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_NO_ARMWRESTLING_WINS"), 21, true);
            STATS::STAT_SET_BOOL(MISC::GET_HASH_KEY("MP0_AWD_FMATTGANGHQ"), true, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_FMBBETWIN"), 50000, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_FM_DM_WINS"), 51, true);
            STATS::STAT_SET_BOOL(MISC::GET_HASH_KEY("MP0_AWD_FMFULLYMODDEDCAR"), true, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_FM_DM_TOTALKILLS"), 500, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_MPPLY_DM_TOTAL_DEATHS"), 412, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_MPPLY_TIMES_FINISH_DM_TOP_3"), 36, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_PLAYER_HEADSHOTS"), 623, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_FM_DM_WINS"), 63, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_FM_TDM_WINS"), 13, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_FM_GTA_RACES_WON"), 12, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_FM_GOLF_WON"), 2, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_FM_SHOOTRANG_TG_WON"), 2, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_FM_SHOOTRANG_RT_WON"), 2, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_FM_SHOOTRANG_CT_WON"), 2, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_FM_SHOOTRANG_GRAN_WON"), 2, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_FM_TENNIS_WON"), 2, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_MPPLY_TENNIS_MATCHES_WON"), 2, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_MPPLY_TOTAL_TDEATHMATCH_WON"), 63, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_MPPLY_TOTAL_RACES_WON"), 101, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_MPPLY_TOTAL_DEATHMATCH_LOST"), 23, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_MPPLY_TOTAL_RACES_LOST"), 36, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_25_KILLS_STICKYBOMBS"), 50, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_50_KILLS_GRENADES"), 50, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_GRENADE_ENEMY_KILLS"), 50, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_20_KILLS_MELEE"), 50, true);
            STATS::STAT_SET_BOOL(MISC::GET_HASH_KEY("MP0_AWD_FMMOSTKILLSSURVIVE"), true, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_FMRALLYWONDRIVE"), 2, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_FMWINSEARACE"), 2, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_FMWINAIRRACE"), 2, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_MPPLY_TIMES_RACE_BEST_LAP"), 101, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_NUMBER_TURBO_STARTS_IN_RACE"), 100, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_FM_RACES_FASTEST_LAP"), 101, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_NUMBER_SLIPSTREAMS_IN_RACE"), 105, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_MPPLY_OVERALL_CHEAT"), 0, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_LAP_DANCED_BOUGHT"), 50, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_FMKILLBOUNTY"), 50, true);
            STATS::STAT_SET_BOOL(MISC::GET_HASH_KEY("MP0_AWD_FMKILL3ANDWINGTARACE"), true, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_FMREVENGEKILLSDM"), 60, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_SECURITY_CARS_ROBBED"), 40, true);
            STATS::STAT_SET_BOOL(MISC::GET_HASH_KEY("MP0_AWD_FMPICKUPDLCCRATE1ST"), true, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_SCRIPT_INCREASE_STAM"), 100, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_SCRIPT_INCREASE_STRN"), 100, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_SCRIPT_INCREASE_LUNG"), 100, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_SCRIPT_INCREASE_DRIV"), 100, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_SCRIPT_INCREASE_FLY"), 100, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_SCRIPT_INCREASE_SHO"), 100, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_SCRIPT_INCREASE_STL"), 100, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_RACES_WON"), 100, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_PISTOL_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CMBTPISTOL_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_APPISTOL_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_MICROSMG_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_SMG_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_ASLTSMG_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_ASLTRIFLE_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CRBNRIFLE_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_ADVRIFLE_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_HVYSNIPER_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_SNIPERRFL_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_ASLTSHTGN_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_PUMP_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_GRNLAUNCH_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_RPG_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_MINIGUNS_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_ASLTSMG_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_ASLTRIFLE_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CRBNRIFLE_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_ADVRIFLE_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_HVYSNIPER_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_SNIPERRFL_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_MG_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CMBTMG_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_PISTOL_ENEMY_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CMBTPISTOL_ENEMY_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_APPISTOL_ENEMY_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_MICROSMG_ENEMY_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_SMG_ENEMY_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_ASLTSMG_ENEMY_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_ASLTRIFLE_ENEMY_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CRBNRIFLE_ENEMY_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_ADVRIFLE_ENEMY_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_HVYSNIPER_ENEMY_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_SNIPERRFL_ENEMY_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_ASLTSHTGN_ENEMY_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_PUMP_ENEMY_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_GRNLAUNCH_ENEMY_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_RPG_ENEMY_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_MINIGUNS_ENEMY_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_ASLTSMG_ENEMY_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_ASLTRIFLE_ENEMY_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CRBNRIFLE_ENEMY_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_ADVRIFLE_ENEMY_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_HVYSNIPER_ENEMY_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_SNIPERRFL_ENEMY_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_MG_ENEMY_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CMBTMG_ENEMY_KILLS"), 600, true);
            STATS::STAT_SET_BOOL(MISC::GET_HASH_KEY("MP1_AWD_FMRACEWORLDRECHOLDER"), true, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_AWD_ENEMYDRIVEBYKILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_USJS_COMPLETED"), 50, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_USJS_FOUND"), 50, true);
            STATS::STAT_SET_BOOL(MISC::GET_HASH_KEY("MP1_AWD_FMWINALLRACEMODES"), true, true);
            STATS::STAT_SET_BOOL(MISC::GET_HASH_KEY("MP1_AWD_FMWINEVERYGAMEMODE"), true, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_DB_PLAYER_KILLS"), 1000, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_KILLS_PLAYERS"), 1000, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_AWD_FMHORDWAVESSURVIVE"), 21, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_AWD_CAR_BOMBS_ENEMY_KILLS"), 25, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_AWD_FM_TDM_MVP"), 60, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_AWD_HOLD_UP_SHOPS"), 20, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_AWD_RACES_WON"), 101, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_AWD_NO_ARMWRESTLING_WINS"), 21, true);
            STATS::STAT_SET_BOOL(MISC::GET_HASH_KEY("MP1_AWD_FMATTGANGHQ"), true, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_AWD_FMBBETWIN"), 50000, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_AWD_FM_DM_WINS"), 51, true);
            STATS::STAT_SET_BOOL(MISC::GET_HASH_KEY("MP1_AWD_FMFULLYMODDEDCAR"), true, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_AWD_FM_DM_TOTALKILLS"), 500, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_MPPLY_DM_TOTAL_DEATHS"), 412, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_MPPLY_TIMES_FINISH_DM_TOP_3"), 36, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_PLAYER_HEADSHOTS"), 623, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_AWD_FM_DM_WINS"), 63, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_AWD_FM_TDM_WINS"), 13, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_AWD_FM_GTA_RACES_WON"), 12, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_AWD_FM_GOLF_WON"), 2, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_AWD_FM_SHOOTRANG_TG_WON"), 2, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_AWD_FM_SHOOTRANG_RT_WON"), 2, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_AWD_FM_SHOOTRANG_CT_WON"), 2, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_AWD_FM_SHOOTRANG_GRAN_WON"), 2, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_AWD_FM_TENNIS_WON"), 2, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_MPPLY_TENNIS_MATCHES_WON"), 2, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_MPPLY_TOTAL_TDEATHMATCH_WON"), 63, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_MPPLY_TOTAL_RACES_WON"), 101, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_MPPLY_TOTAL_DEATHMATCH_LOST"), 23, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_MPPLY_TOTAL_RACES_LOST"), 36, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_AWD_25_KILLS_STICKYBOMBS"), 50, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_AWD_50_KILLS_GRENADES"), 50, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_GRENADE_ENEMY_KILLS"), 50, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_AWD_20_KILLS_MELEE"), 50, true);
            STATS::STAT_SET_BOOL(MISC::GET_HASH_KEY("MP1_AWD_FMMOSTKILLSSURVIVE"), true, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_AWD_FMRALLYWONDRIVE"), 2, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_AWD_FMWINSEARACE"), 2, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_AWD_FMWINAIRRACE"), 2, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_MPPLY_TIMES_RACE_BEST_LAP"), 101, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_NUMBER_TURBO_STARTS_IN_RACE"), 100, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_AWD_FM_RACES_FASTEST_LAP"), 101, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_NUMBER_SLIPSTREAMS_IN_RACE"), 105, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_MPPLY_OVERALL_CHEAT"), 0, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_LAP_DANCED_BOUGHT"), 50, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_AWD_FMKILLBOUNTY"), 50, true);
            STATS::STAT_SET_BOOL(MISC::GET_HASH_KEY("MP1_AWD_FMKILL3ANDWINGTARACE"), true, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_AWD_FMREVENGEKILLSDM"), 60, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_AWD_SECURITY_CARS_ROBBED"), 40, true);
            STATS::STAT_SET_BOOL(MISC::GET_HASH_KEY("MP1_AWD_FMPICKUPDLCCRATE1ST"), true, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP2_SCRIPT_INCREASE_STAM"), 100, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP2_SCRIPT_INCREASE_STRN"), 100, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP2_SCRIPT_INCREASE_LUNG"), 100, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP2_SCRIPT_INCREASE_DRIV"), 100, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP2_SCRIPT_INCREASE_FLY"), 100, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP2_SCRIPT_INCREASE_SHO"), 100, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP2_SCRIPT_INCREASE_STL"), 100, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP2_RACES_WON"), 100, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP2_PISTOL_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP2_CMBTPISTOL_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP2_APPISTOL_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP2_MICROSMG_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP2_SMG_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP2_ASLTSMG_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP2_ASLTRIFLE_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP2_CRBNRIFLE_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP2_ADVRIFLE_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP2_HVYSNIPER_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP2_SNIPERRFL_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP2_ASLTSHTGN_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP2_PUMP_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP2_GRNLAUNCH_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP2_RPG_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP2_MINIGUNS_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP2_ASLTSMG_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP2_ASLTRIFLE_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP2_CRBNRIFLE_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP2_ADVRIFLE_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP2_HVYSNIPER_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP2_SNIPERRFL_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP2_MG_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP2_CMBTMG_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP2_PISTOL_ENEMY_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP2_CMBTPISTOL_ENEMY_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP2_APPISTOL_ENEMY_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP2_MICROSMG_ENEMY_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP2_SMG_ENEMY_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP2_ASLTSMG_ENEMY_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP2_ASLTRIFLE_ENEMY_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP2_CRBNRIFLE_ENEMY_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP2_ADVRIFLE_ENEMY_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP2_HVYSNIPER_ENEMY_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP2_SNIPERRFL_ENEMY_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP2_ASLTSHTGN_ENEMY_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP2_PUMP_ENEMY_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP2_GRNLAUNCH_ENEMY_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP2_RPG_ENEMY_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP2_MINIGUNS_ENEMY_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP2_ASLTSMG_ENEMY_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP2_ASLTRIFLE_ENEMY_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP2_CRBNRIFLE_ENEMY_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP2_ADVRIFLE_ENEMY_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP2_HVYSNIPER_ENEMY_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP2_SNIPERRFL_ENEMY_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP2_MG_ENEMY_KILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP2_CMBTMG_ENEMY_KILLS"), 600, true);
            STATS::STAT_SET_BOOL(MISC::GET_HASH_KEY("MP2_AWD_FMRACEWORLDRECHOLDER"), true, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP2_AWD_ENEMYDRIVEBYKILLS"), 600, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP2_USJS_COMPLETED"), 50, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP2_USJS_FOUND"), 50, true);
            STATS::STAT_SET_BOOL(MISC::GET_HASH_KEY("MP2_AWD_FMWINALLRACEMODES"), true, true);
            STATS::STAT_SET_BOOL(MISC::GET_HASH_KEY("MP2_AWD_FMWINEVERYGAMEMODE"), true, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP2_DB_PLAYER_KILLS"), 1000, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP2_KILLS_PLAYERS"), 1000, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP2_AWD_FMHORDWAVESSURVIVE"), 21, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP2_AWD_CAR_BOMBS_ENEMY_KILLS"), 25, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP2_AWD_FM_TDM_MVP"), 60, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP2_AWD_HOLD_UP_SHOPS"), 20, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP2_AWD_RACES_WON"), 101, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP2_AWD_NO_ARMWRESTLING_WINS"), 21, true);
            STATS::STAT_SET_BOOL(MISC::GET_HASH_KEY("MP2_AWD_FMATTGANGHQ"), true, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP2_AWD_FMBBETWIN"), 50000, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP2_AWD_FM_DM_WINS"), 51, true);
            STATS::STAT_SET_BOOL(MISC::GET_HASH_KEY("MP2_AWD_FMFULLYMODDEDCAR"), true, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP2_AWD_FM_DM_TOTALKILLS"), 500, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP2_MPPLY_DM_TOTAL_DEATHS"), 412, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP2_MPPLY_TIMES_FINISH_DM_TOP_3"), 36, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP2_PLAYER_HEADSHOTS"), 623, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP2_AWD_FM_DM_WINS"), 63, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP2_AWD_FM_TDM_WINS"), 13, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP2_AWD_FM_GTA_RACES_WON"), 12, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP2_AWD_FM_GOLF_WON"), 2, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP2_AWD_FM_SHOOTRANG_TG_WON"), 2, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP2_AWD_FM_SHOOTRANG_RT_WON"), 2, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP2_AWD_FM_SHOOTRANG_CT_WON"), 2, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP2_AWD_FM_SHOOTRANG_GRAN_WON"), 2, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP2_AWD_FM_TENNIS_WON"), 2, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP2_MPPLY_TENNIS_MATCHES_WON"), 2, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP2_MPPLY_TOTAL_TDEATHMATCH_WON"), 63, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP2_MPPLY_TOTAL_RACES_WON"), 101, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP2_MPPLY_TOTAL_DEATHMATCH_LOST"), 23, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP2_MPPLY_TOTAL_RACES_LOST"), 36, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP2_AWD_25_KILLS_STICKYBOMBS"), 50, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP2_AWD_50_KILLS_GRENADES"), 50, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP2_GRENADE_ENEMY_KILLS"), 50, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP2_AWD_20_KILLS_MELEE"), 50, true);
            STATS::STAT_SET_BOOL(MISC::GET_HASH_KEY("MP2_AWD_FMMOSTKILLSSURVIVE"), true, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP2_AWD_FMRALLYWONDRIVE"), 2, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP2_AWD_FMWINSEARACE"), 2, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP2_AWD_FMWINAIRRACE"), 2, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP2_MPPLY_TIMES_RACE_BEST_LAP"), 101, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP2_NUMBER_TURBO_STARTS_IN_RACE"), 100, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP2_AWD_FM_RACES_FASTEST_LAP"), 101, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP2_NUMBER_SLIPSTREAMS_IN_RACE"), 105, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP2_MPPLY_OVERALL_CHEAT"), 0, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP2_LAP_DANCED_BOUGHT"), 50, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP2_AWD_FMKILLBOUNTY"), 50, true);
            STATS::STAT_SET_BOOL(MISC::GET_HASH_KEY("MP2_AWD_FMKILL3ANDWINGTARACE"), true, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP2_AWD_FMREVENGEKILLSDM"), 60, true);
            STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP2_AWD_SECURITY_CARS_ROBBED"), 40, true);
            STATS::STAT_SET_BOOL(MISC::GET_HASH_KEY("MP2_AWD_FMPICKUPDLCCRATE1ST"), true, true);
			});

			components::button("Complete objectives", [] {
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_COMPLETEDAILYOBJ"), 100, true);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_COMPLETEDAILYOBJTOTAL"), 100, true);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_TOTALDAYCOMPLETED"), 100, true);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_TOTALWEEKCOMPLETED"), 400, true);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_TOTALMONTHCOMPLETED"), 1800, true);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CONSECUTIVEDAYCOMPLETED"), 30, true);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CONSECUTIVEWEEKCOMPLETED"), 4, true);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CONSECUTIVEMONTHCOMPLETE"), 1, true);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_COMPLETEDAILYOBJSA"), 100, true);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_COMPLETEDAILYOBJTOTALSA"), 100, true);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_TOTALDAYCOMPLETEDSA"), 100, true);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_TOTALWEEKCOMPLETEDSA"), 400, true);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_TOTALMONTHCOMPLETEDSA"), 1800, true);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CONSECUTIVEDAYCOMPLETEDSA"), 30, true);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CONSECUTIVEWEEKCOMPLETEDSA"), 4, true);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CONSECUTIVEMONTHCOMPLETESA"), 1, true);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_DAILYOBJCOMPLETEDSA"), 100, true);
			STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_AWD_DAILYOBJCOMPLETED"), 100, true);
			});

			ImGui::TreePop();
		}

		ImGui::EndGroup();

		ImGui::Separator();

		components::sub_title("Police");

		ImGui::Checkbox("Never Wanted", &g.self.never_wanted);

		if (!g.self.never_wanted)
		{
			ImGui::Checkbox("Force Wanted Level", &g.self.force_wanted_level);
			ImGui::Text("Wanted Level");
			if (
				ImGui::SliderInt("###wanted_level", &g.self.wanted_level, 0, 5) &&
				!g.self.force_wanted_level &&
				g_local_player != nullptr
				) {
				g_local_player->m_player_info->m_wanted_level = g.self.wanted_level;
			}
		}

		ImGui::Separator();

		components::sub_title("HUD");

		ImGui::BeginGroup();

		ImGui::Checkbox("Hide Radar", &g.self.hide_radar);

		ImGui::SameLine();

		ImGui::Checkbox("Hide Ammo", &g.self.hide_ammo);

		ImGui::SameLine();

		ImGui::Checkbox("Force show HUD", &g.self.force_show_hud);

		ImGui::Combo("##hud_comp_combo", &g.self.selected_hud_component, hud_component_names, (int)HudComponents::HUD_WEAPONS);
		ImGui::SameLine();
		components::button("Hide", [] {
			g.self.hud_components_states[g.self.selected_hud_component] = true;
		});
		ImGui::SameLine();
		components::button("Show", [] {
			g.self.hud_components_states[g.self.selected_hud_component] = false;
		});

		components::button("Hide all", [] {
			g.self.hide_radar = true;
			g.self.hide_ammo = true;
			for (int i = 0; i < (int)HudComponents::HUD_WEAPONS; i++)
			{
				g.self.hud_components_states[i] = true;
			}
		});
		ImGui::SameLine();
		components::button("Show all", [] {
			g.self.hide_radar = false;
			g.self.hide_ammo = false;
			for (int i = 0; i < (int)HudComponents::HUD_WEAPONS; i++)
			{
				g.self.hud_components_states[i] = false;
			}
		});
		ImGui::SameLine();
		ImGui::Checkbox("Force show HUD element", &g.self.force_show_hud_element);

		ImGui::EndGroup();

		g.self.proof_mask = 0;
		if (g.self.god_mode)
		{
			g.self.proof_mask |= static_cast<int>(eEntityProofs::GOD);
		}
		if (g.self.proof_bullet)
		{
			g.self.proof_mask |= static_cast<int>(eEntityProofs::BULLET);
		}
		if (g.self.proof_fire)
		{
			g.self.proof_mask |= static_cast<int>(eEntityProofs::FIRE);
		}
		if (g.self.proof_collision)
		{
			g.self.proof_mask |= static_cast<int>(eEntityProofs::COLLISION);
		}
		if (g.self.proof_melee)
		{
			g.self.proof_mask |= static_cast<int>(eEntityProofs::MELEE);
		}
		if (g.self.proof_explosion)
		{
			g.self.proof_mask |= static_cast<int>(eEntityProofs::EXPLOSION);
		}
		if (g.self.proof_steam)
		{
			g.self.proof_mask |= static_cast<int>(eEntityProofs::STEAM);
		}
		if (g.self.proof_drown)
		{
			g.self.proof_mask |= static_cast<int>(eEntityProofs::DROWN);
		}
		if (g.self.proof_water)
		{
			g.self.proof_mask |= static_cast<int>(eEntityProofs::WATER);
		}
	}
}
