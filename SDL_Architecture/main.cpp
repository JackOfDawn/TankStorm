#include <iostream>
#include "PerformanceTracker.h"
#include "MemoryTracker.h"
#include "ResourceManager.h"
#include "GraphicsBuffer.h"
#include "Sprite.h"
#include "Animation.h"
#include "GraphicsSystem.h"
#include "Game.h"
#include "MiscDataDef.h"
#include "UnitManager.h"

using namespace std;

Game* gpGame = NULL;
Timer* mpTimer = NULL;
UnitManager* gpUnitManager = NULL;

int main(int argc, char* argv[])
{
	gpMemoryTracker = new MemoryTracker();

	PerformanceTracker* pPerformanceTracker = New PerformanceTracker;
	pPerformanceTracker->startTracking("init");

	gpEventSystem = New EventSystem();
	gpGame = New Game();

	if(!gpGame->init(DISPLAY_WIDTH, DISPLAY_HEIGHT))
	{
		cout << "\nFailed to init Game\n";
		system("PAUSE");
		return 0;
	}

	gpGame->runLoop();

	delete gpUnitManager;
	delete pPerformanceTracker;
	delete gpGame;	
	delete gpEventSystem;
	delete mpTimer;

	if (gpMemoryTracker->getNumAllocations() > 0)
	{
		gpMemoryTracker->reportAllocations(std::cout);
		system("PAUSE");
	}

	delete gpMemoryTracker;

	return 0;
}