#ifndef _PEGGY_GAME_CONTAINERITEM_H
#define _PEGGY_GAME_CONTAINERITEM_H

#include "Item.h"
#include <vector>

class ContainerItem
	: public Item {

	public:
		ContainerItem( size_t id, const string& n, const string& d );
		~ContainerItem();

	private:
		vector<Item> contained;
};

#endif
