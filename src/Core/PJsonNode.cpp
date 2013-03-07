#include "PJsonNode.h"

// Node base
PJsonNode::PJsonNode( const string& n="Unitialized" )
: name( n ) { }

// String node
PJsonStringNode::PJsonStringNode( const string& d )
: data( d ) { }

string
PJsonStringNode::getData()
{
	return data;
}

// Object node
PJsonObjectNode::PJsonObjectNode( const vector<PJsonNode*>& c )
{
	//children = new vector<PJsonNode*>( c );
}

void
PJsonObjectNode::addChild( const PJsonNode& n ) {
	//children.push_back( n );
}

// Int node
PJsonIntNode::PJsonIntNode( const int d )
: data( d ) { }

int
PJsonIntNode::getData()
{
	return data;
}

// Array node
PJsonArrayNode::PJsonArrayNode( const vector<PJsonNode*>& d )
{
//	for( vector<PJsonNode>::const_iterator it = d.begin(); it != d.end(); ++it ) {
//		//data.push_back( it );
//	}
}
