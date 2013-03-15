#include "PJsonNode.h"

// Node base
PJsonNode::PJsonNode( const string& n="Unitialized" )
: name( n ) { }

//ostream&
//operator<<( const ostream& os, const PJsonNode& n )
//{
//	return n.doPrint( os );
//}

// String node
PJsonStringNode::PJsonStringNode( const string& d )
: data( d ) { }

ostream&
PJsonStringNode::doPrint( ostream& os ) const
{
	return os << data << endl;
}

// Object node
PJsonObjectNode::PJsonObjectNode()
{
	children = vector<PJsonNode*>();
}

void
PJsonObjectNode::addChild( PJsonNode* n ) {
	cout << "adding child..." << endl;
	cout << "child name = " << n->name << endl;

	cout << "size of children: " << children.size() << endl;
	children.push_back( n );
}

ostream&
PJsonObjectNode::doPrint( ostream& os ) const
{
	for( int i=0; i<children.size(); i++ ) {
		os << children[i] << ", ";
	}
	return os;
}

// Int node
PJsonIntNode::PJsonIntNode( const int d )
: data( d ) { }

ostream&
PJsonIntNode::doPrint( ostream& os ) const
{
	return os << data;
}

// Array node
PJsonArrayNode::PJsonArrayNode( const vector<PJsonNode*>& d )
{
//	for( vector<PJsonNode>::const_iterator it = d.begin(); it != d.end(); ++it ) {
//		//data.push_back( it );
//	}
}

ostream&
PJsonArrayNode::doPrint( ostream& os ) const
{
	//for( int i=0; i<data.size(); i++ ) {
	//	os << data[i] << ", ";
	//}
	return os;
}
