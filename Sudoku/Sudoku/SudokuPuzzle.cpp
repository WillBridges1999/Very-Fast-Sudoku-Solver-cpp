#include "SudokuPuzzle.h"
#include <iostream>
#include <chrono>


SudokuPuzzle::SudokuPuzzle() {
	// Add code to initialise the SudokuPuzzle object
}


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
}


void SudokuPuzzle::output() const {
	// Add code to output your solved puzzle
}
