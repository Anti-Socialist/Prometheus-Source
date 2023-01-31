#pragma once
#include "pugixml.hpp"
#include "natives.hpp"
#include "util/world_model.hpp"

using namespace std;

namespace big::xmlmaploader {

	inline vector<string> all_xml_maps;

	inline void load_all_xml_maps() {

		folder xml_files_folder = g_file_manager->get_project_folder("./XML-Maps");
		all_xml_maps.clear();

		for (const auto& o : filesystem::directory_iterator(xml_files_folder.get_path())) {
			all_xml_maps.push_back(o.path().filename().string());
		}

	}

	inline void spawn_placement_from_xml_node(const pugi::xml_node& nodeEntity)
	{

		Entity e = 0;
		Hash eModel = nodeEntity.child("ModelHash").text().as_uint();

		int type = (int)nodeEntity.child("Type").text().as_int();
		bool dynamic = nodeEntity.child("Dynamic").text().as_bool();
		bool frozen_pos = nodeEntity.child("FrozenPos").text().as_bool(!dynamic);

		auto nodeEntityPosRot = nodeEntity.child("PositionRotation");
		Vector3 placingEpos;
		Vector3	placingErot;
		placingEpos.x = nodeEntityPosRot.child("X").text().as_float();
		placingEpos.y = nodeEntityPosRot.child("Y").text().as_float();
		placingEpos.z = nodeEntityPosRot.child("Z").text().as_float();
		placingErot.x = nodeEntityPosRot.child("Pitch").text().as_float();
		placingErot.y = nodeEntityPosRot.child("Roll").text().as_float();
		placingErot.z = nodeEntityPosRot.child("Yaw").text().as_float();

		if (type == 3) // Object
		{
			e = world_model::spawn(eModel, placingEpos, true);
			ENTITY::SET_ENTITY_COORDS_NO_OFFSET(e, placingEpos.x, placingEpos.y, placingEpos.z, 1, 1, 1);
			ENTITY::SET_ENTITY_ROTATION(e, placingErot.x, placingErot.y, placingErot.z, 2, 1);

			ENTITY::FREEZE_ENTITY_POSITION(e, true);
			ENTITY::SET_ENTITY_HAS_GRAVITY(e, nodeEntity.child("HasGravity").text().as_bool(true));

			auto nodePropStuff = nodeEntity.child("ObjectProperties");

			int texture_variation = nodePropStuff.child("TextureVariation").text().as_int(-1);
			if (texture_variation != -1)
				OBJECT::SET_OBJECT_TINT_INDEX(e, texture_variation);
		}

		int opacityLevel = nodeEntity.child("OpacityLevel").text().as_int(255);
		if (opacityLevel < 255) ENTITY::SET_ENTITY_ALPHA(e, opacityLevel, 0);
		ENTITY::SET_ENTITY_LOD_DIST(e, nodeEntity.child("LodDistance").text().as_int());
		if (nodeEntity.child("MaxHealth")) ENTITY::SET_ENTITY_MAX_HEALTH(e, nodeEntity.child("MaxHealth").text().as_int());
		if (nodeEntity.child("Health")) ENTITY::SET_ENTITY_MAX_HEALTH(e, nodeEntity.child("Health").text().as_int());

		if (nodeEntity.child("IsOnFire").text().as_bool())
			FIRE::START_ENTITY_FIRE(e);
		else
			FIRE::STOP_ENTITY_FIRE(e);

		ENTITY::SET_ENTITY_INVINCIBLE(e, nodeEntity.child("IsInvincible").text().as_bool());
		ENTITY::SET_ENTITY_DYNAMIC(e, false);
		ENTITY::FREEZE_ENTITY_POSITION(e, true);
		ENTITY::SET_ENTITY_DYNAMIC(e, dynamic);
		ENTITY::FREEZE_ENTITY_POSITION(e, frozen_pos);
		ENTITY::SET_ENTITY_COLLISION(e, !nodeEntity.child("IsCollisionProof").text().as_bool(), 0);
		ENTITY::SET_ENTITY_VISIBLE(e, nodeEntity.child("IsVisible").text().as_bool(), 0);

		auto nodeEntityAttachment = nodeEntity.child("Attachment");
		bool is_attached = nodeEntityAttachment.attribute("isAttached").as_bool();
		Entity attached_to_handle;

		if (is_attached)
		{
			std::string attachedToHandleStr = nodeEntityAttachment.child("AttachedTo").text().as_string();
			if (attachedToHandleStr == "PLAYER")
			{
				attached_to_handle = PLAYER::PLAYER_PED_ID();
			}
			else if (attachedToHandleStr == "VEHICLE")
			{
				if (ENTITY::DOES_ENTITY_EXIST(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0))) attached_to_handle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
				else attached_to_handle = false;
			}
			else
			{
				attached_to_handle = nodeEntityAttachment.child("AttachedTo").text().as_int();
			}
		}

