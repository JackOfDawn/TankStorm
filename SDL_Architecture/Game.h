#pragma once

#include "Trackable.h"
#include "ResourceManager.h"
#include "EventListener.h"
#include "InputManager.h"
#include "Timer.h"
#include "Font.h"
#include <sstream>

class UnitManager;
class Vector2D;
class LevelManager;
class GraphicsSystem;

class Game :
	public EventListener
{
public:
	Game(void);
	virtual ~Game(void);

	bool init(int width, int height);
	void cleanup();
	void runLoop();
	inline ResourceManager* accessResourceManager() const {return mpResourceManager;}
	inline void addPoints(int points) {mScore+=points;}
	inline int getScore() const {return mScore;}

	virtual void handleEvent( const Event& theEvent );
	virtual inline string getClassName( void ) const { cout << mScore << endl; return "Game"; }

private:
	GraphicsSystem*		mpGraphicsSystem;
	GraphicsBuffer*		mpStartScreen;
	GraphicsBuffer*		mpWinScreen;
	GraphicsBuffer*		mpLoseScreen;
	ResourceManager*	mpResourceManager;
	InputManager*		mpInputManager;
	LevelManager*		mpLevelManager;
	Font*				mpFont;
	Color				mpColor;
	Vector2D			mHUDLoc,
						mOriginPoint;
	bool				mKeepLooping,
						mNeedClean,
						mStart,
						mWin,
						mLose;
	int					mScore;
	string				mScoreString;

	//init functions
	void setupDependencies();

	//loop functions
	void update(double frameTime);
	void draw();
};

extern Game* gpGame;
extern Timer* mpTimer;