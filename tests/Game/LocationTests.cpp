#include "src/Game/Location.h"
#include <UnitTest++.h>
#include <sstream>
#include <string>

using namespace std;

SUITE( LocationTests )
{
	/* Tests a Location can be constructed and its name can be printed using the
	 * overloaded insertion operator.
	 */
	TEST( LocationConstruction )
	{
		Location l = Location( 1, "A_Location", 0, 0, 0, 0 );
		
		stringstream ss;
		ss << l;

		CHECK_EQUAL( "A_Location", ss.str() );
	}

	/* Tests the Location's Description accessor methods. */
	TEST( LocationDescription )
	{
		Location l = Location( 2, "MyLocation", 0, 0, 0, 0 );
		l.setDescription( "I'm a test description" );
		
		CHECK_EQUAL( "I'm a test description", l.getDescription() );
	}

	/* Tests that adjacent Location IDs are properly stored and returned. */
	TEST( CheckGetAdjacentLocationId )
	{
		Location l = Location( 3, "MyLocation", 2, 4, 6, -1 );

		CHECK_EQUAL( 2, l.getAdjacentLocationId( NORTH ) );
		CHECK_EQUAL( 4, l.getAdjacentLocationId( EAST ) );
		CHECK_EQUAL( 6, l.getAdjacentLocationId( SOUTH ) );
		CHECK_EQUAL( -1, l.getAdjacentLocationId( WEST ) );
	}
}
