#pragma once
#include "util/entity.hpp"
#include "pugixml.hpp"
#include "file_manager/file.hpp"
#include "util/vehicle.hpp"
#include "pointers.hpp"
#include "pugixml.cpp"

using namespace std;
using json = nlohmann::json;
namespace fs = std::filesystem;


//THIS IS THE ALGORITHM I WROTE
//YOU NEED TO CALL load_xml_vehilce TO SPAWN A VEHICLE FROM THE SPECIFIED DIRECTORY
//load_all_xml_vehicles MUST BE CALLED WHEN THE MOD IS LOADED TO LOAD ALL XML VEHICLES AT THE SPECIFIED DIRECTORY


namespace big::xmlvehicleloader {

	struct RGB {
		int r,
			g,
			b;
	};

	inline vector<string> all_xml_vehicles;

	inline void load_all_xml_vehicles() {

		folder xml_files_folder = g_file_manager->get_project_folder("./XML-Vehicles");
		all_xml_vehicles.clear();

		for (const auto& o : fs::directory_iterator(xml_files_folder.get_path())) {
			all_xml_vehicles.push_back(o.path().filename().string());
		}

	}


	void apply_colors(pugi::xml_node node, Vehicle handle) {
	
		auto vehicle_colors_node = node.child("Colours");
		int mod1a = vehicle_colors_node.child("Mod1_a").text().as_int();
		int mod1b = vehicle_colors_node.child("Mod1_b").text().as_int();
		int mod1c = vehicle_colors_node.child("Mod1_c").text().as_int();
		int mod2a = vehicle_colors_node.child("Mod2_a").text().as_int();
		int mod2b = vehicle_colors_node.child("Mod2_b").text().as_int();
		bool is_primary_custom = vehicle_colors_node.child("IsPrimaryColourCustom").text().as_bool();
		bool is_secondary_custom = vehicle_colors_node.child("IsSecondaryColourCustom").text().as_bool();

		VEHICLE::SET_VEHICLE_LIVERY(handle, node.child("Livery").text().as_int());
		VEHICLE::SET_VEHICLE_MOD_COLOR_1(handle, mod1a, mod1b, mod1c);
		VEHICLE::SET_VEHICLE_MOD_COLOR_2(handle, mod2a, mod2b);
		VEHICLE::SET_VEHICLE_COLOURS(handle, vehicle_colors_node.child("Primary").text().as_int(), vehicle_colors_node.child("Secondary").text().as_int());
		VEHICLE::SET_VEHICLE_EXTRA_COLOURS(handle, vehicle_colors_node.child("Pearl").text().as_int(), vehicle_colors_node.child("Rim").text().as_int());
		
		if (is_primary_custom){
			RGB cust1;
			cust1.r = vehicle_colors_node.child("Cust1_R").text().as_int();
			cust1.g = vehicle_colors_node.child("Cust1_G").text().as_int();
			cust1.b = vehicle_colors_node.child("Cust1_B").text().as_int();
			VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(handle, cust1.r, cust1.g, cust1.b);

		}
		if (is_secondary_custom){
			RGB cust2;
			cust2.r = vehicle_colors_node.child("Cust2_R").text().as_int();
			cust2.g = vehicle_colors_node.child("Cust2_G").text().as_int();
			cust2.b = vehicle_colors_node.child("Cust2_B").text().as_int();
			VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(handle, cust2.r, cust2.g, cust2.b);
		}

		RGB tyreSmokeRgb;
		tyreSmokeRgb.r = vehicle_colors_node.child("tyreSmoke_R").text().as_int();
		tyreSmokeRgb.g = vehicle_colors_node.child("tyreSmoke_G").text().as_int();
		tyreSmokeRgb.b = vehicle_colors_node.child("tyreSmoke_B").text().as_int();
		VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(handle, tyreSmokeRgb.r, tyreSmokeRgb.g, tyreSmokeRgb.b);

	}


