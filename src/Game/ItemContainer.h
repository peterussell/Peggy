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

		int				size() const;
		void			add( const Item& item );
		void			remove( const size_t id, Item& deletedItem ); // returns the item that was removed

		/* Checks the Container for the Item specified as a string.
		 * Arguments:
		 *  name - name of the item. Can either be an ID, the item's short name, 
		 *				 or the item's long name.
		 * Returns: the ID of the item if found in the Container, -1 otherwise.
		 */
		int		getItemIdFromString( const string& name ) const;

		virtual void			printAllItems() = 0;

	protected:
		vector<Item> items;
};

#endif
