#include "Inventory.h"

void
Inventory::printAllItems()
{
	if( items.size() <= 0 ) {
		cout << "You have no worldly possessions." << endl;
		return;
	}

	size_t count = 1;
	cout << "Digging through your inventory, you see.." << endl;
	for( vector<Item>::iterator it = items.begin(); it != items.end(); ++it ) {
		cout << " " << count++ << ". ";
		it->printName();
		cout << "    ";
		it->printDescription();
	}
}
