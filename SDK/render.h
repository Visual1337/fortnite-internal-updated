#pragma once

#include "outline.h"

namespace render {
	bool show_menu = true;
	bool draw_cursor = true;
	bool show_menu_old = false;
	bool outline = true;
	double linethickness = 2.f;
	int hovered_headers = 0;
	uworld* world;
	aplayercontroller* controller;
	ucanvas* canvas;
	uobject* font;
	fvector2d screen_center, screen_size;

	bool is_insert_clicked() {
		static bool insert_clicked = false;
		static bool insert_down_already = false;

		bool insert_down = render::controller->is_key_down(defines::insert);
		if (insert_down) {
			if (insert_down_already)
				insert_clicked = false;
			else {
				insert_clicked = true;
				insert_down_already = true;
			}
		}
		else {
			insert_clicked = false;
			insert_down_already = false;
		}

		return insert_clicked;
	}

	bool in_circle(int cx, int cy, int r, int x, int y) {
		SPOOF_FUNC;
		int dist = (x - cx) * (x - cx) + (y - cy) * (y - cy);
		if (dist <= r * r)
			return true;
		else
			return false;
	}

	void text(fstring content, fvector2d position, flinearcolor render_color, bool center_x, bool center_y, bool outlined) {
		canvas->k2_draw_text(font, content, position, fvector2d(1.0, 1.0), render_color, 1.0f, flinearcolor(), fvector2d(), center_x, center_y, outlined, flinearcolor(0, 0, 0, 1));
	}

	fvector2d text_size(fstring content) {
		SPOOF_FUNC;
		return canvas->k2_text_size(font, content, fvector2d(1.0, 1.0));
	}

	void line(fvector2d a, fvector2d b, flinearcolor render_color, float thickness) {
		canvas->k2_draw_line(a, b, thickness, render_color);
	}

	void line_with_outline(fvector2d a, fvector2d b, flinearcolor render_color, float thickness)
	{
		if (outline) {
			canvas->k2_draw_line(a, b, outlinethickness, flinearcolor(0.f, 0.f, 0.f, 1.f));
		}
		canvas->k2_draw_line(a, b, linethickness, render_color);
	}

	void circle(fvector2d position, int radius, int segments, flinearcolor color) {
		float PI = 3.1415927f;

		float Step = PI * 2.0 / segments;
		int Count = 0;
		fvector2d V[128];
		for (float a = 0; a < PI * 2.0; a += Step) {
			float X1 = radius * defines::math->cos(a) + position.x;
			float Y1 = radius * defines::math->sin(a) + position.y;
			float X2 = radius * defines::math->cos(a + Step) + position.x;
			float Y2 = radius * defines::math->sin(a + Step) + position.y;
			V[Count].x = X1;
			V[Count].y = Y1;
			V[Count + 1].x = X2;
			V[Count + 1].y = Y2;
			line(fvector2d{ V[Count].x, V[Count].y }, fvector2d{ X2, Y2 }, color, 1.f);
		}
	}

	void drawTriangle(fvector2d point1, fvector2d point2, fvector2d point3, flinearcolor color) {
		// Draw lines between the three points to form a triangle
		// Example code: Replace this with your actual drawing/rendering system
		// Draw line from point1 to point2
		line(point1, point2, color, 1.0f);
		// Draw line from point2 to point3
		line(point2, point3, color, 1.0f);
		// Draw line from point3 to point1
		line(point3, point1, color, 1.0f);
	}

	void filledCircle(fvector2d position, int radius, int segments, flinearcolor color, float alpha) {
		float PI = 3.1415927f;

		float Step = PI * 2.0 / segments;
		int Count = 0;
		fvector2d V[128];
		for (float a = 0; a < PI * 2.0; a += Step) {
			float X1 = radius * defines::math->cos(a) + position.x;
			float Y1 = radius * defines::math->sin(a) + position.y;
			float X2 = radius * defines::math->cos(a + Step) + position.x;
			float Y2 = radius * defines::math->sin(a + Step) + position.y;
			V[Count].x = X1;
			V[Count].y = Y1;
			V[Count + 1].x = X2;
			V[Count + 1].y = Y2;
			line(fvector2d{ V[Count].x, V[Count].y }, fvector2d{ X2, Y2 }, color, 1.f);
		}
	}

	void filled_box(fvector2d position, fvector2d size, flinearcolor render_color) {
		for (int i = 0; i < size.y; i++) {
			canvas->k2_draw_line(fvector2d(position.x, position.y + i), fvector2d(position.x + size.x, position.y + i), 1.f, render_color);
		}
	}

