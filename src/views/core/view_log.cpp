#include "views/view.hpp"
#include "fiber_pool.hpp"
#include "natives.hpp"
#include "logger.hpp"

#include "backend/command.hpp"
#include "backend/context/console_command_context.hpp"
#include "gui.hpp"

namespace big
{
	static ImVec4 get_color(const LEVELS level)
	{
		switch (level.value)
		{
		case g3::kDebugValue:
			return ImVec4(0.0f, 0.44f, 0.85f, 1.0f);
		case g3::kInfoValue:
			return ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
		case g3::kWarningValue:
			return ImVec4(1.0f, 0.7f, 0.0f, 1.0f);
		}
		return g3::internal::wasFatal(level) ? ImVec4(1.0f, 0.4f, 0.4f, 1.0f) : ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
	}

	static size_t iLastLogCount = 0;

	void view::log()
	{
		if (!g.window.console_log.opened || !g_gui->is_open())
            return;		

		if (ImGui::Begin("Console", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoNav))
		{
			components::sub_title("Menu Logs");
			const auto msgs = g_log->get_messages();

			ImGuiListClipper clipper;
			clipper.Begin((int)msgs.size());
			const float footer_height_to_reserve = ImGui::GetStyle().ItemSpacing.y + ImGui::GetFrameHeightWithSpacing();
			ImGui::BeginChild("##scrolling_region_log", ImVec2(0, -footer_height_to_reserve), true, ImGuiWindowFlags_HorizontalScrollbar);

			ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(4, 1)); // Tighten spacing

			while (clipper.Step())
			{
				for (int i = clipper.DisplayStart; i < clipper.DisplayEnd; i++)
				{
					ImGui::PushStyleColor(ImGuiCol_Text, get_color(msgs[i].m_level));
					ImGui::TextUnformatted(msgs[i].m_message.c_str());
					ImGui::PopStyleColor();
				}
			}

			if (ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
				ImGui::SetScrollHereY(1.0f);

			ImGui::PopStyleVar();
			ImGui::EndChild();

			static std::string command_input;
			// TODO: Move this to components
			static ImGuiInputTextFlags flags = ImGuiInputTextFlags_CtrlEnterForNewLine | ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_EscapeClearsAll | ImGuiInputTextFlags_CallbackCompletion | ImGuiInputTextFlags_CallbackHistory;
			if (ImGui::IsItemActive())
			{
				g_fiber_pool->queue_job([] {
					PAD::DISABLE_ALL_CONTROL_ACTIONS(0);
				});
			}

			ImGui::End();
		}
	}
}