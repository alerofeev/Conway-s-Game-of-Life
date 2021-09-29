#pragma once
#include "SFML/Graphics.hpp"

namespace ui
{
	class cell
	{
	public:
		cell(float);

		void set_status(const bool);
		void draw(sf::RenderWindow&, const float, const float);

		bool is_mouse_over(const sf::RenderWindow&) const;

	private:
		const sf::Color ALIVE_CELL_COLOR = sf::Color(50, 168, 82);
		const sf::Color DEAD_CELL_COLOR = sf::Color(10, 10, 10);

		sf::RectangleShape cell_shape_;
	};
}
