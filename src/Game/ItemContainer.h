#ifndef GAME_ITEM_CONTAINER_H
#define GAME_ITEM_CONTAINER_H

#include "Item.h"

#include <string.h>
#include <vector>

class ItemContainer
{
	public:
		ItemContainer() { };
		virtual ~ItemContainer() { };

		size_t		size() const;
		void			add( const Item& item );
		void			remove( const size_t id );
		size_t		getItemIdFromString( const string& name ) const;

		virtual void			printAllItems() = 0;

	protected:
		vector<Item> items;
	private:
		size_t		getItemIdFromIdString( const string& idString ) const;
		size_t		getItemIdFromName( const string& name ) const;
		size_t		getItemIdFromShortName( const string& shortName ) const;
};

#endif
