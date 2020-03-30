#include "Cell.h"

Cell::Cell(const int value, const bool givenFlag) // Constructor with params, to populate a cell.
{
	// Filling up the candidate list, from 1 to 9.
	for (int num = 1; num < 10; num++)
	{
		m_candidateList.push_back(num);
	}

	m_value = value;
	m_givenFlag = givenFlag;
}

Cell::~Cell(void)
{
}

Cell::Cell(void) // Default constructor, initialising empty cells.
{
	// Filling up the candidate list, from 1 to 9.
	for (int num = 1; num < 10; num++)
	{
		m_candidateList.push_back(num);
	}

	m_value = 0;
	m_givenFlag = false;
}

/*void Cell::removeCandidateValue(const int value)
{
	// Iterating over a vector properly.
	// Found at: https://stackoverflow.com/questions/409348/iteration-over-stdvector-unsigned-vs-signed-index-variable
	for (std::vector<int>::iterator it = m_candidateList.begin(); it != m_candidateList.end(); ++it) 
	{
		if (m_candidateList[it] == value)
		{

		}
	}
}*/