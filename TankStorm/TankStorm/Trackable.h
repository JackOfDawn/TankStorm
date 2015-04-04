/*	Author:		Spencer Martin
 *	Class:		EGP 310-02
 *	Assignment:	Midterm, Snake
 *	File:		Trackable.h
 *	Certificate of Authenticity:	This file was created with assistance from Stephen Lane-Walsh
 ***************************************************************************************************/
#pragma once

#include <iostream>
#include <string>

class TrackableObject
{
public:
	//dean's
	void* operator new( std::size_t size );
	void operator delete( void *ptr );	
	void* operator new[]( std::size_t size );
	void operator delete[]( void *ptr );

	//new
	void* operator new( std::size_t size, int lineNumber, const char* filename );
	inline void operator delete( void *ptr, int lineNumber, const char* filename  ){::operator delete(ptr);}	
	void* operator new[]( std::size_t size, int lineNumber, const char* filename  );
	inline void operator delete[]( void *ptr, int lineNumber, const char* filename  ){::operator delete[](ptr);}

	virtual std::string getClassName( void ) const = 0;

#define New new(__LINE__, __FILE__)

};
