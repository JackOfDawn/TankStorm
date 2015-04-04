#pragma once

#include "GridUnit.h"

class SpeedCell : public GridUnit
{
public:
	SpeedCell(int x, int y, Animation* cellAnimation);
	~SpeedCell();

	virtual inline std::string getClassName( void ) const {return "Speed Cell";}

private:


};
