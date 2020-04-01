#pragma once
#include "CellGroup.h"
#include <vector>
#include <algorithm>
#include <iomanip>
// Add your code here

class SudokuPuzzle {
public:
	// Intialisation list to set puzzleSize and blockSize.
	SudokuPuzzle() : m_puzzleSize(9), m_blockSize(3) 
	{ }
	
	void solve(const char filenameIn[]);


private:
	// SudokuPuzzle members to save the puzzle size and block size.
	int m_puzzleSize;
	int m_blockSize;

	void output() const; // Output Grid.

	void readPuzzle(const char filenameIn[]) const; // Initialise Grid.

	// Code to intialise the structure 2 pointer CellGroups.
	CellGroup m_gridRows[9];
	CellGroup m_gridColumns[9];
	CellGroup m_gridBlocks[9];
};

