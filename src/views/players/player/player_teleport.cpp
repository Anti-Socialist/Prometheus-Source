#include "views/view.hpp"
#include "util/teleport.hpp"
#include "util/vehicle.hpp"
#include "util/troll.hpp"

namespace big
{
	void view::player_teleport()
	{
		if (ImGui::TreeNode("Teleport"))
		{
			components::player_command_button<"playertp">(g_player_service->get_selected());
			ImGui::SameLine();
			components::player_command_button<"bring">(g_player_service->get_selected());

			components::player_command_button<"playervehtp">(g_player_service->get_selected());
			components::player_command_button<"rcplayer">(g_player_service->get_selected());

			ImGui::TreePop();
		}
	}
}