/*
	Author:		Spencer Martin
	Assignment: midterm
	Due Date:	2/7/14

	Certificate of Authenticity: I certify that, with the exception of where noted, 
								 this project is my own work.

	Purpose:	These are the function definitions for InputManager.
*/


#include <SDL.h>
#include "Game.h"
#include "InputManager.h"
#include "MiscDataDef.h"
#include "UpPressedEvent.h"
#include "DownPressedEvent.h"
#include "LeftPressedEvent.h"
#include "RightPressedEvent.h"
#include "SpacePressedEvent.h"
#include "EscPressedEvent.h"
#include "MouseMoveEvent.h"
#include "ToggleOptionsEvent.h"
#include "ToggleMusicEvent.h"
#include "EnterPressedEvent.h"
#include "LoadGameEvent.h"
#include "SaveGameEvent.h"
#include "MouseLeftClickEvent.h"
#include "IncreaseMusicVolumeEvent.h"
#include "DecreaseMusicVolumeEvent.h"
#include "DeactivateSoundEffectsEvent.h"
#include "ActivateSoundEffectsEvent.h"
#include "DecreaseDifficultyEvent.h"
#include "IncreaseDifficultyEvent.h"



InputManager::InputManager()
{
	mEscKey		= false;
	mSpaceKey	= false;
	mWKey		= false;
	mSKey		= false;
	mAKey		= false;
	mDKey		= false;
	mMKey		= false;
	mOKey		= false;
	mLKey		= false;
	mF5Key		= false;
	mTKey		= false;
	mYKey		= false;
	mGKey		= false;
	mHKey		= false;
	mBKey		= false;
	mNKey		= false;
}


InputManager::~InputManager()
{
	uninstaller();
	
}

int InputManager::init()
{
	return 0;
}

void InputManager::uninstaller()
{

}

