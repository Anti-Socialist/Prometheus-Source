#include "views/view.hpp"
#include "util/toxic.hpp"

namespace big
{
	void view::player_misc()
	{
		if (ImGui::TreeNode("Misc"))
		{
			components::player_command_button<"joinceo">(g_player_service->get_selected());
			components::player_command_button<"enterint">(g_player_service->get_selected());
			components::player_command_button<"copyoutfit">(g_player_service->get_selected());
			ImGui::SameLine();
			components::player_command_button<"copymodel">(g_player_service->get_selected());
			components::player_command_button<"clearwanted">(g_player_service->get_selected());
			ImGui::SameLine();
			components::player_command_button<"givehealth">(g_player_service->get_selected());
			ImGui::SameLine();
			components::player_command_button<"givearmor">(g_player_service->get_selected());
			ImGui::SameLine();
			components::player_command_button<"giveammo">(g_player_service->get_selected());
			components::button("Send Mugger", []
			{
				*script_global(1853348).at(834).at(1).as<Player*>() = g_player_service->get_selected()->id();
				scripts::start_launcher_script(140);
			});
			components::button("Send Gooch", []
			{
				*script_global(1890140).at(244).at(1).as<Player*>() = g_player_service->get_selected()->id();
				scripts::start_launcher_script(171);
			});

			ImGui::Checkbox("Off The Radar", &g_player_service->get_selected()->off_radar);
			ImGui::Checkbox("Never Wanted", &g_player_service->get_selected()->never_wanted);
			ImGui::Checkbox("Semi Godmode", &g_player_service->get_selected()->semi_godmode);

			ImGui::TreePop();
		}
	}
}