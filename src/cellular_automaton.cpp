#include "cellular_automaton.h"
#include <random>
#include <omp.h>

ca::cellular_automaton::cellular_automaton(const int row_size,
                                           const int column_size,
                                           const int threads_counter)
	: current_state_(
		  std::vector<std::vector<char>>(row_size,
		                                 std::vector<char>(column_size, 0))),
	  next_state_(
		  std::vector<std::vector<char>>(row_size,
		                                 std::vector<char>(column_size, 0))),
	  threads_(threads_counter),
	  part_(static_cast<int>(current_state_.size() / threads_.size()))
{
	omp_set_num_threads(threads_counter);
}

ca::cellular_automaton::cellular_automaton(const ca::cellular_automaton& cellular_automaton)
	: current_state_(cellular_automaton.current_state_),
	  next_state_(cellular_automaton.next_state_),
	  threads_(cellular_automaton.threads_.size()), part_(cellular_automaton.part_)
{ }

void ca::cellular_automaton::make_step()
{
	next_state_ = current_state_;
	for (int i = 0; i < static_cast<int>(current_state_.size()); i++)
	{
		for (int j = 0; j < static_cast<int>(current_state_[0].size()); j++)
		{
			set_cell_state(i, j);
		}
	}
	current_state_ = next_state_;
}

void ca::cellular_automaton::make_step_omp()
{
	next_state_ = current_state_;
	#pragma omp parallel for
	for (int i = 0; i < static_cast<int>(current_state_.size()); i++)
	{
		#pragma omp parallel for
		for (int j = 0; j < static_cast<int>(current_state_[0].size()); j++)
		{
			set_cell_state(i, j);
		}
	}
	current_state_ = next_state_;
}

void ca::cellular_automaton::make_step_threads()
{
	next_state_ = current_state_;
	for (size_t t = 0; t < threads_.size(); t++)
	{
		const int from = static_cast<int>(t) * part_;
		const int to = t == threads_.size() - 1
			               ? static_cast<int>(current_state_.size())
			               : from + part_;
		threads_[t] = std::thread([=]
			{
				for (int i = from; i < to; i++)
				{
					for (int j = 0; j < static_cast<int>(current_state_[0].size()); j++)
					{
						set_cell_state(i, j);
					}
				}
			});
	}
	for (auto& thread : threads_)
	{
		thread.join();
	}
	current_state_ = next_state_;
}

std::vector<std::vector<char>> ca::cellular_automaton::get_current_state()
{
	return current_state_;
}

void ca::cellular_automaton::set_initial_state()
{
	std::random_device device;
	std::mt19937 generator(device());
	const std::uniform_int_distribution<int> distribution(0, 100);
	for (auto& row : current_state_)
	{
		for (size_t i = 0; i < current_state_[0].size(); i++)
		{
			row[i] = distribution(generator) % 2 ? 1 : 0;
		}
	}
}

void ca::cellular_automaton::set_cell_state(const int row, const int column)
{
	int neighbors_counter = 0;
	for (auto& position : neighbors_position_)
	{
		if (current_state_[row + position[0] < 0 ? current_state_.size() - 1 :
			row + position[0] > static_cast<int>(current_state_.size()) - 1 ? 0 : row + position[0]]
			[column + position[1] < 0 ? static_cast<int>(current_state_[0].size()) - 1 :
			column + position[1] > static_cast<int>(current_state_[0].size()) - 1 ? 0 : column + position[1]] == 1)
		{
			neighbors_counter++;
		}
	}
	next_state_[row][column] = current_state_[row][column] == 1 && (neighbors_counter > 3 || neighbors_counter < 2) ? 0 :
		neighbors_counter == 3 ? 1 : current_state_[row][column];
}
