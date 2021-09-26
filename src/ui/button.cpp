#include "button.hpp"

ui::button::button() : state_(state::normal), vertical_divider_(1) { }

ui::button::button(const std::string& title, const sf::Font& font, const int character_size, const float vertical_divider,
                   const sf::Vector2f size, const float x_position, const float y_position) : state_(state::normal), vertical_divider_(vertical_divider)
{
	button_shape_.setSize(size);
	button_shape_.setPosition(x_position, y_position);
	button_shape_.setFillColor(sf::Color::Transparent);
	button_shape_.setOutlineColor(sf::Color(204, 204, 204));
	button_shape_.setOutlineThickness(2.f);

	second_outline_.setSize(sf::Vector2f(size.x + 8, size.y + 8));
	second_outline_.setPosition(x_position - 4, y_position - 4);
	second_outline_.setFillColor(sf::Color::Transparent);
	second_outline_.setOutlineColor(sf::Color::Transparent);
	second_outline_.setOutlineThickness(2.f);

	label_.setString(title);
	label_.setFont(font);
	label_.setCharacterSize(character_size);
	label_.setFillColor(sf::Color(204, 204, 204));
	label_.setPosition(button_shape_.getPosition().x + (button_shape_.getSize().x - label_.getGlobalBounds().width) / 2,
		button_shape_.getPosition().y + (button_shape_.getSize().y - label_.getGlobalBounds().height) / vertical_divider_);
}

void ui::button::set_label(const std::string& title)
{
	label_.setString(title);
	label_.setPosition(button_shape_.getPosition().x + (button_shape_.getSize().x - label_.getGlobalBounds().width) / 2,
		button_shape_.getPosition().y + (button_shape_.getSize().y - label_.getGlobalBounds().height) / vertical_divider_);
}

void ui::button::set_normal_state()
{
	state_ = state::normal;

	second_outline_.setOutlineColor(sf::Color::Transparent);
	second_outline_.setSize(sf::Vector2f(button_shape_.getSize().x + 8, button_shape_.getSize().y + 8));
	second_outline_.setPosition(button_shape_.getPosition().x - 4, button_shape_.getPosition().y - 4);
}

void ui::button::set_hovered_state()
{
	state_ = state::hovered;
	second_outline_.setOutlineColor(sf::Color(204, 204, 204));
}

bool ui::button::is_mouse_over(const sf::Vector2i mouse_position) const
{
	return button_shape_.getGlobalBounds().contains(static_cast<sf::Vector2f>(mouse_position));
}

void ui::button::update(const sf::Vector2i mouse_position)
{
	if (is_mouse_over(mouse_position))
	{
		state_ = state::hovered;
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			state_ = state::pressed;
		}
	}

	switch (state_)
	{
		case state::normal:
		{
			second_outline_.setOutlineColor(sf::Color::Transparent);
			second_outline_.setSize(sf::Vector2f(button_shape_.getSize().x + 8, button_shape_.getSize().y + 8));
			second_outline_.setPosition(button_shape_.getPosition().x - 4, button_shape_.getPosition().y - 4);
			break;
		}
		case state::hovered:
		{
			second_outline_.setOutlineColor(sf::Color(204, 204, 204));
			break;
		}
		case state::pressed:
		{
			second_outline_.setOutlineColor(sf::Color(204, 204, 204));
			second_outline_.setSize(sf::Vector2f(button_shape_.getSize().x + 4, button_shape_.getSize().y + 4));
			second_outline_.setPosition(button_shape_.getPosition().x - 2, button_shape_.getPosition().y - 2);
			break;
		}
		default:
			break;
	}

	state_ = state::normal;
}

void ui::button::draw(sf::RenderTarget& target) const
{
	target.draw(second_outline_);
	target.draw(label_);
	target.draw(button_shape_);
}
