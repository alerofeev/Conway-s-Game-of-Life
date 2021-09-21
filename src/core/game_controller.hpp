#pragma once
#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include "../ui/cell.hpp"
#include "engine.hpp"

namespace cr
{
	class game_controller
	{
	public:
		game_controller(sf::RenderWindow&);
		void start();

	private:
		void draw_grid();
		void load_font(const std::string&, const std::string&);
		void setup_window() const;

		const sf::Color BACKGROUND_COLOR = sf::Color(38, 38, 38, 0);

		std::vector<std::vector<ui::cell>> cells_;
		std::chrono::milliseconds delay_;
		engine engine_ = engine(25, 38);
		std::map<std::string, sf::Font> fonts_;
		sf::RenderWindow& window_;
	};
}
