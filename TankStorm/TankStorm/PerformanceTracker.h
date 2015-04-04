#pragma once

#include "Trackable.h"
#include "Timer.h"

#include <map>
#include <string>

class PerformanceTracker: public TrackableObject
{
public:
	PerformanceTracker();
	~PerformanceTracker();

	void startTracking( const std::string& trackerName );
	void stopTracking( const std::string& trackerName );
	double getElapsedTime( const std::string& trackerName );
	void removeTracker( const std::string& trackerName );
	void clearTracker( const std::string& trackerName );

	virtual inline std::string getClassName( void ) const { return "Performance Tracker"; }


private:
	std::map<std::string,Timer*> mTimers;
};

