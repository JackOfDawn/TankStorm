/*	Author:		Spencer Martin
 *	Class:		EGP 310-02
 *	Assignment:	Midterm, Snake
 *	File:		MiscDataDef.h
 *	Certificate of Authenticity:	I certify that this project is entirely my own work.
 *****************************************************************************************/

#include <string>
#include <vector>

using namespace std;

enum CellType
{
	INVALID_CELL_TYPE = -1,
	HEAD_CELL_TYPE,
	BODY_CELL_TYPE,
	TAIL_CELL_TYPE,
	WALL_CELL_TYPE,
	FOOD_CELL_TYPE,
	MOD_CELL_TYPE,
	NUM_CELL_TYPES
};

const std::string CELL_TYPES[NUM_CELL_TYPES] =	
{	
	"Head Cell",
	"Body Cell",
	"Tail Cell",
	"Wall Cell",
	"Food Cell",
	"Modification Cell"
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

//part of the memory tracking Stephen helped with

vector<string> StringSplit( const string& str, const string& sep, const int& limit = -1  )
{
	vector<string> stringParts;

	unsigned int lastEnd = 0;
	for (unsigned int i = 0; i < str.length(); ++i)
	{
		bool check = true;
		for (unsigned int j = 0; j < sep.length(); ++j)
		{
			if (str[i + j] != sep[j])
			{
				check = false;
				break;
			}
		}

		if (check)
		{
			if (limit != -1 && stringParts.size() >= (unsigned)limit - 1)
				break;

			stringParts.push_back(str.substr(lastEnd, i - lastEnd));
			lastEnd = i + sep.length();
		}
	}

	if (lastEnd < str.length())
	{
		stringParts.push_back(str.substr(lastEnd));
	}

	return stringParts;
}

inline string Basename( const string& path )
{
	string splitString = (path.find("\\") != string::npos ? "\\" : "/");

	vector<string> parts = StringSplit(path, splitString);

	if (parts.size() == 0)
		return "";

	return parts[parts.size() - 1];
}
