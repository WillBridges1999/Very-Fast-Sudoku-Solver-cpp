#include "CellGroup.h"

CellGroup::CellGroup(void) // To initialise CellGroup state.
{
	for (int index = 0; index < 9; ++index)
	{
		m_cells[index] = new Cell();
	}
}

CellGroup::~CellGroup(void)
{ }

