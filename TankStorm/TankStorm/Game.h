#pragma once

#include "Trackable.h"
#include "ResourceManager.h"
#include "EventListener.h"
#include "InputManager.h"
#include "Timer.h"
#include "Font.h"
#include <SDL_mixer.h>
#include <sstream>


class UnitManager;
class Vector2D;
class LevelManager;
class GraphicsSystem;
class SoundHandler;

class Game :
	public EventListener
{
public:
	Game(void);
	virtual ~Game(void);

	bool init(int width, int height);
	void cleanup();
	void runLoop();
	int getDiffLevel();
	void setLevelName(string name);

	inline ResourceManager* accessResourceManager() const {return mpResourceManager;}
	inline void addPoints(int points) {mScore+=points;}
	inline void setBonus(int bonus) {mBonus = bonus;}
	inline void resetLives() {mLives = 2;}
	inline void resetScore() {mScore = 0;}
	inline int getScore() const {return mScore;}
	inline bool getStart() const {return mStart;}
	inline bool getStartOptions() const {return mStartOptions;}
	inline bool getWin() const {return mWin;}
	inline bool getLose() const {return mLose;}
	inline bool getOptions() const {return mGameOptions;}
	inline void setDiffLevel(int newDiff) {mDifficultyLevel = newDiff;}

	virtual void handleEvent( const Event& theEvent );
	virtual inline string getClassName( void ) const { cout << mScore << endl; return "Game"; }

	void saveStats();
	void loadStats();

private:
	GraphicsSystem*		mpGraphicsSystem;
	GraphicsBuffer*		mpStartScreen;
	GraphicsBuffer*		mpStartOptions;
	GraphicsBuffer*		mpHUD;
	GraphicsBuffer*		mpGameOptions;
	GraphicsBuffer*		mpWinScreen;
	GraphicsBuffer*		mpLoseScreen;
	ResourceManager*	mpResourceManager;
	InputManager*		mpInputManager;
	LevelManager*		mpLevelManager;
	Font*				mpFont;
	Color				mpColor;
	Vector2D			mHUDLoc,
						mScoreLoc,
						mBonusLoc,
						mLevelNameLoc,
						mLivesLoc,
						mOriginPoint;
	bool				mKeepLooping,
						mNeedClean,
						mStart,
						mStartOptions,
						mWin,
						mLose,
						mGameOptions;
	int					mScore,
						mLives,
						mBonus,
						mDifficultyLevel;
	string				mScoreString,
						mLevelNameString,
						mBonusString,
						mLivesString;
	SoundHandler*		mpSoundHandler;

	//Mix_Music*			mBackgroundLoop;
	//Mix_Music*			mMovingTank;
	//Mix_Chunk*			mBulletFire;
	//Mix_Chunk*			mExplosion_1;

	//init functions
	void setupDependencies();

	//loop functions
	void update(double frameTime);
	void draw();


};

extern Game* gpGame;
extern Timer* mpTimer;