#include "ItemContainer.h"

size_t
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
ItemContainer::remove( const size_t id )
{
	cout << "remove( " << id << " ) called." << endl;
	cout << "Searching for the item to remove..." << endl;

	int pos=0;
	for( vector<Item>::iterator it = items.begin(); it != items.end(); ++it ) {

		if( it->getId()==id ) {
			cout << "FOUND!" << endl;
			
			cout << "size before" << size() << endl;
			items.erase( items.begin()+pos );
			cout << "size after" << size() << endl;
			return;
		} else {
			cout << "Not found :(" << endl;
		}

	pos++;
	}
}

size_t
ItemContainer::getItemIdFromString( const string& name ) const
{
	cout << "ItemContainer.getItemIdFromString() called" << endl;
	cout << "-- string passed in: " << name << endl;
}

size_t
ItemContainer::getItemIdFromIdString( const string& idString ) const
{
	cout << "ItemContainer.getItemIdByIdString() called" << endl;
}

size_t
ItemContainer::getItemIdFromName( const string& name ) const
{
	cout << "ItemContainer.getItemIdByName() called" << endl;
}

size_t
ItemContainer::getItemIdFromShortName( const string& shortName ) const
{
	cout << "ItemContainer.getItemIdByShortName() called" << endl;
}
