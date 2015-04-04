#pragma once

#include "Trackable.h"
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include "Color.h"


class Sprite;
class Vector2D;
class Font;
class Color;

class GraphicsSystem;

class GraphicsBuffer :
	public TrackableObject
{
public:
	GraphicsBuffer(void);
	GraphicsBuffer(int width, int height, Color color, GraphicsSystem* pGraphicsSystem);
	GraphicsBuffer(SDL_Surface* buffer, GraphicsSystem* pGraphicsSystem);
	GraphicsBuffer(std::string sourcePath, GraphicsSystem* pGraphicsSystem);
	virtual ~GraphicsBuffer(void);

	void attachToGraphicsSystem(GraphicsSystem* pGraphicsSystem);

	void draw(Vector2D location, Sprite* sprite, double rotation = 0);
	void drawOrigin(Vector2D location, Sprite* sprite, double rotation = 0);
	void drawScaled(Vector2D location, Sprite* sprite, float scale, double rotation = 0);
	void writeText(Vector2D targetLoc, Font* font, Color color, std::string output);
	
	inline int getHeight() const {return mHeight;}
	inline int getWidth() const {return mWidth;}

	virtual inline std::string getClassName( void ) const { return "Graphics Buffer"; }

private:
	SDL_Surface* mpSurface;
	SDL_Texture* mpTexture;
	int mHeight,
		mWidth;
	bool mOwnsMap;
	std::string mPath;
	GraphicsSystem* mpGraphicsSystem;

	SDL_Texture* getBitmap();

	SDL_Renderer* getRenderer();

	friend class GraphicsSystem;

};

