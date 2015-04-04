/*
* Author: Jack Storm
* Class: EGP310-02
* Assignment: 2
* Certification: I hereby certify that this is entirely my own work
************************************************/

#include "Font.h"

Font::Font(std::string path, float size)
{
	mpFont = TTF_OpenFont(path.c_str(), size);
	m_Path = path;
	m_Size = size;
}

Font::~Font()
{
	TTF_CloseFont(mpFont);
}

float Font::getSize()
{
	return m_Size;
}