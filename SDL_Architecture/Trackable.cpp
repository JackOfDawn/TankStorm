/*	Author:		Spencer Martin
 *	Class:		EGP 310-02
 *	Assignment:	Midterm, Snake
 *	File:		Trackable.cpp
 *	Certificate of Authenticity:	This file was created with assistance from Stephen Lane-Walsh
 ***************************************************************************************************/

#include "Trackable.h"
#include "MemoryTracker.h"

void* TrackableObject::operator new( std::size_t size )
{
	return malloc(size);
}

void TrackableObject::operator delete( void *ptr )
{
	if (gpMemoryTracker)
		gpMemoryTracker->removeAllocation(ptr);

	free(ptr);
}

void* TrackableObject::operator new[]( std::size_t size )
{
	return malloc(size);
}

void TrackableObject::operator delete[]( void *ptr )
{
	if (gpMemoryTracker)
		gpMemoryTracker->removeAllocation(ptr);

	free(ptr);
}


void* TrackableObject::operator new( std::size_t size, int lineNumber, const char* filename  )
{
	void* ptr = malloc(size);
	gpMemoryTracker->addAllocation( (TrackableObject*)ptr, size, lineNumber, filename );
	return ptr;
}

void* TrackableObject::operator new[]( std::size_t size, int lineNumber, const char* filename  )
{
	void* ptr = malloc(size);
	gpMemoryTracker->addAllocation( (TrackableObject*)ptr, size, lineNumber, filename );
	return ptr;
}