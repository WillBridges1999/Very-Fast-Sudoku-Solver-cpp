#pragma once
#include "CellGroup.h"
#include <vector>
#include <algorithm>
#include <iomanip>
#include <fstream>
// Add your code here

class SudokuPuzzle {
public:
	SudokuPuzzle();
	~SudokuPuzzle();
	
	void solve(const char filenameIn[]);


private:
	
	void output() const; // Output Grid.

	void readPuzzle(const char filenameIn[]); // Initialise Grid.

	int getBlockNumber(const int row, const int column, const int p_blockNumber) const;
	int getCellIndexInBlock(const int row, const int column, const int p_cellIndexInBlock) const;

	// Code to intialise the structure 2 pointer CellGroups.
	CellGroup m_gridRows[9];
	CellGroup m_gridColumns[9];
	CellGroup m_gridBlocks[9];
};

