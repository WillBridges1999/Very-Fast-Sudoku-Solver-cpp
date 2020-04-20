#include "SudokuPuzzle.h"
#include <iostream>
#include <chrono>


SudokuPuzzle::SudokuPuzzle()
{
}

SudokuPuzzle::~SudokuPuzzle() { }


void SudokuPuzzle::solve(const char filenameIn[]) {
	// Read puzzle from text file
	readPuzzle(filenameIn);

	// Get start time
	const auto startTime = std::chrono::high_resolution_clock::now();

	// Adding code to solve the puzzle
	bool solved = true;
	int blockNumber = 0, cellIndexInBlock = 0;
	do
	{
		solved = true; // Reset for next pass.

		// Visiting each individual cell.
		for (int row = 0; row < 9; row++)
		{
			for (int column = 0; column < 9; column++)
			{
				// If the value in the cell is equal to zero, then the cell has not been solved, so solve it.
				if (m_gridRows[row].getCell(column)->getValue() == 0)
				{
					solved = false;

					// Gets the specific block number for the next iteration.
					blockNumber = getBlockNumber(row, column, blockNumber);

					// Getting the cellIndexInBlock number for the next iteration.
					cellIndexInBlock = getCellIndexInBlock(row, column, cellIndexInBlock);

					// Doing the 'naked single' solving algorithm.
					for (int cellIndex = 0; cellIndex < 9; cellIndex++)
					{
						// Checking the row context of the current cell.
						if (m_gridRows[row].getCell(cellIndex)->getValue() != 0)
						{
							// Remove this value from the candidate list.
							int valueToRemove = m_gridRows[row].getCell(cellIndex)->getValue();
							m_gridRows[row].getCell(column)->removeCandidateValue(valueToRemove);
						}
					}

					for (int cellIndex = 0; cellIndex < 9; cellIndex++)
					{
						// Checking the column context of the current cell.
						if (m_gridColumns[column].getCell(cellIndex)->getValue() != 0)
						{
							// Remove this value from the candidate list.
							int valueToRemove = m_gridColumns[column].getCell(cellIndex)->getValue();
							m_gridColumns[column].getCell(row)->removeCandidateValue(valueToRemove);
						}
					}
					
					for (int cellIndex = 0; cellIndex < 9; cellIndex++)
					{
						// Checking the block context of the current cell.
						if (m_gridBlocks[blockNumber].getCell(cellIndex)->getValue() != 0)
						{
							// Remove this value from the candidate list.
							int valueToRemove = m_gridBlocks[blockNumber].getCell(cellIndex)->getValue();
							m_gridBlocks[blockNumber].getCell(cellIndexInBlock)->removeCandidateValue(valueToRemove);
						}
					}

					// Checking the size of each cells candidate list. Assign new cell value if size is 1.
					if (m_gridRows[row].getCell(column)->getCandidateListSize() == 1)
					{
						// Since there's only one value in the list, set this cells values to this value.
						m_gridRows[row].getCell(column)->setValue(m_gridRows[row].getCell(column)->getCandidateValueAtIndex(0));
					}
				}
			}
		}

	} while (solved == false);


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
	int blockNumber = 0, cellIndexInBlock = 0;
	for (int row = 0; row < 9; row++) // Leaving as post++, as doesn't affect performance with ints.
	{
		for (int column = 0; column < 9; column++)
		{
			bool givenFlag = true;
			fin >> inputValue;

			if (inputValue == 0)
			{
				givenFlag = false;
			}

			// Reading file values into the CellGroup for the rows.
			m_gridRows[row].setCell(column, new Cell(inputValue, givenFlag));

			// Using the Rows CellGroup to populate the Column CellGroup. To setCell from the Rows CellGroup, 
			// the setCell index param has to be the row, and the Cell we want to point to has to be in the 
			// current row we're on in the loop. Then, we getCell on the correct element index in the row. 
			// This gives us the correct cell to be pointed to by the correct element in our Column CellGroup.
			m_gridColumns[column].setCell(row, m_gridRows[row].getCell(column));

			// Using the Rows CellGroup to populate the Block CellGroup.
			m_gridBlocks[blockNumber].setCell(cellIndexInBlock, m_gridRows[row].getCell(column)); // Should be working now.


			// Gets the specific block number for the next iteration.
			blockNumber = getBlockNumber(row, column, blockNumber);

			// Getting the cellIndexInBlock number for the next iteration.
			cellIndexInBlock = getCellIndexInBlock(row, column, cellIndexInBlock);
		}
	}
}

int SudokuPuzzle::getBlockNumber(const int row, const int column, const int p_blockNumber) const
{
	int blockNumber = p_blockNumber;

	if (column == 2 || column == 5)
	{
		blockNumber++;
	}
	else if (column == 8)
	{
		if (row < 2)
		{
			blockNumber = 0;
		}
		else if (row < 5)
		{
			blockNumber = 3;
		}
		else if (row >= 5)
		{
			blockNumber = 6;
		}
	}

	return blockNumber;
}

int SudokuPuzzle::getCellIndexInBlock(const int row, const int column, const int p_cellIndexInBlock) const
{
	int cellIndexInBlock = p_cellIndexInBlock;

	if (row == 0 || row == 3 || row == 6)
	{
		if (column == 2 || column == 5)
		{
			cellIndexInBlock = 0;
		}
		else
		{
			cellIndexInBlock++;
		}
	}
	else if (row == 1 || row == 4 || row == 7)
	{
		if (column == 2 || column == 5)
		{
			cellIndexInBlock = 3;
		}
		else
		{
			cellIndexInBlock++;
		}
	}
	else if (row == 2 || row == 5 || row == 8)
	{
		if (column == 2 || column == 5)
		{
			cellIndexInBlock = 6;
		}
		else if (column == 8)
		{
			cellIndexInBlock = 0;
		}
		else
		{
			cellIndexInBlock++;
		}
	}

	return cellIndexInBlock;
}

void SudokuPuzzle::output() const {
	// Add code to output your solved puzzle
}
