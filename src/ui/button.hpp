#pragma once
#include <SFML/Graphics.hpp>

namespace ui
{
	class button : public sf::Drawable
	{
	public:
		button();
		button(std::string&, sf::Font&, sf::Vector2f);

		void set_background_color();
		void set_text_color();
		void set_border_color();
		void set_size(sf::Vector2f);
		void set_position(sf::Vector2f);
		void set_text(std::string&);
		void set_font(sf::Font&);

		void update(sf::RenderWindow&, sf::Event&);
		void draw(sf::RenderTarget&, sf::RenderStates&) const;

	private:
		sf::Color color_background_;
		sf::Color color_text_;
		sf::Color color_border_;

		sf::Vector2f size_;
		sf::Vector2f position_;

		sf::Font font_;
		unsigned int font_size_;
	};
}

