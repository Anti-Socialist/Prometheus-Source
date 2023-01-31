#include "backend/looped/looped.hpp"
#include "natives.hpp"
#include "util/entity.hpp"
#include "services/players/player_service.hpp"
#include "fiber_pool.hpp"
#include "util/timer.hpp"
#include "util/toxic.hpp"

namespace big
{

    Vector3 Local_Flying_Axe_Cor;
    Vector3 New_Local_Flying_Axe_Cor;
    static Timer Local_Flying_Axe_Delay(200ms);
    static Timer Local_Flying_Axe_Delay_LOC(200ms);
    bool Local_Flying_Axe_Idle = false;
    bool Local_Flying_Axe_Attack = false;
    bool Local_Flying_Axe_Animation = true;
	Entity Local_Flying_Axe;

	enum ForceType
	{
		MinForce = 0,
		MaxForceRot = 1,
		MinForce2 = 2,
		MaxForceRot2 = 3,
		ForceNoRot = 4,
		ForceRotPlusForce = 5
	};

	void MASS_FORCE_APPLY(Entity Krox_E, Vector3 direc, Vector3 OFSETS, ForceType forceType)
	{
		ENTITY::APPLY_FORCE_TO_ENTITY(Krox_E, static_cast<int>(forceType), direc.x, direc.y, direc.z, OFSETS.x, OFSETS.y, OFSETS.z, false, false, true, true, false, true);
	}

	void MASS_FORCE_APPLY_REAL(Entity Krox_E, float directionx, float directiony, float directionz)
	{
		Vector3 MASS_FORCE_APPLY_Empty = { 0,0,0 };
		Vector3 MASS_FORCE_APPLY_Em = { directionx,directiony,directionz };
		MASS_FORCE_APPLY(Krox_E, MASS_FORCE_APPLY_Em, MASS_FORCE_APPLY_Empty, MaxForceRot);
	}

	int GET_360_VEC_AROUND_ENTITY_SLCT = 0;
	Vector3 GET_360_VEC_AROUND_ENTITY(int ent, float far_distance, float up_down_distance)
	{
		//g_Logger->Notify(300, to_string(GET_360_VEC_AROUND_ENTITY_SLCT));
		if (GET_360_VEC_AROUND_ENTITY_SLCT == 0) {
			GET_360_VEC_AROUND_ENTITY_SLCT = GET_360_VEC_AROUND_ENTITY_SLCT + 1;
			return  ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(ent, 0, 1 * far_distance, 0 + up_down_distance);;
		}   //Front
		else

			if (GET_360_VEC_AROUND_ENTITY_SLCT == 1) { GET_360_VEC_AROUND_ENTITY_SLCT = GET_360_VEC_AROUND_ENTITY_SLCT + 1; return  ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(ent, 1 * far_distance, 1 * far_distance, 0 + 1.f + up_down_distance); } //Front Right
			else	if (GET_360_VEC_AROUND_ENTITY_SLCT == 2) { GET_360_VEC_AROUND_ENTITY_SLCT = GET_360_VEC_AROUND_ENTITY_SLCT + 1; return  ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(ent, 1 * far_distance, 0, 0 + 1.f + up_down_distance); } //Right
			else	if (GET_360_VEC_AROUND_ENTITY_SLCT == 3) { GET_360_VEC_AROUND_ENTITY_SLCT = GET_360_VEC_AROUND_ENTITY_SLCT + 1; return  ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(ent, 1 * far_distance, -1 * far_distance, 0 + 1.f + up_down_distance); } //Right Behind
			else	if (GET_360_VEC_AROUND_ENTITY_SLCT == 4) { GET_360_VEC_AROUND_ENTITY_SLCT = GET_360_VEC_AROUND_ENTITY_SLCT + 1; return  ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(ent, 0, -1 * far_distance, 0 + 1.f + up_down_distance); }//Behind
			else	if (GET_360_VEC_AROUND_ENTITY_SLCT == 5) { GET_360_VEC_AROUND_ENTITY_SLCT = GET_360_VEC_AROUND_ENTITY_SLCT + 1; return  ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(ent, -1 * far_distance, -1 * far_distance, 0 + 1.f + up_down_distance); }//Bhiend Left
			else	if (GET_360_VEC_AROUND_ENTITY_SLCT == 6) { GET_360_VEC_AROUND_ENTITY_SLCT = GET_360_VEC_AROUND_ENTITY_SLCT + 1; return  ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(ent, -1 * far_distance, 0, 0 + 1.f + up_down_distance); }//Left
			else	if (GET_360_VEC_AROUND_ENTITY_SLCT == 7) { GET_360_VEC_AROUND_ENTITY_SLCT = 0; return  ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(ent, -1 * far_distance, 1 * far_distance, 0 + 1.f + up_down_distance); }//Front Left	
		return Vector3{ 0,0,0 };
	}

