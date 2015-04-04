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

Game* gpGame = nullptr;
Timer* mpTimer = nullptr;
UnitManager* gpUnitManager = nullptr;

int main(int argc, char* argv[])
{
	gpMemoryTracker = new MemoryTracker();

	PerformanceTracker* pPerformanceTracker = New PerformanceTracker;
	pPerformanceTracker->startTracking("init");

	gpEventSystem = New EventSystem();
		if(gpEventSystem!=nullptr)
			cout << "EventSystem instantiated\n";
	gpGame = New Game();
		if(gpEventSystem!=nullptr)
			cout << "Game instantiated\n";

	if(!gpGame->init(DISPLAY_WIDTH, DISPLAY_HEIGHT))
	{
		cout << "\nFailed to init Game\n";
		system("PAUSE");
		return 0;
	}
	else
		cout << "Game initialized\n";

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