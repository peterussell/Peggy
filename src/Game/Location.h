#ifndef _PEGGY_GAME_LOCATION_H
#define _PEGGY_GAME_LOCATION_H

#include "Item.h"
#include "LocationItems.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

enum Direction {
	NORTH,
	EAST,
	SOUTH,
	WEST,
	INVALID
};

class World;

class Location
{
	friend ostream& operator<<( ostream&, const Location& );

	public:
		/* Creates a new location.
		 * Parameters: ID, Name, Exits to adjacent rooms (north, east, south, west)
		 */
		Location( World& w,
							int i,
							const string& n,
							int dn=-1,
							int de=-1,
							int ds=-1,
							int dw=-1
							);

	Location( const Location& );
	
	Location&
	operator=( const Location& );

	virtual ~Location() { }

		void printName();

		/* Description accessors */
		void setDescription( const string& );
		string getDescription();

		/* Takes a direction and returns the ID of the adjacent Location in
		 * that direction, or -1 if no adjacent location exists. */
		int getAdjacentLocationId( const Direction& );

		void addItem( const Item& );
		void removeItem( const string& someIdentifier, Item& removedItem );
		void printAllItems();
		void printExits();

	private:
		int								id;
		string						name;
		string						description;
		int 							north, east, south, west;
		LocationItems			items;
		World&						world;
};

#endif
