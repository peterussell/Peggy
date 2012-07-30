#ifndef _PEGGY_GAME_ITEM_H
#define _PEGGY_GAME_ITEM_H

#include <iostream>
#include <string>

using namespace std;

class Item
{
	public:
		Item( const size_t ID, const string& sn="NoShortName", const string& n="NoName", const string& d=NULL ) :
			id( ID ),
			shortName( sn ),
			name( n ),
			description( d ) { }
		virtual ~Item() { }

		void printName() const;
		void printDescription() const;

		size_t getId() const { return id; }
		string getName() const { return name; }
		string getShortName() const { return shortName; }

	protected:
		size_t id;
		string shortName;
		string name;
		string description;
};

#endif
