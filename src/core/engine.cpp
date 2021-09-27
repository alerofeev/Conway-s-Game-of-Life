#include "engine.hpp"

cr::engine::engine(const int i, const int j)
	: current_state_(std::vector<std::vector<char>>(i, std::vector<char>(j, 0))),
	next_state_(std::vector<std::vector<char>>(i, std::vector<char>(j, 0)))
{ }

cr::engine::engine(const engine& engine) : current_state_(engine.current_state_),
	next_state_(engine.next_state_)
{ }

void cr::engine::make_step()
{
	next_state_ = current_state_;
	for (size_t i = 0; i < current_state_.size(); i++)
	{
		for (size_t j = 0; j < current_state_[0].size(); j++)
		{
			check_neighbors(static_cast<int>(i), static_cast<int>(j));
		}
	}
	current_state_ = next_state_;
	++step_counter_;
}

void cr::engine::clear_state()
{
	for (size_t i = 0; i < current_state_.size(); i++)
	{
		for (size_t j = 0; j < current_state_[i].size(); j++)
		{
			current_state_[i][j] = 0;
		}
	}
	step_counter_ = 0;
}

void cr::engine::set_state_status(const int i, const int j, const int status)
{
	current_state_[i][j] = status;
}

bool cr::engine::get_state_status(const int i, const int j) const
{
	return current_state_[i][j];
}

int cr::engine::get_step_count() const
{
	return step_counter_;
}

void cr::engine::check_neighbors(const int i, const int j)
{
	int neighbors_counter = 0;
	for (auto& position : neighbors_position_)
	{
		if (current_state_[i + position[0] < 0 ? current_state_.size() - 1 : 
			i + position[0] > static_cast<int>(current_state_.size()) - 1 ? 0 : i + position[0]][j + position[1] < 0 ? static_cast<int>(current_state_[0].size()) - 1 :
			j + position[1] > static_cast<int>(current_state_[0].size()) - 1 ? 0 : j + position[1]] == 1)
		{
			neighbors_counter++;
		}
	}
	next_state_[i][j] = current_state_[i][j] == 1 && (neighbors_counter > 3 || neighbors_counter < 2) ? false : neighbors_counter == 3 ? 1 : next_state_[i][j];
}
