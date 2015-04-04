#include "FoodCell.h"

FoodCell::FoodCell(int x, int y, Animation* cellAnimation)
	:GridUnit(x, y, cellAnimation, FOOD_CELL_TYPE)
{

}

FoodCell::~FoodCell()
{

}

