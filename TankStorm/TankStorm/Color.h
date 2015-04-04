/*
* Author: Jack Storm
* Class: EGP310-02
* Assignment: 2
* Certification: I hereby certify that this is entirely my own work
************************************************/
#pragma once

#include <SDL.h>
#include "Vector2D.h"
#include "GraphicsBuffer.h"

class Color : public TrackableObject
{
private:
	SDL_Color m_Color;
	SDL_Color getSDLColor();

public:
	Color(float red, float green, float blue, float alpha);
	~Color();

	float getAlpha();
	float getBlue();
	float getGreen();
	float getRed();

	void setAlpha(float alpha);
	

	virtual inline std::string getClassName( void ) const { return "Color"; }

	friend class GraphicsBuffer;
};

