#pragma once
#include <string>

namespace ui
{
	class button
	{
	public:
		button();
		button(std::string);

		void draw_button();

		// void set_style();
		void set_position(const float, const float);

	private:

		std::string title_;

	};
}

