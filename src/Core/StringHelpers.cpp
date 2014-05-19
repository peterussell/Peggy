#include "StringHelpers.h"

#include <iostream>
#include <sstream>
#include <algorithm>

void
StringHelpers::toUpper( string& input )
{
	transform( input.begin(), input.end(), input.begin(), (int(*)(int))toupper );
}

size_t
StringHelpers::stringToInt( const string& input )
{
	int result;
	if( !( istringstream( input ) >> result ) ) {
		return -1; // failed to convert
	} else {
		return result;
	}
}
