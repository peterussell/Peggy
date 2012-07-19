#include "src/Game/Item.h"
#include <UnitTest++.h>
#include <string>

using namespace std;

SUITE( ItemTests )
{
	/* Tests that an Item constructor correctly saves its name and
	 * description, and that they can be retreived using the Name()
	 * and Description() functions.
	 */
	TEST( ItemConstruction )
	{
		Item i = Item( 1, "My_Item", "This is a my new item" );

		CHECK_EQUAL( "My_Item", i.Name() );
	}
}
