/*	Author:		Spencer Martin
 *	Class:		EGP 310-02
 *	Assignment:	Midterm, Snake
 *	File:		GridUnit.h
 *	Certificate of Authenticity:	I certify that this project is entirely my own work.
 *****************************************************************************************/

#pragma once

#include "Trackable.h"
#include "MiscDataDef.h"
#include "Unit.h"

class Sprite;

class GridUnit : public Unit
{
public:
	GridUnit(int x, int y, Animation* animation, CellType type);
	virtual ~GridUnit();

	inline CellType getType() const { return mType;};
	inline int getX() const {return mGridPosX;};
	inline int getY() const {return mGridPosY;};
	inline Animation* getAnimation() const {return mpAnimation;}

	inline void setType(CellType newType) {mType = newType;}
	void setPosition(int x, int y);

	virtual inline std::string getClassName( void ) const {return "Grid Unit ";}

	virtual void draw(GraphicsBuffer* targetDrawBuffer);

	virtual inline Vector2D getLocation() const { return Vector2D((float)mGridPosX, (float)mGridPosY); }

	virtual int getGridPosX() const { return mGridPosX; }
	virtual int getGridPosY() const { return mGridPosY; }
protected:
	CellType	mType;
	int			mGridPosX,
				mGridPosY;

};
