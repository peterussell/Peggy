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

/* TODO: needs a unit test, compare names before and after, compare children before and after */
PJsonObjectNode::PJsonObjectNode( const PJsonObjectNode& other )
{
	name = other.name;
	children = other.children;
}
void
PJsonObjectNode::addChild( PJsonNode* n ) {
	n->parent = this;
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

vector<PJsonObjectNode*>
PJsonObjectNode::getObjectChildren() const
{
	vector<PJsonObjectNode*> newChildren = vector<PJsonObjectNode*>();
	for( int i=0; i<children.size(); i++) {
		if( typeid( *children[i] ) == typeid( PJsonObjectNode ) ) {
			cout << "Found super object " << children[i]->name << endl;
			newChildren.push_back( (PJsonObjectNode*) children[i] );
		}
	}

	for( int i=0; i<newChildren.size(); i++ ) {
		cout << "new object " << newChildren[i]->name << endl;
	}

	return newChildren;
}

// Int node
PJsonIntNode::PJsonIntNode( const int d )
: data( d ) { }

ostream&
PJsonIntNode::doPrint( ostream& os ) const
{
	return os << data;
}

void
PJsonIntNode::doPrint2()
{
	cout << data << endl;
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