	void spawn_and_attach_ped(pugi::xml_node node, Hash model, Vector3 pos, Vector3 rot, Vector3 offset, Vehicle veh_to_attach_to, int bone) {

		auto ped_node = node.child("PedProperties");
		Ped handle = entity::create_ped(model, 4, pos, 0, *g_pointers->m_is_session_started, true);
		bool isUsingScenario = ped_node.child("ScenarioActive").text().as_bool();
		bool isUsingAnim = ped_node.child("AnimActive").text().as_bool();

		if (entity::take_control_of(handle)) {
			ENTITY::FREEZE_ENTITY_POSITION(handle, true);
			PED::SET_PED_CAN_RAGDOLL(handle, ped_node.child("CanRagdoll").text().as_bool(true));
			PED::SET_PED_RAGDOLL_ON_COLLISION(handle, ped_node.child("CanRagdoll").text().as_bool(false));

			if (ped_node.child("HasShortHeight").text().as_bool()) PED::SET_PED_CONFIG_FLAG(handle, 223, 1);
			ENTITY::SET_ENTITY_VISIBLE(handle, node.child("IsVisible").text().as_bool(), true);
			ENTITY::SET_ENTITY_INVINCIBLE(handle, node.child("IsInvincible").text().as_bool());

			if (isUsingScenario)
			{
				std::string ScenarioName = ped_node.child("ScenarioName").text().as_string();
				TASK::TASK_START_SCENARIO_IN_PLACE(handle, const_cast<PCHAR>(ScenarioName.c_str()), 0, true);
				if (ScenarioName.find("MUSICIAN") != std::string::npos) TASK::TASK_START_SCENARIO_IN_PLACE(handle, "WORLD_HUMAN_MUSICIAN", 0, true);
			}
			if (isUsingAnim)
			{
				std::string AnimDict = ped_node.child("AnimDict").text().as_string();
				std::string AnimName = ped_node.child("AnimName").text().as_string();

				STREAMING::REQUEST_ANIM_DICT(AnimDict.c_str());
				for (int i = 0; !STREAMING::HAS_ANIM_DICT_LOADED(AnimDict.c_str()) && i < 100; i++) script::get_current()->yield();
				TASK::TASK_PLAY_ANIM(handle, AnimDict.c_str(), AnimName.c_str(), 8.0f, 0.0f, -1, 9, 0, 0, 0, 0);
			}

			PED::SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(handle, ped_node.child("IsStill").text().as_bool());
			PED::SET_PED_ARMOUR(handle, ped_node.child("Armour").text().as_int());
			if (!WEAPON::HAS_PED_GOT_WEAPON(handle, ped_node.child("CurrentWeapon").text().as_uint(), false))
				WEAPON::GIVE_WEAPON_TO_PED(handle, ped_node.child("CurrentWeapon").text().as_uint(), 9999, true, false);
			WEAPON::SET_CURRENT_PED_WEAPON(handle, ped_node.child("CurrentWeapon").text().as_uint(), true);
			PED::SET_PED_CAN_SWITCH_WEAPON(handle, false);
			TASK::SET_PED_PATH_CAN_USE_CLIMBOVERS(handle, true);
			TASK::SET_PED_PATH_CAN_USE_LADDERS(handle, true);
			TASK::SET_PED_PATH_CAN_DROP_FROM_HEIGHT(handle, true);
			PED::SET_PED_COMBAT_ABILITY(handle, 2);
			PED::SET_PED_COMBAT_MOVEMENT(handle, 2);

			PED::SET_PED_CAN_PLAY_AMBIENT_ANIMS(handle, true);
			PED::SET_PED_CAN_PLAY_AMBIENT_BASE_ANIMS(handle, true);
			PED::SET_PED_CAN_PLAY_GESTURE_ANIMS(handle, true);
			PED::SET_PED_CAN_PLAY_VISEME_ANIMS(handle, true, TRUE);
			ENTITY::ATTACH_ENTITY_TO_ENTITY(handle, veh_to_attach_to, bone, offset.x, offset.y, offset.z, rot.x, rot.y, rot.z, false, false, true, false, 2, true, false);

		}
	}

	void spawn_and_attach_vehicle(pugi::xml_node node, Hash model, Vector3 pos, Vector3 rot, Vector3 offset, Vehicle veh_to_attach_to, int bone) {

		auto veh_node = node.child("VehicleProperties");
		auto veh_colors_node = veh_node.child("Colours");
		Vehicle handle = vehicle::spawn("", pos, 0, *g_pointers->m_is_session_started, model);

		int mod1a = veh_colors_node.child("Mod1_a").text().as_int();
		int mod1b = veh_colors_node.child("Mod1_b").text().as_int();
		int mod1c = veh_colors_node.child("Mod1_c").text().as_int();
		int mod2a = veh_colors_node.child("Mod2_a").text().as_int();
		int mod2b = veh_colors_node.child("Mod2_b").text().as_int();

		bool isPrimaryColourCustom = veh_colors_node.child("IsPrimaryColourCustom").text().as_bool();
		bool isSecondaryColourCustom = veh_colors_node.child("IsSecondaryColourCustom").text().as_bool();

		if (entity::take_control_of(handle)) {

			VEHICLE::SET_VEHICLE_MOD_KIT(handle, 0);
			VEHICLE::SET_VEHICLE_LIVERY(handle, veh_node.child("Livery").text().as_int());
			ENTITY::SET_ENTITY_VISIBLE(handle, veh_node.child("IsVisible").text().as_bool(), true);
			ENTITY::SET_ENTITY_INVINCIBLE(handle, veh_node.child("IsInvincible").text().as_bool());
			VEHICLE::SET_VEHICLE_MOD_COLOR_1(handle, mod1a, mod1b, mod1c);
			VEHICLE::SET_VEHICLE_MOD_COLOR_2(handle, mod2a, mod2b);
			VEHICLE::SET_VEHICLE_COLOURS(handle, veh_colors_node.child("Primary").text().as_int(), veh_colors_node.child("Secondary").text().as_int());
			VEHICLE::SET_VEHICLE_EXTRA_COLOURS(handle, veh_colors_node.child("Pearl").text().as_int(), veh_colors_node.child("Rim").text().as_int());
				if (isPrimaryColourCustom)
			{
				RGB cust1;
				cust1.r = veh_colors_node.child("Cust1_R").text().as_int();
				cust1.g = veh_colors_node.child("Cust1_G").text().as_int();
				cust1.b = veh_colors_node.child("Cust1_B").text().as_int();
				VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(handle, cust1.r, cust1.g, cust1.b);

			}
			if (isSecondaryColourCustom)
			{
				RGB cust2;
				cust2.r = veh_colors_node.child("Cust2_R").text().as_int();
				cust2.g = veh_colors_node.child("Cust2_G").text().as_int();
				cust2.b = veh_colors_node.child("Cust2_B").text().as_int();
				VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(handle, cust2.r, cust2.g, cust2.b);
			}
			ENTITY::ATTACH_ENTITY_TO_ENTITY(handle, veh_to_attach_to, bone, offset.x, offset.y, offset.z, rot.x, rot.y, rot.z, false, false, true, false, 2, true, false);
		}
	}

