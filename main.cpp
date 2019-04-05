#include <iostream>
#include <random>
#include "Sudoku.hpp"

int main()
{
	Sudoku S;
	S.generate();
	S.printSolution();

	return 0;
}