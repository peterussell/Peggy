#ifndef CORE_STRINGHELPERS_H
#define CORE_STRINGHELPERS_H

#include <string>

using namespace std;

class StringHelpers
{
	public:
		/* Converts a string to uppercase */
		static void toUpper( string& input );

		/* Attempts to convert a string to int. Returns -1 on failure */
		static size_t stringToInt( const string& input );
};

#endif
