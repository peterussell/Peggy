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
	Item i = Item( 43, "item43", "Peggy's Item 43", "This is a description of Peggy's 43rd Item" );
	Item i2 = Item( 44, "item44", "Peggy's Item 44", "This is a description of Peggy's 44th Item" );
	Item i3 = Item( 42, "item", "Peggy's Other Item", "This is a description of Peggy's Item" );

	cout << "Size of inventory " << inventory.size() << endl;
	addToInventory( i );
	addToInventory( i2 );
	addToInventory( i3 );
	printInventory();
	inventory.remove( 42 );
	inventory.getItemIdFromString( "pete's awesome item" );
	cout << "Size of inventory " << inventory.size() << endl;
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
	inventory.printAllItems();
}

void
Actor::addToInventory( const Item& item )
{
	inventory.add( item );
}

void
Actor::removeFromInventory( const string& id )
{
	if( inventory.size()<=0 ) {
		cout << "There's nothing in your inventory to remove." << endl;
		return;
	}
	// TODO: convert string id to a size_t and pass to inventory.remove( size_t id )
	cout << "Attempting to remove id " << id << endl;
	size_t itemId = inventory.getItemIdFromString( id );
	//inventory.remove( itemId );
}
