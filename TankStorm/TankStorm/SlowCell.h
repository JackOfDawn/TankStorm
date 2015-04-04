#pragma once

#include "GridUnit.h"

class SlowCell : public GridUnit
{
public:
	SlowCell(int x, int y, Animation* cellAnimation);
	~SlowCell();

	virtual inline std::string getClassName( void ) const {return "Slow Cell";}

private:


};
