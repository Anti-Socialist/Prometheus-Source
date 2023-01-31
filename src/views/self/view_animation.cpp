#include "views/view.hpp"
#include "fiber_pool.hpp"
#include "util/ped.hpp"
#include "services/gta_data/gta_data_service.hpp"
#include "core/data/animations.hpp"

namespace big
{
	void view::animation()
	{
		static bool flag_repeat = false;
		static bool flag_stop_last_frame = false;
		static bool flag_upperbody = false;
		static bool flag_enable_player_control = false;
		static bool flag_cancelable = false;

		components::sub_title("Animation List");

		if (ImGui::Button("Stop Animation", { 500,0 }))
		{
			g_fiber_pool->queue_job([] {TASK::CLEAR_PED_TASKS_IMMEDIATELY(self::ped); });
		}

		static char search[256];
		ImGui::SetNextItemWidth(500);
		components::input_text_with_hint("Animation Name", "Search", search, sizeof(search), ImGuiInputTextFlags_None);

		ImGui::ListBoxHeader("##Animation Box Header", { 500,static_cast<float>(*g_pointers->m_resolution_x * 0.2) });
		{
			std::string lower_search = search;
			std::transform(lower_search.begin(), lower_search.end(), lower_search.begin(), tolower);
			for (auto& item : animations)
			{
				std::string display_name = item.second;
				std::string lower_display_name = display_name;
				std::transform(lower_display_name.begin(), lower_display_name.end(), lower_display_name.begin(), ::tolower);
				if (lower_display_name.find(lower_search) != std::string::npos)
				{
					components::selectable(std::format("{}##{}: {}", display_name, item.first, item.second), false, [&item] {
						int flag = ANIM_FLAG_NORMAL;
						if (flag_repeat) flag |= ANIM_FLAG_REPEAT;
						if (flag_stop_last_frame) flag |= ANIM_FLAG_STOP_LAST_FRAME;
						if (flag_upperbody) flag |= ANIM_FLAG_UPPERBODY;
						if (flag_enable_player_control) flag |= ANIM_FLAG_ENABLE_PLAYER_CONTROL;
						if (flag_cancelable) flag |= ANIM_FLAG_CANCELABLE;
						ped::play_animation(self::ped, item.first.c_str(), item.second.c_str(), flag);
					});
				}
			}
		}
		ImGui::ListBoxFooter();

		ImGui::Separator();

		components::sub_title("Flag");
		ImGui::Checkbox("Repeat", &flag_repeat);
		ImGui::Checkbox("Stop Last Frame", &flag_stop_last_frame);
		ImGui::Checkbox("Upper Body", &flag_upperbody);
		ImGui::Checkbox("Enable Player Control", &flag_enable_player_control);
		ImGui::Checkbox("Cancelable", &flag_cancelable);

		ImGui::Separator();

		components::sub_title("Other");

		if (ImGui::TreeNode("Walking Styles"))
		{

			components::button("Male Default", [] { ped::setPlayerWalkingStyle("move_m@generic"); });
			components::button("Female Default", [] { ped::setPlayerWalkingStyle("move_f@generic"); });
			components::button("Fat Fuck", [] { ped::setPlayerWalkingStyle("move_m@fat@a"); });
			components::button("Drunk", [] { ped::setPlayerWalkingStyle("move_m@drunk@verydrunk"); });
			components::button("Gangster", [] { ped::setPlayerWalkingStyle("move_m@gangster@var_e"); });
			components::button("Injured", [] { ped::setPlayerWalkingStyle("move_m@injured"); });
			components::button("Business Man", [] { ped::setPlayerWalkingStyle("move_m@business@a"); });
			components::button("Hiker", [] { ped::setPlayerWalkingStyle("move_m@hiking"); });
			components::button("Running", [] { ped::setPlayerWalkingStyle("move_f@film_reel"); });

			ImGui::TreePop();
		}

		if (ImGui::TreeNode("Scenarios"))
		{

			components::button("Kill Animation", [] { TASK::CLEAR_PED_TASKS_IMMEDIATELY(PLAYER::PLAYER_PED_ID()); });
			components::button("Paparazzi", [] { TASK::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_PAPARAZZI", 0, true); });

			components::button("Drug Dealer", [] { TASK::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_DRUG_DEALER_HARD", 0, true); });
			ImGui::SameLine();
			components::button("Drinking Coffee", [] { TASK::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_AA_COFFEE", 0, true); });

			components::button("Playing Instruments", [] { TASK::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_MUSICIAN", 0, true); });
			ImGui::SameLine();
			components::button("Flexing", [] { TASK::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_MUSCLE_FLEX", 0, true); });

			components::button("Jogging", [] { TASK::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_JOG_STANDING", 0, true); });
			ImGui::SameLine();
			components::button("Binoculars", [] { TASK::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_BINOCULARS", 0, true); });

			components::button("Clipboard", [] { TASK::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_CLIPBOARD", 0, true); });
			ImGui::SameLine();
			components::button("Bench Press", [] { TASK::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "PROP_HUMAN_SEAT_MUSCLE_BENCH_PRESS", 0, true); });

			components::button("Chin Ups", [] { TASK::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "PROP_HUMAN_MUSCLE_CHIN_UPS", 0, true); });
			ImGui::SameLine();
			components::button("BBQ", [] { TASK::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "PROP_HUMAN_BBQ", 0, true); });

			components::button("Superhero", [] { TASK::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_SUPERHERO", 0, true); });
			ImGui::SameLine();
			components::button("Fishing", [] { TASK::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_STAND_FISHING", 0, true); });

			components::button("Security", [] { TASK::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_SECURITY_SHINE_TORCH", 0, true); });
			ImGui::SameLine();
			components::button("Leaf Blower", [] { TASK::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_GARDENER_LEAF_BLOWER", 0, true); });

			components::button("Film Shocking", [] { TASK::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_MOBILE_FILM_SHOCKING", 0, true); });
			ImGui::SameLine();
			components::button("Idle Cop", [] { TASK::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_COP_IDLES", 0, true); });

			components::button("Drinking", [] { TASK::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_DRINKING", 0, true); });
			ImGui::SameLine();
			components::button("Golf Player", [] { TASK::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_GOLF_PLAYER", 0, true); });

			components::button("Welding", [] { TASK::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_WELDING", 0, true); });
			ImGui::SameLine();
			components::button("Smoking Pot", [] { TASK::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_SMOKING_POT", 0, true); });

			components::button("Hammering", [] { TASK::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_HAMMERING", 0, true); });
			ImGui::SameLine();

			components::button("Tennis", [] { TASK::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_TENNIS_PLAYER", 0, true); });
			ImGui::SameLine();
			components::button("Drilling", [] { TASK::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_CONST_DRILL", 0, true); });

			ImGui::TreePop();
		}
	}
}