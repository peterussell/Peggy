#include "StringHelpers.h"

#include <iostream>
#include <sstream>

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