		ENTITY::SET_ENTITY_LIGHTS(e, 0);
	}

	inline bool load_placements_from_xml_file(std::string filePath)
	{
		pugi::xml_document doc;
		file xml_file = g_file_manager->get_project_file("./XML-Maps\\" + filePath);

		if (doc.load_file(xml_file.get_path().c_str()).status != pugi::status_ok)
		{
			LOG(INFO) << "Couldn't load " << filePath;
			return NULL;
		}

		Ped myPed = PLAYER::PLAYER_PED_ID();
		Vehicle myVehicle = PED::GET_VEHICLE_PED_IS_IN(myPed, false);
		Vector3 myPos = ENTITY::GET_ENTITY_COORDS(myPed, 1);

		pugi::xml_node nodeRoot = doc.child("SpoonerPlacements");

		auto nodeIplsToUnload = nodeRoot.child("IPLsToRemove");
		for (auto nodeIplToUnload = nodeIplsToUnload.first_child(); nodeIplToUnload; nodeIplToUnload = nodeIplToUnload.next_sibling())
		{
			PCHAR iplName = (PCHAR)nodeIplToUnload.text().as_string();
			if (STREAMING::IS_IPL_ACTIVE(iplName)) STREAMING::REMOVE_IPL(iplName);
		}
		auto nodeIplsToLoad = nodeRoot.child("IPLsToLoad");
		bool bIplsRequireMpMaps = nodeIplsToLoad.attribute("load_mp_maps").as_bool();
		bool bIplsRequireSpMaps = nodeIplsToLoad.attribute("load_sp_maps").as_bool();
		if (bIplsRequireMpMaps)
		{
			MISC::SET_INSTANCE_PRIORITY_MODE(true);
			DLC::ON_ENTER_MP();
		}
		if (bIplsRequireSpMaps)
		{
			MISC::SET_INSTANCE_PRIORITY_MODE(true);
			DLC::ON_ENTER_SP();
		}
		for (auto nodeIplToLoad = nodeIplsToLoad.first_child(); nodeIplToLoad; nodeIplToLoad = nodeIplToLoad.next_sibling())
		{
			PCHAR iplName = (PCHAR)nodeIplToLoad.text().as_string();
			if (!STREAMING::IS_IPL_ACTIVE(iplName)) STREAMING::REQUEST_IPL(iplName);
		}

		auto nodeInteriorsToEnable = nodeRoot.child("InteriorsToEnable");
		for (auto nodeInterior = nodeInteriorsToEnable.first_child(); nodeInterior; nodeInterior = nodeInterior.next_sibling())
		{
			bool enableOrNah = nodeInterior.attribute("enable").as_bool(true);
			int interior = nodeInterior.attribute("id").as_int(-1);
			if (interior == -1)
			{
				if (nodeInterior.attribute("X"))
				{
					Vector3 coords;
					coords.x = nodeInterior.attribute("X").as_float();
					coords.y = nodeInterior.attribute("Y").as_float();
					coords.z = nodeInterior.attribute("Z").as_float();
					interior = INTERIOR::GET_INTERIOR_AT_COORDS(coords.x, coords.y, coords.z);
				}
				else if (nodeInterior.child("X"))
				{
					Vector3 coords;
					coords.x = nodeInterior.child("X").text().as_float();
					coords.y = nodeInterior.child("Y").text().as_float();
					coords.z = nodeInterior.child("Z").text().as_float();
					interior = INTERIOR::GET_INTERIOR_AT_COORDS(coords.x, coords.y, coords.z);
				}
			}
			if (INTERIOR::IS_VALID_INTERIOR(interior))
			{
				if (enableOrNah)
				{
					INTERIOR::PIN_INTERIOR_IN_MEMORY(interior);
					if (INTERIOR::IS_INTERIOR_DISABLED(interior))
					{
						INTERIOR::DISABLE_INTERIOR(interior, false);
					}
					for (auto nodeInteriorProp = nodeInterior.child("InteriorProp"); nodeInteriorProp; nodeInteriorProp = nodeInterior.next_sibling("InteriorProp"))
					{
						std::string interiorPropName = nodeInteriorProp.attribute("name").as_string();
						if (interiorPropName.length())
						{
							if (nodeInteriorProp.attribute("enable").as_bool(true))
							{
								INTERIOR::ACTIVATE_INTERIOR_ENTITY_SET(interior, const_cast<PCHAR>(interiorPropName.c_str()));
							}
							else
							{
								INTERIOR::DEACTIVATE_INTERIOR_ENTITY_SET(interior, const_cast<PCHAR>(interiorPropName.c_str()));
							}

						}
					}
					INTERIOR::REFRESH_INTERIOR(interior);
				}
				else
				{
					if (!INTERIOR::IS_INTERIOR_DISABLED(interior))
					{
						INTERIOR::DISABLE_INTERIOR(interior, true);
					}
				}
			}
		}
		auto nodeInteriorsToCap = nodeRoot.child("InteriorsToCap");
		for (auto nodeInterior = nodeInteriorsToCap.first_child(); nodeInterior; nodeInterior = nodeInterior.next_sibling())
		{
			bool capOrNah = nodeInterior.attribute("cap").as_bool(true);
			int interior = nodeInterior.attribute("id").as_int(-1);
			if (interior == -1)
			{
				if (nodeInterior.attribute("X"))
				{
					Vector3 coords;
					coords.x = nodeInterior.attribute("X").as_float();
					coords.y = nodeInterior.attribute("Y").as_float();
					coords.z = nodeInterior.attribute("Z").as_float();
					interior = INTERIOR::GET_INTERIOR_AT_COORDS(coords.x, coords.y, coords.z);
				}
				else if (nodeInterior.child("X"))
				{
					Vector3 coords;
					coords.x = nodeInterior.child("X").text().as_float();
					coords.y = nodeInterior.child("Y").text().as_float();
					coords.z = nodeInterior.child("Z").text().as_float();
					interior = INTERIOR::GET_INTERIOR_AT_COORDS(coords.x, coords.y, coords.z);
				}
			}
			if (INTERIOR::IS_VALID_INTERIOR(interior))
			{
				INTERIOR::CAP_INTERIOR(interior, capOrNah);
			}
		}

		if (bIplsRequireMpMaps || bIplsRequireSpMaps)
		{
			MISC::SET_INSTANCE_PRIORITY_MODE(false);
		}

		auto nodeWeatherToSet = nodeRoot.child("WeatherToSet");
		if (nodeWeatherToSet)
		{
			std::string weatherToSet = nodeWeatherToSet.text().as_string();
			if (weatherToSet.length() > 0)
			{
				MISC::CLEAR_OVERRIDE_WEATHER();
				MISC::SET_WEATHER_TYPE_OVERTIME_PERSIST(const_cast<PCHAR>(weatherToSet.c_str()), float(3000) / 1000.0f);
			}
		}

		auto nodeTimecycMod = nodeRoot.child("TimecycleModifier");
		if (nodeTimecycMod)
		{
			std::string timecycMod = nodeTimecycMod.text().as_string();
			float timecycModStren = nodeTimecycMod.attribute("strength").as_float(1.0f);
			if (timecycMod.length() > 0)
			{
				GRAPHICS::SET_TIMECYCLE_MODIFIER(const_cast<PCHAR>(timecycMod.c_str()));
				GRAPHICS::SET_TIMECYCLE_MODIFIER_STRENGTH(timecycModStren);
			}
		}

		bool bStartTaskSeqsOnLoad = nodeRoot.child("StartTaskSequencesOnLoad").text().as_bool(true);

		Vector3 imgLoadingCoords;
		auto nodeImgLoadingCoords = nodeRoot.child("ImgLoadingCoords");
		if (nodeImgLoadingCoords)
		{
			imgLoadingCoords.x = nodeImgLoadingCoords.child("X").text().as_float();
			imgLoadingCoords.y = nodeImgLoadingCoords.child("Y").text().as_float();
			imgLoadingCoords.z = nodeImgLoadingCoords.child("Z").text().as_float();
		}


		for (pugi::xml_node tool = nodeRoot.child("Placement"); tool; tool = tool.next_sibling("Placement"))
		{
			spawn_placement_from_xml_node(tool);
		}

		if (nodeImgLoadingCoords)
		{
			PED::SET_PED_COORDS_KEEP_VEHICLE(myPed, imgLoadingCoords.x, imgLoadingCoords.y, imgLoadingCoords.z);
			SYSTEM::WAIT(1400);
		}

		return true;
	}
}