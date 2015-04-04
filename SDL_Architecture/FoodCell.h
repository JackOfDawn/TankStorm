#pragma once

#include "GridUnit.h"

class FoodCell : public GridUnit
{
public:
	FoodCell(int x, int y, Animation* cellAnimation);
	~FoodCell();

	virtual inline std::string getClassName( void ) const {return "Body Cell";}

private:


};

