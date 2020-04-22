#pragma once
#include "Cell.h"

class CellGroup
{
public:
	CellGroup(void);
	~CellGroup(void);

	// Copy constructor and copy assignment constructor due to private, pointer-type variables (for severity 3 pass).
	CellGroup(const CellGroup &c);
	CellGroup& operator=(const CellGroup &c);

	// Getter/ accessor for a cell (return a Cell pointer).
	inline Cell* getCell(const int index) const
	{
		return m_cells[index];
	}

	// Setter/ mutator for a cell (via a Cell type pointer).
	inline void setCell(const int index, Cell* const cell)
	{
		m_cells[index] = cell;
	}

private:
	Cell *m_cells[9];
};

