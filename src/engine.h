#pragma once
#include <vector>

namespace cgl
{
	class engine
	{
	public:
		engine(const int, const int);
		void make_step();
		void set_state_status(const int, const int, bool);
		bool get_state_status(const int, const int) const;

	private:
		void check_neighbors(const int, const int);

		const int neighbors_position_[8][2] = { { -1, -1 }, { -1, 0 }, { -1, 1 }, { 0, -1 }, { 0, 1 }, { 1, -1 }, { 1, 0 }, { 1, 1 } };

		std::vector<std::vector<bool>> current_state_;
		std::vector<std::vector<bool>> next_state_;
	};
}

