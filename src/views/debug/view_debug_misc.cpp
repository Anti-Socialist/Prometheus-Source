#include "gui/components/components.hpp"
#include "natives.hpp"
#include "util/system.hpp"
#include "util/misc.hpp"
#include "view_debug.hpp"
#include "network/Network.hpp"
#include "script.hpp"
#include "gta/joaat.hpp"
#include "script_global.hpp"
#include "gta_util.hpp"
#include "util/xml_map_loader.hpp"
#include "pugixml.hpp"

namespace big
{
	void debug::misc()
	{
		if (ImGui::BeginTabItem("Misc"))
		{
			components::button("Test", []
				{
					xmlmaploader::load_placements_from_xml_file(R"(C:\Users\customer\AppData\Roaming\PromeTheus\baguette.xml)");
				});

			if (components::button("Dump Entrypoints"))
			{
				system::dump_entry_points();
			}

			components::button("Network Bail", []
			{
				NETWORK::NETWORK_BAIL(16, 0, 0);
			});

			components::button("Remove From Bad Sport", []
			{
				STATS::STAT_SET_FLOAT(RAGE_JOAAT("mpply_overall_badsport"), 0.0f, TRUE);
				STATS::STAT_SET_BOOL(RAGE_JOAAT("mpply_was_i_bad_sport"), FALSE, TRUE);
			});

			components::button("Undo Corruption ", []
			{
				STATS::STAT_SET_INT(RAGE_JOAAT("mpply_last_mp_char"), 0, true);
				STATS::STAT_SET_INT(RAGE_JOAAT("MP0_CHAR_ISACTIVE"), 1, true);
				STATS::STAT_SET_INT(RAGE_JOAAT("MP1_CHAR_ISACTIVE"), 1, true);
			});

			components::button("Force Cloud Save", []
			{
				STATS::STAT_SAVE(0, 0, 3, 0);
			});

			if (components::button("Load MP Map"))
			{
				DLC::ON_ENTER_MP();
			}
			ImGui::SameLine();
			if (components::button("Load SP Map"))
			{
				DLC::ON_ENTER_SP();
            }

			if (components::button("Skip Cutscene"))
			{
				CUTSCENE::STOP_CUTSCENE_IMMEDIATELY();
			}

			if (components::button("Refresh Interior"))
			{
				Interior interior = INTERIOR::GET_INTERIOR_AT_COORDS(self::pos.x, self::pos.y, self::pos.z);
				INTERIOR::REFRESH_INTERIOR(interior);
			}
			if (ImGui::IsItemHovered())
			{
				ImGui::SetTooltip("You Will Have To Refresh Again When Exiting Interior.\n SPAMMING WILL CRASH GAME");
			}

			ImGui::EndTabItem();
		}
	}
}