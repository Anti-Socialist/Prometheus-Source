#include "backend/player_command.hpp"
#include "natives.hpp"
#include "pointers.hpp"
#include "core/scr_globals.hpp"
#include "util/scripts.hpp"
#include "gta_util.hpp"
#include "util/troll.hpp"
#include "util/toxic.hpp"

#include <network/Network.hpp>


namespace big::friendly
{
	inline void give_all_pickups(Player player)
	{
		static Hash prop_list[] = { 437412629, 1298470051, 1955543594, 446117594, 1025210927, 3644302825, 601745115, 2568981558, 3030532197 };
		STREAMING::REQUEST_MODEL(prop_list[rand() % 9]);
		if (STREAMING::HAS_MODEL_LOADED(prop_list[rand() % 9])) {
			Vector3 coords = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_player_service->get_selected()->id()), false);

			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 437412629, false, true);
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 1298470051, false, true);
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 1955543594, false, true);
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 446117594, false, true);
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 3644302825, false, true);
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 601745115, false, true);
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 1298470051, false, true);
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 2568981558, false, true);
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 3030532197, false, true);



			STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(prop_list[rand() % 8]);
		}
		script::get_current()->yield();
	}

	inline void alien_pickup(Player player)
	{
		STREAMING::REQUEST_MODEL(1298470051);
		if (STREAMING::HAS_MODEL_LOADED(1298470051)) {
			Vector3 coords = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_player_service->get_selected()->id()), false);
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 1298470051, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 1298470051, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 1298470051, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 1298470051, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 1298470051, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 1298470051, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 1298470051, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 1298470051, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 1298470051, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 1298470051, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 1298470051, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 1298470051, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 1298470051, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 1298470051, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 1298470051, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 1298470051, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 1298470051, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 1298470051, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 1298470051, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 1298470051, false, true);
			STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(1298470051);
		}
		script::get_current()->yield();
	}

	inline void beast_pickup(Player player)
	{
		STREAMING::REQUEST_MODEL(1955543594);
		if (STREAMING::HAS_MODEL_LOADED(1955543594)) { 
			Vector3 coords = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_player_service->get_selected()->id()), false);
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 1955543594, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 1955543594, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 1955543594, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 1955543594, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 1955543594, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 1955543594, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 1955543594, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 1955543594, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 1955543594, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 1955543594, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 1955543594, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 1955543594, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 1955543594, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 1955543594, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 1955543594, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 1955543594, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 1955543594, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 1955543594, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 1955543594, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 1955543594, false, true);
			STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(1955543594);
		}
		script::get_current()->yield();
	}

	inline void imporage_pickup(Player player)
	{
		STREAMING::REQUEST_MODEL(446117594);
		if (STREAMING::HAS_MODEL_LOADED(446117594)) {
			Vector3 coords = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_player_service->get_selected()->id()), false);
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 446117594, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 446117594, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 446117594, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 446117594, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 446117594, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 446117594, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 446117594, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 446117594, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 446117594, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 446117594, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 446117594, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 446117594, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 446117594, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 446117594, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 446117594, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 446117594, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 446117594, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 446117594, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 446117594, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 446117594, false, true);
			STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(446117594);
		}
		script::get_current()->yield();
	}

	inline void pogo_pickup(Player player)
	{
		STREAMING::REQUEST_MODEL(1025210927);
		if (STREAMING::HAS_MODEL_LOADED(1025210927)) { 

			Vector3 coords = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_player_service->get_selected()->id()), false);
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 1025210927, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 1025210927, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 1025210927, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 1025210927, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 1025210927, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 1025210927, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 1025210927, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 1025210927, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 1025210927, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 1025210927, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 1025210927, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 1025210927, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 1025210927, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 1025210927, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 1025210927, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 1025210927, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 1025210927, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 1025210927, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 1025210927, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 1025210927, false, true);
			STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(1025210927);
		}
		script::get_current()->yield();
	}

	inline void prbubble_pickup(Player player)
	{
		STREAMING::REQUEST_MODEL(437412629);
		if (STREAMING::HAS_MODEL_LOADED(437412629)) {
			Vector3 coords = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_player_service->get_selected()->id()), false);
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 437412629, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 437412629, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 437412629, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 437412629, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 437412629, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 437412629, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 437412629, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 437412629, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 437412629, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 437412629, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 437412629, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 437412629, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 437412629, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 437412629, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 437412629, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 437412629, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 437412629, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 437412629, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 437412629, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 437412629, false, true);
			STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(437412629);
		}
		script::get_current()->yield();
	}

	inline void rsrcomm_pickup(Player player)
	{
		STREAMING::REQUEST_MODEL(3644302825);
		if (STREAMING::HAS_MODEL_LOADED(3644302825)) {
			Vector3 coords = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_player_service->get_selected()->id()), false);
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 3644302825, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 3644302825, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 3644302825, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 3644302825, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 3644302825, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 3644302825, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 3644302825, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 3644302825, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 3644302825, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 3644302825, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 3644302825, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 3644302825, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 3644302825, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 3644302825, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 3644302825, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 3644302825, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 3644302825, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 3644302825, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 3644302825, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 3644302825, false, true);
			STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(3644302825);
		}
		script::get_current()->yield();
	}

	inline void rsrgeneric_pickup(Player player)
	{
		STREAMING::REQUEST_MODEL(601745115);
		if (STREAMING::HAS_MODEL_LOADED(601745115)) {
			Vector3 coords = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_player_service->get_selected()->id()), false);
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 601745115, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 601745115, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 601745115, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 601745115, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 601745115, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 601745115, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 601745115, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 601745115, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 601745115, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 601745115, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 601745115, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 601745115, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 601745115, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 601745115, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 601745115, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 601745115, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 601745115, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 601745115, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 601745115, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 601745115, false, true);
			STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(601745115);
		}
		script::get_current()->yield();
	}

	inline void set_bounty()
	{
		g_player_service->iterate([](auto& plyr)
			{
				for (int i = 0; i < 1; i++)
				{
					if (PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i) == PLAYER::PLAYER_PED_ID()) continue;
					{
						troll::set_bounty_on_player(g_player_service->get_by_id(i), 10000, g.session.anonymous_bounty);
						script::get_current()->yield(3s);
						toxic::blame_explode_all();
					}
				}
			});
	}

	inline void cards_pickup(Player player)
	{
		STREAMING::REQUEST_MODEL(3030532197);
		if (STREAMING::HAS_MODEL_LOADED(3030532197)) {
			Vector3 coords = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_player_service->get_selected()->id()), false);
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 3030532197, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 3030532197, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 3030532197, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 3030532197, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 3030532197, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 3030532197, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 3030532197, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 3030532197, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 3030532197, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 3030532197, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 3030532197, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 3030532197, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 3030532197, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 3030532197, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 3030532197, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 3030532197, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 3030532197, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 3030532197, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 3030532197, false, true);
			
			OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, coords.x, coords.y, coords.z + 2.0f, 0, 10, 3030532197, false, true);
			STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(3030532197);
		}
		script::get_current()->yield();
	}
}