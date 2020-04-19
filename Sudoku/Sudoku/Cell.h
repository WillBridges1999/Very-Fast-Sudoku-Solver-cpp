#pragma once
#include <vector>
#include <algorithm>

using namespace std;

class Cell
{
public:
	Cell(const int value, const bool givenFlag); // Main, non-default constructor.

	~Cell(void); // Destructor.
	Cell(void); // Void constructor.

	// Getters/ accessors for member variables, candidate values and list size.
	// Inlined for performance.
	inline int getValue() const
	{
		return m_value;
	}
	inline bool getGivenFlag() const
	{
		return m_givenFlag;
	}
	inline int getCandidateValueAtIndex(const int index) const
	{
		return m_candidateList[index];
	}
	inline int getCandidateListSize() const
	{
		return m_candidateList.size();
	}

	// Setters/ mutators for member variables.
	inline void setValue(const int value)
	{
		m_value = value;
	}
	inline void setGivenFlag(const bool flagState)
	{
		m_givenFlag = flagState;
	}

	// Method to alter the candidate list.
	void removeCandidateValue(const int value);


private:
	vector<int> m_candidateList; // The candidate list (using vector as it's easier) i.e. the possible cell values.
	int m_value; // The contained value of the Cell, if known.
	bool m_givenFlag; // The flag to show whether the value was given, or found out later.
};

