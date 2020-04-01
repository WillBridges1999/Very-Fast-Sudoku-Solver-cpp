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
	// SudokuPuzzle members to save the puzzle size and block size.
	int m_puzzleSize;
	int m_blockSize;

	void output() const; // Output Grid.

	void readPuzzle(const char filenameIn[]); // Initialise Grid.

	// Code to intialise the structure 2 pointer CellGroups.
	CellGroup m_gridRows[9];
	CellGroup m_gridColumns[9];
	CellGroup m_gridBlocks[9];
};

