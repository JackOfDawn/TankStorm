/*	Author:		Spencer Martin
 *	Class:		EGP 310-02
 *	Assignment:	Midterm, Snake
 *	File:		BodyCell.h
 *	Certificate of Authenticity:	I certify that this project is entirely my own work.
 *****************************************************************************************/

#pragma once

#pragma once

#include "GridUnit.h"

class BodyCell : public GridUnit
{
public:
	BodyCell(int x, int y, Animation* cellAnimation);
	~BodyCell();

	virtual inline std::string getClassName( void ) const {return "Body Cell";}

private:


};