	void box(fvector2d position, fvector2d size, flinearcolor render_color, float thickness)
	{
		render::line(fvector2d(position.x, position.y), fvector2d(position.x + size.x, position.y), render_color, thickness);
		render::line(fvector2d(position.x + size.x, position.y), fvector2d(position.x + size.x, position.y + size.y), render_color, thickness);
		render::line(fvector2d(position.x + size.x, position.y + size.y), fvector2d(position.x, position.y + size.y), render_color, thickness);
		render::line(fvector2d(position.x, position.y + size.y), fvector2d(position.x, position.y), render_color, thickness);
	}

	void mouse_cursor() {
		auto cursor = render::controller->get_mouse_position();
		filled_box(fvector2d(cursor.x - 2.5, cursor.y - 2.5), fvector2d(5, 5), flinearcolor(0.f, 0.f, 0.f, 1.f));
	}

	class menu_column {
	public:
		bool is_collapsed() {
			SPOOF_FUNC;
			return this->collapsed;
		}

		bool in_area(fvector2d pos, fvector2d size) {
			SPOOF_FUNC;
			if (this->cursor_pos.x > pos.x && this->cursor_pos.y > pos.y)
				if (this->cursor_pos.x < pos.x + size.x && this->cursor_pos.y < pos.y + size.y)
					return true;

			return false;
		}

		void checkbox(fstring text, bool* option) {
			fvector2d current = menu_pos + menu_offset;
			fvector2d size = fvector2d(this->menu_size.x - (this->wide_offset * 2), 35);

			bool hovered = in_area(current, size);
			bool down = hovered && this->mouse_down;
			bool clicked = hovered && this->mouse_clicked;

			flinearcolor render_color = flinearcolor();
			if (*option)
				render_color = flinearcolor(0.2f, 0.075f, 0.175f, 1.f);

			if (render_color)
				render::filled_box(current, size, render_color);

			render::text(text.c_str(), fvector2d(current.x + size.x / 2, current.y + 9), flinearcolor(1.f, 1.f, 1.f, 1.f), true, false, false);

			if (clicked) *option = !*option;

			this->menu_offset.y += 35;
		}

		void slider(fstring text, double min, double max, double* value) {
			fvector2d current = menu_pos + menu_offset;
			fvector2d size = fvector2d(this->menu_size.x - (this->wide_offset * 2), 35);

			bool hovered = in_area(current, size);
			bool down = hovered && this->mouse_down;

			if (hovered && down) {
				*value = ((this->cursor_pos.x - current.x) * ((max - min) / size.x)) + min;
				*value = defines::math->round(*value);
				if (*value < min) *value = min;
				if (*value > max) *value = max;
			}

			flinearcolor render_color = flinearcolor(0.2f, 0.075f, 0.175f, 1.f);
			double oneP = size.x / (max - min);
			render::filled_box(current, fvector2d(oneP * (*value - min), size.y), render_color);

			fstring end_text = defines::string->build_string_double(text.c_str(), L"", *value, L"");
			render::text(end_text.c_str(), fvector2d(current.x + size.x / 2, current.y + 9), flinearcolor(1.f, 1.f, 1.f, 1.f), true, false, false);

			this->menu_offset.y += 35;
		}

		bool invisible_button(fvector2d size, bool* hovered) {
			SPOOF_FUNC;
			fvector2d current = menu_pos + menu_offset;

			*hovered = in_area(current, size);
			bool clicked = *hovered && this->mouse_clicked;

			return clicked;
		}

		bool invisible_r_button(fvector2d size, bool* hovered) {
			SPOOF_FUNC;
			fvector2d current = menu_pos + menu_offset;

			*hovered = in_area(current, size);
			bool clicked = *hovered && this->mouse_rmb_clicked;

			return clicked;
		}

		void handle_input() {
			this->cursor_pos = render::controller->get_mouse_position();

			this->mouse_rmb_down = render::controller->is_key_down(defines::right_mouse_button);
			if (this->mouse_rmb_down) {
				if (this->mouse_rmb_down_already)
					this->mouse_rmb_clicked = false;
				else {
					this->mouse_rmb_clicked = true;
					this->mouse_rmb_down_already = true;
				}
			}
			else {
				this->mouse_rmb_clicked = false;
				this->mouse_rmb_down_already = false;
			}

			this->mouse_down = render::controller->is_key_down(defines::left_mouse_button);
			if (this->mouse_down) {
				if (this->mouse_down_already)
					this->mouse_clicked = false;
				else {
					this->mouse_clicked = true;
					this->mouse_down_already = true;
				}
			}
			else {
				this->mouse_clicked = false;
				this->mouse_down_already = false;
			}
		}

