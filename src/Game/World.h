#ifndef GAME_WORLD_H
#define GAME_WORLD_H

#include "Location.h"
#include "Actor.h"
#include <vector>

class World
{
	public:
		World();
		virtual ~World();

		void					movePeggy( const string& );
		void					peggyLook();
		Location*			getLocationById( int );

	private:
		Location*			getAdjacentLocation( Location*, const Direction& );
		Direction			getDirection( const string& );

		vector<Location>		locations;
		Actor*							peggy;
};

#endif
