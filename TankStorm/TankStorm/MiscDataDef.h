/*	Author:		Spencer Martin
 *	Class:		EGP 310-02
 *	Assignment:	Midterm, Snake
 *	File:		MiscDataDef.h
 *	Certificate of Authenticity:	I certify that this project is entirely my own work.
 *****************************************************************************************/
#pragma once

#include <string>

const static int DISPLAY_WIDTH = 800;
const static int DISPLAY_HEIGHT = 600;
const static int CELL_DIMENSION = 32;

const static std::string SAVE_FILE_STAT = "../SAVE/gameSaveStat.txt";
const static std::string SAVE_FILE_LEVEL = "../SAVE/gameSaveLevel.txt";

enum CellType
{
	INVALID_CELL_TYPE = -1,
	FLOOR_CELL_TYPE,
	WALL_CELL_TYPE,
	TANK_CELL_TYPE,
	NUM_CELL_TYPES
};


const std::string CELL_TYPES[NUM_CELL_TYPES] =	
{	
	"Floor Cell",
	"Wall Cell",
	"Tank Cell"
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
/*
enum GraphicLabel
{
	NO_APPLICABLE_GRAPHIC = -1,
	LEVEL_FLOOR,					//0
	LEVEL_WALL,						//1
	PLAYER_TANK,					//2
	NUM_GRAPHIC_TILES				//3

};
*/

enum UnitType
{
	PLAYER = 0,
	ENEMY,
	BULLET,
	WALL,
	FLOOR,
	NUM_TYPES
};


const std::string UNIT_TYPES[NUM_TYPES] = 
{
	"PLAYER",
	"ENEMY",
	"BULLET",
	"WALL",
	"FLOOR"
};