	void spawn_and_attach_object(pugi::xml_node node, Hash model, Vector3 pos, Vector3 rot, Vector3 offset, Vehicle veh_to_attach_to, int bone) {

		Object handle = entity::create_object(model, pos, true, true, true);
		ENTITY::FREEZE_ENTITY_POSITION(handle, true);
		ENTITY::SET_ENTITY_VISIBLE(handle, node.child("IsVisible").text().as_bool(), true);
		ENTITY::SET_ENTITY_INVINCIBLE(handle, node.child("IsInvincible").text().as_bool());
		ENTITY::ATTACH_ENTITY_TO_ENTITY(handle, veh_to_attach_to, bone, offset.x, offset.y, offset.z, rot.x, rot.y, rot.z, false, false, true, false, 2, true, false);

	}

	void spawn_and_attach_entities(pugi::xml_node node, Vehicle handle) {

		for (auto itterated_attachment_node = node.first_child(); itterated_attachment_node; itterated_attachment_node = itterated_attachment_node.next_sibling()) {

			auto attachment_vector_node = itterated_attachment_node.child("Attachment");
			auto entity_vector_node = itterated_attachment_node.child("PositionRotation");

			Vector3 position = { entity_vector_node.child("X").text().as_float(),  entity_vector_node.child("Y").text().as_float(), entity_vector_node.child("z").text().as_float() };
			Vector3 rotation = { attachment_vector_node.child("Pitch").text().as_float(),  attachment_vector_node.child("Roll").text().as_float(), attachment_vector_node.child("Yaw").text().as_float() };
			Vector3 offset = { attachment_vector_node.child("X").text().as_float(),  attachment_vector_node.child("Y").text().as_float(), attachment_vector_node.child("Z").text().as_float() };
			int boneIndex = attachment_vector_node.child("BoneIndex").text().as_int();

			Hash entity_model_hash = itterated_attachment_node.child("ModelHash").text().as_uint();
			int type = itterated_attachment_node.child("Type").text().as_int();

			switch (type) {
			case 1:
				spawn_and_attach_ped(itterated_attachment_node, entity_model_hash, position, rotation, offset, handle, boneIndex);
				break;
			case 2:
				spawn_and_attach_vehicle(itterated_attachment_node, entity_model_hash, position, rotation, offset, handle, boneIndex);
				break;
			case 3:
				spawn_and_attach_object(itterated_attachment_node, entity_model_hash, position, rotation, offset, handle, boneIndex);
			}

		}

	}

	inline Vehicle load_xml_vehilce(string filename, Vector3 coords, float heading) {

		pugi::xml_document doc;
		file xml_file = g_file_manager->get_project_file("./XML-Vehicles\\" + filename);

		if (doc.load_file(xml_file.get_path().c_str()).status != pugi::status_ok)
		{
			LOG(INFO) << "Couldn't load " << filename;
			return NULL;
		}
			
		auto vehicle_node = doc.child("Vehicle");
		auto vehicle_properties_node = vehicle_node.child("VehicleProperties");
		auto vehicle_attachments_node = vehicle_node.child("SpoonerAttachments");
		auto model_hash = vehicle_node.child("ModelHash").text().as_uint();

		Vehicle handle = vehicle::spawn("", coords, heading, *g_pointers->m_is_session_started, model_hash);

		if (entity::take_control_of(handle)) {
			ENTITY::SET_ENTITY_INVINCIBLE(handle, vehicle_node.child("IsInvincible").text().as_bool());
			ENTITY::SET_ENTITY_VISIBLE(handle, vehicle_node.child("IsVisible").text().as_bool(), true);
			
			apply_colors(vehicle_properties_node, handle);
			spawn_and_attach_entities(vehicle_attachments_node, handle);

		}

		return handle;
		
	}

}