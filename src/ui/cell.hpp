#pragma once
#include "SFML/Graphics.hpp"

namespace ui
{
	class cell
	{
	public:
		cell();
		void set_status(const bool);
		void draw(sf::RenderWindow&, const float, const float);

	private:
		const sf::Color ALIVE_CELL_COLOR = sf::Color(50, 168, 82);
		const sf::Color DEAD_CELL_COLOR = sf::Color(38, 38, 38);

		sf::RectangleShape cell_shape_ = sf::RectangleShape(sf::Vector2f(24.f, 24.f));
	};
}

