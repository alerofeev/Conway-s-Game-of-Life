#include <iostream>
#include <SFML/Graphics.hpp>
#include "core/game_controller.h"

int main()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	sf::RenderWindow window(sf::VideoMode(1280, 720), "Conway's Game of Life", sf::Style::Close | sf::Style::Titlebar, settings);
	cr::game_controller game(window);
	game.start();

	return EXIT_SUCCESS;
}