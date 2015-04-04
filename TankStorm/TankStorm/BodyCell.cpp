#include "BodyCell.h"

BodyCell::BodyCell(int x, int y, Animation* cellAnimation)
	:GridUnit(x, y, cellAnimation, BODY_CELL_TYPE)
{

}

BodyCell::~BodyCell()
{

}

