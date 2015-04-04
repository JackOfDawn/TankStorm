#pragma once

#include "Trackable.h"
#include <string>
#include <map>
#include <vector>

class GraphicsBuffer;
class Sprite;
class Animation;
class GraphicsSystem;

using namespace std;

typedef string ResourceKey;

class ResourceManager :
	public TrackableObject
{
public:
	
	ResourceManager(void);
	virtual ~ResourceManager(void);

	void addAnimation( ResourceKey key, Animation* newAnimation );
	void addAnimation( ResourceKey key, vector<Sprite*>, int speed, bool shouldLoop);

	void addGraphicsBuffer ( ResourceKey key, GraphicsBuffer* newGraphicsBuffer );
	void loadGraphicsBuffer( ResourceKey key, string filePath, GraphicsSystem* pGSystem );

	void addSprite( ResourceKey key, Sprite* newSprite );
	void addSprite(ResourceKey key, GraphicsBuffer* GBuffer, int x, int y, int width, int height);

	Animation* getAnimation( ResourceKey key );
	GraphicsBuffer* getGraphicsBuffer( ResourceKey key );
	Sprite* getSprite( ResourceKey key );

	void cleanup();

	virtual inline string getClassName( void ) const { return "Resource Manager"; }

private:

	map<ResourceKey, Animation*> mpAnimationMap;
	map<ResourceKey, GraphicsBuffer*> mpGraphicsBufferMap;
	map<ResourceKey, Sprite*> mpSpriteMap;

};

extern ResourceManager* gpResourceManager;