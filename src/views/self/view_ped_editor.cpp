// TODO: FaithfulLunaa
//       Get the name of the clothing and display it (in brackets next to the component name)
//       Get the max amount of drawables and textures and display it (in brackets next to the id InputInt)

#include "fiber_pool.hpp"
#include "views/view.hpp"
#include "natives.hpp"
#include "util/ped_editor.hpp"

namespace big
{
	void view::ped_editor()
	{
		components::sub_title("Clothing");

		ImGui::SameLine();

		if (components::button("Help"))
		{
			ImGui::OpenPopup("###help_popup");
		}

		ImGui::SetNextWindowSize(ImVec2{ 400.0f, 0.0f });
		if (ImGui::BeginPopup("###help_popup", ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove))
		{
			ImGui::TextWrapped("For each component, you can set the drawable id and the texture id.");
			ImGui::EndPopup();
		}

		ImGui::Separator();

		if (ImGui::BeginTable("###clothing_table", 4, ImGuiTableFlags_NoSavedSettings))
		{
			for (int i = 0; i < _countof(ped_editor::clothing_component_ids); ++i)
			{
				ImGui::PushID(i);

				ImGui::TableNextRow();
				ImGui::TableNextColumn();

				ImGui::PushItemWidth(10.0f);
				ImGui::Text(ped_editor::clothing_names[i]);
				ImGui::PopItemWidth();

				ImGui::TableNextColumn();

				ImGui::PushItemWidth(150.0f);
				ImGui::InputInt("###clothing_drawable_id", &ped_editor::clothing_drawable_ids[i]);
				ImGui::PopItemWidth();

				ImGui::TableNextColumn();

				ImGui::PushItemWidth(150.0f);
				ImGui::InputInt("###clothing_texture_id", &ped_editor::clothing_texture_ids[i]);
				ImGui::PopItemWidth();

				ImGui::PopID();
			}

			ImGui::EndTable();
		}

		components::sub_title("Props");

		ImGui::Separator();

		if (ImGui::BeginTable("###props_table", 4, ImGuiTableFlags_NoSavedSettings))
		{
			for (int i = 0; i < _countof(ped_editor::prop_component_ids); ++i)
			{
				ImGui::PushID(i);

				ImGui::TableNextRow();
				ImGui::TableNextColumn();

				ImGui::PushItemWidth(10.0f);
				ImGui::Text(ped_editor::prop_names[i]);
				ImGui::PopItemWidth();

				ImGui::TableNextColumn();

				ImGui::PushItemWidth(150.0f);
				ImGui::InputInt("###prop_drawable_id", &ped_editor::prop_drawable_ids[i]);
				ImGui::PopItemWidth();

				ImGui::TableNextColumn();

				ImGui::PushItemWidth(150.0f);
				ImGui::InputInt("###prop_texture_id", &ped_editor::prop_texture_ids[i]);
				ImGui::PopItemWidth();

				ImGui::TableNextColumn();

				components::button("Remove", [i] {
					ped_editor::remove_ped_prop(i);
				});

				ImGui::PopID();
			}

			ImGui::EndTable();
		}

		ImGui::Separator();

		components::button("Get IDs", [] {
			ped_editor::get_ped_clothing();
			ped_editor::get_ped_props();
		});

		ImGui::SameLine();

		components::button("Set IDs", [] {
			ped_editor::set_ped_clothing();
			ped_editor::set_ped_props();
		});

		ImGui::SameLine();

		components::button("Reset Ped", [] {
			PED::SET_PED_DEFAULT_COMPONENT_VARIATION(self::ped);
		});
	}
}
