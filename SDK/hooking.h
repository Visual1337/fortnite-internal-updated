#pragma once
#include "skibidi.h"

#include "outline.h"

inline bool prediction = true;

bool in_area(fvector2d target, fvector2d pos, fvector2d size)
{
	SPOOF_FUNC;
	if (target.x > pos.x && target.y > pos.y)
		if (target.x < pos.x + size.x && target.y < pos.y + size.y)
			return true;

	return false;
}

namespace menu {
	static void run(ucanvas* canvas, player_pawn* local_pawn) {
		SPOOF_FUNC

			if (local_pawn && render::show_menu_old != render::show_menu) {
				if (render::show_menu) local_pawn->disable_input(render::controller);
				else local_pawn->enable_input(render::controller);

				render::show_menu_old = render::show_menu;
			}

		if (render::show_menu) {

			static vantax::menu::menu_class::gui menu;
			static auto menu_tab = int(1);
			//////////////////////////////////////////x//////y
			menu.begin((L""), fvector2d(100, 200), fvector2d(650, 310));

			menu.set_y(65);

			if (menu.button(Encrypt(L"Aim"), menu_tab == 0)) menu_tab = 0;
			if (menu.button(Encrypt(L"ESP"), menu_tab == 1)) menu_tab = 1;
			if (menu.button(Encrypt(L"Enviroment"), menu_tab == 2)) menu_tab = 2;
			//if (menu.button(Encrypt(L"Miscellaneous"), menu_tab == 3)) menu_tab = 3;
			if (menu.button(Encrypt(L"Exploits"), menu_tab == 4)) menu_tab = 4;

			menu.set_x(130);
			menu.set_y(30);

			if (menu_tab == 0)
			{
				//aimbot page 1, child 1
				menu.text(Encrypt(L"Aim Methods:"));
				menu.space(5, 5);

				menu.checkbox(Encrypt(L"Enable Aimbot"), &settings::aimbot::enable);
				menu.checkbox(Encrypt(L"Mouse Aim"), &settings::aimbot::mouse);
				if (settings::aimbot::mouse == true)
				{
					menu.slider(Encrypt(L"Smoothing"), 1, 30, &settings::aimbot::mouse_speed);
				}
				else
				{

				}

				menu.checkbox(Encrypt(L"Silent Aim"), &settings::aimbot::silent);
				if (settings::aimbot::silent == true)
				{
					settings::exploits::enable_hooks = true;
				}
				else
				{
					settings::exploits::enable_hooks = false;
				}
				menu.checkbox(Encrypt(L"Memory Aim"), &settings::aimbot::memory);
				if (settings::aimbot::memory == true)
				{
					menu.checkbox(Encrypt(L"Interpolate"), &settings::aimbot::interpolate);

					menu.checkbox(Encrypt(L"Constant"), &settings::aimbot::constant);

					menu.slider(Encrypt(L"Smoothing"), 1, 30, &settings::aimbot::interpolate_speed);
				}
				else
				{

				}

				menu.set_x(370);
				menu.set_y(30);

				menu.text(Encrypt(L"Aimbot Options:"));
				menu.space(5, 5);
				menu.checkbox(Encrypt(L"Visible Check"), &settings::aimbot::visible_only);

				menu.checkbox(Encrypt(L"Muzzle Line"), &settings::aimbot::muzzle_line);

				menu.checkbox(Encrypt(L"Enemy Target Line"), &settings::aimbot::muzzle_line);

				menu.checkbox(Encrypt(L"Show Fov"), &settings::aimbot::show_fov);

				menu.slider(Encrypt(L"Fov Size"), 1, 50, &settings::aimbot::field_of_view);

				menu.checkbox(Encrypt(L"Head Bone"), &settings::bones::head);

				menu.checkbox(Encrypt(L"Neck Bone"), &settings::bones::neck);

				menu.checkbox(Encrypt(L"Pelvis Bone"), &settings::bones::pelvis);

				menu.checkbox(Encrypt(L"Torso Bone"), &settings::bones::torso);

				static bool target_line = false;

				static bool aimbot_fov = true;
			}
			else if (menu_tab == 1)
			{
				//player page 1, child 1
				menu.text(Encrypt(L"Visual Settings:"));
				menu.space(5, 5);

				menu.checkbox(Encrypt(L"Enable Visuals"), &settings::player::enable);

				menu.checkbox(Encrypt(L"2D Box"), &settings::player::normal_box);

				menu.checkbox(Encrypt(L"Corner Box"), &settings::player::cornered_box);

				menu.checkbox(Encrypt(L"Skeleton"), &settings::player::skeleton);

				menu.checkbox(Encrypt(L"Snaplines"), &settings::player::snapline);

				menu.checkbox(Encrypt(L"Username"), &settings::player::player_name);

				menu.checkbox(Encrypt(L"Distance"), &settings::player::display_distance);

				menu.slider(Encrypt(L"Outline Thickness"), 1, 50, &outlinethickness);

				//switch
				menu.set_x(370);
				menu.set_y(30);

			}
			else if (menu_tab == 2)
			{
				menu.text(Encrypt(L"Enviroment Settings:"));
				menu.space(5, 5);

				menu.checkbox(Encrypt(L"Enable Enviroment"), &settings::pickups::enable);

				menu.checkbox(Encrypt(L"Common Loot"), &settings::pickups::common);

				menu.checkbox(Encrypt(L"Uncommon Loot"), &settings::pickups::uncommon);

				menu.checkbox(Encrypt(L"Rare Loot"), &settings::pickups::rare);

				menu.checkbox(Encrypt(L"Epic Loot"), &settings::pickups::epic);

				menu.checkbox(Encrypt(L"Legendary Loot"), &settings::pickups::legendary);

				menu.set_x(370);
				menu.set_y(30);

				menu.text(Encrypt(L"Enviroment Misc:"));
				menu.space(5, 5);

				menu.checkbox(Encrypt(L"Enable Miscators"), &settings::miscactors::enable);

				menu.checkbox(Encrypt(L"Enable Containers"), &settings::containers::enable);

				menu.checkbox(Encrypt(L"Chests"), &settings::containers::chest);

				menu.checkbox(Encrypt(L"Ammo Box"), &settings::containers::ammo_box);

				menu.checkbox(Encrypt(L"Vehicles"), &settings::miscactors::vehicles);

				menu.checkbox(Encrypt(L"Rifts"), &settings::miscactors::rifts);

				menu.checkbox(Encrypt(L"Traps"), &settings::miscactors::traps);

				menu.checkbox(Encrypt(L"Ignore Opened"), &settings::containers::ignore_opened);
			}
			
		else if (menu_tab == 4)
			{
				menu.text(Encrypt(L"Exploit Settings:"));
				menu.space(5, 5);
				menu.checkbox(Encrypt(L"Fov"), &settings::miscellaneous::fovchanger);
				if (settings::miscellaneous::fovchanger == true)
				{
					menu.slider(Encrypt(L"slider"), 1, 180, &settings::miscellaneous::fovslider);
				}
				menu.checkbox(Encrypt(L"Bullettp"), &settings::aimbot::bulletp);
				
				






				menu.set_x(370);
				menu.set_y(30);
				menu.text(Encrypt(L"radar and shit"));
				menu.checkbox(Encrypt(L"Radar"), &settings::radar::enable);

				menu.checkbox(Encrypt(L"Players"), &settings::radar::players);

				menu.slider(Encrypt(L"Radar Range"), 1, 250, &settings::radar::range);

				menu.slider(Encrypt(L"Radar Size"), 1, 250, &settings::radar::size);

				menu.slider(Encrypt(L"Position X"), 1, 10000, &settings::radar::positionx);

				menu.slider(Encrypt(L"Position Y"), 1, 10000, &settings::radar::positiony);

				menu.space(5, 5);
			}
			
			menu.end();

			
		}
	}
}

