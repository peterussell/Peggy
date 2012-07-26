#include "World.h"
#include "Location.h"

#include <iostream>

Location&
Location::operator=( const Location& l )
{
	world = l.world;
	id = l.id;
	name = l.name;
	north = l.north;
	east = l.east;
	south = l.south;
	west = l.west;
}

Location::Location( 
	World& w,
	const int i, 
	const string& n,
	const int dn,
	const int de,
	const int ds,
	const int dw
	)
: world( w ),
	id( i ),
	name( n ),
	north( dn ),
	east( de ),
	south( ds ),
	west( dw )
{ }

Location::Location( const Location& l )
: world( l.world ),
	id( l.id ),
	name( l.name ),
	north( l.north ),
	east( l.east ),
	south( l.south ),
	west( l.west)
{ }

void
Location::printName()
{
	cout << name << endl;
}

void
Location::setDescription( const string& desc )
{
	description = desc;
	return;
}

string
Location::getDescription( void )
{
	return description;
}

int
Location::getAdjacentLocationId( const Direction& d )
{
	if( d == NORTH ) {

		return north;
	} else if( d == EAST ) {
		return east;
	} else if( d == SOUTH ) {
		return south;
	} else if( d == WEST ) {
		return west;
	} else {
		return -1;
	}
}

void
Location::addItem( const Item& item )
{
	items.push_back( item );
}

Item
Location::removeItem( const Item& item )
{
}

void
Location::printAllItems()
{
	if ( items.size() < 1 ) {
		cout << "This place is devoid of anything interesting." << endl;
		return;
	}
	cout << endl;

	cout << "There are " << items.size() << " items in " << name << endl;
	for( vector<Item>::iterator it = items.begin(); it!= items.end(); ++it ) {
		it->printName();
	}
	cout << endl;
}

void
Location::printExits()
{
	cout << "You see the following exits: " << endl;

	if( north>=0 ) {
		cout << " [NORTH]\t";
		world.getLocationById( north )->printName();
	}

	if( east>=0 ) {
		cout << " [EAST]\t\t";
		world.getLocationById( east )->printName();
	}

	if( south>=0 ) {
		cout << " [SOUTH]\t";
		world.getLocationById( south )->printName();
	}
	if( west>=0 ) {
		cout << " [WEST]\t\t";
		world.getLocationById( west )->printName();
	}
}

ostream&
operator<<( ostream& ostr, const Location& l )
{
	return ostr << l.name;
}
