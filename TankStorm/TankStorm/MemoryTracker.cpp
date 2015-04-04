/*	Author:		Spencer Martin
 *	Class:		EGP 310-02
 *	Assignment:	Midterm, Snake
 *	File:		MemoryTracker.cpp
 *	Certificate of Authenticity:	This file was created with assistance from Stephen Lane-Walsh
 ***************************************************************************************************/


#include <iostream>
#include "MemoryTracker.h"
#include "Trackable.h"
#include <string>
#include "FunctionsUtil.h"

using namespace std;

int MemoryTracker::msAllocationNum = 0;
MemoryTracker* gpMemoryTracker = nullptr;

MemoryTracker::MemoryTracker()
{
}

MemoryTracker::~MemoryTracker()
{
}

void MemoryTracker::addAllocation( TrackableObject* ptr, size_t size, int lineNum, const char* filename )
{
	//make sure it's not already in the map
	auto iter = mAllocations.find( ptr );
	if( iter != mAllocations.end() )
	{
		//already exists - problem!
	}
	else
	{
		AllocationRecord theRec( msAllocationNum, size, lineNum, string(filename) );
		pair<TrackableObject*,AllocationRecord> thePair(ptr,theRec);
		mAllocations.insert( thePair );
		msAllocationNum++;
	}
}

void MemoryTracker::removeAllocation( void* ptr )
{
	//find it in the map!
	auto iter = mAllocations.find( (TrackableObject*)ptr );
	if( iter == mAllocations.end() )
	{
		//problem!!!!
	}
	else
	{
		mAllocations.erase( iter );
	}
}

void MemoryTracker::reportAllocations( std::ostream& stream )
{
	stream << "Current memory allocations:\n";

	for(auto iter = mAllocations.begin(); iter != mAllocations.end(); ++iter )
	{
		stream << "name: " << iter->first->getClassName() << "address:" << iter->first << " size:" << iter->second.size << " num:" << iter->second.num << " file name:" << Basename(iter->second.filename) << " line number:" << iter->second.lineNum << endl;
	}
}

int MemoryTracker::getNumAllocations()
{
	return mAllocations.size();
}
