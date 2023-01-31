#pragma once
#include "natives.hpp"
#include "script.hpp"
#include "pointers.hpp"

namespace big::ped_editor
{
	inline constexpr const char* const clothing_names[12] = { 
		"Head", 
		"Masks", 
		"Hair", 
		"Torso", 
		"Legs", 
		"Bags", 
		"Feet", 
		"Accessories", 
		"Undershirts", 
		"Body Armor", 
		"Decals", 
		"Tops" 
	};
	inline constexpr const char* const prop_names[5] = {
		"Hats",
		"Glasses",
		"Ears",
		"Watches",
		"Bracelets"
	};

	inline constexpr int clothing_component_ids[12] = {
		PED_COMP_HEAD, 
		PED_COMP_MASKS, 
		PED_COMP_HAIR, 
		PED_COMP_TORSO, 
		PED_COMP_LEGS, 
		PED_COMP_BAGS, 
		PED_COMP_FEET, 
		PED_COMP_ACCESSORIES, 
		PED_COMP_UNDERSHIRT, 
		PED_COMP_BODY_ARMOR, 
		PED_COMP_DECALS, 
		PED_COMP_TOPS 
	};
	inline constexpr int prop_component_ids[5] = {
		PED_PROP_HATS,
		PED_PROP_GLASSES,
		PED_PROP_EARS,
		PED_PROP_WATCHES,
		PED_PROP_BRACELETS
	};

	inline int clothing_drawable_ids[12] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	inline int clothing_texture_ids[12] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	inline int prop_drawable_ids[5] = { 0, 0, 0, 0, 0 };
	inline int prop_texture_ids[5] = { 0, 0, 0, 0, 0 };

	inline bool get_ped_clothing()
	{
		Ped ped = self::ped;

		for (int i = 0; i < _countof(clothing_component_ids); ++i)
		{
			clothing_drawable_ids[i] = PED::GET_PED_DRAWABLE_VARIATION(ped, clothing_component_ids[i]);
			clothing_texture_ids[i] = PED::GET_PED_TEXTURE_VARIATION(ped, clothing_component_ids[i]);
		}

		return true;
	}

	inline bool set_ped_clothing()
	{
		Ped ped = self::ped;

		for (int i = 0; i < _countof(clothing_component_ids); ++i)
		{
			PED::SET_PED_COMPONENT_VARIATION(ped, i, clothing_drawable_ids[i], clothing_texture_ids[i], 2);
		}

		return true;
	}

	inline bool get_ped_props()
	{
		Ped ped = self::ped;

		for (int i = 0; i < _countof(prop_component_ids); ++i)
		{
			prop_drawable_ids[i] = PED::GET_PED_PROP_INDEX(ped, prop_component_ids[i]);
			prop_texture_ids[i] = PED::GET_PED_PROP_TEXTURE_INDEX(ped, prop_component_ids[i]);
		}

		return true;
	}

	inline bool set_ped_props()
	{
		Ped ped = self::ped;

		for (int i = 0; i < _countof(prop_component_ids); ++i)
		{
			PED::SET_PED_PROP_INDEX(ped, prop_component_ids[i], prop_drawable_ids[i], prop_texture_ids[i], TRUE);
		}

		return true;
	}

	inline bool remove_ped_prop(int prop_id)
	{
		Ped ped = self::ped;

		PED::CLEAR_PED_PROP(ped, prop_id);
		return true;
	}
}