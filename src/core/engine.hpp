#pragma once
#include <atomic>
#include <iostream>
#include <vector>

namespace cr
{
	class engine
	{
	public:
		engine(int, int);
		engine(const engine&);
		void make_step();
		void clear_state();
		void set_state_status(int, int, char);
		bool get_state_status(int, int) const;
		int get_step_count() const;
		bool is_game_over();

	private:
		void check_neighbors(int, int);

		const char neighbors_position_[8][2] = { { -1, -1 }, { -1, 0 }, { -1, 1 }, { 0, -1 }, { 0, 1 }, { 1, -1 }, { 1, 0 }, { 1, 1 } };

		std::vector<std::vector<char>> current_state_;
		std::vector<std::vector<char>> next_state_;
		std::atomic<int> step_counter_ {0};
	};
}
