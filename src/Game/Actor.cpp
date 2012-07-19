#include "Actor.h"
#include <iostream>
using namespace std;

Actor::Actor(
	const string& n,
	Location& l
)
:	name( n ), 
	currentLocation( &l )
{
	cout << "My name is " << name << " and I am in ";
	currentLocation->printName();
}

Actor::~Actor()
{
}

Location*
Actor::getCurrentLocation()
{
	if( currentLocation ) {
		return currentLocation;
	} else {
		return NULL;
	}
}

void
Actor::setCurrentLocation( Location* newLoc )
{
	//todo: error checking when we get == operators etc.
	currentLocation = newLoc;
	cout << "Peggy is now at the ";
	currentLocation->printName();
}

void
Actor::printCurrentLocation()
{
	currentLocation->printName();
}

void
Actor::look()
{
	currentLocation->printExits();
	currentLocation->printAllItems();
}
