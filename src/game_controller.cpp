#include "game_controller.h"

cgl::game_controller::game_controller(sf::RenderWindow& window) : window_(window)
{
	load_font("back_to_1982", "backto1982");
	load_font("roboto_regular", "roboto-regular");

	for (int i = 0; i < 25; i++)
	{
		std::vector<cell> temp;
		temp.reserve(38);
		for (int j = 0; j < 38; j++)
		{
			temp.emplace_back(window_);
		}
		cells_.push_back(temp);
	}
}

void cgl::game_controller::start()
{
	engine_.set_state_status(2, 10, true);
	engine_.set_state_status(3, 11, true);
	engine_.set_state_status(2, 12, true);
	engine_.set_state_status(3, 12, true);
	engine_.set_state_status(1, 11, true);

	engine_.set_state_status(4, 15, true);
	engine_.set_state_status(4, 16, true);
	engine_.set_state_status(4, 17, true);

	engine_.set_state_status(6, 2, true);
	engine_.set_state_status(6, 3, true);
	engine_.set_state_status(6, 4, true);
	engine_.set_state_status(5, 4, true);
	engine_.set_state_status(4, 3, true);

	while (window_.isOpen())
	{
		sf::Event event{};
		while (window_.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window_.close();
			}
		}
		setup_window();

		draw_grid();

		window_.display();
	}
}


void cgl::game_controller::draw_grid()
{
	for (int i = 0; i < cells_.size(); i++)
	{
		for (int j = 0; j < cells_[i].size(); j++)
		{
			cells_[i][j].set_status(engine_.get_state_status(i, j));
			cells_[i][j].draw(static_cast<float>(36 + j * 24), static_cast<float>(36 + i * 24));
		}
	}

	sf::RectangleShape vertical_line(sf::Vector2f(2.f, 602.f));
	vertical_line.setFillColor(sf::Color(204, 204, 204));
	for (auto i = 0; i <= 38; i++)
	{
		vertical_line.setPosition(static_cast<float>(36 + i * 24), 36);
		window_.draw(vertical_line);
	}

	sf::RectangleShape horizontal_line(sf::Vector2f(914.f, 2.f));
	horizontal_line.setFillColor(sf::Color(204, 204, 204));
	for (auto i = 0; i <= 25; i++)
	{
		horizontal_line.setPosition(36, static_cast<float>(36 + i * 24));
		window_.draw(horizontal_line);
	}

	std::thread engine_thread([this]()
	{
		engine_.make_step();
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
	});
	engine_thread.join();
}


void cgl::game_controller::load_font(const std::string& key, const std::string& font_name)
{
	sf::Font font;
	if (font.loadFromFile("fonts/" + font_name + ".ttf"))
	{
		fonts_.insert(std::pair<std::string, sf::Font>(key, font));
	}
	else
	{
		std::cout << "Can't load font \"" + font_name + ".ttf\"" << std::endl;
	}
}

void cgl::game_controller::setup_window() const
{
	window_.clear(BACKGROUND_COLOR);

	sf::Text game_logo;
	game_logo.setFillColor(sf::Color(204, 204, 204));
	game_logo.setFont(fonts_.find("back_to_1982")->second);
	game_logo.setString("   Conway's\nGame of Life");
	game_logo.setCharacterSize(28);
	game_logo.setLineSpacing(1.2f);
	game_logo.setPosition(980, 35);
	window_.draw(game_logo);
}
