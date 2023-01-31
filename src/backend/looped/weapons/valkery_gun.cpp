#include "backend/looped/looped.hpp"
#include "natives.hpp"
#include "gta/joaat.hpp"
#include "gui.hpp"
#include "core/enums.hpp"
#include "util/vehicle.hpp"
#include "util/math.hpp"
#include "core/globals.hpp"
#include "util/toxic.hpp"

namespace big
{

	//Vector3 AddV3(Vector3 vectorA, Vector3 vectorB) {
	//	Vector3 result;
	//	result.x = vectorA.x;
	//	result.y = vectorA.y;
	//	result.z = vectorA.z;
	//	result.x += vectorB.x;
	//	result.y += vectorB.y;
	//	result.z += vectorB.z;
	//	return result;
	//}

	//Vector3 MultiplyV3(Vector3 vector, float x) {
	//	Vector3 result;
	//	result.x = vector.x;
	//	result.y = vector.y;
	//	result.z = vector.z;
	//	result.x *= x;
	//	result.y *= x;
	//	result.z *= x;
	//	return result;
	//}

	//Vector3 RotationToDirectionV3(Vector3 rot) {
	//	Vector3 dir;
	//	float radiansZ = rot.z * 0.0174532924f;
	//	float radiansX = rot.x * 0.0174532924f;
	//	float num = abs((float)cos((double)radiansX));
	//	dir.x = (float)((double)((float)(-(float)sin((double)radiansZ))) * (double)num);
	//	dir.y = (float)((double)((float)cos((double)radiansZ)) * (double)num);
	//	dir.z = (float)sin((double)radiansX);
	//	return dir;
	//}

