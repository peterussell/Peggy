#include "LocationItems.h"

void
LocationItems::printAllItems()
{
	if( items.size() <= 0 ) {
		cout << "There are no items here." << endl;
		return;
	}

	size_t count = 1;
	for( vector<Item>::iterator it = items.begin(); it != items.end(); ++it ) {
		cout << " " << count++ << ". ";
		it->printName();
		cout << "    ";
		it->printDescription();
	}
}
