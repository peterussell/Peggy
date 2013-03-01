#include "Item.h"
#include "../Core/StringHelpers.h"

void
Item::printName() const
{
	cout << name << endl;
}

void
Item::printShortDescription() const
{
	cout << description << endl;
}

void
Item::printLongDescription() const
{
	cout << longDescription << endl;
}

string
Item::getNameUpper() const
{
	string tmp = name;
	StringHelpers::toUpper( tmp );
	return tmp;
}

string
Item::getShortNameUpper() const
{
	string tmp = shortName;
	StringHelpers::toUpper( tmp );
	return tmp;
}
