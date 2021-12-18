#include <algorithm>
#include <iostream>
#include <vector>
#include <thread>

namespace cr
{
	class engine
	{
	public:
		engine(const int i, const int j)
			: current_state_(std::vector<std::vector<char>>(i, std::vector<char>(j, 0))),
			next_state_(std::vector<std::vector<char>>(i, std::vector<char>(j, 0))) { }

		void make_step()
		{
			next_state_ = current_state_;
			for (size_t i = 0; i < current_state_.size(); i++)
			{
				for (size_t j = 0; j < current_state_[0].size(); j++)
				{
					set_cell_state(static_cast<int>(i), static_cast<int>(j));
				}
			}
			current_state_ = next_state_;
		}

		std::vector<std::vector<char>> get_current_state()
		{
			return current_state_;
		}

		void set_cell_state(const int i, const int j, const char state)
		{
			current_state_[i][j] = state;
		}

	private:
		std::vector<std::vector<char>> current_state_;
		std::vector<std::vector<char>> next_state_;
		std::vector<std::vector<char>> neighbors_position_ = {
			{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}
		};

		void set_cell_state(const int i, const int j)
		{
			int neighbors_counter = 0;
			for (auto& position : neighbors_position_)
			{
				if (current_state_[i + position[0] < 0 ? current_state_.size() - 1 :
					i + position[0] > static_cast<int>(current_state_.size()) - 1 ? 0 : i + position[0]][j + position[1] < 0 ?
					static_cast<int>(current_state_[0].size()) - 1 : j + position[1] > static_cast<int>(current_state_[0].size()) - 1 ? 0 :
					j + position[1]] == 1)
				{
					neighbors_counter++;
				}
			}
			next_state_[i][j] = current_state_[i][j] == 1 && (neighbors_counter > 3 || neighbors_counter < 2) ? 0 :
				neighbors_counter == 3 ? 1 : current_state_[i][j];
		}
	};
}


int main()
{
	constexpr int rows_counter = 100, columns_counter = 100;
	constexpr int steps_counter = 100;

	cr::engine engine(rows_counter, columns_counter);

	engine.set_cell_state(4, 6, 1);
	engine.set_cell_state(4, 7, 1);
	engine.set_cell_state(5, 5, 1);
	engine.set_cell_state(5, 6, 1);
	engine.set_cell_state(6, 6, 1);
	
	const auto start = std::chrono::high_resolution_clock::now();
	for (int iterator = 0; iterator < steps_counter; iterator++)
	{
		engine.make_step();
	}
	const auto end = std::chrono::high_resolution_clock::now();

	std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms" << std::endl;

	return EXIT_SUCCESS;
}