#pragma once
#include <string>
#include <thread>
#include <chrono>
#include <SFML/Graphics.hpp>

namespace ui
{
	namespace state
	{
		enum
		{
			normal = 0,
			hovered = 1,
			pressed = 2
		};
	}

	class button
	{
	public:
		button();
		button(const std::string&, const sf::Font&, int, float, sf::Vector2f, float, float);

		void set_label(const std::string&);
		void set_normal_state();
		void set_hovered_state();
		bool is_mouse_over(const sf::Vector2i) const;
		void update(const sf::Vector2i);
		void draw(sf::RenderTarget&) const;

	private:
		sf::RectangleShape button_shape_;
		sf::RectangleShape second_outline_;

		sf::Font font_;
		sf::Text label_;

		sf::Uint32 state_;
		float vertical_divider_;
	};
}

