#include "views/view.hpp"
#include "util/teleport.hpp"
#include "util/toxic.hpp"
#include "util/kick.hpp"
#include "util/player.hpp"
#include "services/gta_data/gta_data_service.hpp"

namespace big
{
	void view::player_anti_cheat()
	{
		CPlayerInfo* player_info = g_player_service->get_selected()->get_player_info();
		CPed* cped = g_player_service->get_selected()->get_ped();
		if (ImGui::TreeNode("Anti Cheat"))
		{
			if (rage::rlGamerInfo* net_player_data = g_player_service->get_selected()->get_net_data(); net_player_data != nullptr)
			{
				if (ImGui::TreeNode("Net Info"))
				{
					ImGui::Text("Rockstar ID: %d", net_player_data->m_gamer_handle_2.m_rockstar_id);

					ImGui::SameLine();

					if (ImGui::Button("Copy##RID")) ImGui::SetClipboardText(std::to_string(net_player_data->m_gamer_handle_2.m_rockstar_id).data());

					if (g_player_service->get_selected()->real_rid != net_player_data->m_gamer_handle_2.m_rockstar_id)
					{
						ImGui::Text("Real Rockstar ID: %d", g_player_service->get_selected()->real_rid);
						ImGui::SameLine();
						if (ImGui::Button("Copy##IP")) ImGui::SetClipboardText(std::to_string(g_player_service->get_selected()->real_rid).data());
					}

					ImGui::Text(
						"IP Address: %d.%d.%d.%d:%d",
						net_player_data->m_external_ip.m_field1,
						net_player_data->m_external_ip.m_field2,
						net_player_data->m_external_ip.m_field3,
						net_player_data->m_external_ip.m_field4,
						net_player_data->m_external_port
					);

					ImGui::SameLine();

					if (ImGui::Button("Copy"))
					{
						ImGui::SetClipboardText(std::format("{}.{}.{}.{}:{}", net_player_data->m_external_ip.m_field1,
							net_player_data->m_external_ip.m_field2,
							net_player_data->m_external_ip.m_field3,
							net_player_data->m_external_ip.m_field4,
							net_player_data->m_external_port).data()
						);
					}

					//ImGui::Text("Game State: %s", game_states[(int32_t)player_info->m_game_state]);

					components::button("Open SC Overlay", [] {
						int gamerHandle;
					NETWORK::NETWORK_HANDLE_FROM_PLAYER(g_player_service->get_selected()->id(), &gamerHandle, 13);
					NETWORK::NETWORK_SHOW_PROFILE_UI(&gamerHandle);
						});
					ImGui::TreePop();
				}
			}

			if (persistent_player* current_player = g_player_database_service->get_player_by_rockstar_id(g_player_service->get_selected()->real_rid); current_player != nullptr)
			{
				if (ImGui::TreeNode("Infractions"))
				{
					if (!current_player->infractions.empty())
					{
						for (auto& infraction : current_player->infractions)
						{
							ImGui::BulletText(infraction_desc[(Infraction)infraction]);
						}
					}
					ImGui::TreePop();
				}
			}

			if (cped != nullptr)
			{
				if (ImGui::TreeNode("Ped Info"))
				{
					ImGui::Text("Health: %f / %f", cped->m_health, cped->m_maxhealth);
					ImGui::SameLine();
					ImGui::Text("Armor: %f", cped->m_armor);
					ImGui::Text("Pos X: %f, Y: %f, Z: %f",
						cped->m_navigation->get_position()->x,
						cped->m_navigation->get_position()->y,
						cped->m_navigation->get_position()->z
					);

					ImGui::Text("Distance: %f", math::distance_between_vectors(misc::fvector3_to_Vector3(*g_local_player->get_position()), misc::fvector3_to_Vector3(*cped->get_position())));
					ImGui::Text("Speed: %f", cped->get_speed());
					ImGui::Text("Can Be Ragdolled: %s", cped->can_be_ragdolled() ? "Yes" : "No");
					ImGui::TreePop();
				}

				if (player_info != nullptr && cped->m_weapon_manager != nullptr)
				{
					if (ImGui::TreeNode("Weapon Info"))
					{
						ImGui::Text("Weapon Name: %s", g_gta_data_service->weapon_by_hash(cped->m_weapon_manager->m_selected_weapon_hash).m_name);
						ImGui::Text("Weapon Display Name: %s", g_gta_data_service->weapon_by_hash(cped->m_weapon_manager->m_selected_weapon_hash).m_display_name);
						if (cped->m_weapon_manager->m_weapon_info != nullptr)
						{
							ImGui::Text("Weapon Damage: %f", cped->m_weapon_manager->m_weapon_info->m_damage);
							ImGui::Text("Weapon Damage Mult: %f", cped->m_weapon_manager->m_weapon_info->m_network_player_damage_modifier);
						}
						else if (cped->m_weapon_manager->m_vehicle_weapon_info != nullptr)
						{
							ImGui::Text("Weapon Damage: %f", cped->m_weapon_manager->m_vehicle_weapon_info->m_damage);
							ImGui::Text("Weapon Damage Mult: %f", cped->m_weapon_manager->m_vehicle_weapon_info->m_network_player_damage_modifier);
						}
						ImGui::Text("Mele Damage Mult: %f", player_info->m_melee_weapon_damage_mult);
						ImGui::TreePop();
					}
				}

				if (cped->m_vehicle != nullptr)
				{
					if (ImGui::TreeNode("Vehicle Info"))
					{
						const auto vehicle = cped->m_vehicle;
						ImGui::Text("Health: %f / %f", vehicle->m_health, vehicle->m_maxhealth);
						ImGui::Text("Engine Health: %f", vehicle->m_engine_health);
						ImGui::Text("Body Health: %f", vehicle->m_body_health);
						ImGui::Text("Petrol Tank Health: %f", vehicle->m_petrol_tank_health);
						ImGui::SameLine();
						ImGui::Text("Deform God: %s", vehicle->m_deform_god ? "Yes" : "No");
						ImGui::Text("Num Passengers %i", vehicle->m_num_of_passengers);
						ImGui::Text("Boost: %f", vehicle->m_boost);
						ImGui::TreePop();
					}
				}

			if (ImGui::TreeNode("Global Stats"))
			{
				ImGui::Text("RP: %d", util::player::get_player_stat<int64_t*>(g_player_service->get_selected()->id(), ePlayerStatType::RP));
				ImGui::SameLine();
				ImGui::Text("Rank: %d", util::player::get_player_stat<int64_t*>(g_player_service->get_selected()->id(), ePlayerStatType::Rank));
				ImGui::Text("Global RP: %d", util::player::get_player_stat<int64_t*>(g_player_service->get_selected()->id(), ePlayerStatType::GlobalRP));

				ImGui::Text("Money Cash: %u", util::player::get_player_stat<uint64_t*>(g_player_service->get_selected()->id(), ePlayerStatType::MoneyCash));
				ImGui::SameLine();
				ImGui::Text("Money Bank: %u", util::player::get_player_stat<uint64_t*>(g_player_service->get_selected()->id(), ePlayerStatType::MoneyAll));

				int64_t* kills = util::player::get_player_stat<int64_t*>(g_player_service->get_selected()->id(), ePlayerStatType::Kills);
				int64_t* deaths = util::player::get_player_stat<int64_t*>(g_player_service->get_selected()->id(), ePlayerStatType::Deaths);
				ImGui::Text("Kills: %d", kills);
				ImGui::SameLine();
				ImGui::Text("Deaths: %d", deaths);


				ImGui::Text("Allows Spectating: %s", util::player::get_player_stat<BOOL*>(g_player_service->get_selected()->id(), ePlayerStatType::CanSpectate) ? "Yes" : "No");

				ImGui::TreePop();
			}
		}

			ImGui::TreePop();
		}
	}
}