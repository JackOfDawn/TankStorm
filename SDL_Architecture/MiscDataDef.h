/*	Author:		Spencer Martin
 *	Class:		EGP 310-02
 *	Assignment:	Midterm, Snake
 *	File:		MiscDataDef.h
 *	Certificate of Authenticity:	I certify that this project is entirely my own work.
 *****************************************************************************************/
#pragma once

#include <string>

const static int DISPLAY_WIDTH = 960;
const static int DISPLAY_HEIGHT = 540;
const static int CELL_DIMENSION = 30;

enum CellType
{
	INVALID_CELL_TYPE = -1,
	FLOOR_CELL_TYPE,
	HEAD_CELL_TYPE,
	BODY_CELL_TYPE,
	WALL_CELL_TYPE,
	FOOD_CELL_TYPE,
	SLOW_CELL_TYPE,
	SPEED_CELL_TYPE,
	NUM_CELL_TYPES
};

const std::string CELL_TYPES[NUM_CELL_TYPES] =	
{	
	"Floor Cell",
	"Head Cell",
	"Body Cell",
	"Wall Cell",
	"Food Cell",
	"Slow Cell",
	"Speed Cell"
};

enum Direction
{
	IMMOBILE = -1,
	DIRECTION_UP, 
	DIRECTION_DOWN,
	DIRECTION_LEFT, 
	DIRECTION_RIGHT,
	NUM_DIRECTIONS
};

const std::string DIRECTION_TYPES[NUM_DIRECTIONS] =	
{	
	"Up",
	"Down",
	"Left",
	"Right"
};

enum GraphicLabel
{
	NO_APPLICABLE_GRAPHIC = -1,
	SNAKE_BODY,						//0
	SNAKE_HEAD,						//1
	SNAKE_BASIC_FOOD,				//2
	SPEED_UP_FOOD,					//3
	SLOW_DOWN_FOOD,					//4
	FLOOR_GRAPHIC,					//5
	WALL_GRAPHIC,					//6
	NUM_GRAPHIC_TILES				//7

};