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

	// tmp
	Item i = Item( 42, "item", "Peggy's Other Item", "This is a description of Peggy's Item" );

	addToInventory( i );
	printInventory();

	// end tmp

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

void
Actor::printInventory()
{
	if( inventory.size() <= 0 ) {
		cout << "Your inventory is empty" << endl;
	}

	cout << "Inventory" << endl;

	int count = 1;
	for( vector<Item>::iterator it = inventory.begin(); it != inventory.end(); ++it ) {

		cout << count++ << ". ";
		it->printName();
		cout << "   ";
		it->printDescription();
		cout << endl;
	}
}

void
Actor::addToInventory( const Item& item )
{
	inventory.push_back( item );
}

void
Actor::removeFromInventory( const size_t id )
{
	/* TODO:
			Find the item in the inventory vector and remove it.
			Update this function to return the item we've just removed.
	*/
}
