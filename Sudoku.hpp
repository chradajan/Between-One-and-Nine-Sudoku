#ifndef SUDOKU_H
#define SUDOKU_H

#include <stack>
#include <set>
#include <random>

struct Cell
{
	int row;
	int column;
	int value;
};

class Sudoku
{
private:
	Cell* playGrid[9][9];
	Cell* solutionGrid[9][9];
	int rowSum[9];
	int columnSum[9];

	std::random_device device;
	std::default_random_engine engine{device()};

	const std::set<int> POSSIBLE_VALUES {1,2,3,4,5,6,7,8,9};


public:
	Sudoku();
	void generate();
	void printSolution(); //for testing (remove later)
	~Sudoku();

private:
	bool fillCells(std::stack<Cell*>& cellStack);
	void getNeighborValues(std::set<int>& neighborValues, int row, int column);
};

#endif