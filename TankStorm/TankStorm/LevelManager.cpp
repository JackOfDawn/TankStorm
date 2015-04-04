

#include "LevelManager.h"
#include "ResourceManager.h"
#include "Level.h"
#include "Snake.h"
#include "LevelCompleteEvent.h"
#include "LevelFailedEvent.h"
#include "Animation.h"
#include "GraphicsBuffer.h"
#include "GameCompleteEvent.h"

#include <vector>
#include <sstream>
#include <fstream>

using namespace std;


LevelManager::LevelManager(void)
{
	mCurrentLevel = -1;
	gameWon = false;
	levelComplete = false;
	gpEventSystem->addListener(SAVE_GAME_EVENT, this);
	gpEventSystem->addListener(LOAD_GAME_EVENT, this);
	savedGame = false;
	mpSavedLevel = nullptr;
}

LevelManager::~LevelManager(void)
{
	cleanup();
}

void LevelManager::loadLevel(std::string sourcePath, ResourceManager* pResourceManager)
{
	mpResourceManager = pResourceManager;

	int levelNum;
	levelNum = mpLevels.size()+1;

	Level* tempLevel = New Level(levelNum);

	tempLevel->loadFromFile(sourcePath, pResourceManager);

	mLevelFiles.push_back(sourcePath);
	mpLevels.push_back(tempLevel);
}

void LevelManager::nextLevel()
{

	if (mCurrentLevel != -1 && !savedGame)
		mpLevels[mCurrentLevel]->cleanup();
	else if(savedGame)
	{
		mpSavedLevel->cleanup();
		savedGame = false;
	}

	mCurrentLevel++;

	if(mCurrentLevel != -1 && mCurrentLevel < (signed)mpLevels.size())
		mpLevels[mCurrentLevel]->setup();
	else
	{
		gpEventSystem->fireEvent(GameCompleteEvent());
	}
}

void LevelManager::update(double passedTime)
{
	if (gameWon)
	{
		gpEventSystem->fireEvent(LEVEL_COMPLETE_EVENT);
	}
	
	
	if (savedGame)
	{
		if(!mpSavedLevel->getTanksLeft())
		{
			nextLevel();
			return;
		}
		mpSavedLevel->update(passedTime);
	}


	else
	{
		if(!mpLevels[mCurrentLevel]->getTanksLeft())
		{
			nextLevel();
			return;
		}
		mpLevels[mCurrentLevel]->update(passedTime);
	}
}

void LevelManager::cleanup()
{
	//if(mCurrentLevel != -1 && mCurrentLevel < (signed)mpLevels.size())
		//mpLevels[mCurrentLevel]->cleanup();

	for(unsigned int i=0; i < mpLevels.size(); i++)
	{
		delete mpLevels[i];
	}
	mpLevels.clear();

	//clean up savedlevel
	if(mpSavedLevel != nullptr)
	{
		 delete mpSavedLevel; // well shii
		 mpSavedLevel = nullptr;
	}

	

	mCurrentLevel = -1;
}

void LevelManager::draw(GraphicsBuffer* targetBuffer)
{

	if(mCurrentLevel != -1 && mCurrentLevel < (signed)mpLevels.size() && !savedGame)
		mpLevels[mCurrentLevel]->draw(targetBuffer);
	else if (savedGame)
	{
		mpSavedLevel->draw(targetBuffer);
	}
}

void LevelManager::restart()
{
	gameWon = false;
	cleanup();

	vector<std::string> levelFiles = mLevelFiles;
	mLevelFiles.clear();

	for (unsigned int i = 0; i < levelFiles.size(); ++i)
	{
		loadLevel(levelFiles[i], mpResourceManager);
	}

	
	gpGame->resetLives();
	gpGame->resetScore();
	mCurrentLevel = -1;
	nextLevel();
}


void LevelManager::handleEvent(const Event& theEvent)
{
	if(theEvent.getType() == SAVE_GAME_EVENT)
	{
		save();
	}
	else if(theEvent.getType() == LOAD_GAME_EVENT)
	{
		loadSave();
	}
	else
	{
		nextLevel();
	}
}

void LevelManager::save()
{
	ofstream saveFile = ofstream(SAVE_FILE_LEVEL);

	//LevelNumber
	saveFile << mCurrentLevel << endl;

	
	if(!savedGame)
		mpLevels.at(mCurrentLevel)->saveLevel(saveFile);
	else
		mpSavedLevel->saveLevel(saveFile);
	//LevelName
	//saveFile << mpLevels.at(mCurrentLevel)->getLevelName() << endl;

	//player location
	//saveFile << mpLevels
	//number of enemies

	//enemy locations

	//levellayout

	saveFile.close();
}

void LevelManager::loadSave()
{
	ifstream loadfile = ifstream(SAVE_FILE_LEVEL);
	string junk;

	if(mpSavedLevel != nullptr)
		delete mpSavedLevel;

	if(loadfile)
	{
		// level number
		loadfile >> mCurrentLevel;
		getline(loadfile, junk);
		Level* tmpLevel = New Level(mCurrentLevel);
		
		tmpLevel->loadSave(loadfile, mpResourceManager);

		mpSavedLevel = tmpLevel;
		tmpLevel = nullptr;

		savedGame = true;
		mpSavedLevel->setup();

		//call the correct thing to start the level?
	}
}

Level* LevelManager::getCurrentLevel()
{
	if(savedGame)
		return mpSavedLevel;
	return mpLevels[mCurrentLevel];
}

void LevelManager::modulateDifficulty(bool harder)
{
	if (harder)
	{
		if (gpGame->getDiffLevel() >= 3)
		{
			gpGame->setDiffLevel(3);
		}
		else
		{
			gpGame->setDiffLevel(gpGame->getDiffLevel() + 1);
		}
	}
	else
	{
		if (gpGame->getDiffLevel() <= 1)
		{
			gpGame->setDiffLevel(1);
		}
		else
		{
			gpGame->setDiffLevel(gpGame->getDiffLevel() - 1);
		}
	}
}
