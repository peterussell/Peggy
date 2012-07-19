#ifndef GAME_ACTOR_H
#define GAME_ACTOR_H

#include "Location.h"
#include <string.h>

class Actor
{
	public:
		Actor( const string&, Location& );
		~Actor();

		Location* 		getCurrentLocation();
		void 					setCurrentLocation( Location* );
		void 					printCurrentLocation();
		void					look();

	private:
		string			name;
		Location*		currentLocation;
};

#endif