void InputManager::update()
{
	bool oldEscKey		= mEscKey,
		 oldSpaceKey	= mSpaceKey,
		 oldEnterKey	= mEnterKey,
		 oldAKey		= mAKey,
		 oldDKey		= mDKey,
		 oldWKey		= mWKey,
		 oldSKey		= mSKey,
		 oldMKey		= mMKey,
		 oldOKey		= mOKey,
		 oldLKey		= mLKey,
		 oldTKey		= mTKey,
		 oldYKey		= mYKey,
		 oldGKey		= mGKey,
		 oldHKey		= mHKey,
		 oldLeftButton	= mLeftButton,
		 oldF5Key		= mF5Key,
	     oldBKey		= mBKey,
		 oldNKey		= mNKey;
	
	SDL_PumpEvents();

	const Uint8* pKeyboardState = SDL_GetKeyboardState( nullptr );

	mWKey =		( pKeyboardState[SDL_SCANCODE_W]     == 1 );
	mSKey =		( pKeyboardState[SDL_SCANCODE_S]   == 1 );
	mAKey =		( pKeyboardState[SDL_SCANCODE_A]   == 1 );
	mDKey =		( pKeyboardState[SDL_SCANCODE_D]  == 1 );
	mEscKey =   ( pKeyboardState[SDL_SCANCODE_ESCAPE] == 1 );
	mSpaceKey = ( pKeyboardState[SDL_SCANCODE_SPACE]  == 1 );
	mEnterKey = ( pKeyboardState[SDL_SCANCODE_RETURN]  == 1 );
	mMKey =		( pKeyboardState[SDL_SCANCODE_M] == 1);
	mOKey =		( pKeyboardState[SDL_SCANCODE_O] == 1);
	mLKey =		( pKeyboardState[SDL_SCANCODE_L] == 1);
	mTKey =		( pKeyboardState[SDL_SCANCODE_T] == 1);
	mYKey =		( pKeyboardState[SDL_SCANCODE_Y] == 1);
	mGKey =		( pKeyboardState[SDL_SCANCODE_G] == 1);
	mHKey =		( pKeyboardState[SDL_SCANCODE_H] == 1);
	mF5Key =	( pKeyboardState[SDL_SCANCODE_F5] == 1);
	mBKey =		( pKeyboardState[SDL_SCANCODE_B] == 1);
	mNKey =		( pKeyboardState[SDL_SCANCODE_N] == 1);

	handleMouseButtons();
	
	int mouseX = 0, mouseY = 0;
	const Uint32 mouseState = SDL_GetMouseState(&mouseX, &mouseY);
	
	if (mEscKey && !oldEscKey)
	{
		if(!gpGame->getStart() && !gpGame->getStartOptions() && !gpGame->getWin() && !gpGame->getLose() && !gpGame->getOptions())
			gpEventSystem->fireEvent(SaveGameEvent());

		gpEventSystem->fireEvent(EscPressedEvent());

	}

	if (gpGame->getStart())
	{
		if (mOKey && !oldOKey)
		{
			gpEventSystem->fireEvent(ToggleOptionsEvent());
		}	
		if (mEnterKey && !oldEnterKey)
		{
			gpEventSystem->fireEvent(EnterPressedEvent());
		}
		if (mLKey && !oldLKey)
		{
			gpEventSystem->fireEvent(LoadGameEvent());
		}
	}

	else if (gpGame->getStartOptions())
	{
		if (mOKey && !oldOKey)
		{
			gpEventSystem->fireEvent(ToggleOptionsEvent());
		}

		if (mTKey && !oldTKey)
		{
			gpEventSystem->fireEvent(DecreaseMusicVolumeEvent());
		}
		
		if (mYKey && !oldYKey)
		{
			gpEventSystem->fireEvent(IncreaseMusicVolumeEvent());
		}

		if (mMKey && !oldMKey)
		{
			gpEventSystem->fireEvent(ToggleMusicEvent());
		}

		if (mGKey && !oldGKey)
		{
			gpEventSystem->fireEvent(DeactivateSoundEffectsEvent());
		}

		if (mHKey && !oldHKey)
		{
			gpEventSystem->fireEvent(ActivateSoundEffectsEvent());
		}

		if (mBKey && !oldBKey)
		{
			gpEventSystem->fireEvent(DecreaseDifficultyEvent());
		}

		if (mNKey && !oldNKey)
		{
			gpEventSystem->fireEvent(IncreaseDifficultyEvent());
		}
	}

	else if (gpGame->getWin())
	{
		if (mLKey && !oldLKey)
		{
			gpEventSystem->fireEvent(LoadGameEvent());
		}

		if (mEnterKey && !oldEnterKey)
		{
			gpEventSystem->fireEvent(EnterPressedEvent());
		}
	}

	else if (gpGame->getLose())
	{
		if (mLKey && !oldLKey)
		{
			gpEventSystem->fireEvent(LoadGameEvent());
		}
		
		if (mEnterKey && !oldEnterKey)
		{
			gpEventSystem->fireEvent(EnterPressedEvent());
		}
	}

	else if (gpGame->getOptions())
	{
		if (mOKey && !oldOKey)
		{
			gpEventSystem->fireEvent(ToggleOptionsEvent());
		}

		if(mF5Key && !oldF5Key)
		{
			gpEventSystem->fireEvent(SaveGameEvent());
		}

		if (mTKey && !oldTKey)
		{
			gpEventSystem->fireEvent(DecreaseMusicVolumeEvent());
		}
		
		if (mYKey && !oldYKey)
		{
			gpEventSystem->fireEvent(IncreaseMusicVolumeEvent());
		}

		if (mMKey && !oldMKey)
		{
			gpEventSystem->fireEvent(ToggleMusicEvent());
		}

		if (mGKey && !oldGKey)
		{
			gpEventSystem->fireEvent(DeactivateSoundEffectsEvent());
		}

		if (mHKey && !oldHKey)
		{
			gpEventSystem->fireEvent(ActivateSoundEffectsEvent());
		}
	}

	else
	{
		if (mSpaceKey && !oldSpaceKey)
		{
			gpEventSystem->fireEvent(SpacePressedEvent());
		}

		if (mAKey)
		{
			gpEventSystem->fireEvent(LeftPressedEvent());
		}

		if (mDKey)
		{
			gpEventSystem->fireEvent(RightPressedEvent());
		}

		if (mWKey)
		{
			gpEventSystem->fireEvent(UpPressedEvent());
		}

		if (mSKey)
		{
			gpEventSystem->fireEvent(DownPressedEvent());
		}

		if (mMKey && !oldMKey)
		{
			gpEventSystem->fireEvent(ToggleMusicEvent());
		}

		if (mOKey && !oldOKey)
		{
			gpEventSystem->fireEvent(ToggleOptionsEvent());
		}	

		if(mLeftButton && !oldLeftButton)
		{
			//cout << "CLICK";
			gpEventSystem->fireEvent(MouseLeftClickEvent());
		}
		
		if(mF5Key && !oldF5Key)
		{
			gpEventSystem->fireEvent(SaveGameEvent());
		}
	}

	gpEventSystem->fireEvent(MouseMovedEvent(mouseX, mouseY));
}

void InputManager::handleMouseButtons()
{
	if(SDL_GetMouseState(nullptr, nullptr) & SDL_BUTTON(1) && !mLeftButton) //Left Click
	{
		mLeftButton = true;
	}
	else if(!SDL_GetMouseState(nullptr, nullptr) & SDL_BUTTON(1) && mLeftButton)
	{
		mLeftButton = false;
	}
}