		bool begin(fstring title, fvector2d pos, fvector2d size, flinearcolor header_color) {
			if (!this->once) {
				this->menu_pos = pos;
				this->menu_size = size;

				this->wide_offset = 8;

				this->header_color = header_color;

				this->collapsed = true;
				this->once = true;
			}

			//todo: set world
			this->world_delta_time = defines::game_statics->get_world_delta_seconds(render::world);

			this->menu_offset = fvector2d();

			this->handle_input();

			bool header_hovered = false;
			bool header_clicked = invisible_r_button(fvector2d(this->menu_size.x, 40), &header_hovered);
			if (header_clicked) this->collapsed = !this->collapsed;

			//fix menu moving
			if (header_hovered) {
				render::hovered_headers += 1;
			}

			//menu moving
			{
				static fvector2d static_cursor = fvector2d();
				static fvector2d static_calculated = fvector2d();

				if (render::hovered_headers == 1 && header_hovered && this->mouse_down) {
					if (!static_cursor)
						static_cursor = this->cursor_pos;

					if (!static_calculated)
						static_calculated = static_cursor - this->menu_pos;

					this->menu_pos = this->cursor_pos - static_calculated;
				}

				if (!this->mouse_down) {
					static_cursor = fvector2d();
					static_calculated = fvector2d();
				}
			}

			//header rendering
			{
				flinearcolor header_color = flinearcolor(0.025f, 0.025f, 0.025f, 1.f);
				if (!this->collapsed)
					header_color = this->header_color;

				render::filled_box(this->menu_pos, fvector2d(this->menu_size.x, 40), header_color);
				render::text(title.c_str(), fvector2d(this->menu_pos.x + (this->menu_size.x / 2), this->menu_pos.y + 12), flinearcolor(0.9f, 0.9f, 0.9f, 0.9f), true, false, false);
			}

			//background rendering
			if (!this->collapsed) {
				flinearcolor background_color = flinearcolor(0.025f, 0.025f, 0.025f, 1.f);
				render::filled_box(fvector2d(this->menu_pos.x + this->wide_offset, this->menu_pos.y + 40), fvector2d(this->menu_size.x - (this->wide_offset * 2), this->menu_size.y), background_color);

				this->menu_offset = fvector2d(this->wide_offset, 40);
			}
			SPOOF_FUNC;
			return true;
		}

		bool end() {
			SPOOF_FUNC;
			return true;
		}
	private:
		float world_delta_time;

		double wide_offset;

		bool anim_opening;
		bool anim_closing;

		bool once;
		bool collapsed;

		bool mouse_rmb_clicked;
		bool mouse_rmb_down;
		bool mouse_rmb_down_already;

		bool mouse_clicked;
		bool mouse_down;
		bool mouse_down_already;

		fvector2d cursor_pos;
		fvector2d menu_pos;
		fvector2d menu_size;
		fvector2d menu_offset;
		double real_menu_size_y;

		flinearcolor header_color;
	};
}


#pragma once

namespace vantax
{
	namespace menu
	{
		namespace menu_class
		{
			int total_open_popups = 0;

			namespace color
			{
				float add(float current, float white)
				{
					current += white;

					if (current >= 255.f) return 255.f;

					return current;
				}
			}

			class gui
			{
			public:
				void init()
				{
					this->background_color = flinearcolor(0.01f, 0.01f, 0.01f, 1.f);
					this->main_color = flinearcolor(0.f, 1.f, 1.f, 1.f);
					this->frame_color = flinearcolor(0.03f, 0.03f, 0.03f, 1.f);
					this->frame_hovered_color = flinearcolor(0.04f, 0.04f, 0.04f, 1.f);
					this->frame_pressed_color = flinearcolor(0.05f, 0.05f, 0.05f, 1.f);
					this->text_color = flinearcolor(1.f, 1.f, 1.f, 1.f);

					this->position = position;
					this->size = size;

					this->item_spacing = 11;
				}

				bool is_hovered(fvector2d pos, fvector2d size)
				{
					if (this->cursor.x > pos.x && this->cursor.y > pos.y)
						if (this->cursor.x < pos.x + size.x && this->cursor.y < pos.y + size.y)
							return true;

					return false;
				}

