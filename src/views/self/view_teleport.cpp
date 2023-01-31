#include "views/view.hpp"
#include "fiber_pool.hpp"
#include "util/globals.hpp"
#include "util/mobile.hpp"
#include "util/teleport.hpp"
#include "util/vehicle.hpp"

namespace big
{
	void view::teleport()
	{
		ImGui::Text("Blips:");

		components::command_button<"waypointtp">({}, "Waypoint");
		ImGui::SameLine();
		components::command_button<"objectivetp">({}, "Objective");

		ImGui::Checkbox("Auto-Teleport To Waypoint", &g.self.auto_tp);

		ImGui::Text("Vehicles:");
		components::command_button<"lastvehtp">();
		ImGui::SameLine();
		components::command_button<"bringpv">();
		ImGui::SameLine();
		components::command_button<"pvtp">();

		ImGui::Text("Other:");

		if (ImGui::TreeNode("Special Locations")) {

			components::button("North Yankton", []
				{
					teleport::north_yankton();
				});
			ImGui::SameLine();
			components::button("Porn Yacht", []
				{
					teleport::porn_yacht();
				});

			components::button("Aircraft Carrier", []
				{
					teleport::aircraft_carrier();
				});
			ImGui::SameLine();
			components::button("Sunken Cargoship", []
				{
					teleport::sunken_cargoship();
				});

			components::button("Hospital", []
				{
					teleport::hospital();
				});
			ImGui::SameLine();
			components::button("Oneil Farm", []
				{
					teleport::oneil_farm();
				});

			components::button("Lifeinvader Office", []
				{
					teleport::life_invader_office();
				});
			ImGui::SameLine();
			components::button("Cargoship", []
				{
					teleport::cargoship();
				});

			components::button("Jewel Store", []
				{
					teleport::jewel_store();
				});
			ImGui::SameLine();
			components::button("Morgue", []
				{
					teleport::morgue();
				});

			ImGui::TreePop();
		}

		if (ImGui::TreeNode("Landmarks")) {

			components::button("Airport Entrance", []
				{
					teleport::airport_entrance();
				});
			ImGui::SameLine();
			components::button("Airport Field", []
				{
					teleport::arport_field();
				});

			components::button("Cult Camp", []
				{
					teleport::cult_camp();
				});
			ImGui::SameLine();
			components::button("Fort Zancudo", []
				{
					teleport::fort_zancudo();
				});

			components::button("LS Customs", []
				{
					teleport::los_santos_custom();
				});
			ImGui::SameLine();
			components::button("Clothes Store", []
				{
					teleport::clothing_store();
				});

			components::button("Mask Store", []
				{
					teleport::mask_store();
				});
			ImGui::SameLine();
			components::button("Water Fall", []
				{
					teleport::water_fall();
				});

			components::button("Mt. Chiliad", []
				{
					teleport::mount_chiliad();
				});
			ImGui::SameLine();
			components::button("Ferris Wheel", []
				{
					teleport::ferris_wheel();
				});

			ImGui::TreePop();
		}

		if (ImGui::TreeNode("Under Water")) {

			components::button("Dead Sea Monster", []
				{
					teleport::dead_sea_monster();
				});
			ImGui::SameLine();
			components::button("Hatch", []
				{
					teleport::under_water_hatch();
				});

			components::button("Ufo", []
				{
					teleport::under_water_ufo();
				});
			ImGui::SameLine();
			components::button("WW2 Tank", []
				{
					teleport::under_water_ww2_tank();
				});

			components::button("Dead Body", []
				{
					teleport::sunken_body();
				});
			ImGui::SameLine();
			components::button("Cargo Ship", []
				{
					teleport::sunken_cargo_ship();
				});

			ImGui::TreePop();
		}

	}
}