#pragma once
#include "Cell.h"

class CellGroup
{
public:
	CellGroup(void);
	~CellGroup(void);

	// Getter/ accessor for a cell (return a Cell pointer).
	inline Cell* getCell(const int index) const
	{
		return m_cells[index];
	}

	// Setter/ mutator for a cell (via a Cell type pointer).
	inline void setCell(const int index, Cell *cell)
	{
		m_cells[index] = cell;
	}

private:
	Cell *m_cells[9];
};

