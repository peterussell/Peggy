#include "ItemContainer.h"
#include "../Core/StringHelpers.h"

int
ItemContainer::size() const
{
	return items.size();
}

void
ItemContainer::add( const Item& item )
{
	items.push_back( item );
}

void
ItemContainer::remove( const size_t id, Item& deletedItem )
{
	if( id < 0 || items.size() <= 0 ) {
		deletedItem = Item( -1, "", "", "" );
	}

	for( int i=0; i<items.size(); i++ ) {
		if ( items[i].getId()==id ) {
			deletedItem = items[i];
			items.erase( items.begin()+i );
			return;
		}
	}
}

int
ItemContainer::getItemIdFromString( const string& name ) const
{

	int id = StringHelpers::stringToInt( name );

	// If the string passed in was an ID, check for it when we iterate
	// through the items.
	bool checkForId = false;
	if( id >= 0 ) {
		checkForId = true;
	}

	for( vector<Item>::const_iterator it = items.begin(); it != items.end(); ++it ) {

		if( checkForId && it->getId()==id ) {
			// Found Item by its ID
			return id;
		} else if( strcmp( it->getShortNameUpper().c_str(), name.c_str() )==0 ) {
			// Found Item by its short name
			return it->getId();
		} else if( strcmp( it->getNameUpper().c_str(), name.c_str() )==0 ) {
			// Found Item by its long name
			return it->getId();
		}
	}

	// Didn't find item
	return -1;
}
