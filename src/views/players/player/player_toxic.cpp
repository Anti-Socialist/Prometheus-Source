#include "views/view.hpp"
#include "util/teleport.hpp"
#include "util/toxic.hpp"
#include "core/data/apartment_names.hpp"
#include "core/data/warehouse_names.hpp"
#include "util/troll.hpp"

namespace big
{
	void view::player_toxic()
	{
		if (ImGui::TreeNode("Toxic"))
		{
			components::player_command_button<"kill">(g_player_service->get_selected(), {});
			ImGui::SameLine();
			components::player_command_button<"explode">(g_player_service->get_selected(), {});

			components::player_command_button<"ceokick">(g_player_service->get_selected(), {});
			ImGui::SameLine();
			components::button("Blame Explode All", []
							   { toxic::blame_explode_all(); });

			components::player_command_button<"vehkick">(g_player_service->get_selected(), {});
			ImGui::SameLine();
			components::player_command_button<"ragdoll">(g_player_service->get_selected(), {});

			components::button("Taze", []
							   { toxic::taze_player(g_player_service->get_selected()->id()); });
			ImGui::SameLine();
			components::button("Send Attacker", []
							   { toxic::send_attacker(g_player_service->get_selected()->id()); });
			components::button("Ram Player", []
							   { toxic::ram_player(g_player_service->get_selected()->id()); });
			components::button("Big Cage", []
							   { toxic::big_cage(g_player_service->get_selected()->id()); });
			ImGui::SameLine();
			components::button("Cage", []
							   { toxic::cage_him(g_player_service->get_selected()->id()); });

			components::button("Earrape", []
							   { toxic::EarRape(g_player_service->get_selected()->id()); });
			ImGui::SameLine();
			components::button("Emp", []
							   { toxic::emp_player(g_player_service->get_selected()->id()); });

			ImGui::Checkbox("Water Loop", &g.self.water_loop);
			ImGui::SameLine();
			ImGui::Checkbox("Fire Loop", &g.self.fire_loop);

			components::button("Godmode kill", []
							   {
				teleport::teleport_player(g_player_service->get_selected()->id(), Vector3(8110, 20, 0));
			script::get_current()->yield(1s);
			TASK::CLEAR_PED_TASKS_IMMEDIATELY(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_player_service->get_selected()->id()));
			entity::delete_entity(PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_player_service->get_selected()->id()), false)); });
			ImGui::SameLine();
			components::button("Send Moaning Ped", []
							   { toxic::send_moaning_ped(g_player_service->get_selected()->id()); });
			ImGui::SameLine();
			components::player_command_button<"sext">(g_player_service->get_selected(), {});

			static int bounty_value = 0;

			ImGui::SliderInt("Bounty", &bounty_value, 0, 10000);
			ImGui::SameLine();
			components::button("Set", []
							   { troll::set_bounty_on_player(g_player_service->get_selected(), bounty_value, g.session.anonymous_bounty); });

			components::player_command_button<"intkick">(g_player_service->get_selected(), {});
			ImGui::SameLine();
			components::player_command_button<"beast">(g_player_service->get_selected(), {});

			components::button("Airstrike", []
							   { toxic::airstrike(g_player_service->get_selected()->id()); });

			components::player_command_button<"fakeban">(g_player_service->get_selected(), {});
			//ImGui::SameLine();
			//components::button("Corrupt Account", []
			//				   { toxic::ban(g_player_service->get_selected()); });

			components::button("Bounty Player", []
							   { toxic::set_bounty_on_player(g_player_service->get_selected(), 10000); });

			components::player_command_button<"mission">(g_player_service->get_selected(), {});

			components::player_command_button<"error">(g_player_service->get_selected(), {});

			components::player_command_button<"ceoraid">(g_player_service->get_selected(), {});
			ImGui::SameLine();
			components::button("Trigger MC Raid", []
							   { toxic::start_activity(g_player_service->get_selected(), eActivityType::BikerDefend); });
			ImGui::SameLine();
			components::button("Trigger Bunker Raid", []
							   { toxic::start_activity(g_player_service->get_selected(), eActivityType::GunrunningDefend); });

			components::player_command_button<"sext">(g_player_service->get_selected(), {});

			static int wanted_level;
			ImGui::SliderInt("Wanted Level", &wanted_level, 0, 5);
			ImGui::SameLine();
			components::player_command_button<"wanted">(g_player_service->get_selected(), {(uint64_t)wanted_level}, "Set");

			components::small_text("Teleports");

			if (ImGui::BeginCombo("##apartment", apartment_names[g.session.send_to_apartment_idx]))
			{
				for (int i = 1; i < apartment_names.size(); i++)
				{
					if (ImGui::Selectable(apartment_names[i], i == g.session.send_to_apartment_idx))
					{
						g.session.send_to_apartment_idx = i;
					}

					if (i == g.session.send_to_apartment_idx)
					{
						ImGui::SetItemDefaultFocus();
					}
				}

				ImGui::EndCombo();
			}

			ImGui::SameLine();

			components::player_command_button<"apartmenttp">(g_player_service->get_selected(), {(uint64_t)g.session.send_to_apartment_idx});

			if (ImGui::BeginCombo("##warehouse", warehouse_names[g.session.send_to_warehouse_idx]))
			{
				for (int i = 1; i < warehouse_names.size(); i++)
				{
					if (ImGui::Selectable(warehouse_names[i], i == g.session.send_to_warehouse_idx))
					{
						g.session.send_to_warehouse_idx = i;
					}

					if (i == g.session.send_to_warehouse_idx)
					{
						ImGui::SetItemDefaultFocus();
					}
				}

				ImGui::EndCombo();
			}

			ImGui::SameLine();

			components::player_command_button<"warehousetp">(g_player_service->get_selected(), {(uint64_t)g.session.send_to_warehouse_idx});

			components::button("TP To Darts", []
							   { toxic::start_activity(g_player_service->get_selected(), eActivityType::Darts); });
			ImGui::SameLine();
			components::button("TP To Flight School", []
							   { toxic::start_activity(g_player_service->get_selected(), eActivityType::PilotSchool); });
			ImGui::SameLine();
			components::button("TP To Map Center", []
							   { toxic::start_activity(g_player_service->get_selected(), eActivityType::ArmWresling); });

			components::button("TP To Skydive", []
							   { toxic::start_activity(g_player_service->get_selected(), eActivityType::Skydive); });
			ImGui::SameLine();
			components::player_command_button<"cayotp">(g_player_service->get_selected(), {});
			ImGui::SameLine();
			components::player_command_button<"interiortp">(g_player_service->get_selected(), {81}, "TP To MOC");

			components::player_command_button<"interiortp">(g_player_service->get_selected(), {123}, "TP To Casino");
			ImGui::SameLine();
			components::player_command_button<"interiortp">(g_player_service->get_selected(), {124}, "TP To Penthouse");
			ImGui::SameLine();
			components::player_command_button<"interiortp">(g_player_service->get_selected(), {128}, "TP To Arcade");

			components::player_command_button<"interiortp">(g_player_service->get_selected(), {146}, "TP To Music Locker");
			ImGui::SameLine();
			components::player_command_button<"interiortp">(g_player_service->get_selected(), {148}, "TP To Record A Studios");
			ImGui::SameLine();
			components::player_command_button<"interiortp">(g_player_service->get_selected(), {149}, "TP To Custom Auto Shop");

			components::player_command_button<"interiortp">(g_player_service->get_selected(), {155}, "TP To Agency");
			ImGui::SameLine();
			components::player_command_button<"interiortp">(g_player_service->get_selected(), {160}, "TP To Freakshop");
			ImGui::SameLine();
			components::player_command_button<"interiortp">(g_player_service->get_selected(), {161}, "TP To Multi Floor Garage");
			ImGui::SameLine();

			components::player_command_button<"giveweaps">(g_player_service->get_selected(), {});
			ImGui::SameLine();
			components::player_command_button<"remweaps">(g_player_service->get_selected(), {});

			components::player_command_button<"tutorial">(g_player_service->get_selected(), {});
			ImGui::SameLine();
			components::player_command_button<"golf">(g_player_service->get_selected(), {});
			ImGui::SameLine();
			components::player_command_button<"flightschool">(g_player_service->get_selected(), {});
			ImGui::SameLine();
			components::player_command_button<"darts">(g_player_service->get_selected(), {});

			components::player_command_button<"badlands">(g_player_service->get_selected(), {});
			ImGui::SameLine();
			components::player_command_button<"spacemonkey">(g_player_service->get_selected(), {});
			ImGui::SameLine();
			components::player_command_button<"wizard">(g_player_service->get_selected(), {});

			components::player_command_button<"qub3d">(g_player_service->get_selected(), {});
			ImGui::SameLine();
			components::player_command_button<"camhedz">(g_player_service->get_selected(), {});

			components::small_text("Warp Time (requires session host)");

			components::button("+1 Minute", []
							   { toxic::warp_time_forward(g_player_service->get_selected(), 60 * 1000); });
			ImGui::SameLine();
			components::button("+5 Minutes", []
							   { toxic::warp_time_forward(g_player_service->get_selected(), 5 * 60 * 1000); });
			ImGui::SameLine();
			components::button("+48 Minutes", []
							   { toxic::warp_time_forward(g_player_service->get_selected(), 48 * 60 * 1000); });
			ImGui::SameLine();
			components::button("+96 Minutes", []
							   { toxic::warp_time_forward(g_player_service->get_selected(), 96 * 60 * 1000); });
			ImGui::SameLine();
			components::button("+200 Minutes", []
							   { toxic::warp_time_forward(g_player_service->get_selected(), 200 * 60 * 1000); });
			ImGui::SameLine();
			components::button("Stop Time", []
							   { toxic::set_time(g_player_service->get_selected(), INT_MAX - 3000); });

			ImGui::Checkbox("Kill Loop", &g_player_service->get_selected()->kill_loop);
			ImGui::SameLine();
			ImGui::Checkbox("Explosion Loop", &g_player_service->get_selected()->explosion_loop);
			ImGui::SameLine();
			ImGui::Checkbox("Freeze Loop", &g_player_service->get_selected()->freeze_loop);

			ImGui::Checkbox("Ragdoll Loop", &g_player_service->get_selected()->ragdoll_loop);
			ImGui::SameLine();
			ImGui::Checkbox("Rotate Cam Loop", &g_player_service->get_selected()->rotate_cam_loop);
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip("Also brings the player out of godmode if the event isn't blocked");

			ImGui::TreePop();
		}
	}
}