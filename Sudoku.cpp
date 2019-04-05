#include "Sudoku.hpp"
#include <algorithm>
#include <vector>
#include <iostream> //for testing (remove later)


Sudoku::Sudoku()
{
	for(int i = 0; i < 9; ++i)
		for(int j = 0; j < 9; ++j)
			playGrid[i][j] = new Cell{i,j,0};
}

void Sudoku::generate()
{
	std::stack<Cell*> cellStack;

	for(int i = 0; i < 9; ++i)
		for(int j = 0; j < 9; ++j)
			cellStack.push(playGrid[i][j]);

	fillCells(cellStack);
}

void Sudoku::printSolution()
{
	int cCount = 0;
	int rCount = 0;

	for(int i = 0; i < 9; ++i)
	{
		++rCount;

		for(int j = 0; j < 9; ++j)
		{
			++cCount;
			std::cout << playGrid[i][j]->value << " ";
			if(cCount == 3)
			{
				std::cout << "  ";
				cCount = 0;
			}
			if(j == 8) std::cout << std::endl;
		}

		if(rCount == 3)
		{
			std::cout << std::endl;
			rCount = 0;
		}
	}
}

bool Sudoku::fillCells(std::stack<Cell*>& cellStack)
{
	Cell* cell = cellStack.top();
	cellStack.pop();

	std::set<int> neighborValues;
	std::vector<int> options;
	getNeighborValues(neighborValues, cell->row, cell->column);

	std::set_difference(POSSIBLE_VALUES.begin(), POSSIBLE_VALUES.end(), neighborValues.begin(), neighborValues.end(), inserter(options, options.end()));

	std::shuffle(options.begin(), options.end(), engine);

	for(auto option : options)
	{
		cell->value = option;

		if(cellStack.empty())
			return true;

		if(fillCells(cellStack))
			return true;
	}

	cell->value = 0;
	cellStack.push(cell);
	return false;
}

void Sudoku::getNeighborValues(std::set<int>& neighborValues, int row, int column)
{
	for(int i = 0; i < 9; i++)
	{
		if (playGrid[row][i]->value != 0)
			neighborValues.insert(playGrid[row][i]->value);
		if (playGrid[i][column]->value != 0)
			neighborValues.insert(playGrid[i][column]->value);
	}

	for(int i = row / 3 * 3; i < row / 3 * 3 + 3; ++i)
		for(int j = column / 3 * 3; j < column / 3 * 3 + 3; ++j)
			if (playGrid[i][j]->value != 0)
				neighborValues.insert(playGrid[i][j]->value);
}

Sudoku::~Sudoku()
{
	for(int i = 0; i < 9; ++i)
		for(int j = 0; j < 9; ++j)
			delete playGrid[i][j];
}