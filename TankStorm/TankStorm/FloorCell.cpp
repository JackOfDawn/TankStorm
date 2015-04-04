#include "FloorCell.h"


FloorCell::FloorCell(int x, int y, Animation* cellAnimation)
	:GridUnit(x, y, cellAnimation, FLOOR_CELL_TYPE)
{

}

FloorCell::~FloorCell()
{

}
