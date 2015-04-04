#include "GraphicsSystem.h"
#include "GraphicsBuffer.h"




GraphicsSystem::GraphicsSystem(void)
{
	mpDisplay = NULL;
	mpBackBuffer = NULL;
	mpRenderer = NULL;
}

GraphicsSystem::~GraphicsSystem(void)
{
	cleanup();
}

bool GraphicsSystem::init(int width, int height)
{

	//Initialize video
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "This could be a problem, " << SDL_GetError() << std::endl;
		return false;
	}

	mWidth = width;
	mHeight = height;

	mpDisplay = SDL_CreateWindow("Tank Storm", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,  mWidth, mHeight, SDL_WINDOW_SHOWN);


	//Get SDL WINDOW UP AND RUNNING
	if (mpDisplay == NULL)
	{
		std::cout << "This could be a problem, "  << SDL_GetError() << std::endl;
		return false;
	}
	else
	{
		//creating the renderer
		mpRenderer = SDL_CreateRenderer(mpDisplay, -1, SDL_RENDERER_ACCELERATED);
		if(mpRenderer == NULL)
		{
			std::cout << "Renderer was not created, "  << SDL_GetError() << std::endl;
		}
		else
		{
			//initialize render wipe color
			SDL_SetRenderDrawColor(mpRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

			//init that PNG loading
			int imgFlags = IMG_INIT_PNG;
			if(!(IMG_Init(imgFlags) & imgFlags))
			{
				std::cout << "SDL_Image could not load was not created, "  << IMG_GetError() << std::endl;
			}

			//init SDL_TTF
			if(TTF_Init() == -1)
			{
				std::cout << "SDL_Font could not load was not created" << std::endl;

			}
		}  
	}

	mpBackBuffer = New GraphicsBuffer(SDL_GetWindowSurface(mpDisplay), this);
	return true;
}

void GraphicsSystem::cleanup()
{
	SDL_DestroyRenderer(mpRenderer);
	SDL_DestroyWindow(mpDisplay);

	IMG_Quit();
	TTF_Quit();

	SDL_Quit();
	delete mpBackBuffer;
}

void GraphicsSystem::flipBuffer()
{
	//SDL_UpdateWindowSurface(mpDisplay);
	SDL_RenderPresent(mpRenderer);
}

void GraphicsSystem::clearScreen()
{
	SDL_RenderClear(mpRenderer);
}

SDL_Renderer* GraphicsSystem::getSystemRenderer()
{
	return SDL_GetRenderer(mpDisplay);
}