#define M_PI   3.14159265358979323846264338327950288

float degree_to_radian(float degree) {
	SPOOF_FUNC;
	return degree * (M_PI / 180);
}

void angle_rotation(const frotator& angles, fvector* forward)
{
	float	sp, sy, cp, cy;

	sy = sin(degree_to_radian(angles.yaw));
	cy = cos(degree_to_radian(angles.yaw));

	sp = sin(degree_to_radian(angles.pitch));
	cp = cos(degree_to_radian(angles.pitch));

	forward->x = cp * cy;
	forward->y = cp * sy;
	forward->z = -sp;
}

namespace fortnite {
	namespace temp {
		bool silent_active = false;
		frotator silent_rotation = frotator();
		bool sticky_silent_active = false;
		frotator sticky_silent_rotation = frotator();
	}
	bool visible;
	namespace radar {
		fvector2d position, size;
		fvector camera_location;
		frotator camera_rotation;

		void range(double* x, double* y, double range) {
			if (defines::math->abs((*x)) > range || defines::math->abs((*y)) > range) {
				if ((*y) > (*x)) {
					if ((*y) > -(*x)) {
						(*x) = range * (*x) / (*y);
						(*y) = range;
					}
					else {
						(*y) = -range * (*y) / (*x);
						(*x) = -range;
					}
				}
				else {
					if ((*y) > -(*x)) {
						(*y) = range * (*y) / (*x);
						(*x) = range;
					}
					else {
						(*x) = -range * (*x) / (*y);
						(*y) = -range;
					}
				}
			}
		}

		void rotate_point(fvector2d* screen, fvector origin, fvector camera_location, frotator camera_rotation) {
			auto yaw = camera_rotation.yaw * 3.1415927 / 180;

			double dx = origin.x - camera_location.x;
			double dy = origin.y - camera_location.y;

			double fsin_yaw = defines::math->sin(yaw);
			double fminus_cos_yaw = -defines::math->cos(yaw);

			double x = -(dy * fminus_cos_yaw + dx * fsin_yaw);
			double y = dx * fminus_cos_yaw - dy * fsin_yaw;

			double range_value = settings::radar::range * 1000;
			range(&x, &y, range_value);

			auto DrawPos = radar::position;
			auto DrawSize = radar::size;

			int rad_x = (int)DrawPos.x;
			int rad_y = (int)DrawPos.y;

			double r_siz_x = DrawSize.x;
			double r_siz_y = DrawSize.y;

			int x_max = (int)r_siz_x + rad_x - 5;
			int y_max = (int)r_siz_y + rad_y - 5;

			double out_screen_x = rad_x + ((int)r_siz_x / 2 + int(x / range_value * r_siz_x));
			double out_screen_y = rad_y + ((int)r_siz_y / 2 + int(y / range_value * r_siz_y));

			if (out_screen_x > x_max)
				out_screen_x = x_max;

			if (out_screen_x < rad_x)
				out_screen_x = rad_x;

			if (out_screen_y > y_max)
				out_screen_y = y_max;

			if (out_screen_y < rad_y)
				out_screen_y = rad_y;

			*screen = fvector2d(out_screen_x, out_screen_y);
		}

		void add_to_radar(fvector world_location, flinearcolor color) {
			fvector2d screen;
			rotate_point(&screen, world_location, radar::camera_location, radar::camera_rotation);

			render::filled_box(screen, fvector2d(4, 4), color);
		}

		void radar_initialize(fvector2d position, fvector2d size, fvector camera_location, frotator camera_rotation) {
			radar::position = position;
			radar::size = size;
			radar::camera_location = camera_location;
			radar::camera_rotation = camera_rotation;

			render::filled_box(position, size, flinearcolor(0.060f, 0.060f, 0.060f, 1.f));

			//if (settings::radar::useless_circle) {
			//	render::circle(fvector2d(position.x + size.x / 2, position.y + size.y / 2), size.x / 2, 100, flinearcolor(1.f, 1.f, 1.f, 1.f) 2.f); // 1.f, 0.f, 0.f, 1.f
			//}

			if (settings::radar::show_line_of_sight) {
				render::line(fvector2d(position.x + size.x / 2, position.y + size.y), fvector2d(position.x + size.x / 2, position.y + size.y / 2), flinearcolor(0.020f, 0.020f, 0.020f, 1.f), 1.f);
				render::line(fvector2d(position.x + size.x / 2, position.y + size.y / 2), fvector2d(position.x, position.y), flinearcolor(0.020f, 0.020f, 0.020f, 1.f), 1.f);
				render::line(fvector2d(position.x + size.x / 2, position.y + size.y / 2), fvector2d(position.x + size.x, position.y), flinearcolor(0.020f, 0.020f, 0.020f, 1.f), 1.f);
			}
		}
	}

	void set_aim_mouse(aplayercontroller* controller, fvector aim_location, float width, float height, float smooth) {
		SPOOF_FUNC;
		float ScreenCenterX = (width / 2);
		float ScreenCenterY = (height / 2);
		float TargetX = 0;
		float TargetY = 0;
		auto aim_screen = fvector2d();
		if (controller->w2s(aim_location, &aim_screen) && aim_screen) {
			if (aim_screen.x != 0)
			{
				if (aim_screen.x > ScreenCenterX)
				{
					TargetX = -(ScreenCenterX - aim_screen.x);
					TargetX /= smooth;
					if (TargetX + ScreenCenterX > ScreenCenterX * 2) TargetX = -0;
				}

				if (aim_screen.x < ScreenCenterX)
				{
					TargetX = aim_screen.x - ScreenCenterX;
					TargetX /= smooth;
					if (TargetX + ScreenCenterX < 0) TargetX = -0;
				}
			}

			if (aim_screen.y != 0)
			{
				if (aim_screen.y > ScreenCenterY)
				{
					TargetY = -(ScreenCenterY - aim_screen.y);
					TargetY /= smooth;
					if (TargetY + ScreenCenterY > ScreenCenterY * 2) TargetY = -0;
				}

				if (aim_screen.y < ScreenCenterY)
				{
					TargetY = aim_screen.y - ScreenCenterY;
					TargetY /= smooth;
					if (TargetY + ScreenCenterY < 0) TargetY = -0;
				}
			}
			IFH(mouse_event)(MOUSEEVENTF_MOVE, static_cast<DWORD>(TargetX), static_cast<DWORD>(TargetY), NULL, NULL);
		}

	}

