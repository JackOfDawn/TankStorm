/*
	Author:		Spencer Martin
	Assignment: midterm
	Due Date:	2/7/14

	Certificate of Authenticity: I certify that, with the exception of where noted, 
								 this project is my own work.

	Purpose:	This is a the header for the InputManager that processes the given types of input.
*/

#pragma once

#include <iostream>
#include <map>
#include "Trackable.h"
#include "EventSystem.h"


class Event;

class InputManager : public TrackableObject
{
public:
	InputManager();
	virtual ~InputManager();

	int  init();
	void uninstaller();

	void update();

	virtual inline string getClassName( void ) const { return "Input Manager "; }

private:
	bool mEscKey,
		 mSpaceKey,
		 mEnterKey,
		 mWKey,
		 mSKey,
		 mAKey,
		 mDKey,
		 mMKey,
		 mOKey,
		 mLKey,
		 mTKey,
		 mYKey,
		 mGKey,
		 mHKey,
		 mBKey,
		 mNKey,
		 mLeftButton,
		 mF5Key;

	void handleMouseButtons();
};


