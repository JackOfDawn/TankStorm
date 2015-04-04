#pragma once

#include "GridUnit.h"

class HeadCell : public GridUnit
{
public:
	HeadCell(int x, int y, Animation* cellAnimation);
	~HeadCell();

	virtual inline std::string getClassName( void ) const {return "Body Cell ";}

private:


};