#include "GraphicsBuffer.h"
#include "GraphicsSystem.h"
#include "Vector2D.h"
#include "Color.h"
#include "Sprite.h"

#include "Font.h"

GraphicsBuffer::GraphicsBuffer(void)
{
}

GraphicsBuffer::GraphicsBuffer(int width, int height, Color color, GraphicsSystem* pGraphicsSystem)
{
	mWidth = width;
	mHeight = height;
	mPath = "";
	attachToGraphicsSystem(pGraphicsSystem);

	//create surface
	SDL_Surface* tmpSurface = SDL_CreateRGBSurface(0, mWidth, mHeight, 32, color.getSDLColor().r, color.getSDLColor().g, color.getSDLColor().b, 0);
	
	//convert to texture
	mpTexture = SDL_CreateTextureFromSurface(getRenderer(), tmpSurface);
	

	//free surface
	SDL_FreeSurface(tmpSurface);

	mOwnsMap = true;
}

GraphicsBuffer::GraphicsBuffer(SDL_Surface* buffer, GraphicsSystem* pGraphicsSystem)
{
	attachToGraphicsSystem(pGraphicsSystem);
	mpSurface = buffer;
	mOwnsMap = false;

	
}

GraphicsBuffer::GraphicsBuffer(std::string sourcePath, GraphicsSystem* pGraphicsSystem)
{
	mPath = sourcePath;
	attachToGraphicsSystem(pGraphicsSystem);

	SDL_Surface* tmpSurface;

	if (!(tmpSurface = IMG_Load(mPath.c_str())))
	{
		std::cout << "This could be a problem... SDL couldn't load the buffer image.\n";
	}
	else
	{
		mpTexture = SDL_CreateTextureFromSurface(getRenderer(), tmpSurface);
	}

	//free surface
	SDL_FreeSurface(tmpSurface);

	mOwnsMap = true;

	
}

GraphicsBuffer::~GraphicsBuffer(void)
{
	if(mOwnsMap)
		SDL_DestroyTexture(mpTexture);
}

void GraphicsBuffer::attachToGraphicsSystem(GraphicsSystem* pGraphicsSystem)
{
	mpGraphicsSystem = pGraphicsSystem;
}

void GraphicsBuffer::draw(Vector2D location, Sprite* sprite)
{
	SDL_Rect tmpLocationRect = SDL_Rect();
	tmpLocationRect.x = (int)location.getX();
	tmpLocationRect.y = (int)location.getY();
	tmpLocationRect.w = sprite->getWidth();
	tmpLocationRect.h = sprite->getHeight();

	SDL_Point center = SDL_Point();
	center.x = 0;
	center.y = 0;

	//SDL_RenderCopy(getRenderer(), sprite->getBuffer()->getBitmap(), sprite->getSourceRect(), &tmpLocationRect);
	SDL_RenderCopyEx(getRenderer(),sprite->getBuffer()->getBitmap(), sprite->getSourceRect(), &tmpLocationRect, (location.getY() * location.getX()) / 2,  &center, SDL_FLIP_HORIZONTAL);
}

void GraphicsBuffer::drawOrigin(Vector2D location, Sprite* sprite)
{
	int halfWidth = sprite->getWidth() / 2;
	int halfHeight = sprite->getHeight() / 2;

	SDL_Rect tmpLocationRect = SDL_Rect();
	tmpLocationRect.x = (int)location.getX();
	tmpLocationRect.y = (int)location.getY();
	tmpLocationRect.w = sprite->getWidth() - halfWidth;
	tmpLocationRect.h = sprite->getHeight() - halfHeight;

	SDL_Point center = SDL_Point();
	center.x = 0;
	center.y = 0;

	//SDL_RenderCopy(getRenderer(), sprite->getBuffer()->getBitmap(), sprite->getSourceRect(), &tmpLocationRect);
	SDL_RenderCopyEx(getRenderer(),sprite->getBuffer()->getBitmap(), sprite->getSourceRect(), &tmpLocationRect, (location.getY() * location.getX()) / 2,  &center, SDL_FLIP_HORIZONTAL);
}

void GraphicsBuffer::drawScaled(Vector2D location, Sprite* sprite, float scale)
{
	SDL_Rect tmpLocationRect = SDL_Rect();
	tmpLocationRect.x = (int)location.getX();
	tmpLocationRect.y = (int)location.getY();
	tmpLocationRect.w = sprite->getWidth() * scale;
	tmpLocationRect.h = sprite->getHeight() * scale;

	SDL_Point center = SDL_Point();
	center.x = 0;
	center.y = 0;
	

	//SDL_RenderCopy(getRenderer(), sprite->getBuffer()->getBitmap(), sprite->getSourceRect(), &tmpLocationRect);
	SDL_RenderCopyEx(getRenderer(),sprite->getBuffer()->getBitmap(), sprite->getSourceRect(), &tmpLocationRect, (location.getY() * location.getX()) / 2,  &center, SDL_FLIP_HORIZONTAL);
}

SDL_Texture* GraphicsBuffer::getBitmap()
{
	return mpTexture;
}

void GraphicsBuffer::writeText(Vector2D targetLoc, Font* font, Color color, std::string output)
{
	//Render Text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid(font->getFont(), output.c_str(), color.getSDLColor());

	//Create Texture from surface
	SDL_Texture* txtTexture = SDL_CreateTextureFromSurface(getRenderer(), textSurface);

	//create tempRectangle
	SDL_Rect tmpLocationRect = SDL_Rect();
	tmpLocationRect.x = (int)targetLoc.getX();
	tmpLocationRect.y = (int)targetLoc.getY();
	tmpLocationRect.w = textSurface->w;
	tmpLocationRect.h = textSurface->h;

	//Draw
	SDL_RenderCopy(getRenderer(), txtTexture, NULL, &tmpLocationRect);


	//Cleanup
	SDL_FreeSurface(textSurface);
	SDL_DestroyTexture(txtTexture);

	

}

SDL_Renderer* GraphicsBuffer::getRenderer()
{
	return mpGraphicsSystem->getSystemRenderer();
}
