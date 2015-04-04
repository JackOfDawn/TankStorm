#include "ResourceManager.h"
#include "GraphicsBuffer.h"
#include "Sprite.h"
#include "Animation.h"
#include "GraphicsSystem.h"

ResourceManager* gpResourceManager = nullptr;

ResourceManager::ResourceManager(void)
{

}

ResourceManager::~ResourceManager(void)
{
	cleanup();
}


void ResourceManager::addAnimation( ResourceKey key, Animation* newAnimation )
{
	mpAnimationMap.insert(pair<ResourceKey, Animation*>(key, newAnimation));
}

void ResourceManager::addAnimation( ResourceKey key, vector<Sprite*> sprite, int speed, bool shouldLoop)
{
	Animation* newAnimation = New Animation(sprite, (float)speed, shouldLoop);
	addAnimation(key, newAnimation);
}

void ResourceManager::addGraphicsBuffer ( ResourceKey key, GraphicsBuffer* newGraphicsBuffer )
{
	mpGraphicsBufferMap.insert(pair<ResourceKey, GraphicsBuffer*>(key, newGraphicsBuffer));
}

void ResourceManager::addSprite( ResourceKey key, Sprite* newSprite )
{
	mpSpriteMap.insert(pair<ResourceKey, Sprite*>(key, newSprite));
}

void ResourceManager::addSprite(ResourceKey key, GraphicsBuffer* GBuffer, int x, int y, int width, int height)
{
	Vector2D temp((float)x,(float) y);

	Sprite* newSprite = New Sprite(GBuffer, temp, width, height);

	addSprite(key, newSprite);

}

void ResourceManager::loadGraphicsBuffer( ResourceKey key, string filePath, GraphicsSystem* pGSystem )
{
	GraphicsBuffer* newBuffer = New GraphicsBuffer(filePath, pGSystem);

	addGraphicsBuffer(key, newBuffer);
}

//Access Resource functions

Animation* ResourceManager::getAnimation( ResourceKey key )
{
	return mpAnimationMap.find(key)->second;
}

GraphicsBuffer* ResourceManager::getGraphicsBuffer( ResourceKey key )
{
	return mpGraphicsBufferMap.find(key)->second;
}

Sprite* ResourceManager::getSprite( ResourceKey key )
{
	return mpSpriteMap.find(key)->second;
}

//Cleanup Resource Maps function

void ResourceManager::cleanup()
{
	for(auto it = mpAnimationMap.begin(); it != mpAnimationMap.end(); ++it)
	{
		delete it->second;
	}

	mpAnimationMap.clear();

	for(auto it = mpSpriteMap.begin(); it != mpSpriteMap.end(); ++it)
	{
		delete it->second;
	}

	mpSpriteMap.clear();

	for(auto it = mpGraphicsBufferMap.begin(); it != mpGraphicsBufferMap.end(); ++it)
	{
		delete it->second;
	}

	mpGraphicsBufferMap.clear();

}