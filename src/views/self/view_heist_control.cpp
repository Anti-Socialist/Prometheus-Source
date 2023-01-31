#include "views/view.hpp"
#include "util/heist_control.hpp"
#include "util/teleport.hpp"

namespace big
{
	void view::heist_control() {
		components::sub_title("Automated Presets");

		components::button("Instant Setup", [] {
			heist_control::oneClickCayoSetup(4188152);
			});

		components::sub_title("1 Player");
		ImGui::BeginGroup();

		components::button("Sapphire Panther", [] {
			heist_control::sapphire_panther1();
			});
		ImGui::SameLine();

		components::button("Ruby Necklace", [] {
			heist_control::ruby_necklace1();
			});

		ImGui::EndGroup();

		components::sub_title("2 Player");

		ImGui::BeginGroup();

		components::button("Sapphire Panther", [] {
			heist_control::sapphire_panther2();
			});
		ImGui::SameLine();

		components::button("Ruby Necklace", [] {
			heist_control::ruby_necklace2();
			});

		ImGui::EndGroup();

		components::sub_title("3 Player");

		ImGui::BeginGroup();

		components::button("Sapphire Panther", [] {
			heist_control::sapphire_panther3();
			});
		ImGui::SameLine();

		components::button("Ruby Necklace", [] {
			heist_control::ruby_necklace3();
			});

		ImGui::EndGroup();

		components::sub_title("4 Player");

		ImGui::BeginGroup();

		components::button("Sapphire Panther", [] {
			heist_control::sapphire_panther4();
			});
		ImGui::SameLine();

		components::button("Ruby Necklace", [] {
			heist_control::ruby_necklace4();
			});

		ImGui::EndGroup();

		components::sub_title("Custom Teleports");

		components::sub_title("Compound");

		components::sub_title("Storage");

		ImGui::BeginGroup();

		components::button("North", [] {
			teleport::north_storage();
			});
		ImGui::SameLine();

		components::button("West", [] {
			teleport::west_storage();
			});
		ImGui::SameLine();

		components::button("South", [] {
			teleport::south_storage();
			});

		components::sub_title("Vault");

		components::button("Primary Target", [] {
			teleport::primary_targetcayo();
			});

		ImGui::SameLine();

		components::button("Secondary Target", [] {
			teleport::secondary_targetcayo();
			});

		ImGui::SameLine();

		components::button("El Rubio's Office", [] {
			teleport::el_rubios_office();
			});

		ImGui::SameLine();

		components::button("Front Gate Exit", [] {
			teleport::frontgate_exit();
			});

		components::sub_title("Island");

		components::sub_title("Airstrip");

		components::button("Loot #1", [] {
			teleport::loot_1();
			});
		ImGui::SameLine();

		components::button("Loot #2", [] {
			teleport::loot_2();
			});
		ImGui::SameLine();

		components::button("Loot #3", [] {
			teleport::loot_3();
			});

		components::sub_title("Crop Fields");

		components::button("Loot #1", [] {
			teleport::crop_fields_loot();
			});

		components::sub_title("Main Dock");

		components::button("Loot #1", [] {
			teleport::main_dock1();
			});

		ImGui::SameLine();

		components::button("Loot #2", [] {
			teleport::main_dock2();
			});

		ImGui::SameLine();

		components::button("Loot #3", [] {
			teleport::main_dock3();
			});
		ImGui::SameLine();

		components::button("Loot #4", [] {
			teleport::main_dock4();
			});

		components::sub_title("North Dock");

		components::button("Loot #1", [] {
			teleport::north_dock1();
			});

		ImGui::SameLine();

		components::button("Loot #2", [] {
			teleport::north_dock2();
			});

		ImGui::SameLine();

		components::button("Loot #3", [] {
			teleport::north_dock3();
			});

		components::sub_title("Entrance");

		components::button("Radio Tower", [] {
			teleport::radio_tower();
			});

		ImGui::SameLine();

		components::button("Drainage Pipe", [] {
			teleport::drainage_pipe();
			});

		ImGui::SameLine();

		components::button("Drainage: 2nd Checkpoint", [] {
			teleport::drainage_checkpoint();
			});

		ImGui::SameLine();

		components::button("Ocean (Safe Zone)", [] {
			teleport::ocean_safepoint();
			});

		//components::sub_title("Bag Capacity Modifier"); // Work On
	}
}