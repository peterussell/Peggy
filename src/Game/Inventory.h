#ifndef GAME_INVENTORY_H
#define GAME_INVENTORY_H

#include "ItemContainer.h"

class Inventory : public ItemContainer
{
	public:
		Inventory() { };
		virtual ~Inventory() { };

		void			printAllItems();
};

#endif
