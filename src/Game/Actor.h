#ifndef GAME_ACTOR_H
#define GAME_ACTOR_H

#include "Location.h"
#include "Item.h"

#include <string.h>
#include <vector>

class Actor
{
	public:
		Actor( const string&, Location& );
		~Actor();

		Location* 		getCurrentLocation();
		void 					setCurrentLocation( Location* );
		void 					printCurrentLocation();
		void					look();
		void					printInventory();
		void					addToInventory( const Item& );
		void					removeFromInventory( const size_t );

	private:
		string				name;
		Location*			currentLocation;
		vector<Item>	inventory;
};

#endif
