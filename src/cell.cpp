#include "cell.h"

cgl::cell::cell(sf::RenderWindow& window) : window_(window)
{
	cell_shape_.setFillColor(sf::Color::Transparent);
	// cell_shape_.setOutlineColor(CELL_OUTLINE_COLOR);
	// cell_shape_.setOutlineThickness(1.f);
}

void cgl::cell::draw(const float x_position, const float y_position)
{
	cell_shape_.setPosition(x_position, y_position);
	window_.draw(cell_shape_);
}

void cgl::cell::set_status(const bool status)
{
	status_ = status;
	status ? cell_shape_.setFillColor(ALIVE_CELL_COLOR) : cell_shape_.setFillColor(DEAD_CELL_COLOR);
}

bool cgl::cell::get_status() const
{
	return status_;
}
