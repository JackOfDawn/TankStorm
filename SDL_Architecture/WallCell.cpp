#include "WallCell.h"




WallCell::WallCell(int x, int y, Animation* cellAnimation)
	:GridUnit(x, y, cellAnimation, WALL_CELL_TYPE)
{
	
}

WallCell::~WallCell()
{

}
