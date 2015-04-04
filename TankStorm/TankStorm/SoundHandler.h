#ifndef SOUND_HANDLER
#define SOUND_HANDLER

#include "EventListener.h"
#include <SDL_mixer.h>

class SoundHandler : public EventListener
{
public:
	SoundHandler();
	~SoundHandler();

	void checkForGameLoop();
	void loadAssets();
	void increaseVolume();
	void decreaseVolume();
	void toggleSoundEffects();

	void playSound(int which);

private:
	bool			loopingGame,
					soundEffects;

	Mix_Music*		mBackgroundLoop;
//	Mix_Music*		mMovingTank;
	Mix_Chunk*		mBulletFire;
	Mix_Chunk*		mExplosion_1;
	int				volumeLevel;



	virtual void handleEvent( const Event& theEvent );
	virtual inline std::string getClassName( void ) const { return "SoundHandler "; }
};






#endif