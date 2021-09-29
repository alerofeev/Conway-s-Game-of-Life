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
		game_controller(sf::RenderWindow&, int, int, int);
		void start();

	private:
		static void initialize_text(sf::Text&, sf::Color, const sf::Font&, const std::string&, int, float, float, float);
		void draw_grid();
		void draw_controls();
		void set_cells_status(char);
		void set_font(const std::string&, const std::string&);
		void set_delay(int, int);
		void make_step(const std::atomic<bool>&);

		const sf::Color BACKGROUND_COLOR = sf::Color(10, 10, 10, 0);
		const sf::Color TEXT_COLOR = sf::Color(204, 204, 204);
		const sf::Color TEXT_COLOR_GREEN = sf::Color(50, 168, 82);

		std::atomic<int> delay_;
		int cell_size_;
		int rows_;
		int columns_;
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
