/*
	Author:		Spencer Martin
	Assignment: midterm
	Due Date:	2/7/14

	Certificate of Authenticity: I certify that, with the exception of where noted, 
								 this project is my own work.

	Purpose:	These are the function definitions for InputManager.
*/


#include <SDL.h>
#include "InputManager.h"
#include "MiscDataDef.h"
#include "UpPressedEvent.h"
#include "DownPressedEvent.h"
#include "LeftPressedEvent.h"
#include "RightPressedEvent.h"
#include "SpacePressedEvent.h"
#include "EscPressedEvent.h"


InputManager::InputManager()
{
	mEscKey		= false;
	mSpaceKey	= false;
	mUpKey		= false;
	mDownKey	= false;
	mLeftKey	= false;
	mRightKey	= false;
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
	bool oldEscKey = mEscKey,
		 oldLeftKey = mLeftKey,
		 oldRightKey = mRightKey,
		 oldUpKey = mUpKey,
		 oldDownKey = mDownKey,
		 oldSpaceKey = mSpaceKey;

	SDL_PumpEvents();

	const Uint8* pKeyboardState = SDL_GetKeyboardState( NULL );

	mUpKey =    ( pKeyboardState[SDL_SCANCODE_UP]     == 1 );
	mDownKey =  ( pKeyboardState[SDL_SCANCODE_DOWN]   == 1 );
	mLeftKey =  ( pKeyboardState[SDL_SCANCODE_LEFT]   == 1 );
	mRightKey = ( pKeyboardState[SDL_SCANCODE_RIGHT]  == 1 );
	mEscKey =   ( pKeyboardState[SDL_SCANCODE_ESCAPE] == 1 );
	mSpaceKey = ( pKeyboardState[SDL_SCANCODE_SPACE]  == 1 );



	if (mEscKey && !oldEscKey)
	{
		gpEventSystem->fireEvent(EscPressedEvent());
	}

	if (mSpaceKey && !oldSpaceKey)
	{
		gpEventSystem->fireEvent(SpacePressedEvent());
	}

	if (mLeftKey && !oldLeftKey)
	{
		gpEventSystem->fireEvent(LeftPressedEvent());
	}

	if (mRightKey && !oldRightKey)
	{
		gpEventSystem->fireEvent(RightPressedEvent());
	}

	if (mUpKey && !oldUpKey)
	{
		gpEventSystem->fireEvent(UpPressedEvent());
	}

	if (mDownKey && !oldDownKey)
	{
		gpEventSystem->fireEvent(DownPressedEvent());
	}
}







