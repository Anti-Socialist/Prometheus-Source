#include "views/view.hpp"
#include "util/teleport.hpp"
#include "util/toxic.hpp"

namespace big
{
	void view::player_kick()
	{
		if (ImGui::TreeNode("Kick"))
		{
			auto const is_session_host = [] { return gta_util::get_network()->m_game_session_ptr->is_host(); };
			components::sub_title("Kicks");
			components::player_command_button<"breakup">(g_player_service->get_selected());
			ImGui::SameLine();
			components::command_checkbox<"breakupcheating">();
			components::disable_unless(std::not_fn(is_session_host), []
			{
				components::player_command_button<"lckick">(g_player_service->get_selected());
			});
			components::player_command_button<"bailkick">(g_player_service->get_selected());
			components::player_command_button<"nfkick">(g_player_service->get_selected());
			components::player_command_button<"oomkick">(g_player_service->get_selected());
			components::player_command_button<"gikick">(g_player_service->get_selected());
			components::player_command_button<"shkick">(g_player_service->get_selected());
			components::player_command_button<"endkick">(g_player_service->get_selected());
			components::player_command_button<"desync">(g_player_service->get_selected());
            components::player_command_button<"invalidpickup">(g_player_service->get_selected());
			components::sub_title("Crashes");			
			components::player_command_button<"tsecrash">(g_player_service->get_selected());
			components::player_command_button<"crash">(g_player_service->get_selected());
			components::player_command_button<"slodpedcrash">(g_player_service->get_selected());
			components::player_command_button<"desktop">(g_player_service->get_selected());
			components::player_command_button<"fragment">(g_player_service->get_selected());
			components::player_command_button<"soundspam">(g_player_service->get_selected());
			components::player_command_button<"ultimate">(g_player_service->get_selected());
			ImGui::Checkbox("OP CRASH", &g.self.sync_fuzzer);
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip("Teleport to them and wait.");
			ImGui::TreePop();
		}
	}
}