	Vector3 SUB_VECTORS(Vector3 Krox_Vec1, Vector3 Krox_Vec2)
	{
		Vector3 Krox_Sub_Results;
		{
			float Krox_Sub_Results_X = Krox_Vec1.x - Krox_Vec2.x;
			float Krox_Sub_Results_Y = Krox_Vec1.y - Krox_Vec2.y;
			float Krox_Sub_Results_Z = Krox_Vec1.z - Krox_Vec2.z;
			Krox_Sub_Results.x = Krox_Sub_Results_X;
			Krox_Sub_Results.y = Krox_Sub_Results_Y;
			Krox_Sub_Results.z = Krox_Sub_Results_Z;

		}
		return Krox_Sub_Results;
	}

	void apply_force_to_pos(Entity enity, float xx_corrd, float y_corrd, float z_corrd, Vector3 to_coords, float frq, float ratio)
	{
		int forcetype = 3;
		//ENTITY::APPLY_FORCE_TO_ENTITY(enity, forcetype, (xx_corrd * (frq * frq)) - (2.0f * frq * ratio * to_coords.x) + 0.0f, (y_corrd * (frq * frq)) - (2.0f * frq * ratio * to_coords.y) + 0.0f, (z_corrd * (frq * frq)) - (2.0f * frq * ratio * to_coords.z) + 0.1f, 0.f, 0.f, 0.f, false, false, true, true, false, true);
		ENTITY::APPLY_FORCE_TO_ENTITY(enity, forcetype, (xx_corrd * (frq * frq)) - (2.00001f * frq * ratio * to_coords.x) + 0.0f, (y_corrd * (frq * frq)) - (2.0f * frq * ratio * to_coords.y) + 0.0f, (z_corrd * (frq * frq)) - (2.0f * frq * ratio * to_coords.z) + 0.1f, 0.0f, 0.f, 0.f, 0, 0, 1, 1, 0, 1);

	}

	void Local_Misc_Flying_Axe_Fuc(int ent)
	{
		if (ent != self::veh)
		{
			float K_SPPED = ENTITY::GET_ENTITY_SPEED(Local_Flying_Axe);
			if (K_SPPED < 0.5f)
				return;
			float PUSH_FORCE = K_SPPED * 3.5;

			if (ENTITY::IS_ENTITY_TOUCHING_ENTITY(Local_Flying_Axe, ent))
			{
				if (entity::take_control_of(ent))
				{
					Vector3 CLisson_f = ENTITY::GET_COLLISION_NORMAL_OF_LAST_HIT_FOR_ENTITY(Local_Flying_Axe);
					MASS_FORCE_APPLY_REAL(ent, CLisson_f.x * PUSH_FORCE, CLisson_f.y * PUSH_FORCE, CLisson_f.z * PUSH_FORCE);
					if (ENTITY::IS_ENTITY_A_PED(ent)) PED::APPLY_DAMAGE_TO_PED(ent, 9999, 0, 0);
				}
			}
		}
	}

