/*	Author:		Spencer Martin
 *	Class:		EGP 310-02
 *	Assignment:	Midterm, Snake
 *	File:		WallGridUnit.h
 *	Certificate of Authenticity:	I certify that this project is entirely my own work.
 *****************************************************************************************/

#pragma once

#include "GridUnit.h"
class Sprite;

class WallCell : public GridUnit
{
public:
	WallCell(int x, int y, Animation* cellAnimation);
	~WallCell();

	virtual inline std::string getClassName( void ) const {return "Wall Cell";}

private:
	

};



