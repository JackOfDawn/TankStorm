/*	Author:		Spencer Martin
 *	Class:		EGP 310-02
 *	Assignment:	Midterm, Snake
 *	File:		GridUnit.h
 *	Certificate of Authenticity:	I certify that this project is entirely my own work.
 *****************************************************************************************/

#include "GridUnit.h"

GridUnit::GridUnit(int x, int y, Animation* animation, CellType type)
{
	mGridPosX = x;
	mGridPosY = y;
	mpAnimation = animation;
	mType = type;
}

GridUnit::~GridUnit()
{

}

void GridUnit::setPosition(int x, int y)
{
	mGridPosX = x;
	mGridPosY = y;
}

void GridUnit::draw(GraphicsBuffer* targetDrawBuffer)
{
	mLocation.setX(mGridPosX * CELL_DIMENSION);
	mLocation.setY(mGridPosY * CELL_DIMENSION);

	Unit::draw(targetDrawBuffer);
}
