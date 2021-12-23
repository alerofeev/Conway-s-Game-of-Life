#pragma once
#include <vector>
#include <thread>

namespace ca
{
	class cellular_automaton
	{
	public:
		cellular_automaton(int, int, int);
		cellular_automaton(const cellular_automaton&);

		void make_step();
		void make_step_omp();
		void make_step_threads();

		std::vector<std::vector<char>> get_current_state();
		void set_initial_state();

	private:
		std::vector<std::vector<char>> current_state_;
		std::vector<std::vector<char>> next_state_;
		std::vector<std::vector<char>> neighbors_position_ = {
			{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}
		};
		std::vector<std::thread> threads_;
		const int part_;

		void set_cell_state(int, int);
		
	};
}
