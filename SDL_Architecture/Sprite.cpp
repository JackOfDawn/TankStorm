/*
* Author: Jack Storm
* Class: EGP310-02
* Assignment: 2
* Certification: I hereby certify that this is entirely my own work
************************************************/

#include "sprite.h"

Sprite::Sprite()
{
	mp_GraphicsBuffer = NULL;
	m_SourceLocation = Vector2D();
	m_Width = 0;
	m_Height = 0;
}

Sprite::Sprite(GraphicsBuffer* graphicsBuffer, Vector2D sourceLoc, int width, int height)
{
	mp_GraphicsBuffer = graphicsBuffer;
	m_SourceLocation = sourceLoc;

	mp_SourceRect = new SDL_Rect();

	mp_SourceRect->x = m_SourceLocation.getX();
	mp_SourceRect->y = m_SourceLocation.getY();
	m_Width = mp_SourceRect->w = width;
	m_Height = mp_SourceRect->h = height;
	

}

Sprite::~Sprite()
{

}

Vector2D Sprite::getSourceLocation()
{
	return m_SourceLocation;
}

SDL_Rect* Sprite::getSourceRect()
{
	return mp_SourceRect;
}

GraphicsBuffer* Sprite::getBuffer()
{
	return mp_GraphicsBuffer;
}

int Sprite::getHeight()
{
	return m_Height;
}

int Sprite::getWidth()
{
	return m_Width;
}
