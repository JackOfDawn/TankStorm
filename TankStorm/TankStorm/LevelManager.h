#pragma once

#include <vector>
#include "EventListener.h"
#include <string>


class ResourceManager;
class Level;
class Snake;
class Unit;
class Animation;
class GraphicsBuffer;

class LevelManager : public EventListener
{
public:
	LevelManager(void);
	virtual ~LevelManager(void);

	void loadLevel(std::string sourcePath, ResourceManager* pResourceManager);
	void nextLevel();
	void restart();
	void update(double passedTime);
	void draw(GraphicsBuffer* targetBuffer);
	void modulateDifficulty(bool harder);

	void cleanup();

	bool gameShouldEnd() { return gameWon; }
	Level* getCurrentLevel();

	virtual inline std::string getClassName( void ) const { return "LevelManager "; }
	virtual void handleEvent( const Event& theEvent );

	void loadSave();
	void save();


private:

	ResourceManager* mpResourceManager;


	bool savedGame;


	std::vector<std::string> mLevelFiles;

	std::vector<Level*> mpLevels;
	Level* mpSavedLevel;


	int	mCurrentLevel;
	bool levelComplete;
	bool gameWon;
	bool levelSetup;
	

	

};

