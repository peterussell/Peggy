#ifndef _PEGGY_GAME_ITEM_H
#define _PEGGY_GAME_ITEM_H

#include <iostream>
#include <string>

using namespace std;

class Item
{
	public:
		Item( const size_t ID, const string& n="NoName", const string& d=NULL ) :
			id( ID ),
			name( n ),
			description( d ) { }
		virtual ~Item() { }

		void printName();
		void printDescription() const;

	protected:
		size_t id;
		string name;
		string description;
};

#endif
