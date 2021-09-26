#include <iostream>
#include <SFML/Graphics.hpp>
#include "core/game_controller.hpp"

int main()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	sf::RenderWindow window(sf::VideoMode(1294, 712), "Conway's Game of Life", sf::Style::Close | sf::Style::Titlebar, settings);
	cr::game_controller game(window, 25, 38);
	game.start();

	return EXIT_SUCCESS;
}