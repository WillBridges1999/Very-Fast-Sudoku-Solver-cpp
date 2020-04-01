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


void SudokuPuzzle::readPuzzle(const char filenameIn[]) 
{
	ifstream fin(filenameIn);
	// First part of algorithm needs to input all the file values into the CellGroup for gridRows[9], as specified in ACW.

	int inputValue; // Declare these ONCE in the entire class, if it's re-used in future code (performance increase).
	for (int row = 0; row < m_puzzleSize; row++) // Leaving as post++, as doesn't affect performance with ints.
	{
		for (int column = 0; column < m_puzzleSize; column++)
		{
			bool givenFlag = true;
			fin >> inputValue;

			if (inputValue == 0)
			{
				givenFlag = false;
			}

			// Reading file values into the CellGroup for the rows.
			m_gridRows[row].setCell(column, new Cell(inputValue, givenFlag));

			// Using the Rows CellGroup to populate the Column CellGroup. To setCell from the Rows CellGroup, the setCell index param has to 
			// be the row, and the Cell we want to point to has to be in the current row we're on in the loop. Then, we getCell on the correct 
			// element index in the row. This gives us the correct cell to be pointed to by the correct element in our Column CellGroup.
			m_gridColumns[column].setCell(row, m_gridRows[row].getCell(column));

			// Using the Rows CellGroup to populate the Block CellGroup.
			m_gridBlocks[row].setCell(row, m_gridRows[row].getCell(column)); // NOT WORKING. Gonna be complicated...
		}
	}
}


void SudokuPuzzle::output() const {
	// Add code to output your solved puzzle
}
