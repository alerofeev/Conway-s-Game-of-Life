#include "button.h"

ui::button::button(const std::string& label)
{
	container_.setSize(sf::Vector2f(100.f, 35.f));
	container_.setPosition(36.f, 36.f);
	container_.setFillColor(sf::Color::Transparent);
	container_.setOutlineColor(sf::Color(204, 204, 204));
	container_.setOutlineThickness(2.f);

	label_.setString(label);

	label_.setCharacterSize(10);
	set_label_position();
}

void ui::button::draw_button(sf::RenderWindow& window)
{
	/*
	sf::RectangleShape second_outline(sf::Vector2f(container_.getSize().x + 8, container_.getSize().y + 8));
	second_outline.setPosition(container_.getPosition().x - 4, container_.getPosition().y - 4);
	second_outline.setFillColor(sf::Color::Transparent);
	second_outline.setOutlineColor(sf::Color(204, 204, 204));
	second_outline.setOutlineThickness(2.f);
	window.draw(second_outline);
	*/

	window.draw(label_);
	window.draw(container_);
}


void ui::button::set_position(const float x_position, const float y_position)
{ 
	container_.setPosition(x_position, y_position);
	set_label_position();
}

void ui::button::set_size(const float width, const float height)
{
	container_.setSize(sf::Vector2f(width, height));
	set_label_position();
}


void ui::button::set_color(const unsigned char r, const unsigned char g, const unsigned char b)
{
	container_.setFillColor(sf::Color(r, g, b));
}

void ui::button::set_color(const unsigned char r, const unsigned char g, const unsigned char b, const unsigned char a)
{
	container_.setFillColor(sf::Color(r, g, b, a));
}

void ui::button::set_font(const sf::Font& font)
{
	label_.setFont(font);
	set_label_position();
}

void ui::button::set_font_size(const unsigned int size)
{
	label_.setCharacterSize(size);
	set_label_position();
}

bool ui::button::is_mouse_hover(sf::RenderWindow& window) const
{
	const float mouse_position_x = static_cast<float>(sf::Mouse::getPosition().x),
		mouse_position_y = static_cast<float>(sf::Mouse::getPosition().y),

		container_position_x = container_.getPosition().x,
		container_position_y = container_.getPosition().y,

		container_position_x_width = container_.getPosition().x + container_.getLocalBounds().width,
		container_position_y_height = container_.getPosition().y + container_.getLocalBounds().height;

	if (mouse_position_x < container_position_x_width && mouse_position_x > container_position_x &&
		mouse_position_y < container_position_y_height && mouse_position_y > container_position_y)
	{
		return true;
	}
	return false;
}

void ui::button::set_label_position()
{
	label_.setPosition(container_.getPosition().x + (container_.getSize().x - label_.getGlobalBounds().width) / 2,
		container_.getPosition().y + (container_.getSize().y - label_.getGlobalBounds().height) / 2);
}
