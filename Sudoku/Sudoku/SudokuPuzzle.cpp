#include "SudokuPuzzle.h"
#include <iostream>
#include <chrono>


SudokuPuzzle::SudokuPuzzle() 
{
	// Setting these because only solving 3 by 3 sudoku puzzles.
	m_puzzleSize = 9; 
	m_blockSize = 3;
}

SudokuPuzzle::~SudokuPuzzle() { }


void SudokuPuzzle::solve(const char filenameIn[]) {
	// Read puzzle from text file
	readPuzzle(filenameIn);

	// Get start time
	const auto startTime = std::chrono::high_resolution_clock::now();

	// Add code to solve the puzzle

	// Get end time
	const auto endTime = std::chrono::high_resolution_clock::now();
	const auto duration = (endTime - startTime).count();

	// Sample timing output in nanoseconds
	std::cout << duration << "ns" << std::endl;

	// Output the solved puzzle
	output();
}


void SudokuPuzzle::readPuzzle(const char filenameIn[]) const {
	// Add code to read in a puzzle from the text file and store within the SudokuPuzzle object

	// Also, need to assign all these file values into the m_gridRows[9] CellGroup...
}


void SudokuPuzzle::output() const {
	// Add code to output your solved puzzle
}