	void PTFX_USE_NON_LOOP(int ent, char* call1, char* call2, char* name, float scale)
	{
		STREAMING::REQUEST_NAMED_PTFX_ASSET(call1);
		if (STREAMING::HAS_NAMED_PTFX_ASSET_LOADED(call1))
		{
			GRAPHICS::USE_PARTICLE_FX_ASSET(call2);
			GRAPHICS::START_NETWORKED_PARTICLE_FX_NON_LOOPED_ON_ENTITY(name, ent, 0, 0, 0, 0, 0, 0.0, scale, true, true, true);

		}
	}

	Vector3 GET_COORDINATES_OF_MY_CAM(int Krox_Distance)
	{
		Vector3 Krox_Com_Pos = CAM::GET_GAMEPLAY_CAM_COORD();
		Vector3 Krox_Rot = CAM::GET_GAMEPLAY_CAM_ROT(0);
		Vector3 Krox_Die = toxic::RotationToDirection2(Krox_Rot);
		float Krox_Dis = Krox_Distance;
		Vector3 Krox_Leg_Vec = toxic::Multiply(Krox_Die, Krox_Dis);
		Vector3 Results = toxic::Add(Krox_Com_Pos, Krox_Leg_Vec);
		return Results;
	}

#define nearbyPedArraySize 100

	struct nearbyEnts {
		int size;//still 32 bit integer
		int64_t entities[nearbyPedArraySize];
	};
	void NEARBY_PEDS(int player, void (*f)(int)) {
		nearbyEnts arr;
		arr.size = nearbyPedArraySize;
		int ped = PLAYER::GET_PLAYER_PED(player);
		int size = PED::GET_PED_NEARBY_PEDS(ped, (int*)&arr, ped);
		for (int i = 0; i < size; i++) {
			if (!PED::IS_PED_A_PLAYER(arr.entities[i])) {
				f(arr.entities[i]);
			}
		}
	}
	void NEARBY_Vehs(int player, void (*f)(int)) {
		nearbyEnts arr;
		arr.size = nearbyPedArraySize;
		int ped = PLAYER::GET_PLAYER_PED(player);
		int size = PED::GET_PED_NEARBY_VEHICLES(ped, (int*)&arr);
		for (int i = 0; i < size; i++) {
			if (!PED::IS_PED_A_PLAYER(arr.entities[i])) {
				f(arr.entities[i]);
			}
		}
	}

