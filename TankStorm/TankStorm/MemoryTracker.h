/*	Author:		Spencer Martin
 *	Class:		EGP 310-02
 *	Assignment:	Midterm, Snake
 *	File:		MemoryTracker.h
 *	Certificate of Authenticity:	This file was created with assistance from Stephen Lane-Walsh
 ***************************************************************************************************/

#pragma once

#include <map>
#include <iostream>


struct AllocationRecord
{
	AllocationRecord( int theNum, size_t theSize, int theLineNum, std::string theFilename ): num(theNum), size(theSize), lineNum(theLineNum), filename(theFilename){};
	int num,
		lineNum;
	std::string filename;
	size_t size;
};

class TrackableObject;

class MemoryTracker
{
public:
	MemoryTracker();
	~MemoryTracker();

	void addAllocation( TrackableObject* ptr, size_t size, int lineNum, const char* filename );
	void removeAllocation( void* ptr );
	
	void reportAllocations( std::ostream& stream );

	int getNumAllocations();

private:
	//copying not allowed
	MemoryTracker( const MemoryTracker& );
	MemoryTracker& operator=( const MemoryTracker& );
	std::map<TrackableObject*,AllocationRecord> mAllocations;

	static int msAllocationNum;
};

extern MemoryTracker* gpMemoryTracker;