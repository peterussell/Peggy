#ifndef GAME_LOCATIONITEMS_H
#define GAME_LOCATIONITEMS_H

#include "ItemContainer.h"

class LocationItems : public ItemContainer
{
	public:
		LocationItems() { };
		virtual ~LocationItems() { };

		void			printAllItems();
};

#endif