	void set_aim(uworld* world, aplayercontroller* controller, fvector camera_location, frotator camera_rotation, fvector aim_location, bool interpolate, bool constant, double speed) {
		SPOOF_FUNC;
		auto aim_rotation = defines::math->find_look_at_rotation(camera_location, aim_location);
		auto world_delta_seconds = defines::game_statics->get_world_delta_seconds(world);

		auto result = aim_rotation;
		if (interpolate) {
			if (constant)
				result = defines::math->interp_to_constant(camera_rotation, aim_rotation, world_delta_seconds, speed);
			else
				result = defines::math->interp_to(camera_rotation, aim_rotation, world_delta_seconds, speed);
		}

		result.pitch = (result.pitch - camera_rotation.pitch) / controller->input_pitch_scale();
		result.yaw = (result.yaw - camera_rotation.yaw) / controller->input_yaw_scale();

		controller->add_pitch_input((float)result.pitch);
		controller->add_yaw_input((float)result.yaw);
	}

	fvector bottom, bottom_2, head, head_2, neck, chest, pelvis, rshoulder, relbow, rhand, rthigh, rknee, rfoot, rfootout, lshoulder, lelbow, lhand, lthigh, lknee, lfoot, lfootout;
	fvector2d s_bottom, s_bottom_2, s_head, s_head_2, s_neck, s_chest, s_pelvis, s_rshoulder, s_relbow, s_rhand, s_rthigh, s_rknee, s_rfoot, s_rfootout, s_lshoulder, s_lelbow, s_lhand, s_lthigh, s_lknee, s_lfoot, s_lfootout;

	bool get_performance_bones(aplayercontroller* controller, mesh* mesh) {
		SPOOF_FUNC;
		bool success = true;

		bottom = mesh->get_bone_location(0);
		if (success && !controller->w2s(bottom, &s_bottom)) success = false;


		head = mesh->get_bone_location(109);
		if (success && !controller->w2s(head, &s_head)) success = false;

		if (!s_bottom || !s_head)
			return false;

		return success;
	}

	bool get_all_bones(aplayercontroller* controller, mesh* mesh) {
		SPOOF_FUNC;
		bool success = true;

		bottom = mesh->get_bone_location(0);
		if (success && !controller->w2s(bottom, &s_bottom)) success = false;

		bottom_2 = bottom; bottom_2.z -= 10;
		if (success && !controller->w2s(bottom_2, &s_bottom_2)) success = false;

		head = mesh->get_bone_location(109);
		if (success && !controller->w2s(head, &s_head)) success = false;

		head_2 = head; head_2.z += 13;
		if (success && !controller->w2s(head_2, &s_head_2)) success = false;

		neck = mesh->get_bone_location(67);
		if (success && !controller->w2s(neck, &s_neck)) success = false;

		chest = mesh->get_bone_location(7); chest.z += 7;
		if (success && !controller->w2s(chest, &s_chest)) success = false;

		pelvis = mesh->get_bone_location(2);
		if (success && !controller->w2s(pelvis, &s_pelvis)) success = false;

		rshoulder = mesh->get_bone_location(38);
		if (success && !controller->w2s(rshoulder, &s_rshoulder)) success = false;

		relbow = mesh->get_bone_location(39);
		if (success && !controller->w2s(relbow, &s_relbow)) success = false;

		rhand = mesh->get_bone_location(40);
		if (success && !controller->w2s(rhand, &s_rhand)) success = false;

		rthigh = mesh->get_bone_location(78);
		if (success && !controller->w2s(rthigh, &s_rthigh)) success = false;

		rknee = mesh->get_bone_location(79);
		if (success && !controller->w2s(rknee, &s_rknee)) success = false;

		rfoot = mesh->get_bone_location(82);
		if (success && !controller->w2s(rfoot, &s_rfoot)) success = false;

		rfootout = mesh->get_bone_location(83);
		if (success && !controller->w2s(rfootout, &s_rfootout)) success = false;

		lshoulder = mesh->get_bone_location(9);
		if (success && !controller->w2s(lshoulder, &s_lshoulder)) success = false;

		lelbow = mesh->get_bone_location(10);
		if (success && !controller->w2s(lelbow, &s_lelbow)) success = false;

		lhand = mesh->get_bone_location(11);
		if (success && !controller->w2s(lhand, &s_lhand)) success = false;

		lthigh = mesh->get_bone_location(71);
		if (success && !controller->w2s(lthigh, &s_lthigh)) success = false;

		lknee = mesh->get_bone_location(72);
		if (success && !controller->w2s(lknee, &s_lknee)) success = false;

		lfoot = mesh->get_bone_location(75);
		if (success && !controller->w2s(lfoot, &s_lfoot)) success = false;

		lfootout = mesh->get_bone_location(76);
		if (success && !controller->w2s(lfootout, &s_lfootout)) success = false;

		if (!s_bottom || !s_head || !s_neck || !s_chest || !s_rshoulder || !s_relbow || !s_rhand || !s_lshoulder || !s_lelbow || !s_lhand || !s_rthigh || !s_rknee || !s_rfoot || !s_rfootout || !s_lthigh || !s_lknee || !s_lfoot || !s_lfootout)
			return false;


		return success;
	}
}

namespace essential_hooks {
	fvector location_o = fvector();
	frotator rotation_o = frotator();

	ulocalplayer* local_player_old = 0;
	aplayercontroller* player_controller_old = 0;

	using get_view_point_sim = void(*)(ulocalplayer* local_player, fminimalviewinfo* out_viewinfo, BYTE stereo_pass);
	get_view_point_sim get_view_point_o = 0;

	void get_view_point(ulocalplayer* local_player, fminimalviewinfo* out_viewinfo, BYTE stereo_pass) {
		get_view_point_o(local_player, out_viewinfo, stereo_pass);

		if (fortnite::temp::silent_active) {
			out_viewinfo->location = location_o;
			out_viewinfo->rotation = rotation_o;
		}

		if (fortnite::temp::sticky_silent_active) {
			out_viewinfo->location = location_o;
			out_viewinfo->location.z += 40;
			out_viewinfo->rotation = fortnite::temp::sticky_silent_rotation;

		}
	}

	using get_player_view_point_sim = void(*)(aplayercontroller* controller, fvector* location, frotator* rotation);
	get_player_view_point_sim get_player_view_point_o = 0;

	void get_player_view_point(aplayercontroller* controller, fvector* location, frotator* rotation) {
		get_player_view_point_o(controller, location, rotation);

		location_o = *location;
		rotation_o = *rotation;

		if (fortnite::temp::silent_active) {
			*rotation = fortnite::temp::silent_rotation;
		}

		if (fortnite::temp::sticky_silent_active) {
			*rotation = fortnite::temp::sticky_silent_rotation;
		}
	}

	void run(aplayercontroller* controller, ulocalplayer* local_player) {
		if (local_player != essential_hooks::local_player_old) {
			essential_hooks::get_view_point_o = vmt<decltype(essential_hooks::get_view_point_o)>(reinterpret_cast<void*>(local_player), reinterpret_cast<void*>(essential_hooks::get_view_point), 0x58);
			essential_hooks::local_player_old = local_player;
		}

		if (controller != essential_hooks::player_controller_old) {
			essential_hooks::get_player_view_point_o = vmt<decltype(essential_hooks::get_player_view_point_o)>(reinterpret_cast<void*>(controller), reinterpret_cast<void*>(essential_hooks::get_player_view_point), 0xFE);
			essential_hooks::player_controller_old = controller;
		}
	}
}