	void looped::valkery_gun()
	{
		Ped playerPed = self::ped;
		Vector3 pos;
		static std::int32_t rocket, cam;
		static std::uint8_t y;
		static float bar;
		static bool init;
		if (!HUD::IS_PAUSE_MENU_ACTIVE() && !g_gui->is_open() && !PED::IS_PED_DEAD_OR_DYING(self::ped, true) && !PED::IS_PED_IN_ANY_VEHICLE(self::ped, TRUE))
		{
		if (PAD::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_ATTACK)) {
			if (!init) init = true;
		}
			if (init && g.weapons.valkery_gun) {
				if (!ENTITY::DOES_ENTITY_EXIST(rocket)) {
					auto weapon = WEAPON::GET_CURRENT_PED_WEAPON_ENTITY_INDEX(playerPed, false);
					auto c = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(weapon, 0.f, 1.f, 0.f);
					Hash hash = RAGE_JOAAT("w_lr_rpg_rocket");
					rocket = OBJECT::CREATE_OBJECT(hash, c.x, c.y, c.z, 1, 1, 0);
					CAM::DESTROY_ALL_CAMS(true);
					cam = CAM::CREATE_CAM("DEFAULT_SCRIPTED_CAMERA", 1);
					CAM::ATTACH_CAM_TO_ENTITY(cam, rocket, 0.f, 0.f, 0.f, 1);
					CAM::RENDER_SCRIPT_CAMS(1, true, 700, 1, 1, false);
					CAM::SET_CAM_ACTIVE(cam, 1);
					ENTITY::SET_ENTITY_VISIBLE(rocket, 0, 0);
					bar = .5f; y = 255;
				}
				else {
					CAM::SET_CAM_ROT(cam, CAM::GET_GAMEPLAY_CAM_ROT(0).x, CAM::GET_GAMEPLAY_CAM_ROT(0).y, CAM::GET_GAMEPLAY_CAM_ROT(0).z, 0);
					ENTITY::SET_ENTITY_ROTATION(rocket, CAM::GET_GAMEPLAY_CAM_ROT(0).x, CAM::GET_GAMEPLAY_CAM_ROT(0).y, CAM::GET_GAMEPLAY_CAM_ROT(0).z, 0, 1);

					auto c = toxic::Add(ENTITY::GET_ENTITY_COORDS(rocket, 1), toxic::Multiply(toxic::RotationToDirection(CAM::GET_GAMEPLAY_CAM_ROT(0)), .8f));
					ENTITY::SET_ENTITY_COORDS(rocket, c.x, c.y, c.z, 0, 0, 0, 0);

					HUD::HIDE_HUD_AND_RADAR_THIS_FRAME();
					PLAYER::DISABLE_PLAYER_FIRING(self::id, 1);
					ENTITY::FREEZE_ENTITY_POSITION(playerPed, 1);
					HUD::HUD_SUPPRESS_WEAPON_WHEEL_RESULTS_THIS_FRAME();

					GRAPHICS::DRAW_RECT(0.5f, 0.5f - 0.025f, 0.050f, 0.002f, 255, 255, 255, 255, false);
					GRAPHICS::DRAW_RECT(0.5f, 0.5f + 0.025f, 0.050f, 0.002f, 255, 255, 255, 255, false);
					GRAPHICS::DRAW_RECT(0.5f - 0.025f, 0.5f, 0.002f, 0.050f, 255, 255, 255, 255, false);
					GRAPHICS::DRAW_RECT(0.5f + 0.025f, 0.5f, 0.002f, 0.050f, 255, 255, 255, 255, false);
					GRAPHICS::DRAW_RECT(0.5f + 0.05f, 0.5f, 0.050f, 0.002f, 255, 255, 255, 255, false);
					GRAPHICS::DRAW_RECT(0.5f - 0.05f, 0.5f, 0.050f, 0.002f, 255, 255, 255, 255, false);
					GRAPHICS::DRAW_RECT(0.5f, 0.5f + 0.05f, 0.002f, 0.050f, 255, 255, 255, 255, false);
					GRAPHICS::DRAW_RECT(0.5f, 0.5f - 0.05f, 0.002f, 0.050f, 255, 255, 255, 255, false);
					GRAPHICS::SET_TIMECYCLE_MODIFIER("CAMERA_secuirity");

					GRAPHICS::DRAW_RECT(0.25f, 0.5f, 0.03f, 0.5f, 255, 255, 255, 255, false);
					static auto ticker = GetTickCount64();
					if (GetTickCount64() - ticker >= 100) {
						bar -= .01f; y -= 4; ticker = GetTickCount64();
					}
					GRAPHICS::DRAW_RECT(0.25f, 0.75f - (bar / 2), 0.03f, bar, 255, y, 0, 255, false);

					float groundZ;
					MISC::GET_GROUND_Z_FOR_3D_COORD(ENTITY::GET_ENTITY_COORDS(rocket, 1).x, ENTITY::GET_ENTITY_COORDS(rocket, 1).y, ENTITY::GET_ENTITY_COORDS(rocket, 1).z, &groundZ, 0, false);
					if (ENTITY::HAS_ENTITY_COLLIDED_WITH_ANYTHING(rocket) ||
						(std::abs(ENTITY::GET_ENTITY_COORDS(rocket, 1).z - groundZ) < .5f) ||
						bar <= 0.01) {
						auto impact_coord = ENTITY::GET_ENTITY_COORDS(rocket, 1); ENTITY::FREEZE_ENTITY_POSITION(playerPed, 0);
						FIRE::ADD_EXPLOSION(impact_coord.x, impact_coord.y, impact_coord.z, 0, 10.f, 1, 0, .4f, false);
						ENTITY::DELETE_ENTITY(&rocket);
						rocket = 0;
						PLAYER::DISABLE_PLAYER_FIRING(self::id, 0);
						CAM::RENDER_SCRIPT_CAMS(false, true, 500, true, true, 0);
						CAM::DESTROY_CAM(cam, 1);
						STREAMING::SET_FOCUS_ENTITY(self::ped);
						GRAPHICS::SET_TIMECYCLE_MODIFIER("DEFAULT");
						init = false;
					}
				}
				//if (!VALKYIREROCKET) {
				//	CAM::DESTROY_CAM(cam, 1);
				//	PAD::DISABLE_CONTROL_ACTION(0, (int)ControllerInputs::INPUT_ATTACK, false);
				//	rocket = 0;
				//	bar = .5f;
				//	y = 255;
				//	ENTITY::FREEZE_ENTITY_POSITION(PLAYER::PLAYER_PED_ID(), 0);
				//	init = false;
				//}
			}
		}
	}
}