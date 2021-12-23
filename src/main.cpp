#include <iostream>
#include "cellular_automaton.h"

void print_field(ca::cellular_automaton& cellular_automaton)
{
	for (const auto& row : cellular_automaton.get_current_state())
	{
		for (const auto column : row)
		{
			std::cout << (column == 1 ? '#' : '*') << " ";
		}
		std::cout << std::endl;
	}
}

int main()
{
	constexpr int row_size = 20, column_size = 20;

	ca::cellular_automaton cellular_automaton(row_size, column_size, 8);
	cellular_automaton.set_initial_state();

	while (true)
	{
		system("cls");
		print_field(cellular_automaton);
		cellular_automaton.make_step();
		if (getchar() == 'q')
		{
			break;
		}
	}

	return EXIT_SUCCESS;
}

