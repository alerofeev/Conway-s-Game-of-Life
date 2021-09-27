#pragma once
#include <iostream>
#include <thread>
#include <atomic>
#include <chrono>
#include <vector>
#include <map>
#include <string>
#include <SFML/Graphics.hpp>
#include "../ui/cell.hpp"
#include "../ui/button.hpp"
#include "engine.hpp"

namespace cr
{
	class game_controller
	{
	public:
		game_controller(sf::RenderWindow&, int, int);
		void start();

	private:
		static void initialize_text(sf::Text&, sf::Color, const sf::Font&, const std::string&, int, float, float, float);
		void draw_grid();
		void load_font(const std::string&, const std::string&);
		void change_delay(int, int);
		void setup_window();
		void make_step(const std::atomic<bool>&);

		const sf::Color BACKGROUND_COLOR = sf::Color(38, 38, 38, 0);

		std::atomic<int> delay_;
		int rows_;
		int columns_;
		// std::atomic<engine> engine_;
		engine engine_;

		std::map<std::string, sf::Font> fonts_;
		sf::RenderWindow& window_;
		sf::Text game_logo_text_;
		sf::Text generation_label_;
		sf::Text generation_number_;
		sf::Text speed_picker_label_;

		std::vector<std::vector<ui::cell>> cells_;
		std::vector<ui::button> speed_buttons_;
		ui::button start_game_button_;
		ui::button clear_field_button_;
		ui::button exit_button_;
	};
}
