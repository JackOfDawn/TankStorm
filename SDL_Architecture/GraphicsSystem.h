#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include "Trackable.h"
#include <string>
#include "GraphicsBuffer.h"


class GraphicsSystem :
	public TrackableObject
{
public:

	GraphicsSystem(void);
	virtual ~GraphicsSystem(void);

	bool init(int width, int height);
	void cleanup();

	inline int getWidth() const {return mWidth;}
	inline int getHeight() const {return mHeight;}

	inline GraphicsBuffer* getBackBuffer() const {return mpBackBuffer;}
	void flipBuffer();
	void clearScreen();

	virtual inline std::string getClassName( void ) const { return "Graphics System"; }

private:
	SDL_Window* mpDisplay;
	SDL_Renderer* mpRenderer;
	
	GraphicsBuffer* mpBackBuffer;
	int		mWidth,
			mHeight;

	SDL_Renderer* getSystemRenderer();

	friend SDL_Renderer* GraphicsBuffer::getRenderer();
};

