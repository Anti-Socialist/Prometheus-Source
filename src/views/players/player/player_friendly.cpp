#include "views/view.hpp"
#include "util/friendly.hpp"
#include "util/troll.hpp"
#include "util/toxic.hpp"
#include "pointers.hpp"


namespace big
{
	void view::player_friendly()
	{
		if (ImGui::TreeNode("Friendly (Risky)"))
		{
			components::button("Give All Collectables", [] {
				friendly::give_all_pickups(g_player_service->get_selected()->id());
				});

			components::button("Drop Alien Figurines", [] {
				friendly::alien_pickup(g_player_service->get_selected()->id());
				});

			components::button("Drop Beast Figurines", [] {
				friendly::beast_pickup(g_player_service->get_selected()->id());
				});

			components::button("Drop Imporage Figurines", [] {
				friendly::imporage_pickup(g_player_service->get_selected()->id());
				});

			components::button("Drop Pogo Figurines", [] {
				friendly::pogo_pickup(g_player_service->get_selected()->id());
				});

			components::button("Drop Prbubble Figurines", [] {
				friendly::prbubble_pickup(g_player_service->get_selected()->id());
				});

			components::button("Drop Rsrcomm Figurines", [] {
				friendly::rsrcomm_pickup(g_player_service->get_selected()->id());
				});

			components::button("Drop Rsrgeneric Figurines", [] {
				friendly::rsrgeneric_pickup(g_player_service->get_selected()->id());
				});

			components::button("Drop Playing Cards", [] {
				friendly::cards_pickup(g_player_service->get_selected()->id());
				});

			ImGui::Checkbox("Money Drop", &g.self.money_drop);
			ImGui::Checkbox("Collectable Drop", &g.self.collectable_drop);

			components::button("10k Ped", [] { toxic::golden_ped(g_player_service->get_selected()->id()); });

			components::button("Give 15 Million", [] { toxic::money(g_player_service->get_selected()); });
		}
	}
}