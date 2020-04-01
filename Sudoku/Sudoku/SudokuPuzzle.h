#pragma once
#include "CellGroup.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <iomanip>
// Add your code here

class SudokuPuzzle {
public:
	SudokuPuzzle();
	
	void solve(const char filenameIn[]);


private:
	void output() const; // Output Grid.

	void readPuzzle(const char filenameIn[]) const; // Initialise Grid.

	// Code to intialise the structure 2 pointer CellGroups.
	CellGroup m_gridRows[9];
	CellGroup m_gridColumns[9];
	CellGroup m_gridBlocks[9];
};

