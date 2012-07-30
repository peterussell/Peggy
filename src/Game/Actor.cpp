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
	currentLocation->printName();

	// tmp - delete these after 'take' is implemented
	Item i = Item( 43, "item43", "Peggy's Item 43", "This is a description of Peggy's 43rd Item" );
	Item i2 = Item( 44, "item44", "Peggy's Item 44", "This is a description of Peggy's 44th Item" );
	Item i3 = Item( 42, "item", "Peggy's Other Item", "This is a description of Peggy's Item" );

	addToInventory( i );
	addToInventory( i2 );
	addToInventory( i3 );
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
	cout << "Picked up " << item.getName() << "." << endl;
}

void
Actor::removeFromInventory( const string& someIdentifier, Item& removedItem )
{
	if( inventory.size()<=0 ) {
		cout << "There's nothing in your inventory to drop." << endl;
		return;
	}

	int itemId = inventory.getItemIdFromString( someIdentifier );
	if( itemId < 0 ) {
		cout << "That item isn't in your inventory." << endl;
		return;
	}

	inventory.remove( itemId, removedItem );
	cout << "Dropped " << removedItem.getName() << "." << endl;
}
