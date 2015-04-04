#include "SoundHandler.h"
#include "Event.h"
#include "Game.h"

SoundHandler::SoundHandler()
{
	mBackgroundLoop = nullptr;
//	mMovingTank = NULL;
	mBulletFire = nullptr;
	mExplosion_1 = nullptr;

	volumeLevel = 128;
}

SoundHandler::~SoundHandler()
{
	Mix_HaltMusic();
	Mix_FreeChunk(mBulletFire);
	Mix_FreeChunk(mExplosion_1);
	Mix_FreeMusic(mBackgroundLoop);
//	Mix_FreeMusic(mMovingTank);
}

void SoundHandler::playSound(int which)
{

}

void SoundHandler::handleEvent( const Event& theEvent )
{
	checkForGameLoop();
	
	if (theEvent.getType() == TOGGLE_MUSIC_EVENT)
	{
		if( Mix_PlayingMusic() == 0 ) 
		{ 
			Mix_PlayMusic( mBackgroundLoop, -1 ); 
		} 
		else 
		{ 
			if( Mix_PausedMusic() == 1 )
			{ 
				Mix_ResumeMusic(); 
			} 
			else 
			{ 
				Mix_PauseMusic(); 
			} 
		} 
	}
	
	
	if (loopingGame && soundEffects && theEvent.getType() == FIRED_EVENT )
	{
		Mix_PlayChannel( -1, mBulletFire, 0 );
	}

	if (loopingGame && soundEffects && theEvent.getType() == TANK_DESTROYED_EVENT)
	{
		Mix_PlayChannel( -1, mExplosion_1, 0);
	}

	if(theEvent.getType() == VOLUME_INCREASE_EVENT)
	{
		increaseVolume();
	}

	if(theEvent.getType() == VOLUME_DECREASE_EVENT)
	{
		decreaseVolume();
	}

	if (theEvent.getType() == ACTIVATE_SE_EVENT)
	{
		soundEffects = true;
	}

	if (theEvent.getType() == DEACTIVATE_SE_EVENT)
	{
		soundEffects = false;
	}
}

void SoundHandler::checkForGameLoop()
{
	if(gpGame->getStart())
		loopingGame = false;
	else if (gpGame->getStartOptions())
		loopingGame = false;
	else if (gpGame->getWin())
		loopingGame = false;
	else if (gpGame->getLose())
		loopingGame = false;
	else
		loopingGame = true;
}


void SoundHandler::loadAssets()
{
	mBackgroundLoop = Mix_LoadMUS("../ASSETS/sounds/Level_Music.mp3");
	if( mBackgroundLoop == nullptr ) 
	{ 
		printf( "Failed to load background music! SDL_mixer Error: %s\n", Mix_GetError() ); 
	}
	//mMovingTank = Mix_LoadMUS("../ASSETS/sounds/Tank_Movement.mp3");
	//if( mMovingTank == NULL ) 
	//{ 
	//	printf( "Failed to load tank movement sounds! SDL_mixer Error: %s\n", Mix_GetError() ); 
	//}
	mBulletFire = Mix_LoadWAV("../ASSETS/sounds/Cannon_Shot.wav");
	if( mBulletFire == nullptr ) 
	{ 
		printf( "Failed to load bullet sound effect! SDL_mixer Error: %s\n", Mix_GetError() ); 
	}
	mExplosion_1 = Mix_LoadWAV("../ASSETS/sounds/Explosion_1.wav");
	if( mExplosion_1 == nullptr ) 
	{ 
		printf( "Failed to load explosion_1 sound effect! SDL_mixer Error: %s\n", Mix_GetError() ); 
	}
}

void SoundHandler::increaseVolume()
{
	if(volumeLevel >= 128)
	{
		volumeLevel = 128;
		return;
	}
	else
		volumeLevel += 8;

	Mix_VolumeMusic(volumeLevel);
}

void SoundHandler::decreaseVolume()
{
	if(volumeLevel <= 0)
	{
		volumeLevel = 0;
		return;
	}
	else
		volumeLevel -= 8;

	Mix_VolumeMusic(volumeLevel);
}

void SoundHandler::toggleSoundEffects()
{

	soundEffects = !soundEffects;

}