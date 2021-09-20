#pragma once
#include "SFML/Graphics.hpp"

namespace ui
{
	class cell
	{
	public:
		cell(sf::RenderWindow&);
		void draw(const float, const float);
		void set_status(bool);
		// void set_editable(bool);
		bool get_status() const;

	private:
		// void onclick_event_listener();

		const sf::Color ALIVE_CELL_COLOR = sf::Color(50, 168, 82);
		const sf::Color DEAD_CELL_COLOR = sf::Color(38, 38, 38);
		// const sf::Color CELL_OUTLINE_COLOR = sf::Color(204, 204, 204);

		sf::RenderWindow& window_;
		sf::RectangleShape cell_shape_ = sf::RectangleShape(sf::Vector2f(24.f, 24.f));
		bool status_ = false; // true - cell is alive, false - cell is dead
		// bool is_editable_ = true;
	};

}

