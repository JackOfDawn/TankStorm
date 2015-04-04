/*
* Author: Jack Storm
* Class: EGP310-02
* Assignment: 2
* Certification: I hereby certify that this is entirely my own work
************************************************/

#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include "Vector2D.h"
#include "GraphicsBuffer.h"

class GraphicsBuffer;
class Color;

class Font : public TrackableObject
{

	
private:
	TTF_Font* mpFont;

	std::string m_Path;
	float m_Size;

public: 

	Font(std::string path, float size); //this needs to be changed
	~Font();

	inline TTF_Font* getFont() {return mpFont;}
	float getSize();

	virtual inline std::string getClassName( void ) const { return "Font"; }

};
