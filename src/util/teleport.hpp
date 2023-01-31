#pragma once
#include "blip.hpp"
#include "entity.hpp"
#include "gta/enums.hpp"
#include "services/players/player_service.hpp"

namespace big::teleport
{
	inline bool teleport_player_to_coords(player_ptr player, Vector3 coords)
	{
		Entity ent = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player->id());

		if (ENTITY::IS_ENTITY_DEAD(ent, true))
		{
			g_notification_service->push_warning("Teleport", "Target player is dead.");
			return false;
		}

		if (!PED::IS_PED_IN_ANY_VEHICLE(ent, true))
		{
			g_notification_service->push_warning("Teleport", "Target player is not in a vehicle.");
			return false;
		}

		ent = PED::GET_VEHICLE_PED_IS_IN(ent, false);

		if (entity::take_control_of(ent))
			ENTITY::SET_ENTITY_COORDS(ent, coords.x, coords.y, coords.z, 0, 0, 0, 0);
		else
			g_notification_service->push_warning("Teleport", "Failed to take control of player vehicle.");

		return true;
	}

	inline bool teleport_player(Player player, Vector3 location)
	{
		Entity ent = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player);

		if (ENTITY::IS_ENTITY_DEAD(ent, true))
		{
			g_notification_service->push_warning("Teleport", "Target player is dead.");

			return false;
		}

		if (!PED::IS_PED_IN_ANY_VEHICLE(ent, true))
		{
			g_notification_service->push_warning("Teleport", "Target player is not in a vehicle.");

			return false;
		}

		ent = PED::GET_VEHICLE_PED_IS_IN(ent, false);

		if (entity::take_control_of(ent))
			ENTITY::SET_ENTITY_COORDS(ent, location.x, location.y, location.z, 0, 0, 0, 0);
		else
			g_notification_service->push_warning("Teleport", "Failed to take control of player vehicle.");

		return true;
	}

	inline bool bring_player(player_ptr player)
	{
		return teleport_player_to_coords(player, self::pos);
	}

	inline bool load_ground_at_3dcoord(Vector3& location)
	{
		float groundZ;
		const uint8_t attempts = 10;

		for (uint8_t i = 0; i < attempts; i++)
		{
			// Only request a collision after the first try failed because the location might already be loaded on first attempt.
			for (uint16_t z = 0; i && z < 1000; z += 100)
			{
				STREAMING::REQUEST_COLLISION_AT_COORD(location.x, location.y, (float)z);

				script::get_current()->yield();
			}

			if (MISC::GET_GROUND_Z_FOR_3D_COORD(location.x, location.y, 1000.f, &groundZ, false, false))
			{
				location.z = groundZ + 1.f;

				return true;
			}

			script::get_current()->yield();
		}

		location.z = 1000.f;

		return false;
	}

	inline bool into_vehicle(Vehicle veh)
	{
		if (!ENTITY::IS_ENTITY_A_VEHICLE(veh))
		{
			g_notification_service->push_warning("Teleport", "Invalid vehicle handle");

			return false;
		}

		int seat_index = 255;
		if (VEHICLE::IS_VEHICLE_SEAT_FREE(veh, -1, true))
			seat_index = -1;
		else if (VEHICLE::IS_VEHICLE_SEAT_FREE(veh, -2, true))
			seat_index = -2;

		if (seat_index == 255)
		{
			g_notification_service->push_warning("Teleport", "No seats are free in the player vehicle.");

			return false;
		}

		Vector3 location = ENTITY::GET_ENTITY_COORDS(veh, true);
		load_ground_at_3dcoord(location);

		Ped ped = self::ped;

		ENTITY::SET_ENTITY_COORDS(ped, location.x, location.y, location.z, 0, 0, 0, 0);

		script::get_current()->yield();

		PED::SET_PED_INTO_VEHICLE(ped, veh, seat_index);

		return true;
	}

	inline void to_coords(Vector3 location)
	{
		PED::SET_PED_COORDS_KEEP_VEHICLE(self::ped, location.x, location.y, location.z + 1.f);
	}


	inline void teleportToLocation(Vector3 Coords)
	{
		int Handle = self::ped;
		if (PED::IS_PED_IN_ANY_VEHICLE(Handle, 0))
		{
			ENTITY::SET_ENTITY_COORDS(PED::GET_VEHICLE_PED_IS_IN(Handle, false), Coords.x, Coords.y, Coords.z, 0, 0, 0, 1);
		}
		else
			ENTITY::SET_ENTITY_COORDS(Handle, Coords.x, Coords.y, Coords.z, 0, 0, 0, 1);
	}


	inline void north_yankton()
	{
		STREAMING::REQUEST_IPL("prologue01");
		STREAMING::REQUEST_IPL("Prologue01c");
		STREAMING::REQUEST_IPL("Prologue01d");
		STREAMING::REQUEST_IPL("Prologue01e");
		STREAMING::REQUEST_IPL("Prologue01f");
		STREAMING::REQUEST_IPL("Prologue01g");
		STREAMING::REQUEST_IPL("prologue01h");
		STREAMING::REQUEST_IPL("prologue01i");
		STREAMING::REQUEST_IPL("prologue01j");
		STREAMING::REQUEST_IPL("prologue01k");
		STREAMING::REQUEST_IPL("prologue01z");
		STREAMING::REQUEST_IPL("prologue02");
		STREAMING::REQUEST_IPL("prologue03");
		STREAMING::REQUEST_IPL("prologue03b");
		STREAMING::REQUEST_IPL("prologue03_grv_cov");
		STREAMING::REQUEST_IPL("prologue03_grv_dug");
		STREAMING::REQUEST_IPL("prologue03_grv_fun");
		STREAMING::REQUEST_IPL("prologue04");
		STREAMING::REQUEST_IPL("prologue04b");
		STREAMING::REQUEST_IPL("prologue04_cover");
		STREAMING::REQUEST_IPL("prologue05");
		STREAMING::REQUEST_IPL("prologue05b");
		STREAMING::REQUEST_IPL("prologue06");
		STREAMING::REQUEST_IPL("prologue06b");
		STREAMING::REQUEST_IPL("prologue06_int");
		STREAMING::REQUEST_IPL("prologuerd");
		STREAMING::REQUEST_IPL("prologuerdb");
		STREAMING::REQUEST_IPL("prologue_DistantLights");
		STREAMING::REQUEST_IPL("prologue_grv_torch");
		STREAMING::REQUEST_IPL("prologue_m2_door");
		STREAMING::REQUEST_IPL("prologue_LODLights");
		STREAMING::REQUEST_IPL("DES_ProTree_start");
		Vector3 Coords;
		Coords.x = 3595.39673f; Coords.y = -4893.727f; Coords.z = 115.838394f;
		teleportToLocation(Coords);
	}

	inline void porn_yacht()
	{
		STREAMING::REQUEST_IPL("smboat");
		Vector3 Coords;
		Coords.x = -2045.8f; Coords.y = -1031.2f; Coords.z = 11.9f;
		teleportToLocation(Coords);
	}

	inline void aircraft_carrier()
	{
		STREAMING::REQUEST_IPL("hei_carrier");
		STREAMING::REQUEST_IPL("hei_carrier_DistantLights");
		STREAMING::REQUEST_IPL("hei_Carrier_int1");
		STREAMING::REQUEST_IPL("hei_Carrier_int2");
		STREAMING::REQUEST_IPL("hei_Carrier_int3");
		STREAMING::REQUEST_IPL("hei_Carrier_int4");
		STREAMING::REQUEST_IPL("hei_Carrier_int5");
		STREAMING::REQUEST_IPL("hei_Carrier_int6");
		STREAMING::REQUEST_IPL("hei_carrier_LODLights");
		Vector3 Coords;
		Coords.x = 3069.330f; Coords.y = -4632.4f; Coords.z = 15.043f;
		teleportToLocation(Coords);
	}
	inline void sunken_cargoship()
	{
		STREAMING::REQUEST_IPL("sunkcargoship");
		Vector3 Coords;
		Coords.x = -162.8918f; Coords.y = -2365.769f; Coords.z = 0.0f;
		teleportToLocation(Coords);
	}
	inline void hospital()
	{
		STREAMING::REQUEST_IPL("RC12B_HospitalInterior");
		STREAMING::REQUEST_IPL("RC12B_Destroyed");
		Vector3 Coords;
		Coords.x = 356.8f; Coords.y = -590.1f; Coords.z = 43.3f;
		teleportToLocation(Coords);
	}
	inline void oneil_farm()
	{
		STREAMING::REMOVE_IPL("farm_burnt");
		STREAMING::REMOVE_IPL("farm_burnt_props");
		STREAMING::REQUEST_IPL("farm");
		STREAMING::REQUEST_IPL("farm_props");
		STREAMING::REQUEST_IPL("farmint");
		STREAMING::REQUEST_IPL("farmint_cap");
		Vector3 Coords;
		Coords.x = 2441.2f; Coords.y = 4968.5f; Coords.z = 51.7f;
		teleportToLocation(Coords);
	}
	inline void life_invader_office()
	{
		STREAMING::REQUEST_IPL("facelobby");
		STREAMING::REQUEST_IPL("facelobbyfake");
		Vector3 Coords;
		Coords.x = -1047.9f; Coords.y = -233.0f; Coords.z = 39.0f;
		teleportToLocation(Coords);
	}
	inline void cargoship()
	{
		STREAMING::REQUEST_IPL("cargoship");
		Vector3 Coords;
		Coords.x = -162.8918f; Coords.y = -2365.769f; Coords.z = 9.3192f;
		teleportToLocation(Coords);
	}
	inline void jewel_store()
	{
		STREAMING::REQUEST_IPL("jewel2fake");
		STREAMING::REQUEST_IPL("post_hiest_unload");
		STREAMING::REQUEST_IPL("bh1_16_refurb");
		Vector3 Coords;
		Coords.x = -630.4f; Coords.y = -236.7f; Coords.z = 40.0f;
		teleportToLocation(Coords);
	}
	inline void morgue()
	{
		STREAMING::REQUEST_IPL("Coroner_Int_on");
		Vector3 Coords;
		Coords.x = 244.9f; Coords.y = -1374.7f; Coords.z = 39.5f;
		teleportToLocation(Coords);
	}

	//underwater start
	inline void dead_sea_monster()
	{
		Vector3 Coords;
		Coords.x = -3373.726; Coords.y = 504.714; Coords.z = -24.656;
		teleportToLocation(Coords);
	}
	inline void under_water_hatch()
	{
		Vector3 Coords;
		Coords.x = 4273.950; Coords.y = 2975.714; Coords.z = -170.746;
		teleportToLocation(Coords);
	}
	inline void under_water_ufo()
	{
		Vector3 Coords;
		Coords.x = 762.426; Coords.y = 7380.371; Coords.z = -111.377;
		teleportToLocation(Coords);
	}
	inline void under_water_ww2_tank()
	{
		Vector3 Coords;
		Coords.x = 4201.633; Coords.y = 3643.821; Coords.z = -39.016;
		teleportToLocation(Coords);
	}
	inline void sunken_body()
	{
		Vector3 Coords;
		Coords.x = -3161.078; Coords.y = 3001.998; Coords.z = -37.974;
		teleportToLocation(Coords);
	}
	inline void sunken_cargo_ship()
	{
		Vector3 Coords;
		Coords.x = 3199.748; Coords.y = -379.018; Coords.z = -22.500;
		teleportToLocation(Coords);;
	}
	//underwater end
	//landmark start
	inline void airport_entrance()
	{
		Vector3 Coords;
		Coords.x = -1034.6; Coords.y = -2733.6; Coords.z = 13.8;
		teleportToLocation(Coords);
	}
	inline void arport_field()
	{
		Vector3 Coords;
		Coords.x = -1102.2910; Coords.y = -2894.5160; Coords.z = 13.9467;
		teleportToLocation(Coords);
	}
	inline void cult_camp()
	{
		Vector3 Coords;
		Coords.x = -1170.841; Coords.y = 4926.646; Coords.z = 224.295;
		teleportToLocation(Coords);
	}
	inline void fort_zancudo()
	{
		Vector3 Coords;
		Coords.x = -2047.4; Coords.y = 3132.1; Coords.z = 32.8;
		teleportToLocation(Coords);
	}
	inline void los_santos_custom()
	{
		Vector3 Coords;
		Coords.x = -373.01; Coords.y = -124.91; Coords.z = 38.31;
		teleportToLocation(Coords);
	}
	inline void clothing_store()
	{
		Vector3 Coords;
		Coords.x = -718.91; Coords.y = -158.16; Coords.z = 37.00;
		teleportToLocation(Coords);
	}
	inline void mask_store()
	{
		Vector3 Coords;
		Coords.x = -1338.16; Coords.y = -1278.11; Coords.z = 4.87;
		teleportToLocation(Coords);
	}
	inline void water_fall()
	{
		Vector3 Coords;
		Coords.x = -597.9525f; Coords.y = 4475.2910f; Coords.z = 25.6890f;
		teleportToLocation(Coords);
	}
	inline void mount_chiliad()
	{
		Vector3 Coords;
		Coords.x = 425.4; Coords.y = 5614.3; Coords.z = 766.5;
		teleportToLocation(Coords);
	}
	inline void ferris_wheel()
	{
		Vector3 Coords;
		Coords.x = -1670.7; Coords.y = -1125.0; Coords.z = 13.0;
		teleportToLocation(Coords);
	}
	//landmark end

	inline bool to_blip(int sprite, int color = -1)
	{
		Vector3 location;

		if (!blip::get_blip_location(location, sprite, color))
			return false;

		if (sprite == (int)BlipIcons::Waypoint)
			load_ground_at_3dcoord(location);

		PED::SET_PED_COORDS_KEEP_VEHICLE(self::ped, location.x, location.y, location.z);

		return true;
	}

	inline bool to_entity(Entity ent)
	{
		Vector3 location = ENTITY::GET_ENTITY_COORDS(ent, true);

		PED::SET_PED_COORDS_KEEP_VEHICLE(self::ped, location.x, location.y, location.z);

		return true;
	}

	inline bool to_player(Player player)
	{
		return to_entity(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player));
	}

	inline bool to_waypoint()
	{
		if (!to_blip((int)BlipIcons::Waypoint))
		{
			g_notification_service->push_warning("Teleport", "Failed to find waypoint position");

			return false;
		}
		return true;
	}

	inline bool to_objective()
	{
		Vector3 location;

		if (!blip::get_objective_location(location))
		{
			g_notification_service->push_warning("Teleport", "Failed to find objective position");
			return false;
		}

		PED::SET_PED_COORDS_KEEP_VEHICLE(self::ped, location.x, location.y, location.z);

		return false;
	}

	inline void primary_targetcayo()
	{
		Vector3 Coords;
		Coords.x = 5006.7; Coords.y = -5756.2; Coords.z = 14.8;
		teleportToLocation(Coords);
	}

	inline void secondary_targetcayo()
	{
		Vector3 Coords;
		Coords.x = 4999.764160; Coords.y = -5749.863770; Coords.z = 14.840000;
		teleportToLocation(Coords);
	}

	inline void el_rubios_office()
	{
		Vector3 Coords;
		Coords.x = 5010.12; Coords.y = -5750.1353; Coords.z = 28.84334;
		teleportToLocation(Coords);
	}

	inline void frontgate_exit()
	{
		Vector3 Coords;
		Coords.x = 4990.0386; Coords.y = -5717.6895; Coords.z = 19.880217;
		teleportToLocation(Coords);
	}

	inline void north_storage()
	{
		Vector3 Coords;
		Coords.x = 5081.0415; Coords.y = -5755.32; Coords.z = 15.829645;
		teleportToLocation(Coords);
	}
	
	inline void west_storage()
	{
		Vector3 Coords;
		Coords.x = 5006.722; Coords.y = -5786.5967; Coords.z = 17.831688;
		teleportToLocation(Coords);
	}

	inline void south_storage()
	{
		Vector3 Coords;
		Coords.x = 5027.603; Coords.y = -5734.682; Coords.z = 17.255005;
		teleportToLocation(Coords);
	}

	inline void loot_1()
	{
		Vector3 Coords;
		Coords.x = 4503.587402; Coords.y = -4555.740723; Coords.z = 2.854459;
		teleportToLocation(Coords);
	}

	inline void loot_2()
	{
		Vector3 Coords;
		Coords.x = 4437.821777; Coords.y = -4447.841309; Coords.z = 3.028436;
		teleportToLocation(Coords);
	}

	inline void loot_3()
	{
		Vector3 Coords;
		Coords.x = 4447.091797; Coords.y = -4442.184082; Coords.z = 5.936794;
		teleportToLocation(Coords);
	}

	inline void crop_fields_loot()
	{
		Vector3 Coords;
		Coords.x = 5330.527; Coords.y = -5269.7515; Coords.z = 33.18603;
		teleportToLocation(Coords);
	}

	inline void main_dock1()
	{
		Vector3 Coords;
		Coords.x = 5193.909668; Coords.y = -5135.642578; Coords.z = 2.045917;
		teleportToLocation(Coords);
	}

	inline void main_dock2()
	{
		Vector3 Coords;
		Coords.x = 4963.184570; Coords.y = -5108.933105; Coords.z = 1.670808;
		teleportToLocation(Coords);
	}

	inline void main_dock3()
	{
		Vector3 Coords;
		Coords.x = 4998.709473; Coords.y = -5165.559570; Coords.z = 1.464137;
		teleportToLocation(Coords);
	}

	inline void main_dock4()
	{
		Vector3 Coords;
		Coords.x = 4924.693359; Coords.y = -5243.244629; Coords.z = 1.223599;
		teleportToLocation(Coords);
	}

	inline void north_dock1()
	{
		Vector3 Coords;
		Coords.x = 5132.558594; Coords.y = -4612.922852; Coords.z = 1.162808;
		teleportToLocation(Coords);
	}

	inline void north_dock2()
	{
		Vector3 Coords;
		Coords.x = 5065.255371; Coords.y = -4591.706543; Coords.z = 1.555012;
		teleportToLocation(Coords);
	}

	inline void north_dock3()
	{
		Vector3 Coords;
		Coords.x = 5090.916016; Coords.y = -4682.670898; Coords.z = 1.107098;
		teleportToLocation(Coords);
	}

	inline void radio_tower()
	{
		Vector3 Coords;
		Coords.x = 5263.7124; Coords.y = -5407.5835; Coords.z = 65.24931;
		teleportToLocation(Coords);
	}

	inline void drainage_pipe()
	{
		Vector3 Coords;
		Coords.x = 5044.001; Coords.y = -5815.6426; Coords.z = 11.808871;
		teleportToLocation(Coords);
	}

	inline void drainage_checkpoint()
	{
		Vector3 Coords;
		Coords.x = 5053.773; Coords.y = -5773.2266; Coords.z = 5.40778;
		teleportToLocation(Coords);
	}

	inline void ocean_safepoint()
	{
		Vector3 Coords;
		Coords.x = 4771.479; Coords.y = -6165.737; Coords.z = 39.079613;
		teleportToLocation(Coords);
	}
}
