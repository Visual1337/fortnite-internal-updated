#pragma once
#include <stdlib.h>

double outlinethickness = 1.0f;

namespace settings {
	namespace bones
	{
		bool head = true;
		bool neck = false;
		bool torso = false;
		bool pelvis = false;
	}

	namespace triggerbot {
		bool enable = false;
	}

	namespace aimbot {

		bool enable = false;
		bool bulletp = false;
		bool muzzle_line = false;
		bool bulletp_s = false;
		bool selfcol = false;
		bool selfcol_s = false;
		bool memory = false;
		bool test = false;
		bool mouse = false;
		bool silent = false;
		bool sticky_silent = false;
		bool interpolate = false;
		bool constant = false;
		bool show_fov = false;
		bool visible_only = false;
		bool target_line = false;
		double mouse_speed = 5;
		double interpolate_speed = 5;
		double field_of_view = 20;
	}

	namespace player {
		bool enable = false;
		bool skeleton = false;
		bool box = false;
		bool normal_box = false;
		bool cornered_box = false;
		bool snapline = false;
		bool eyes = false;
		bool player_name = false;
		bool active_weapon = false;
		bool display_distance = false;
		double max_distance = 300;
	}

	namespace containers {
		bool enable = false;
		bool ignore_opened = false;
		bool display_distance = false;
		bool lines = false;
		bool chest = false;
		bool ammo_box = false;
		bool cooler_and_food = false;
		bool safe = false;
		bool others = false;
		double max_distance = 450;
		double line_offset = 20;
	}

	namespace pickups {
		bool enable = false;
		bool display_distance = false;
		bool lines = false;
		bool common = false;
		bool uncommon = false;
		bool rare = false;
		bool epic = false;
		bool legendary = false;
		bool mythic = false;
		double max_distance = 50;
		double line_offset = 20;
	}

	namespace weakspot {
		bool enable = false;
		bool weakspot_aimbot = true;
		bool silent = false;
		bool mouse = false;
		bool memory = false;
		bool interpolate = false;
		bool constant = false;
		bool target_line = false;
		double interpolate_speed = 1;
	}

	namespace radar {
		bool enable = false;
		bool show_line_of_sight = true;
		bool useless_circle = true;
		bool players = true;
		bool containers = false;
		bool pickups = false;
		bool vehicles = false;
		double range = 100;
		double positionx = 100;
		double positiony = 100;
		double size = 150;
	}

	namespace exploits {
		bool enable_hooks = false;
		bool adswhilejumping = false;
		bool killyourself = false;
		double camerafovalue = 80;

		bool vehiclefly = false;
		double vehicle_flight_speed = 50;
		bool nobloom = false;
		bool fullautoweapons = false;
		bool bullettp = false;
		bool magicbullet = false;
		bool norecoil = false;
		double vehiclegravityslider = 0.01;
		bool doublepump = false;
		bool boatspeed = false;
		double boatspeedslider = 10;
		bool rapidfire = false;
		bool noreload = false;
		bool ziplinefly = false;
		bool testingthing = false;
		bool playerfly = false;
		bool creativefly = false;
		bool speedhack = false;
		bool instantrespawntest = false;
		bool vehiclespinbot = false;
		bool ziplinetp = false;
	}

	namespace miscellaneous {
		bool vehiclefly = false;
		double vehicle_flight_speed = 50;
		bool fovchanger = false;
		double fovslider = 105;
	}

	namespace rifts {
		bool enable = false;
		bool display_distance = false;
		double max_distance = 150;
	}

	namespace miscactors {
		bool enable = false;
		bool display_distance = false;
		double max_distance = 50;
		bool vehicles = false;
		bool rifts = false;
		bool flags = false;
		bool traps = false;

	}
	namespace vehicles {
		bool enable = false;
		bool display_distance = false;
		double max_distance = 150;
	}

	namespace style {
		/*bool text_outlined = true;*/
		float text_outlined = 2.f;
		bool performance = false;
	}
}