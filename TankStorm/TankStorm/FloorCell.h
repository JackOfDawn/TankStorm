#pragma once

#include "GridUnit.h"

class FloorCell : public GridUnit
{
public:
	FloorCell(int x, int y, Animation* cellAnimation);
	~FloorCell();

	virtual inline std::string getClassName( void ) const {return "Body Cell";}

private:


};