    void looped::flying_axe()
    {
        if (g.self.flying_axe)
        {
			if (!ENTITY::DOES_ENTITY_EXIST(Local_Flying_Axe))
			{
				Local_Flying_Axe_Delay.SetDelay(200ms);
				if (Local_Flying_Axe_Delay.Update())
				{

					Vector3 COORDSPWA2 = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(self::ped, 0, 0, 6.5);
					Hash tospawn = rage::joaat("prop_ld_fireaxe");
					g_fiber_pool->queue_job([=]
						{
							if (!STREAMING::IS_MODEL_IN_CDIMAGE(tospawn))
							return 0;
					while (!STREAMING::HAS_MODEL_LOADED(tospawn))
					{
						STREAMING::REQUEST_MODEL(tospawn);
						script::get_current()->yield();
					}
					if (STREAMING::HAS_MODEL_LOADED(tospawn))

					Local_Flying_Axe = OBJECT::CREATE_OBJECT(tospawn, COORDSPWA2.x, COORDSPWA2.y, COORDSPWA2.z, ENTITY::GET_ENTITY_HEADING(self::ped), true, false);
					//g_ui_mgr->create_notification(2000, g_translation.options["misc"]["bool_axe"].get<std::string>().c_str(),(char*)"Axe Spawnewd");
					ENTITY::SET_ENTITY_INVINCIBLE(Local_Flying_Axe, TRUE);
					auto KROX_NET_ID = NETWORK::OBJ_TO_NET(Local_Flying_Axe);
					NETWORK::NETWORK_REGISTER_ENTITY_AS_NETWORKED(Local_Flying_Axe);
					NETWORK::SET_NETWORK_ID_EXISTS_ON_ALL_MACHINES(KROX_NET_ID, true);
					{

						ENTITY::SET_ENTITY_AS_MISSION_ENTITY(Local_Flying_Axe, true, true);
						DECORATOR::DECOR_REGISTER("MissionType", 3);
						ENTITY::SET_ENTITY_SHOULD_FREEZE_WAITING_ON_COLLISION(Local_Flying_Axe, false);
						DECORATOR::DECOR_SET_INT(Local_Flying_Axe, (char*)"MPBitset", 0);
						DECORATOR::DECOR_SET_INT(Local_Flying_Axe, (char*)"MissionType", 0);
					}
					return 0;
					});
				}
			}
			else
			{
				Local_Flying_Axe_Cor.x += (New_Local_Flying_Axe_Cor.x - Local_Flying_Axe_Cor.x) * 0.2;
				Local_Flying_Axe_Cor.y += (New_Local_Flying_Axe_Cor.y - Local_Flying_Axe_Cor.y) * 0.2;
				Local_Flying_Axe_Cor.z += (New_Local_Flying_Axe_Cor.z - Local_Flying_Axe_Cor.z) * 0.2;
				//		Functions::Vector3_Lerp(Local_Flying_Axe_Cor, New_Local_Flying_Axe_Cor);
				Local_Flying_Axe_Delay_LOC.SetDelay(300ms);
				Vector3 Dev_Veh_C = ENTITY::GET_ENTITY_COORDS(Local_Flying_Axe, 0);
				if (Local_Flying_Axe_Delay_LOC.Update()) {
					Vector3 rot = ENTITY::GET_ENTITY_ROTATION(Local_Flying_Axe, 2);
					if (Local_Flying_Axe_Idle) { New_Local_Flying_Axe_Cor = GET_360_VEC_AROUND_ENTITY(self::ped, 20, 0); }
					if (!Local_Flying_Axe_Idle || Local_Flying_Axe_Attack) { ENTITY::SET_ENTITY_ROTATION(Local_Flying_Axe, rot.x + 50, rot.y + 50, rot.z + 50, 2, 0); }
					PTFX_USE_NON_LOOP(Local_Flying_Axe, (char*)"scr_paletoscore", (char*)"scr_paletoscore", (char*)"scr_paleto_box_sparks", 0.1);
					PTFX_USE_NON_LOOP(Local_Flying_Axe, (char*)"scr_rcbarry2", (char*)"scr_rcbarry2", (char*)"scr_exp_clown_trails", 0.5);
				}
				NEARBY_PEDS(self::id, Local_Misc_Flying_Axe_Fuc);
				NEARBY_Vehs(self::id, Local_Misc_Flying_Axe_Fuc);
				//	PAD::DISABLE_CONTROL_ACTION(0, INPUT_AIM, TRUE);
				Hash wep;
				WEAPON::GET_CURRENT_PED_WEAPON(self::ped, &wep, 1);

				if (PAD::IS_DISABLED_CONTROL_PRESSED(0, 25) && !self::veh && wep == -1569615261)
				{
					//g_ui_mgr->create_notification(2000, g_translation.options["misc"]["bool_axe"].get<std::string>().c_str(), (char*)"Axe Called");
					Vector3 camrot = CAM::GET_GAMEPLAY_CAM_ROT(2);
					ENTITY::SET_ENTITY_ROTATION((self::ped), camrot.x, camrot.y, camrot.z, 2, 0);
					Local_Flying_Axe_Idle = false;
					if (!Local_Flying_Axe_Attack) {
						New_Local_Flying_Axe_Cor = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(self::ped, 0, 0, 0);
						if (MISC::GET_DISTANCE_BETWEEN_COORDS(Dev_Veh_C.x, Dev_Veh_C.y, Dev_Veh_C.z, self::pos.x, self::pos.y, self::pos.z, true) < 5) {
							if (Local_Flying_Axe_Animation)
							{
								const char* KROX_ANIMA = "cover@first_person@weapon@grenade";
								const char* KROX_ANIMAID = "low_l_throw_long";
								if (!ENTITY::IS_ENTITY_PLAYING_ANIM(self::ped, KROX_ANIMA, KROX_ANIMAID, 3))
								{
									STREAMING::REQUEST_ANIM_DICT(KROX_ANIMA);
									if (STREAMING::HAS_ANIM_DICT_LOADED((KROX_ANIMA)))
									{

										TASK::TASK_PLAY_ANIM(self::ped, KROX_ANIMA, KROX_ANIMAID, 8.00, 8.00, -1, 48, 0, FALSE, FALSE, FALSE);
										Local_Flying_Axe_Animation = false;
									}
								}
							}

							int bone = ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(self::ped, (char*)"IK_R_Hand");
							ENTITY::ATTACH_ENTITY_TO_ENTITY(Local_Flying_Axe, self::ped, bone, 0, -0.05, -0.05, -61, 28.4, -48.8, false, false, true, true, 0, true, false);

						}


					}
					else
					{
						if (ENTITY::IS_ENTITY_ATTACHED(Local_Flying_Axe))
						{


							ENTITY::DETACH_ENTITY(Local_Flying_Axe, 0, true);
							if (!Local_Flying_Axe_Animation)
							{
								const char* KROX_ANIMA = "weapons@first_person@aim_rng@generic@projectile@grenade_str";
								const char* KROX_ANIMAID = "throw_m_fb_forward";
								if (!ENTITY::IS_ENTITY_PLAYING_ANIM(self::ped, KROX_ANIMA, KROX_ANIMAID, 3))
								{
									STREAMING::REQUEST_ANIM_DICT(KROX_ANIMA);
									if (STREAMING::HAS_ANIM_DICT_LOADED((KROX_ANIMA)))
									{

										TASK::TASK_PLAY_ANIM(self::ped, KROX_ANIMA, KROX_ANIMAID, 8.00, 8.00, -1, 48, 0, FALSE, FALSE, FALSE);
										Local_Flying_Axe_Animation = true;
									}
								}
							}


						}
					}
					PAD::DISABLE_CONTROL_ACTION(0, 24, TRUE);
					if (PAD::IS_DISABLED_CONTROL_PRESSED(0, 24))
					{
						//	g_ui_mgr->create_notification(2000, g_translation.options["misc"]["bool_axe"].get<std::string>().c_str(), (char*)"Axe Going Away");

						Local_Flying_Axe_Attack = true;
						New_Local_Flying_Axe_Cor = GET_COORDINATES_OF_MY_CAM(150);
						PAD::SET_CONTROL_SHAKE(0, 1, 5);
					}
					else
					{

					}
				}
				else
				{
					Local_Flying_Axe_Attack = false;
					Local_Flying_Axe_Idle = true;
				}
				Vector3 Sub_Vect = SUB_VECTORS(Local_Flying_Axe_Cor, Dev_Veh_C);
				Vector3 Vecoloty_k = ENTITY::GET_ENTITY_VELOCITY(Local_Flying_Axe);
				if (entity::take_control_of(Local_Flying_Axe))

					Local_Flying_Axe_Idle ? apply_force_to_pos(Local_Flying_Axe, Sub_Vect.x * 1, Sub_Vect.y * 1, Sub_Vect.z * 1, Vecoloty_k, 0.5, 0.3) : apply_force_to_pos(Local_Flying_Axe, Sub_Vect.x * 1, Sub_Vect.y * 1, Sub_Vect.z * 1, Vecoloty_k, 2.5, 0.3);

			}
		}
		else
		{
			if (ENTITY::DOES_ENTITY_EXIST(Local_Flying_Axe))
			{
				ENTITY::DELETE_ENTITY(&Local_Flying_Axe);
			}
		}
	}
}