#pragma once

#include <vector>
#include "Trackable.h"
#include <string>

class ResourceManager;
class Level;
class Snake;
class Unit;
class Animation;
class GraphicsBuffer;

class LevelManager : public TrackableObject
{
public:
	LevelManager(void);
	virtual ~LevelManager(void);

	void loadLevel(std::string sourcePath, Animation* head, ResourceManager* pResourceManager);
	void nextLevel();
	void restart();
	void setupLevel();
	void update(double passedTime);
	void draw(GraphicsBuffer* targetBuffer);

	void cleanup();

	bool gameShouldEnd() { return gameWon; }
	inline Level* getCurrentLevel() const {return mpLevels[mCurrentLevel];}

	virtual inline std::string getClassName( void ) const { return "LevelManager "; }

private:

	ResourceManager* mpResourceManager;
	Animation* mpHeadAnim;

	std::vector<std::string> mLevelFiles;

	std::vector<Level*> mpLevels;

	int	mCurrentLevel;
	bool levelComplete;
	bool gameWon;
	bool levelSetup;
	

};

