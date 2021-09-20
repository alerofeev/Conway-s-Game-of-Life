#pragma once
#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include "cell.h"
#include "engine.h"

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

		sf::RenderWindow& window_;
		std::map<std::string, sf::Font> fonts_;
		std::vector<std::vector<cell>> cells_;
		engine engine_ = engine(25, 38);
	};
}
