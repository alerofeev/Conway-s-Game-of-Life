#include "game_controller.hpp"

cr::game_controller::game_controller(sf::RenderWindow& window, const int rows, const int columns)
	: delay_(std::chrono::milliseconds(400)), engine_(engine(rows, columns)), window_(window), rows_(rows), columns_(columns)
{
	load_font("back_to_1982", "backto1982");
	load_font("roboto_regular", "roboto-regular");

	start_game_button_ = ui::button("Start Game", fonts_.find("roboto_regular")->second, 18, 2.8f, sf::Vector2f(273.f, 50.f), 984.f, 130.f);
	clear_field_button_ = ui::button("Clear Field", fonts_.find("roboto_regular")->second, 18, 2.8f, sf::Vector2f(273.f, 50.f), 984.f, 200.f);
	exit_button_ = ui::button("Exit", fonts_.find("roboto_regular")->second, 18, 2.8f, sf::Vector2f(273.f, 50.f), 984.f, 270.f);

	for (int i = 0; i < 3; i++)
	{
		speed_buttons_.emplace_back(ui::button("x" + std::to_string(i + 1), fonts_.find("roboto_regular")->second, 14, 4.f,
			sf::Vector2f(53.f, 23.f), 100.f + 73.f * static_cast<float>(i), 36.f));
	}

	speed_buttons_[0].set_hovered_state();

	game_logo_text_.setFillColor(sf::Color(204, 204, 204));
	game_logo_text_.setFont(fonts_.find("back_to_1982")->second);
	game_logo_text_.setString("   Conway's\nGame of Life");
	game_logo_text_.setCharacterSize(28);
	game_logo_text_.setLineSpacing(1.2f);
	game_logo_text_.setPosition(984, 36);

	generation_label_.setFillColor(sf::Color(204, 204, 204));
	generation_label_.setFont(fonts_.find("roboto_regular")->second);
	generation_label_.setString("Generation:");
	generation_label_.setCharacterSize(18);
	generation_label_.setPosition(329, 36);

	generation_number_.setFillColor(sf::Color(50, 168, 82));
	generation_number_.setFont(fonts_.find("roboto_regular")->second);
	generation_number_.setString("0");
	generation_number_.setCharacterSize(18);
	generation_number_.setPosition(427, 36);

	speed_picker_label_.setFillColor(sf::Color(204, 204, 204));
	speed_picker_label_.setFont(fonts_.find("roboto_regular")->second);
	speed_picker_label_.setString("Speed:");
	speed_picker_label_.setCharacterSize(18);
	speed_picker_label_.setPosition(36, 36);

	for (int i = 0; i < rows_; i++)
	{
		std::vector<ui::cell> temp;
		temp.reserve(columns_);
		for (int j = 0; j < columns_; j++)
		{
			temp.emplace_back();
		}
		cells_.push_back(temp);
	}
}

void cr::game_controller::start()
{
	bool is_game_started = false;
	while (window_.isOpen())
	{
		sf::Event event{};
		while (window_.pollEvent(event))
		{
			switch (event.type)
			{
				case sf::Event::Closed:
				{
					window_.close();
					break;
				}
				case sf::Event::MouseButtonPressed:
				{
					if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
					{
						if (start_game_button_.is_mouse_over(sf::Mouse::getPosition(window_)))
						{
							is_game_started ? is_game_started = false : is_game_started = true;
							is_game_started ? start_game_button_.set_label("Stop Game") : start_game_button_.set_label("Continue Game");
							break;
						}

						if (clear_field_button_.is_mouse_over(sf::Mouse::getPosition(window_)))
						{
							is_game_started = false;
							engine_.clear_state();
							generation_number_.setString("0");
							start_game_button_.set_label("Start Game");
							break;
						}

						if (exit_button_.is_mouse_over(sf::Mouse::getPosition(window_)))
						{
							window_.close();
							break;
						}

						if (speed_buttons_[0].is_mouse_over(sf::Mouse::getPosition(window_)))
						{
							speed_buttons_[0].set_hovered_state();
							speed_buttons_[1].set_normal_state();
							speed_buttons_[2].set_normal_state();
							delay_ = std::chrono::milliseconds(400);
							break;
						}

						if (speed_buttons_[1].is_mouse_over(sf::Mouse::getPosition(window_)))
						{
							speed_buttons_[0].set_normal_state();
							speed_buttons_[1].set_hovered_state();
							speed_buttons_[2].set_normal_state();
							delay_ = std::chrono::milliseconds(200);
							break;
						}

						if (speed_buttons_[2].is_mouse_over(sf::Mouse::getPosition(window_)))
						{
							speed_buttons_[0].set_normal_state();
							speed_buttons_[1].set_normal_state();
							speed_buttons_[2].set_hovered_state();
							delay_ = std::chrono::milliseconds(100);
							break;
						}

						if (!is_game_started)
						{
							for (int i = 0; i < rows_; i++)
							{
								for (int j = 0; j < columns_; j++)
								{
									if (cells_[i][j].is_mouse_over(window_))
									{
										engine_.set_state_status(i, j, true);
									}
								}
							}
						}
					}
					break;
				}
				default:
					break;
			}
		}

		setup_window();

		draw_grid(is_game_started);

		window_.display();
	}
}

void cr::game_controller::draw_grid(bool is_game_started)
{
	for (int i = 0; i < rows_; i++)
	{
		for (int j = 0; j < columns_; j++)
		{
			cells_[i][j].set_status(engine_.get_state_status(i, j));
			cells_[i][j].draw(window_, static_cast<float>(36 + j * 24), static_cast<float>(72 + i * 24));
		}
	}

	sf::RectangleShape vertical_line(sf::Vector2f(2.f, 602.f));
	vertical_line.setFillColor(sf::Color(204, 204, 204));
	for (auto i = 0; i <= 38; i++)
	{
		vertical_line.setPosition(static_cast<float>(36 + i * 24), 72);
		window_.draw(vertical_line);
	}

	sf::RectangleShape horizontal_line(sf::Vector2f(914.f, 2.f));
	horizontal_line.setFillColor(sf::Color(204, 204, 204));
	for (auto i = 0; i <= 25; i++)
	{
		horizontal_line.setPosition(36, static_cast<float>(72 + i * 24));
		window_.draw(horizontal_line);
	}

	if (is_game_started)
	{
		std::thread engine_thread([this]()
		{
			engine_.make_step();
			generation_number_.setString(std::to_string(engine_.get_step_count()));
			std::this_thread::sleep_for(std::chrono::milliseconds(delay_));
		});
		engine_thread.join();
	}
}


void cr::game_controller::load_font(const std::string& key, const std::string& font_name)
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

void cr::game_controller::setup_window()
{
	start_game_button_.set_normal_state();
	start_game_button_.update(sf::Mouse::getPosition(window_));

	clear_field_button_.set_normal_state();
	clear_field_button_.update(sf::Mouse::getPosition(window_));

	exit_button_.set_normal_state();
	exit_button_.update(sf::Mouse::getPosition(window_));

	window_.clear(BACKGROUND_COLOR);

	start_game_button_.draw(window_);
	clear_field_button_.draw(window_);
	exit_button_.draw(window_);

	for(int i = 0; i < 3; i++)
	{
		speed_buttons_[i].draw(window_);
	}

	window_.draw(game_logo_text_);
	window_.draw(speed_picker_label_);

	window_.draw(generation_label_);
	window_.draw(generation_number_);
}
