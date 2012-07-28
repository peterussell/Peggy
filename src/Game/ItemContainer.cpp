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
	cout << "ItemContainer.removeItem() called" << endl;
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
