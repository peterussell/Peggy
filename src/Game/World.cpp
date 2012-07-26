#include "World.h"

#include <string.h>
#include <iostream>
using namespace std;

World::World() {
	locations = vector<Location>();
	locations.push_back( Location( *this, 0, "Ticket Booth", 2, 5, -1, -1 ) );
	locations.push_back( Location( *this, 1, "Latex Lane", -1, -1, 2, -1 ) );
	locations.push_back( Location( *this, 2, "Centipede Carousel", 1, 3, 0, -1 ) );
	locations.push_back( Location( *this, 3, "Tax Return Alley", -1, 4, -1, 2 ) );
	locations.push_back( Location( *this, 4, "Wafer Thin Foodcourt", -1, -1, 7, 3 ) );
	locations.push_back( Location( *this, 5, "Bowling Ball Pit", -1, 6, 9, 0 ) );
	locations.push_back( Location( *this, 6, "Soul Twister", -1, 7, -1, 5 ) );
	locations.push_back( Location( *this, 7, "Second Aid Tent", 4, -1, 10, 6 ) );
	locations.push_back( Location( *this, 8, "Hippy Bath House", -1, 11, -1, -1 ) );
	locations.push_back( Location( *this, 9, "Canonical Courtyard", 5, -1, 12, -1 ) );
	locations.push_back( Location( *this, 10, "Corridor of Flesh", 7, -1, 23, 15 ) );
	locations.push_back( Location( *this, 11, "Freak Fall", -1, 12, 13, 8 ) );
	locations.push_back( Location( *this, 12, "Smegging Bumper Cars", 9, -1, 14, 11 ) );
	locations.push_back( Location( *this, 13, "Not-Too-Haunted House", 11, 14, 17, -1 ) );
	locations.push_back( Location( *this, 14, "Time Machine of Promptness", 12, 15, -1, 13 ) );
	locations.push_back( Location( *this, 15, "Spam Range", -1, 10, -1, 14 ) );
	locations.push_back( Location( *this, 16, "Luxury Tom Cruises", -1, 17, 18, -1 ) );
	locations.push_back( Location( *this, 17, "Amateur Surgery House", 13, -1, 19, 16 ) );
	locations.push_back( Location( *this, 19, "Embalming Mountain", 17, 20, -1, 18 ) );
	locations.push_back( Location( *this, 20, "Really-Quite-Haunted House", -1, 21, -1, 19 ) );
	locations.push_back( Location( *this, 21, "Total Gym of Doom", -1, 22, -1, 20 ) );
	locations.push_back( Location( *this, 22, "Artery Articulation", -1, 23, -1, 21 ) );
	locations.push_back( Location( *this, 23, "Acid Splash Mountain", 10, -1, -1, 22 ) );

	locations[0].addItem( Item( 0, "ticket", "Ticket Booth Item", "This is an item in the Ticket Booth" ) );
	locations[3].addItem( Item( 3, "tax", "Tax Return Alley Item", "This is an item in Tax Return Alley" ) );
	locations[7].addItem( Item( 7, "second", "Second Aid Tent Item", "This is an item in the Second Aid Tent" ) );
	locations[11].addItem( Item( 11, "freak", "Freak Fall Item", "This is an item in the Freak Fall" ) );
	locations[15].addItem( Item( 15, "spam", "Spam Range Item", "This is an item in Spam Range" ) );
	locations[19].addItem( Item( 19, "embalming", "Ebalming Mountain Item", "This is an embalming mountain item" ) );
	locations[21].addItem( Item( 21, "artery", "Artery Articulation Item", "This is an Artery Articulation item" ) );

	locations[7].addItem( Item ( 8, "second2", "Second Aid Tent Item 2", "This is the second item in the Second Aid Tent" ) );
	locations[15].addItem( Item ( 16, "spam2", "Spam Range Item 2", "This is the second item in Spam Range" ) );

	peggy = new Actor( "Peggy", locations[0] );
}

World::~World() {
	// empty all Location objects
}

void
World::peggyMove( const string& dName )
{
	Direction direction = getDirection( dName );
	if( direction==INVALID ) {
		return;
	}

	Location* currentLoc = peggy->getCurrentLocation();
	Location* newLoc = getAdjacentLocation( currentLoc, direction );

	peggy->setCurrentLocation( newLoc );
	// todo: player needs to be added to and removed from the locations' list of Actors
}

Location*
World::getAdjacentLocation( Location* loc, const Direction& dir )
{
	if( loc!=NULL ) {

		int adjLocId = loc->getAdjacentLocationId( dir );

		if( adjLocId > -1 ) {
			return getLocationById( adjLocId );
		} else {
			return loc; // return the current location if the adjacent one is invalid
		}

	} else {
		return loc;
	}
}

Location*
World::getLocationById( int id )
{
	if( id>=0 && id<locations.size() ) {
		return &(locations[id]);
	} else {
		return NULL;
	}
}

Direction
World::getDirection( const string& name )
{
	if( name.compare( "NORTH" ) == 0) {
		return NORTH;
	} else if( name.compare( "EAST" ) == 0 ) {
		return EAST;
	} else if( name.compare( "SOUTH" ) == 0 ) {
		return SOUTH;
	} else if( name.compare( "WEST" ) == 0 ) {
		return WEST;
	} else {
		return INVALID;
	}
}

void
World::peggyLook()
{
	peggy->look();
}

void
World::peggyPrintInventory()
{
	peggy->printInventory();
}

void
World::peggyDropFromInventory( const string& cmdParam )
{
	cout << "Param: " << cmdParam << endl;

	/* TODO:
			1. Figure out what the parameter is. It could be:
					a) an int, specifying the index of the item from the list we printed (it should be the item's vector index +1)
					b) a short name, eg. "sack" for a Big Brown Sack
					c) the full name, eg. "Big Brown Sack"
			2. Translate the parameter to an item ID. This function will be needed in the Location, Inventory and ContainerItem classes,
					so it probably makes sense to create an ItemHelpers class with static GetItemId( const string&, vector<Item>* ) and
					GetItemId( const size_t, vector<Item>* ) functions, these can then be referenced by any class that has an Item collection
					stored in it.
					ON SECOND THOUGHT: maybe anything with an Item collection should inherit from an abstract class that has these functions
					already in it... yeah, that sounds better.
			3. Get the item from the inventory (dropItem( ... ) will need to be modified to return an Item) and add it to the 
					current location.

					Note: peggyAddItemToInventory( .. ) should be similiar but the other way around.
	*/
}