				void combo(wchar_t* text, bool* active, int* value, wchar_t* arg[], int num_args)
				{
					fvector2d current = this->position + this->offset;
					fvector2d size = fvector2d(100, 20);

					bool any_hovered = false;
					bool hovered = is_hovered(current, size);
					bool clicked = left_mouse_clicked && hovered;

					if (clicked)
					{
						if (*active)
						{
							*active = false;
						}
						else if (!total_open_popups)
						{
							*active = true;
						}
					}

					if (hovered && !any_hovered)
						any_hovered = true;

					render::filled_box(current, size, this->frame_color);
					render::box(current, size, flinearcolor(0.f, 0.f, 0.f, 1.f), 1.f);

					render::text(arg[*value], fvector2d(current.x + (size.x / 2), current.y + 2), this->text_color, true, false, false);
					render::text(text, fvector2d(current.x + size.x + 5, current.y + 1), this->text_color, false, false, false);

					if (*active)
					{
						total_open_popups += 1;

						int differ = 6;
						current.x += differ;
						size.x -= differ * 2;
						current.y += 1;

						for (int i = 0; i < num_args; i++)
						{
							current.y += size.y;

							flinearcolor color = this->frame_color;

							bool item_hovered = is_hovered(current, size);
							bool item_clicked = left_mouse_clicked && item_hovered;
							bool item_down = left_mouse_down && item_hovered;

							if (item_hovered && !any_hovered)
								any_hovered = true;

							if (item_clicked)
							{
								Sleep(30);
								*value = i;
							}

							if (item_hovered)
							{
								color = this->frame_hovered_color;
							}
							else if (*value == i)
							{
								color = this->frame_pressed_color;
							}

							render::filled_box(current, size, color);

							render::text(arg[i], fvector2d(current.x + (size.x / 2), current.y + 2), this->text_color, true, false, false);
						}
					}

					bool clicked_somewhere_else = !any_hovered && left_mouse_clicked;

					if (clicked_somewhere_else && *active)
						*active = false;

					this->offset.y += size.y + this->item_spacing - 1;
				}

				void checkbox(wchar_t* text, bool* option)
				{
					fvector2d current = this->position + this->offset;
					fvector2d size = fvector2d(8, 8);
					flinearcolor draw_color = flinearcolor();

					bool hovered = is_hovered(current, fvector2d(size.x + 80, size.y));
					bool clicked = left_mouse_clicked && hovered;

					if (*option)
						draw_color = this->main_color;
					else if (hovered)
						draw_color = this->frame_hovered_color;
					else
						draw_color = this->frame_color;

					if (clicked && !total_open_popups)
						*option = !*option;

					render::filled_box(current, size, draw_color);
					render::box(current, size, flinearcolor(0.f, 0.f, 0.f, 1.f), 1.f);

					render::text(text, fvector2d(current.x + size.x + 4, current.y + (size.y / 2) - 2), this->text_color, false, true, false);

					this->offset.y += size.y + this->item_spacing + 1;
				}

