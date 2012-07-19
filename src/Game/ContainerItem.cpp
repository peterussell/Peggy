#include "ContainerItem.h"

ContainerItem::ContainerItem(
	size_t id,
	const string& n,
	const string& d=NULL
	) : Item( id, n, d )
{
}

ContainerItem::~ContainerItem()
{
}

//size_t
//ContainerItem::Add( const item& i )
//{
//}