void novacane_main(ugameviewportclient* viewport, ucanvas* canvas) {
	SPOOF_FUNC;
	auto screen_size = fvector2d((double)canvas->clip_x(), (double)canvas->clip_y());
	auto center = fvector2d((double)screen_size.x / 2, (double)screen_size.y / 2);
	bool player_silent = false;

	auto world = viewport->get_world();
	if (!world) return;

	auto game_instance = defines::game_statics->get_game_instance(world);
	if (!game_instance) return;

	auto local_player = game_instance->get_local_players()[0];
	if (!game_instance) return;

	auto controller = defines::game_statics->get_player_controller(world, std::int32_t(0));
	if (!controller) return;

	auto camera_manager = defines::game_statics->get_player_camera_manager(world, std::int32_t(0));
	if (!camera_manager) return;

	if (settings::exploits::enable_hooks) {
		SPOOF_FUNC;
		essential_hooks::run(controller, local_player);
	}

	render::world = world;
	render::canvas = canvas;
	render::controller = controller;
	render::screen_center = center;
	render::screen_size = screen_size;




	auto camera_location = camera_manager->get_camera_location();
	auto camera_rotation = camera_manager->get_camera_rotation();
	auto camera_fov = camera_manager->get_fov_angle();


	auto radius = (settings::aimbot::field_of_view * center.x / (double)camera_fov) / 2;

	auto local_pawn_holding_pickaxe = false;
	auto local_pawn = controller->get_pawn();
	auto local_team = (char)6969;

	if (render::is_insert_clicked()) render::show_menu = !render::show_menu;
	menu::run(canvas, local_pawn);


	if (settings::radar::enable) {
		fortnite::radar::radar_initialize(fvector2d(settings::radar::positionx, settings::radar::positiony), fvector2d(settings::radar::size, settings::radar::size), camera_location, camera_rotation);
	}
	if (settings::miscellaneous::fovchanger) {
		if (local_pawn) {
			controller->fov(settings::miscellaneous::fovslider);
		}
	}
	if (settings::player::enable) {
		SPOOF_FUNC
		double closest_distance = DBL_MAX;
		player_pawn* target_player = 0;

		tarray<uobject*> player_array = defines::game_statics->get_all_actors_of_class(world, defines::actor_player_class);
		for (int i = 0; i < player_array.size(); i++) {
			if (!player_array.valid(i)) continue;

			auto player = (player_pawn*)player_array[i];
			if (player == local_pawn) continue;
			if (!player) continue;

			if (player->is_dead()) continue;

			auto object_name = defines::system->get_object_name(player);

			if (!defines::string->contains(object_name.c_str(), L"PlayerPawn", false, false)) continue;

			bool teammate = player->get_team() == local_team;

			auto skeleton_color = flinearcolor(1.f, 1.f, 1.f, 1.f);
			auto visible_color = flinearcolor(1.f, 0.f, 0.f, 1.f);
			auto black_color = flinearcolor(0.f, 0.f, 0.f, 1.f);

			auto world_location = player->get_actor_location();

			if (settings::radar::enable && settings::radar::players) {
				SPOOF_FUNC
					fortnite::radar::add_to_radar(world_location, visible_color);
			}

			auto max_distance = settings::player::max_distance;
			double distance = defines::math->vector_distance(world_location, camera_location) * 0.01;
			if (distance > max_distance) continue;

			bool visible = defines::lib->CheckLineOfSightToActorWithChannel(camera_location, player, ECollisionChannel::ECC_Visibility, nullptr);
			if (visible) {
				fortnite::visible = true;
				visible_color = flinearcolor(0.0706f, 0.5098f, 0.1098f, 0.75f);
			}
			else {
				fortnite::visible = false;
				visible_color = flinearcolor(0.5608f, 0.3882f, 0.2118f, 0.8f);
			}

			if (teammate)
				visible_color = flinearcolor(0.0706f, 0.5098f, 0.1098f, 0.75f);


			auto mesh = player->get_pawn_mesh();
			if (!mesh) continue;

			if (!settings::style::performance) {
				if (!fortnite::get_all_bones(controller, mesh)) continue;
			}
			else {
				if (!fortnite::get_performance_bones(controller, mesh)) continue;
			}

			if (!in_area(fortnite::s_bottom, fvector2d(50, 50), fvector2d(screen_size.x - (50 * 2), screen_size.y - (50 * 2)))) continue;

			if (settings::player::skeleton) {
				SPOOF_FUNC
					render::line(fortnite::s_head, fortnite::s_neck, skeleton_color, 1.f);
				render::line(fortnite::s_neck, fortnite::s_chest, skeleton_color, 1.f);
				render::line(fortnite::s_chest, fortnite::s_pelvis, skeleton_color, 1.f);

				render::line(fortnite::s_chest, fortnite::s_rshoulder, skeleton_color, 1.f);
				render::line(fortnite::s_rshoulder, fortnite::s_relbow, skeleton_color, 1.f);
				render::line(fortnite::s_relbow, fortnite::s_rhand, skeleton_color, 1.f);
				render::line(fortnite::s_pelvis, fortnite::s_rthigh, skeleton_color, 1.f);
				render::line(fortnite::s_rthigh, fortnite::s_rknee, skeleton_color, 1.f);
				render::line(fortnite::s_rknee, fortnite::s_rfoot, skeleton_color, 1.f);
				//render::line(fortnite::s_rfoot, fortnite::s_rfootout, skeleton_color, 1.f);

				render::line(fortnite::s_chest, fortnite::s_lshoulder, skeleton_color, 1.f);
				render::line(fortnite::s_lshoulder, fortnite::s_lelbow, skeleton_color, 1.f);
				render::line(fortnite::s_lelbow, fortnite::s_lhand, skeleton_color, 1.f);
				render::line(fortnite::s_pelvis, fortnite::s_lthigh, skeleton_color, 1.f);
				render::line(fortnite::s_lthigh, fortnite::s_lknee, skeleton_color, 1.f);
				render::line(fortnite::s_lknee, fortnite::s_lfoot, skeleton_color, 1.f);
				//render::line(fortnite::s_lfoot, fortnite::s_lfootout, esp_color, 1.f);

			}
			auto most_left = DBL_MAX;
			auto most_right = DBL_MIN;
			auto most_top = DBL_MAX;
			auto most_bottom = DBL_MIN;


			if (!settings::style::performance) {
				fvector2d bones_to_check[] = { fortnite::s_bottom, fortnite::s_head, fortnite::s_head_2, fortnite::s_neck, fortnite::s_chest, fortnite::s_pelvis, fortnite::s_rshoulder, fortnite::s_relbow, fortnite::s_rhand, fortnite::s_rthigh, fortnite::s_rknee, fortnite::s_rfoot, fortnite::s_rfootout, fortnite::s_lshoulder, fortnite::s_lelbow,fortnite::s_lhand, fortnite::s_lthigh, fortnite::s_lknee, fortnite::s_lfoot, fortnite::s_lfootout };

				for (int i = 0; i < 20; i++) {
					auto bone = bones_to_check[i];

					if (bone.x < most_left)
						most_left = bone.x;

					if (bone.x > most_right)
						most_right = bone.x;

					if (bone.y < most_top)
						most_top = bone.y;

					if (bone.y > most_bottom)
						most_bottom = bone.y;
				}
			}
			else {
				fvector2d bones_to_check[] = { fortnite::s_bottom, fortnite::s_head };

				for (int i = 0; i < 2; i++) {
					auto bone = bones_to_check[i];

					if (bone.x < most_left)
						most_left = bone.x;

					if (bone.x > most_right)
						most_right = bone.x;

					if (bone.y < most_top)
						most_top = bone.y;

					if (bone.y > most_bottom)
						most_bottom = bone.y;
				}
			}
			auto actor_height = most_bottom - most_top;
			auto actor_width = most_right - most_left;

			auto calculated_distance = max_distance - distance;
			auto offset = calculated_distance * 0.0120;
			//auto offset = calculated_distance * 0.015;
			auto corner_wide = actor_width / 2;
			auto corner_heit = actor_height / 2;

			auto text_offset = double(0);
			fvector2d bottom_middle;
			fvector2d top_middle;
			if (!settings::style::performance) {
				bottom_middle = fvector2d(most_left + actor_width / 2, fortnite::s_bottom_2.y);
			}
			else {
				bottom_middle = fvector2d(most_left + actor_width / 2, fortnite::s_bottom.y);
			}

			if (settings::player::cornered_box) {
				//top left
				render::line(fvector2d(most_left - offset, most_top - offset), fvector2d(most_left - offset + corner_wide, most_top - offset), visible_color, 1.f);
				render::line(fvector2d(most_left - offset, most_top - offset), fvector2d(most_left - offset, most_top - offset + corner_heit), visible_color, 1.f);

				//top right
				render::line(fvector2d(most_right + offset, most_top - offset), fvector2d(most_right + offset - corner_wide, most_top - offset), visible_color, 1.f);
				render::line(fvector2d(most_right + offset, most_top - offset), fvector2d(most_right + offset, most_top - offset + corner_heit), visible_color, 1.f);

				//bottom left
				render::line(fvector2d(most_left - offset, most_bottom + offset), fvector2d(most_left - offset + corner_wide, most_bottom + offset), visible_color, 1.f);
				render::line(fvector2d(most_left - offset, most_bottom + offset), fvector2d(most_left - offset, most_bottom + offset - corner_heit), visible_color, 1.f);

				//bottom right
				render::line(fvector2d(most_right + offset, most_bottom + offset), fvector2d(most_right + offset - corner_wide, most_bottom + offset), visible_color, 1.f);
				render::line(fvector2d(most_right + offset, most_bottom + offset), fvector2d(most_right + offset, most_bottom + offset - corner_heit), visible_color, 1.f);

				// Outline on the other side

			}

			if (settings::player::normal_box) {
				// left line
				render::line_with_outline(fvector2d(most_left - offset, most_top - offset), fvector2d(most_left - offset, most_bottom + offset), visible_color, 1.f);

				// right line
				render::line_with_outline(fvector2d(most_right + offset, most_top - offset), fvector2d(most_right + offset, most_bottom + offset), visible_color, 1.f);

				// top line
				render::line_with_outline(fvector2d(most_left - offset, most_top - offset), fvector2d(most_right + offset, most_top - offset), visible_color, 1.f);

				// bottom line
				render::line_with_outline(fvector2d(most_left - offset, most_bottom + offset), fvector2d(most_right + offset, most_bottom + offset), visible_color, 1.f);
			}


			if (settings::player::player_name) {
				if (local_pawn && render::world && !teammate) {
					auto playername = defines::lib->get_player_name_safe(player, defines::actor_player_nameprivate);
					render::text(playername.c_str(), fvector2d(bottom_middle.x, bottom_middle.y + text_offset), flinearcolor(1.f, 1.f, 1.f, 1.f), true, false, settings::style::text_outlined);
					text_offset += 18;
				}
			}

			if (settings::player::display_distance) {
				auto final = defines::string->build_string_double(L"", L"", defines::math->round(distance), L"m]");
				render::text(final.c_str(), fvector2d(bottom_middle.x, bottom_middle.y + text_offset), flinearcolor(1.f, 1.f, 1.f, 1.f), true, false, settings::style::text_outlined);
				text_offset += 18;
			}

			if (settings::player::active_weapon) {
				if (local_pawn) {
					if (auto current_weapon = player->get_current_weapon()) {
						if (auto weapon_data = current_weapon->get_weapon_data()) {
							auto display_name = weapon_data->display_name();
							if (display_name.data && display_name.c_str()) {
								auto tier = weapon_data->get_tier();

								auto render_color = flinearcolor();
								if (tier == fort_item_tier::I) render_color = flinearcolor(0.4f, 0.4f, 0.4f, 1.f);
								else if (tier == fort_item_tier::II) render_color = flinearcolor(0.2f, 0.8f, 0.4f, 1.f);
								else if (tier == fort_item_tier::III) render_color = flinearcolor(0.f, 0.4f, 0.8f, 1.f);
								else if (tier == fort_item_tier::IV) render_color = flinearcolor(1.f, 0.f, 1.f, 1.f);
								else if (tier == fort_item_tier::V) render_color = flinearcolor(0.7f, 0.7f, 0.f, 1.f);
								else if (tier == fort_item_tier::VI) render_color = flinearcolor(1.f, 1.f, 0.f, 1.f);

								if (render_color) {
									auto a = defines::string->build_string_int(display_name.c_str(), L" [", current_weapon->get_magazine_ammo_count(), L"");
									auto b = defines::string->build_string_int(L"", L"/", current_weapon->get_bullets_per_clip(), L"]");
									auto c = defines::string->concat_str_str(a, b);
									render::text(c.c_str(), fvector2d(bottom_middle.x, bottom_middle.y + text_offset), render_color, true, false, settings::style::text_outlined);
									text_offset += 15;
								}
							}
						}
					}
				}
			}

			if (settings::player::snapline) {
				render::line_with_outline(fvector2d(center.x, screen_size.y - 15), fvector2d(bottom_middle.x, bottom_middle.y + text_offset), visible_color, 1.f);
			}

			/*if (settings::player::eyes)
			{
				frotator _Angle = player->get_actor_rotation();

				fvector test2, headpos;

				headpos = fortnite::head;

				angle_rotation(_Angle, &test2);
				test2.x *= 50;
				test2.y *= 50;
				test2.z *= 50;

				fvector end = headpos + test2;
				fvector2d test1, test3;

				if (controller->w2s(headpos, &test1))
				{
					if (controller->w2s(end, &test3))
					{
						render::line_with_outline(fvector2d(test1.x, test1.y), fvector2d(test3.x, test3.y), { 1.0f, 0.0f, 0.0f, 1.0f }, 1.f);
					}
				}
			}*/

			if (!teammate && !local_pawn_holding_pickaxe && ((settings::aimbot::visible_only && visible) || (!settings::aimbot::visible_only)) && local_pawn && render::in_circle(center.x, center.y, radius, fortnite::s_head.x, fortnite::s_head.y)) {
				double distance = defines::math->distance2d(fortnite::s_head, center);
				if (distance < closest_distance) {
					target_player = player;
					closest_distance = distance;
				}
			}
		}

		if (settings::aimbot::enable) {
			auto temp_silent_active = false;
			auto temp_silent_rotation = frotator();

			auto temp_sticky_silent_active = false;
			auto temp_sticky_silent_rotation = frotator();


			if (settings::aimbot::show_fov) {
				render::filledCircle(center, radius, 100, flinearcolor(0.f, 0.f, 0.f, 1.f), 3.f);
			}



			if (target_player && local_pawn) {
				if (auto mesh = target_player->get_pawn_mesh()) {

					int32_t bone = 109;

					if (settings::bones::head)
						bone = 68;
					else if (settings::bones::neck)
						bone = 67;
					else if (settings::bones::torso)
						bone = 7;
					else if (settings::bones::pelvis)
						bone = 2;


					auto aim_location = mesh->get_bone_location(bone);
					auto esp_color = flinearcolor(0.f, 1.f, 1.f, 1.f);
					bool visible = defines::lib->CheckLineOfSightToActorWithChannel(camera_location, target_player, ECollisionChannel::ECC_Visibility, nullptr);
					if (visible) {
						esp_color = flinearcolor(0.f, 1.f, 1.f, 1.f);
					}
					else {
						esp_color = flinearcolor(1.f, 0.f, 0.f, 1.f);
					}

					if (settings::aimbot::target_line) {
						auto aim_screen = fvector2d();
						if (controller->w2s(aim_location, &aim_screen) && aim_screen) {
							render::line_with_outline(center, aim_screen, esp_color, 1.f);
						}
					}


					if (settings::aimbot::muzzle_line) {
						auto aim_location = mesh->get_bone_location(bone);
						auto activeWeapon = local_pawn->get_current_weapon();
						if (local_pawn) {
							if (activeWeapon) {
								auto aim_screen = fvector2d();
								auto muzzle_screen = fvector2d();
								if (controller->w2s(aim_location, &aim_screen) && controller->w2s(activeWeapon->get_muzzle_location(), &muzzle_screen) && aim_screen)
								{
									render::line_with_outline(muzzle_screen, aim_screen, esp_color, 1.f);
								}
							}
						}
					}
					if (settings::aimbot::bulletp)
					{
						tarray<uobject*> projectile_array = defines::game_statics->get_all_actors_of_class(world, defines::actor_projectile_class);
						for (int i = 0; i < projectile_array.size(); i++) {
							if (!projectile_array.valid(i)) continue;

							auto projectile = (actor*)projectile_array[i];
							if (!projectile) continue;

							auto object_name = defines::system->get_object_name(projectile);

							if (!defines::string->contains(object_name.c_str(), L"Bullet", false, false))
								continue;

							projectile->set_actor_location(aim_location, false, 0, false);
						}
					}
					if (settings::aimbot::silent) {
						SPOOF_FUNC;
						player_silent = true;
						temp_silent_active = true;
						temp_silent_rotation = defines::math->find_look_at_rotation(camera_location, aim_location);
					}

					if (controller->is_key_down(defines::right_mouse_button)) {
						if (settings::aimbot::memory) {
							SPOOF_FUNC;
							fortnite::set_aim(world, controller, camera_location, camera_rotation, aim_location, settings::aimbot::interpolate, settings::aimbot::constant, settings::aimbot::interpolate_speed);
						}
						else if (settings::aimbot::mouse) {
							SPOOF_FUNC;
							fortnite::set_aim_mouse(controller, aim_location, screen_size.x, screen_size.y, settings::aimbot::mouse_speed);
						}
					}
				}
			}

			fortnite::temp::silent_active = temp_silent_active;
			fortnite::temp::silent_rotation = temp_silent_rotation;

			fortnite::temp::sticky_silent_active = temp_sticky_silent_active;
			fortnite::temp::sticky_silent_rotation = temp_sticky_silent_rotation;
		}


	}



	if (settings::miscactors::vehicles)
	{
		SPOOF_FUNC
		tarray<uobject*> vehicle_array = defines::game_statics->get_all_actors_of_class(world, defines::actor_vehicle_class);
		for (int i = 0; i < vehicle_array.size(); i++) {
			if (!vehicle_array.valid(i)) continue;

			auto vehicle = (vehicle_actor*)vehicle_array[i];
			if (!vehicle) continue;

			auto screen_location = fvector2d();
			auto world_location = vehicle->get_actor_location();

			auto distance = defines::math->vector_distance(camera_location, world_location) * 0.01;

			if (distance > settings::miscactors::max_distance) continue;

			if (controller->w2s(world_location, &screen_location)) {

				if (settings::miscactors::display_distance) {
					auto final = defines::string->build_string_double(vehicle->get_display_name().c_str(), L" [", defines::math->round(distance), L"M]");
					render::text(final.c_str(), screen_location, flinearcolor(1.f, 0.f, 1.f, 1.f), true, true, false);
				}
				else {
					render::text(vehicle->get_display_name().c_str(), screen_location, flinearcolor(1.f, 0.f, 1.f, 1.f), true, true, false);
				}

			}
		}
	}

	if (settings::miscactors::flags)
	{
		SPOOF_FUNC
		tarray<uobject*> flag_array = defines::game_statics->get_all_actors_of_class(world, defines::actor_flag_class);
		for (int i = 0; i < flag_array.size(); i++) {
			if (!flag_array.valid(i)) continue;

			auto flag = (flag_actor*)flag_array[i];
			if (!flag) continue;

			auto screen_location = fvector2d();
			auto world_location = flag->get_actor_location();

			auto distance = defines::math->vector_distance(camera_location, world_location) * 0.01;

			if (distance > settings::miscactors::max_distance) continue;

			if (controller->w2s(world_location, &screen_location)) {

				if (settings::miscactors::display_distance) {
					auto final = defines::string->build_string_double(L"Flag", L" [", defines::math->round(distance), L"M]");
					render::text(final.c_str(), screen_location, flinearcolor(0.f, 1.f, 0.f, 1.f), true, true, false);
				}
				else {
					render::text(L"Flag", screen_location, flinearcolor(0.f, 1.f, 0.f, 1.f), true, true, settings::style::text_outlined);
				}

			}
		}
	}

	if (settings::miscactors::traps)
	{
		SPOOF_FUNC
		tarray<uobject*> trap_array = defines::game_statics->get_all_actors_of_class(world, defines::actor_trap_class);
		for (int i = 0; i < trap_array.size(); i++) {
			if (!trap_array.valid(i)) continue;

			auto trap = (trap_actor*)trap_array[i];
			if (!trap) continue;

			auto screen_location = fvector2d();
			auto world_location = trap->get_actor_location();

			auto distance = defines::math->vector_distance(camera_location, world_location) * 0.01;

			if (distance > settings::miscactors::max_distance) continue;

			if (controller->w2s(world_location, &screen_location)) {

				if (settings::miscactors::display_distance) {
					auto final = defines::string->build_string_double(L"Trap", L" [", defines::math->round(distance), L"M]");
					render::text(final.c_str(), screen_location, flinearcolor(0.f, 1.f, 0.f, 1.f), true, true, settings::style::text_outlined);
				}
				else {
					render::text(L"Trap", screen_location, flinearcolor(0.f, 1.f, 0.f, 1.f), true, true, settings::style::text_outlined);
				}

			}
		}
	}

	if (settings::miscactors::rifts) {
		SPOOF_FUNC
		tarray<uobject*> rift_array = defines::game_statics->get_all_actors_of_class(world, defines::actor_rift_class);
		for (int i = 0; i < rift_array.size(); i++) {
			if (!rift_array.valid(i)) continue;

			auto rift = (rift_actor*)rift_array[i];
			if (!rift) continue;


			auto screen_location = fvector2d();
			auto world_location = rift->get_actor_location();

			auto distance = defines::math->vector_distance(camera_location, world_location) * 0.01;

			if (distance > settings::miscactors::max_distance) continue;

			if (controller->w2s(world_location, &screen_location)) {
				if (settings::miscactors::display_distance) {
					auto final = defines::string->build_string_double(L"Rift", L" [", defines::math->round(distance), L"M]");
					render::text(final.c_str(), screen_location, flinearcolor(1.f, 1.f, 0.f, 1.f), true, true, settings::style::text_outlined);
				}
				else {
					render::text(L"Rift", screen_location, flinearcolor(1.f, 1.f, 0.f, 1.f), true, true, settings::style::text_outlined);
				}
			}
		}
	}

	if (settings::weakspot::enable) {
		SPOOF_FUNC
		weakspot_actor* target_weakspot = 0;
		tarray<uobject*> weakspot_array = defines::game_statics->get_all_actors_of_class(world, defines::actor_weakspot_class);
		for (int i = 0; i < weakspot_array.size(); i++) {
			if (!weakspot_array.valid(i)) continue;

			auto weakspot = (weakspot_actor*)weakspot_array[i];
			if (!weakspot) continue;

			if (!weakspot->is_active()) continue;

			target_weakspot = weakspot;
		}

		auto temp_silent_active = false;
		auto temp_silent_rotation = frotator();

		if (target_weakspot) {
			auto aim_location = target_weakspot->get_actor_location();
			auto aim_screen = fvector2d();
			if (controller->w2s(aim_location, &aim_screen) && aim_screen) {

				render::text(L"[X]", aim_screen, flinearcolor(1.f, 0.f, 0.f, 1.f), true, true, settings::style::text_outlined);

				if (settings::weakspot::weakspot_aimbot && local_pawn) {
					SPOOF_FUNC
					if (settings::weakspot::target_line) {
						render::line_with_outline(center, aim_screen, flinearcolor(1.f, 0.f, 0.f, 1.f), 1.f);
					}

					if (controller->is_key_down(defines::left_mouse_button)) {
						SPOOF_FUNC;
						if (settings::weakspot::silent) {
							temp_silent_active = true;
							temp_silent_rotation = defines::math->find_look_at_rotation(camera_location, aim_location);
						}
						else if (settings::weakspot::memory) {
							SPOOF_FUNC;
							fortnite::set_aim(world, controller, camera_location, camera_rotation, aim_location, settings::weakspot::interpolate, settings::weakspot::constant, settings::weakspot::interpolate_speed);
						}
						else if (settings::weakspot::mouse) {
							SPOOF_FUNC;
							float width = ((double)canvas->clip_x());
							float height = ((double)canvas->clip_y());

							fortnite::set_aim_mouse(controller, aim_location, screen_size.x, screen_size.y, settings::aimbot::mouse_speed);
						}
					}
				}
			}
		}

		if (!player_silent) {
			fortnite::temp::silent_active = temp_silent_active;
			fortnite::temp::silent_rotation = temp_silent_rotation;
		}
	}

	if (settings::pickups::enable) {
		tarray<uobject*> pickup_array = defines::game_statics->get_all_actors_of_class(world, defines::actor_pickup_class);
		for (int i = 0; i < pickup_array.size(); i++) {
			if (!pickup_array.valid(i)) continue;

			auto pickup = (pickup_actor*)pickup_array[i];
			if (!pickup) continue;

			auto screen_location = fvector2d();
			auto world_location = pickup->get_actor_location();
			auto distance = defines::math->vector_distance(camera_location, world_location) * 0.01;

			if (distance > settings::pickups::max_distance) continue;

			if (auto definition = pickup->get_item_definition()) {
				auto display_name = definition->display_name();
				if (display_name.data && display_name.c_str()) {
					auto render_color = flinearcolor();
					auto tier = definition->get_tier();

					if (settings::pickups::common && tier == fort_item_tier::I) render_color = flinearcolor(0.4f, 0.4f, 0.4f, 1.f);
					else if (settings::pickups::uncommon && tier == fort_item_tier::II) render_color = flinearcolor(0.2f, 0.8f, 0.4f, 1.f);
					else if (settings::pickups::rare && tier == fort_item_tier::III) render_color = flinearcolor(0.f, 0.4f, 0.8f, 1.f);
					else if (settings::pickups::epic && tier == fort_item_tier::IV) render_color = flinearcolor(1.f, 0.f, 1.f, 1.f);
					else if (settings::pickups::legendary && tier == fort_item_tier::V) render_color = flinearcolor(0.7f, 0.7f, 0.f, 1.f);
					else if (settings::pickups::mythic && tier == fort_item_tier::VI) render_color = flinearcolor(1.f, 1.f, 0.f, 1.f);

					if (settings::radar::enable && settings::radar::pickups && render_color) {
						fortnite::radar::add_to_radar(world_location, render_color);
					}

					if (controller->w2s(world_location, &screen_location) && screen_location) {
						if (render_color) {
							if (settings::pickups::lines && !render::in_circle(center.x, center.y, settings::pickups::line_offset, screen_location.x, screen_location.y)) {
								double angle = defines::math->atan2(screen_location.y - center.y, screen_location.x - center.x);

								double x = settings::pickups::line_offset * defines::math->cos(angle) + center.x;
								double y = settings::pickups::line_offset * defines::math->sin(angle) + center.y;

								fvector2d end_pos = fvector2d(x, y);
								render::line_with_outline(end_pos, fvector2d(screen_location.x, screen_location.y + 8), render_color, 0.75f);
							}

							if (settings::pickups::display_distance) {
								auto final = defines::string->build_string_double(display_name.c_str(), L" [", defines::math->round(distance), L"M]");
								render::text(final.c_str(), screen_location, render_color, true, true, settings::style::text_outlined);
							}
							else render::text(display_name.c_str(), screen_location, render_color, true, true, settings::style::text_outlined);
						}
					}
				}
			}
		}
	}

	if (settings::containers::enable) {
		tarray<uobject*> container_array = defines::game_statics->get_all_actors_of_class(world, defines::actor_container_class);
		for (int i = 0; i < container_array.size(); i++) {
			if (!container_array.valid(i)) continue;

			auto container = (container_actor*)container_array[i];
			if (!container) continue;

			if (settings::containers::ignore_opened && container->already_searched()) continue;

			auto object_name = defines::system->get_object_name(container);

			auto screen_location = fvector2d();
			auto world_location = container->get_actor_location();
			auto distance = defines::math->vector_distance(camera_location, world_location) * 0.01;

			if (distance > settings::containers::max_distance) continue;

			auto render_color = flinearcolor(1.f, 1.f, 1.f, 1.f);
			if (controller->w2s(world_location, &screen_location) && screen_location) {
				if (settings::containers::chest && defines::string->contains(object_name.c_str(), L"Tiered_Chest", false, false)) {
					render_color = flinearcolor(1.f, 1.f, 0.f, 1.f);
					if (settings::containers::display_distance) {
						auto final = defines::string->build_string_double(L"Chest ", L" [", defines::math->round(distance), L"M]");
						render::text(final.c_str(), screen_location, render_color, true, true, settings::style::text_outlined);
					}
					else render::text(L"Chest", screen_location, render_color, true, true, settings::style::text_outlined);
				}
				else if (settings::containers::ammo_box && defines::string->contains(object_name.c_str(), L"Tiered_Ammo", false, false)) {
					render_color = flinearcolor(0.4f, 0.4f, 0.4f, 1.f);
					if (settings::containers::display_distance) {
						auto final = defines::string->build_string_double(L"Ammo Box ", L" [", defines::math->round(distance), L"M]");
						render::text(final.c_str(), screen_location, render_color, true, true, settings::style::text_outlined);
					}
					else render::text(L"Ammo Box", screen_location, render_color, true, true, settings::style::text_outlined);
				}
				else if (settings::containers::chest && defines::string->contains(object_name.c_str(), L"AlwaysSpawn_NormalChest", false, false)) {
					render_color = flinearcolor(1.f, 1.f, 0.f, 1.f);
					if (settings::containers::display_distance) {
						auto final = defines::string->build_string_double(L"Chest ", L" [", defines::math->round(distance), L"M]");
						render::text(final.c_str(), screen_location, render_color, true, true, settings::style::text_outlined);
					}
					else render::text(L"Chest", screen_location, render_color, true, true, settings::style::text_outlined);
				}
				else if (settings::containers::cooler_and_food && defines::string->contains(object_name.c_str(), L"Cooler_Container", false, false)) {
					render_color = flinearcolor(0.f, 1.f, 1.f, 1.f);
					if (settings::containers::display_distance) {
						auto final = defines::string->build_string_double(L"Cooler ", L" [", defines::math->round(distance), L"M]");
						render::text(final.c_str(), screen_location, render_color, true, true, settings::style::text_outlined);
					}
					else render::text(L"Cooler", screen_location, render_color, true, true, settings::style::text_outlined);
				}
				else if (settings::containers::cooler_and_food && defines::string->contains(object_name.c_str(), L"FoodBox_Produce", false, false)) {
					render_color = flinearcolor(0.f, 1.f, 0.4f, 1.f);
					if (settings::containers::display_distance) {
						auto final = defines::string->build_string_double(L"Food Box ", L" [", defines::math->round(distance), L"M]");
						render::text(final.c_str(), screen_location, render_color, true, true, settings::style::text_outlined);
					}
					else render::text(L"Food box", screen_location, render_color, true, true, settings::style::text_outlined);
				}
				else if (settings::containers::safe && defines::string->contains(object_name.c_str(), L"Tiered_Safe", false, false)) {
					render_color = flinearcolor(1.f, 0.f, 0.f, 1.f);
					if (settings::containers::display_distance) {
						auto final = defines::string->build_string_double(L"Safe ", L" [", defines::math->round(distance), L"M]");
						render::text(final.c_str(), screen_location, render_color, true, true, settings::style::text_outlined);
					}
					else render::text(L"Safe", screen_location, render_color, true, true, settings::style::text_outlined);
				}
				else if (settings::containers::others && defines::string->contains(object_name.c_str(), L"Barrel_FishingRod", false, false)) {
					render_color = flinearcolor(0.4f, 0.4f, 0.4f, 1.f);
					if (settings::containers::display_distance) {
						auto final = defines::string->build_string_double(L"Fishing Rod ", L" [", defines::math->round(distance), L"M]");
						render::text(final.c_str(), screen_location, render_color, true, true, settings::style::text_outlined);
					}
					else render::text(L"Fishing rod", screen_location, render_color, true, true, settings::style::text_outlined);
				}
				else if (settings::containers::others && defines::string->contains(object_name.c_str(), L"CashRegister", false, false)) {
					render_color = flinearcolor(0.4f, 0.4f, 0.4f, 1.f);
					if (settings::containers::display_distance) {
						auto final = defines::string->build_string_double(L"Cash Register ", L" [", defines::math->round(distance), L"M]");
						render::text(final.c_str(), screen_location, render_color, true, true, settings::style::text_outlined);
					}
					else render::text(L"Cash register", screen_location, render_color, true, true, settings::style::text_outlined);
				}
				else if (settings::containers::chest && defines::string->contains(object_name.c_str(), L"BuriedChest", false, false)) {
					render_color = flinearcolor(1.f, 1.f, 0.f, 1.f);
					if (settings::containers::display_distance) {
						auto final = defines::string->build_string_double(L"Buried Chest ", L" [", defines::math->round(distance), L"M]");
						render::text(final.c_str(), screen_location, render_color, true, true, settings::style::text_outlined);
					}
					else render::text(L"Buried chest", screen_location, render_color, true, true, settings::style::text_outlined);
				}
				if (settings::containers::lines && render_color && !render::in_circle(center.x, center.y, settings::containers::line_offset, screen_location.x, screen_location.y)) {
					double angle = defines::math->atan2(screen_location.y - center.y, screen_location.x - center.x);

					double x = settings::containers::line_offset * defines::math->cos(angle) + center.x;
					double y = settings::containers::line_offset * defines::math->sin(angle) + center.y;

					fvector2d end_pos = fvector2d(x, y);
					render::line_with_outline(end_pos, fvector2d(screen_location.x, screen_location.y + 8), render_color, 1.f);
				}
			}

			if (settings::radar::enable && settings::radar::containers && render_color) {
				fortnite::radar::add_to_radar(world_location, render_color);
			}
		}
	}
}

namespace UnrealEngine {
	using draw_transition_sim = void(*)(ugameviewportclient* viewport, ucanvas* canvas);
	draw_transition_sim draw_transition_o = 0;


	void draw_transition(ugameviewportclient* viewport, ucanvas* canvas) {
		SPOOF_FUNC;
		novacane_main(viewport, canvas);
		return draw_transition_o(viewport, canvas);
	}


	static void init() {
		SPOOF_FUNC;
		game = get_module(xorstr_(L"FortniteClient-Win64-Shipping.exe"));

		if (!game)
			return;

		defines::init();


		if (auto world = uobject::find_object(xorstr_(L"Frontend"), reinterpret_cast<uobject*>(-1))) {
			auto game_instance = defines::game_statics->get_game_instance(world);
			auto local_player = game_instance->get_local_players()[0];


			auto controller = defines::game_statics->get_player_controller(world, std::int32_t(0));
			auto viewport = local_player->get_viewport();

			auto engine = (uengine*)defines::system->get_outer_object(game_instance);
			render::font = engine->get_font();


			draw_transition_o = vmt<decltype(draw_transition_o)>(reinterpret_cast<void*>(viewport), reinterpret_cast<void*>(draw_transition), 0x70);
		}

	}
}
