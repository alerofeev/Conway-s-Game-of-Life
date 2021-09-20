#pragma once
#include <string>
#include <SFML/Graphics.hpp>

namespace ui
{
	class button
	{
	public:
		button();
		button(const std::string&);

		void draw_button(sf::RenderWindow&);

		// void set_style();
		void set_position(const float, const float);
		void set_size(const float, const float);
		void set_color(const unsigned char, const unsigned char, const unsigned char);
		void set_color(const unsigned char, const unsigned char, const unsigned char, const unsigned char);
		void set_font(const sf::Font&);
		void set_font_size(const unsigned int);
		bool is_mouse_hover(sf::RenderWindow&) const;

	private:
		void set_label_position();

		sf::RectangleShape container_;
		sf::Text label_;
	};
}

