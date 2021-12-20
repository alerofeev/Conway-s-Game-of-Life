#include <algorithm>
#include <iostream>
#include <vector>
#include <thread>
#include <omp.h>

namespace ca
{
	class cellular_automaton
	{
	public:
		cellular_automaton(const int i, const int j)
			: current_state_(std::vector<std::vector<char>>(i, std::vector<char>(j, 0))),
			next_state_(std::vector<std::vector<char>>(i, std::vector<char>(j, 0))) { }

		void make_step()
		{
			next_state_ = current_state_;
			int i = 0, j = 0;
			#pragma omp parallel for private(i)
			for (i = 0; i < current_state_.size(); i++)
			{
				#pragma omp parallel for private(j)
				for (j = 0; j < current_state_[0].size(); j++)
				{
					set_cell_state(i, j);
				}
			}
			current_state_ = next_state_;
		}

		std::vector<std::vector<char>> get_current_state()
		{
			return current_state_;
		}

		void set_cell_state(const int i, const int j, const bool state)
		{
			current_state_[i][j] = state ? 1 : 0;
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
					i + position[0] > static_cast<int>(current_state_.size()) - 1 ? 0 : i + position[0]]
					[j + position[1] < 0 ? static_cast<int>(current_state_[0].size()) - 1 : 
					j + position[1] > static_cast<int>(current_state_[0].size()) - 1 ? 0 : j + position[1]] == 1)
				{
					neighbors_counter++;
				}
			}
			next_state_[i][j] = current_state_[i][j] == 1 && (neighbors_counter > 3 || neighbors_counter < 2) ? 0 :
				neighbors_counter == 3 ? 1 : current_state_[i][j];
		}
	};
}

void print_field(ca::cellular_automaton cellular_automaton)
{
	for (const auto& row : cellular_automaton.get_current_state())
	{
		for (const auto column : row)
		{
			std::cout << (column == 1 ? '#' : '*') << " ";
		}
		std::cout << std::endl;
	}
	getchar();
	system("cls");
}

int main()
{
	constexpr int rows_counter = 10, columns_counter = 10; // размерность игрового поля
	constexpr int steps_counter = 600; // количество итераций

	ca::cellular_automaton cellular_automaton(rows_counter, columns_counter);

	// начальная конфигурация
	/*
	cellular_automaton.set_cell_state(4, 6, true);
	cellular_automaton.set_cell_state(5, 7, true);
	cellular_automaton.set_cell_state(6, 5, true);
	cellular_automaton.set_cell_state(5, 6, true);
	cellular_automaton.set_cell_state(6, 6, true);
	*/

	cellular_automaton.set_cell_state(1, 0, true);
	cellular_automaton.set_cell_state(2, 1, true);
	cellular_automaton.set_cell_state(2, 2, true);
	cellular_automaton.set_cell_state(1, 2, true);
	cellular_automaton.set_cell_state(0, 2, true);


	for (int i = 0; i < steps_counter; i++)
	{
		print_field(cellular_automaton);
		cellular_automaton.make_step();
	}

	return EXIT_SUCCESS;
}

/*
	const auto start = std::chrono::high_resolution_clock::now();
	const auto end = std::chrono::high_resolution_clock::now();
	std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms" << std::endl;
	
		for (const auto& row : cellular_automaton.get_current_state())
		{
			for (const auto column : row)
			{
				std::cout << (column == 1 ? '#' : '*') << " ";
			}
			std::cout << std::endl;
		}
		getchar();
		system("cls");
 */