				void color_picker(wchar_t* text, flinearcolor* color, bool* active)
				{
					fvector2d current = this->position + this->offset;
					fvector2d size = fvector2d(8, 8);

					bool hovered = is_hovered(current, fvector2d(size.x + 80, size.y));
					bool big_hovered = hovered || (*active && is_hovered(current, fvector2d(160, 115)));
					bool clicked = left_mouse_clicked && hovered;
					bool any_other_clicked = left_mouse_clicked && !big_hovered;

					render::filled_box(current, size, *color);
					render::box(current, size, flinearcolor(0.f, 0.f, 0.f, 1.f), 1.f);
					render::text(text, fvector2d(current.x + size.x + 4, current.y + (size.y / 2) - 2), this->text_color, false, true, false);

					if (clicked)
					{
						if (*active)
						{
							*active = false;
						}
						else if (!total_open_popups)
						{
							*active = true;
						}
					}

					if (any_other_clicked && *active)
						*active = false;

					//picker
					if (*active)
					{
						total_open_popups += 1;

						current = fvector2d(current.x + size.x, current.y + size.y);
						double current_x_backup = current.x;

						//up/down (white)
						for (float c = 0; c < 10.f; c++)
						{
							float c_percentage = c / 10.f;

							float c_hx = 200.f * c_percentage;

							//red to green
							for (float i = 0; i < 5.f; i++)
							{
								float percentage = i / 5.f;

								float hx = 255.f * percentage;

								float red = 255.f - hx;
								float green = 255.f - red;
								float blue = 0.f;

								red = color::add(red, c_hx);
								green = color::add(green, c_hx);
								blue = color::add(blue, c_hx);

								flinearcolor converted_color = flinearcolor(red / 255.f, green / 255.f, blue / 255.f, 1.f);

								bool this_color_hovered = is_hovered(current, fvector2d(10, 10));
								bool this_color_clicked = left_mouse_clicked && this_color_hovered;

								if (this_color_clicked)
								{
									*color = converted_color;
									*active = false;
								}

								render::filled_box(current, fvector2d(10, 10), converted_color);
								current.x += 10;
							}

							//green to blue
							for (float i = 0; i < 5.f; i++)
							{
								float percentage = i / 5.f;

								float hx = 255.f * percentage;

								float red = 0.f;
								float green = 255.f - hx;
								float blue = 255.f - green;

								red = color::add(red, c_hx);
								green = color::add(green, c_hx);
								blue = color::add(blue, c_hx);

								flinearcolor converted_color = flinearcolor(red / 255.f, green / 255.f, blue / 255.f, 1.f);

								bool this_color_hovered = is_hovered(current, fvector2d(10, 10));
								bool this_color_clicked = left_mouse_clicked && this_color_hovered;

								if (this_color_clicked)
								{
									*color = converted_color;
									*active = false;
								}

								render::filled_box(current, fvector2d(10, 10), converted_color);
								current.x += 10;
							}

							//blue to red
							for (float i = 0; i < 5.f; i++)
							{
								float percentage = i / 5.f;

								float hx = 255.f * percentage;

								float green = 0.f;
								float blue = 255.f - hx;
								float red = 255.f - blue;

								red = color::add(red, c_hx);
								green = color::add(green, c_hx);
								blue = color::add(blue, c_hx);

								flinearcolor converted_color = flinearcolor(red / 255.f, green / 255.f, blue / 255.f, 1.f);

								bool this_color_hovered = is_hovered(current, fvector2d(10, 10));
								bool this_color_clicked = left_mouse_clicked && this_color_hovered;

								if (this_color_clicked)
								{
									*color = converted_color;
									*active = false;
								}

								render::filled_box(current, fvector2d(10, 10), converted_color);
								current.x += 10;
							}

							current.x = current_x_backup;
							current.y += 10;
						}

						current.x = current_x_backup;

						//white to black
						for (float i = 0; i < 15.f; i++)
						{
							float percentage = i / 15.f;

							float hx = 255.f * percentage;

							float green = 255.f - hx;
							float blue = 255.f - hx;
							float red = 255.f - hx;

							flinearcolor converted_color = flinearcolor(red / 255.f, green / 255.f, blue / 255.f, 1.f);

							bool this_color_hovered = is_hovered(current, fvector2d(10, 10));
							bool this_color_clicked = left_mouse_clicked && this_color_hovered;

							if (this_color_clicked)
							{
								*color = converted_color;
								*active = false;
							}

							render::filled_box(current, fvector2d(10, 10), converted_color);
							current.x += 10;
						}
					}

					this->offset.y += size.y + this->item_spacing + 1;
				}

				void slider(wchar_t* text, double min, double max, double* value)
				{
					fvector2d current = this->position + this->offset;
					fvector2d size = fvector2d(100, 7);
					flinearcolor draw_color = flinearcolor();

					auto converted_text = defines::string->build_string_double(text, fstring(Encrypt(L" (")), *value, fstring(Encrypt(L")")));
					render::text(converted_text.c_str(), fvector2d(current.x + size.x + 5, current.y + 1), this->text_color, false, true, false);

					bool hovered = is_hovered(fvector2d(current.x, current.y - 1), fvector2d(size.x, size.y + 2));
					bool down = left_mouse_down && hovered;

					if (hovered && down && !total_open_popups) {
						*value = ((this->cursor.x - current.x) * ((max - min) / size.x)) + min;
						*value = static_cast<int>(*value);
						if (*value < min) *value = min;
						if (*value > max) *value = max;
					}

					if (hovered)
						draw_color = this->frame_hovered_color;
					else if (down)
						draw_color = this->frame_pressed_color;
					else
						draw_color = this->frame_color;

					render::filled_box(fvector2d(current.x, current.y + 1), fvector2d(size.x, size.y - 2), draw_color);
					render::box(fvector2d(current.x, current.y + 1), fvector2d(size.x, size.y - 2), flinearcolor(0.f, 0.f, 0.f, 1.f), 1.f);

					double percent = size.x / (max - min);
					double point_differ = 2;

					fvector2d point = fvector2d(percent * (*value - min), size.y);
					render::filled_box(fvector2d(current.x + point.x - 2, current.y - point_differ + 1), fvector2d(2, size.y + (point_differ * 2)), this->main_color);

					this->offset.y += size.y + this->item_spacing + 6;
				}

