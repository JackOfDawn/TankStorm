/*
* Author: Jack Storm
* Class: EGP310-02
* Assignment: 2
* Certification: I hereby certify that this is entirely my own work
************************************************/
#pragma once

#include "Vector2D.h"
#include <SDL.h>
class GraphicsBuffer;

class Sprite : public TrackableObject
{
private:
	GraphicsBuffer* mp_GraphicsBuffer;
	Vector2D m_SourceLocation;
	SDL_Rect* mp_SourceRect;
	int m_Width;
	int m_Height;
	double m_rotation;

public:

	Sprite();
	Sprite(GraphicsBuffer* graphicsBuffer, Vector2D sourceLoc, int width, int height);
	virtual ~Sprite();

	Vector2D getSourceLocation();
	SDL_Rect* getSourceRect();
	GraphicsBuffer* getBuffer();
	int getHeight();
	int getWidth();
	double getRotation();
	
	virtual inline std::string getClassName( void ) const { return "Sprite "; }
};

