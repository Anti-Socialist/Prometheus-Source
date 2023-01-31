#include "views/view.hpp"
#include "util/teleport.hpp"
#include "util/toxic.hpp"
#include "util/kick.hpp"

namespace big
{
	void view::player_acrobatic()
	{
		if (ImGui::TreeNode("Vehicle Acrobatics"))
		{
			components::button("Front flip", []
							   { toxic::front_flip(g_player_service->get_selected()->id()); });
			ImGui::SameLine();
			components::button("Back flip", []
							   { toxic::back_flip(g_player_service->get_selected()->id()); });

			components::button("Kick flip", []
							   { toxic::kick_flip(g_player_service->get_selected()->id()); });
			ImGui::SameLine();
			components::button("Heel flip", []
							   { toxic::heel_flip(g_player_service->get_selected()->id()); });

			components::button("Bunny hop", []
							   { toxic::bunny_hop(g_player_service->get_selected()->id()); });
			ImGui::SameLine();
			components::button("Crush", []
							   { toxic::crush_vehicle(g_player_service->get_selected()->id()); });

			ImGui::TreePop();
		}
	}
}