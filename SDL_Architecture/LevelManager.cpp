

#include "LevelManager.h"
#include "ResourceManager.h"
#include "Level.h"
#include "Snake.h"
#include "LevelCompleteEvent.h"
#include "LevelFailedEvent.h"
#include "Animation.h"
#include "GraphicsBuffer.h"

#include <vector>
#include <sstream>
#include <fstream>

using namespace std;


LevelManager::LevelManager(void)
{
	mCurrentLevel = -1;
	gameWon = false;
	levelComplete = false;
}

LevelManager::~LevelManager(void)
{
	cleanup();
}

void LevelManager::loadLevel(std::string sourcePath, Animation* head, ResourceManager* pResourceManager)
{
	mpResourceManager = pResourceManager;
	mpHeadAnim = head;

	int levelNum;
	levelNum = mpLevels.size()+1;

	Level* tempLevel = New Level(levelNum);

	tempLevel->loadFromFile(sourcePath, head, pResourceManager);

	mLevelFiles.push_back(sourcePath);
	mpLevels.push_back(tempLevel);
}

void LevelManager::nextLevel()
{
	if (mCurrentLevel != -1)
		mpLevels[mCurrentLevel]->cleanup();

	mCurrentLevel++;

	if(mCurrentLevel != -1 && mCurrentLevel < (signed)mpLevels.size())
		mpLevels[mCurrentLevel]->setup();
	else
	{
		gameWon = true;
	}
}

void LevelManager::update(double passedTime)
{
	if (gameWon)
	{
		gpEventSystem->fireEvent(LEVEL_COMPLETE_EVENT);
	}

	int segments = mpLevels[mCurrentLevel]->getSnake()->getNumSegments();
	if(segments >= mpLevels[mCurrentLevel]->getTargetSegments())
	{
		nextLevel();
		return;
	}
	
	if(!mpLevels[mCurrentLevel]->isCurrentSpaceSafe())
	{
		gpEventSystem->fireEvent(LEVEL_FAILED_EVENT);

		//mpLevels[mCurrentLevel]->cleanup();
		//mpLevels[mCurrentLevel]->setup();

		nextLevel();

		return;
	}

	mpLevels[mCurrentLevel]->update(passedTime);
}

void LevelManager::cleanup()
{
	if(mCurrentLevel != -1 && mCurrentLevel < (signed)mpLevels.size())
		mpLevels[mCurrentLevel]->cleanup();

	for(unsigned int i=0; i < mpLevels.size(); i++)
	{
		delete mpLevels[i];
	}
	mpLevels.clear();

	mCurrentLevel = -1;
}

void LevelManager::draw(GraphicsBuffer* targetBuffer)
{
	if(mCurrentLevel != -1 && mCurrentLevel < (signed)mpLevels.size())
		mpLevels[mCurrentLevel]->draw(targetBuffer);
}

void LevelManager::restart()
{
	gameWon = false;
	cleanup();

	vector<std::string> levelFiles = mLevelFiles;
	mLevelFiles.clear();

	for (unsigned int i = 0; i < levelFiles.size(); ++i)
	{
		loadLevel(levelFiles[i], mpHeadAnim, mpResourceManager);
	}

	mCurrentLevel = -1;
	nextLevel();
}
