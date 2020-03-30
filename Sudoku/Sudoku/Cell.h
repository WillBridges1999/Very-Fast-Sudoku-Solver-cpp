#pragma once
#include <vector>

using namespace std;

class Cell
{
public:
	~Cell(void); // Destructor.
	Cell(void); // Void constructor.


private:
	vector<int> m_candidateList; // The candidate list (using vector as it's easier) i.e. the possible cell values.
	int m_value; // The contained value of the Cell, if known.
	bool m_givenFlag; // The flag to show whether the value was given, or found out later.
};

