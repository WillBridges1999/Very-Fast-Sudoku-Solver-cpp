#include "SudokuPuzzle.h"
#include <iostream>
#include <chrono>


SudokuPuzzle::SudokuPuzzle()
{
}

SudokuPuzzle::~SudokuPuzzle() { }

int g_cellSolvedCounter{ 0 }; // Global counter, so it has scope in multiple methods.

void SudokuPuzzle::solve(const char filenameIn[]) {
	// Read puzzle from text file
	readPuzzle(filenameIn);


	// Get start time
	const auto startTime = std::chrono::high_resolution_clock::now();

	// Adding code to solve the puzzle
	bool solved = true;
	int candidateValueConsideredCounter = 0;
	int numOfPasses = 0;
	do
	{
		solved = true; // Reset for next pass.
		int blockNumber = 0, cellIndexInBlock = 0;

		// Visiting each individual cell.
		for (int row = 0; row < 9; row++)
		{
			for (int column = 0; column < 9; column++)
			{
				// If the value in the cell is equal to zero, then the cell has not been solved, so solve it.
				if (m_gridRows[row].getCell(column)->getValue() == 0)
				{
					solved = false;

					// Doing the 'naked single' solving algorithm.
					for (int cellIndex = 0; cellIndex < 9; cellIndex++)
					{
						// Checking the row context of the current cell.
						if (m_gridRows[row].getCell(cellIndex)->getValue() != 0)
						{
							// Remove this value from the candidate list.
							const int valueToRemove = m_gridRows[row].getCell(cellIndex)->getValue();
							m_gridRows[row].getCell(column)->removeCandidateValue(valueToRemove);
						}
					}

					for (int cellIndex = 0; cellIndex < 9; cellIndex++)
					{
						// Checking the column context of the current cell.
						if (m_gridColumns[column].getCell(cellIndex)->getValue() != 0)
						{
							// Remove this value from the candidate list.
							const int valueToRemove = m_gridColumns[column].getCell(cellIndex)->getValue();
							m_gridColumns[column].getCell(row)->removeCandidateValue(valueToRemove);
						}
					}
					
					for (int cellIndex = 0; cellIndex < 9; cellIndex++)
					{
						// Checking the block context of the current cell.
						if (m_gridBlocks[blockNumber].getCell(cellIndex)->getValue() != 0)
						{
							// Remove this value from the candidate list.
							const int valueToRemove = m_gridBlocks[blockNumber].getCell(cellIndex)->getValue();
							m_gridBlocks[blockNumber].getCell(cellIndexInBlock)->removeCandidateValue(valueToRemove);
						}
					}

					// Checking the size of each cells candidate list. Assign new cell value if size is 1.
					if (m_gridRows[row].getCell(column)->getCandidateListSize() == 1)
					{
						// Since there's only one value in the list, set this cells values to this value.
						m_gridRows[row].getCell(column)->setValue(m_gridRows[row].getCell(column)->getCandidateValueAtIndex(0));
						g_cellSolvedCounter++;
					}


					// IMPLEMENTING 'HIDDEN SINGLE' ALGORITHM NOW. 
					
					// Need to do another check since we may have solved a cells value in the 'naked single'
					// algorithm, but without this check the 'hidden single' algorithm wouldn't be aware of this.

					if (m_gridRows[row].getCell(column)->getValue() == 0)
					{
						// For each candidate value in the current cells candidate list.
						for (int candidateValueIndex = 0; candidateValueIndex < m_gridRows[row].getCell(column)->getCandidateListSize();
							candidateValueIndex++)
						{
							// Get a candidate value from the current cells candidate list.
							const int candiValue = m_gridRows[row].getCell(column)->getCandidateValueAtIndex(candidateValueIndex);
							bool isHiddenSingle = true;
							std::vector<int> v;

							// For each ROW, COLUMN AND BLOCK CONTEXT cells candidate list, check if the candiValue appears in the list or not.
							for (int cellIndex = 0; cellIndex < 9; cellIndex++)
							{
								candidateValueConsideredCounter++;
								// Some code found from: https://stackoverflow.com/questions/3450860/check-if-a-stdvector-contains-a-certain-object

								// Get the candidate list (vector) for this cell- from the ROW CONTEXT CELLS.
								v = *m_gridRows[row].getCell(cellIndex)->getCandidateList();
								if (std::find(v.begin(), v.end(), candiValue) != v.end())
								{
									// v contains candidateValue
									isHiddenSingle = false;
									break;
								}
								v.clear();

								// Do the same as above, but for the COLUMN INDEX CELLS now.
								v = *m_gridColumns[column].getCell(cellIndex)->getCandidateList();
								if (std::find(v.begin(), v.end(), candiValue) != v.end())
								{
									// v contains candidateValue
									isHiddenSingle = false;
									break;
								}
								v.clear();

								// Finally, do the same but for the BLOCK INDEX CELLS now.
								v = *m_gridBlocks[blockNumber].getCell(cellIndex)->getCandidateList();
								if (std::find(v.begin(), v.end(), candiValue) != v.end())
								{
									// v contains candidateValue
									isHiddenSingle = false;
									break;
								}
								v.clear();
							}

							// After checking all the candidate lists for the triple context, check the hiddenSingle result.
							if (isHiddenSingle)
							{
								// Hidden single found, therefore set this value to the current cells value.
								m_gridRows[row].getCell(column)->setValue(candiValue);
								g_cellSolvedCounter++;
								break;
							}

						}
					}

				}
				// Gets the specific block number for the next iteration.
				blockNumber = getBlockNumber(row, column, blockNumber);

				// Getting the cellIndexInBlock number for the next iteration.
				cellIndexInBlock = getCellIndexInBlock(row, column, cellIndexInBlock);
			}
		}
		numOfPasses++;

	} while (!solved);


	// Get end time
	const auto endTime = std::chrono::high_resolution_clock::now();
	const auto duration = (endTime - startTime).count();

	// Sample timing output in nanoseconds
	std::cout << "Duration to run, in nano-seconds: " << duration << "ns" << std::endl;
	std::cout << "Duration to run, in milli-seconds: " << (static_cast<double>(duration) / 1000000) << "ms" << std::endl;
	std::cout << "Duration to run, in seconds: " << (static_cast<double>(duration) / 1000000000) << "s" << std::endl;


	// Displaying some debug information for the marker of the coursework.
	std::cout << "Amount of cells solved: " << g_cellSolvedCounter << std::endl;
	std::cout << "Number of passes through the grid required: " << numOfPasses << std::endl;
	std::cout << "Number of candidate values considered: " << candidateValueConsideredCounter << std::endl;

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
			else
			{
				g_cellSolvedCounter++;
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
	ofstream fout("sudoku_solution.txt");
	if (fout.is_open())
	{
		for (int row = 0; row < 9; row++)
		{
			for (int column = 0; column < 9; ++column)
			{
				fout << m_gridRows[row].getCell(column)->getValue() << " ";
			}

			fout << endl;
		}

		fout.close();
	}
}
