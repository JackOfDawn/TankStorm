/*
* Author: Jack Storm
* Class: EGP310-02
* Assignment: 2
* Certification: I hereby certify that this is entirely my own work
************************************************/

#include "Color.h"

Color::Color(float red, float green, float blue, float alpha)
{
	m_Color.r = (Uint8)red;
	m_Color.g = (Uint8)green;
	m_Color.b = (Uint8)blue;
	m_Color.a = (Uint8)alpha;

}

Color::~Color()
{
	
}

SDL_Color Color::getSDLColor()
{
	return m_Color;
}

float Color::getAlpha()
{
	return m_Color.a;
}

float Color::getBlue()
{
	return m_Color.b;
}

float Color::getGreen()
{
	return m_Color.g;
}

float Color::getRed()
{
	return m_Color.r;
}

void Color::setAlpha(float alpha)
{
	m_Color.a = (Uint8)alpha;
}