				bool button(wchar_t* text, bool active)
				{
					fvector2d current = this->position + this->offset;
					fvector2d size = fvector2d(100, 30);
					flinearcolor draw_color = flinearcolor();

					bool hovered = is_hovered(current, size);
					bool clicked = left_mouse_clicked && hovered;

					if (active)
						draw_color = this->main_color;
					else if (hovered)
						draw_color = this->frame_hovered_color;
					else
						draw_color = this->frame_color;

					render::filled_box(current, fvector2d(4, size.y), draw_color);

					render::box(current, fvector2d(4, size.y), flinearcolor(0.f, 0.f, 0.f, 1.f), 1.f);

					render::text(text, fvector2d(current.x + 9, current.y + (size.y / 2) - 1), this->text_color, false, true, false);

					this->offset.y += size.y + 9;

					return clicked;
				}

				bool button_2(wchar_t* text)
				{
					fvector2d current = this->position + this->offset;
					fvector2d size = fvector2d(120, 20);

					bool hovered = is_hovered(current, size);
					bool clicked = left_mouse_clicked && hovered;

					render::filled_box(current, size, this->frame_color);
					render::box(current, size, flinearcolor(0.f, 0.f, 0.f, 1.f), 1.f);

					render::text(text, fvector2d(current.x + (size.x / 2), current.y + 2), this->text_color, true, false, false);

					this->offset.y += size.y + 9;

					return clicked;
				}

				void text(wchar_t* text)
				{
					fvector2d current = this->position + this->offset;

					render::text(text, fvector2d(current.x - 1, current.y - 4), this->text_color, false, false, false);

					this->offset.y += 6 + this->item_spacing;
				}

				void space(double x, double y)
				{
					this->offset += fvector2d(x, y);
				}

				void set_x(double value)
				{
					this->offset.x = value;
				}

				void set_y(double value)
				{
					this->offset.y = value;
				}

				bool begin(wchar_t* title, fvector2d start_position, fvector2d size)
				{
					if (!this->initialized)
					{
						this->init();
						this->position = start_position;
						this->size = size;

						this->initialized = true;
					}

					total_open_popups = 0;

					bool insert_down = render::controller->is_key_down(defines::insert);

					this->cursor = render::controller->get_mouse_position();
					this->left_mouse_clicked = render::controller->is_key_down(defines::left_mouse_button);
					this->left_mouse_down = render::controller->is_key_down(defines::left_mouse_button);;
					this->right_mouse_clicked = render::controller->is_key_down(defines::right_mouse_button);
					this->right_mouse_down = render::controller->is_key_down(defines::right_mouse_button);
					this->offset = fvector2d(10, 20);

					static fvector2d static_cursor = fvector2d();
					static fvector2d static_calculated = fvector2d();

					if (this->is_hovered(this->position, fvector2d(this->size.x, 20)) && left_mouse_down)
					{
						if (!static_cursor)
						{
							static_cursor = this->cursor;
						}

						if (!static_calculated)
						{
							static_calculated = static_cursor - this->position;
						}
					}

					if (static_cursor && static_calculated)
					{
						this->position = this->cursor - static_calculated;
					}

					if (!this->left_mouse_down)
					{
						static_cursor = fvector2d();
						static_calculated = fvector2d();
					}

					render::filled_box(this->position, this->size, this->background_color);
					render::box(this->position, this->size, flinearcolor(0.f, 0.f, 0.f, 1.f), 1.f);

					fvector2d loc = fvector2d(this->position.x + this->size.x - 55, this->position.y + 5);
					render::text(title, loc, this->text_color, false, false, false);

					return true;
				}
				bool end()
				{
					render::filled_box(fvector2d(this->cursor.x - 4, this->cursor.y - 4), fvector2d(4, 4), this->text_color);

					return true;
				}
			private:
				bool initialized, left_mouse_clicked, right_mouse_clicked, left_mouse_down, right_mouse_down;
				double item_spacing;
				fvector2d position, size, offset, cursor, screen_center;
				flinearcolor background_color, main_color, frame_color, frame_hovered_color, frame_pressed_color, text_color;
			};
		}
	}
}
