#pragma once
#include "Cell.h"

class CellGroup
{
public:
	CellGroup(void);
	~CellGroup(void);

	// Getter/ accessor for a cell (return a pointer).
	Cell* getCell(const int index) const;

	// Setter/ mutator for a cell (via a pointer).
	void setCell(const int index, const Cell *cell);

private:
	Cell *m_cells[9];
};

