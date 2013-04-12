#include "PJsonReader.h"

#include <fstream>
#include <sstream>
#include <stack>
#include <algorithm>

PJsonReader::PJsonReader()
{
}

PJsonReader::~PJsonReader()
{
	// TODO: set the path to NULL, remove the file handle if applicable
}

void
PJsonReader::parse( const string& filePath )
{
	if( filePath == "" ) {
		cout << "PJsonReader Error: can't open file, no path specified." << endl;
		return;
	}

	path = filePath;
	cout << "Opening " << path << " for reading." << endl;

	ifstream fs( path.c_str(), ios::in );

	if( !fs ) {
		cout << "PJsonReader Error: can't open " << path << " for reading." << endl;
		fs.close();
		return;
	}

	string line = "", contents = "";
	while( getline( fs, line ) ) {
		contents.append( line + "\n" );
	}

	if( contents == "" ) {
		cout << "PJsonReader Error: " << path << " is empty." << endl;
		return;
	}

	int index = 0;
	PJsonObjectNode* root = parseInternal( contents, index );
	fs.close();

	//PJsonObjectNode* found = find( "ROOT_NODE", root );
	PJsonNode* found = find( "Health", root );

	((PJsonIntNode*)found)->doPrint2();
}

PJsonNode*
PJsonReader::find( const string& name, PJsonObjectNode* startNode ) const
{
	cout << "Searching " << startNode->name << " for a node called " << name << endl;
	if( startNode->name == name ) {
		cout << "FOUND IT!" << endl;
		return startNode;
	} else {
		cout << "Didn't find it. Looking for any child nodes and searching them." << endl;
		PJsonNode* child;
		for( int i=0; i<startNode->children.size(); i++ ) {

			child = startNode->children[i];
			cout << ".. found a child called " << child->name << ", match? ... ";
			if( child->name == name ) {
				cout << "YES! Returning."  << endl;
				return ( child );
			} else if( typeid( *child ) == typeid( PJsonObjectNode ) ) {
				cout << "No, but found an object - calling find on that instead." << endl;
				PJsonNode* found = find( name, (PJsonObjectNode*)child );
				if( found != NULL ) {
					return found;
				}
			}
			cout << "Nope." << endl;
		}
		cout << "Didn't find a damn thing, getting out of here." << endl;
		return NULL;
	}
}

PJsonObjectNode*
PJsonReader::parseInternal( const string& contents, int& index )
{
	rootNode = parseObject( contents, index );
	rootNode->name = "ROOT_NODE";
	if( rootNode == NULL ) {
		cout << "PJsonReader Error: unable to parse root node." << endl;
	}
	PJsonNode* node;
	PJsonNode* currentRoot = rootNode;
	while( index < contents.length() ) {
		findNextDelimiter( contents, index );

		if( contents[index] == '}' ) {
			// step back up the tree
			index++;
			cout << "Stepping back up the tree. The currentRoot's parent is" << currentRoot->parent->name << endl;
			if( currentRoot->parent->name == rootNode->name ) {
				cout << "Found end of file." << endl;
				return (PJsonObjectNode*)currentRoot;
			}
			currentRoot = currentRoot->parent;
			continue;
		}

		node = parseNode( contents, index );
		((PJsonObjectNode*)currentRoot)->addChild( node );

		if( typeid( *node ) == typeid( PJsonObjectNode ) ) {
			currentRoot = (PJsonObjectNode*)node;
		}
		cout << "Current Root = " << currentRoot->name << endl;
	}
}

PJsonNode*
PJsonReader::parseNode( const string& contents, int& index )
{
	string nodeName = parseName( contents, index );
	cout << "parseName completed, JSON object name: " + nodeName << endl;

	index++; // skip past opening quote
	eatWhiteSpace( contents, index );

	PJsonNode* node;
	switch( getNodeType( contents[index] ) ) {
		case OBJECT:
			node = parseObject( contents, index );
			break;
		case STRING:
			node = parseString( contents, index );
			break;
		case INTEGER:
			node = parseInteger( contents, index );
			break;
		case ARRAY:
			node = parseArray( contents, index );
			break;
		case BOOLEAN:
			cout << "bool";
			// TODO
			break;

		case NULLOBJ:
			cout << "null object";
			// TODO
			break;
	}
	node->name = nodeName;
	return node;
}

/* Positions the index counter at the next non-whitespace character */
void
PJsonReader::eatWhiteSpace( const string& contents, int& index )
{
	while( isspace( contents[index] ) ) {
		index++;
	}
}

PJsonReader::NodeType
PJsonReader::getNodeType( const char& nodeStart )
{
	switch( tolower( nodeStart ) ) {
		case '{':
			return OBJECT;
		case '\"':
			return STRING;
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			return INTEGER;
		case '[':
			return ARRAY;
		case 't':
		case 'f':
			return BOOLEAN;
		case 'n':
			return NULLOBJ;
	}
}

/* Returns the name (text surrounded by quotes followed by a colon) and positions the index after the name. */
string
PJsonReader::parseName( const string& contents, int& index )
{
	int startPos = index;

	//index = goToNextQuote( contents, index ); // this should be handled by parseInternal now
	char ch;
	string name;
	while( 1 ) {
		ch = contents[++index];
		if( ch == ':' ) {
			index++;
			break;
		} else if ( ch != '"' ) {
			name += ch;
		}
	}

	if( name == "LongDescription" ) {
		int i=0;
		i++;
	}
	return name;
}

PJsonObjectNode*
PJsonReader::parseObject( const string& contents, int& index )
{
	return new PJsonObjectNode();
}

/* Parses a string and returns a pointer to a new PJsonStringNode containing the string. Places the index after the closing quote surrounding the string. */
PJsonStringNode*
PJsonReader::parseString( const string& contents, int& index )
{
	while( contents[index++] != '"' ) { } // skip past opening quote
	
	string strVal = "";
	while( contents[index] != '"' ) {
		strVal += contents[index++];
	}
	index++; // skip past closing quote

	// BROKEN HERE - this should be moved out of this method, the string parser just parses the string and places the index after the closing quote. When this is re-implemented outside of this function it should also handle closing brackets in order to close nexted PJsonObject nodes (setting the currentRoot as the node's parent).
	//while( contents[index++] != ',' ) { } // skip past trailing comma

	cout << "Finished parsing a string node. String is " << strVal << endl;
	cout << "My current position is " << contents[index] << endl;
	cout << "My position -1 is " << contents[index-1] << endl;
	return new PJsonStringNode( strVal );
}

PJsonIntNode*
PJsonReader::parseInteger( const string& contents, int& index )
{
	char c;
	string strVal = "";
	while( true ) {
		c = contents[index];
		if( isdigit( c ) ) {
			strVal.append( &contents[index++] );
		} else {
			break;
	 }
 }

	int val = 0;
	if( strVal != "" )
	{
		val = atoi( strVal.c_str() );
	}
	return new PJsonIntNode( val );
}

PJsonArrayNode*
PJsonReader::parseArray( const string& contents, int& index )
{
	while( contents[index++] != '[' ) { } // find opening bracket and skip past it

	string innards = "";
	char c;
	while( true ) {
		c = contents[index];
		if( contents[index] == ']' || index == contents.length() ) {
			break;
		}
		if( isspace( contents[index] ) ) {
			index++;
		} else {
			innards += c;
			index++;
		}
	}
	index++; // skip past the closing bracket

	int eatFrom = 0;
	eatWhiteSpace( innards, eatFrom );
	PJsonArrayNode::ArrayType type = getArrayType( innards[0] );
	switch( type ) {
		case PJsonArrayNode::INTEGER:
		{
			cout << "Parsing an int array!" << endl;
			vector<PJsonNode*> toks = parseIntArray( innards );
			return new PJsonArrayNode( toks );
			break;
		}
		case PJsonArrayNode::BOOLEAN:
		{
			cout << "Parsing a boolean array!" << endl;
			break;
		}
		case PJsonArrayNode::STRING:
		default:
		{
			cout << "Parsing a string array!" << endl;
			vector<PJsonNode*> toks = parseStringArray( innards );
			return new PJsonArrayNode( toks );
			break;
		}
	}
}

vector<PJsonNode*>
PJsonReader::parseStringArray( const string& innards )
{
	vector<PJsonNode*> data = vector<PJsonNode*>();

	istringstream iss( innards );
	string token;
	while( getline( iss, token, ',' ) ) {
		PJsonStringNode n = PJsonStringNode( token );
		data.push_back( &n );
	}
	return data;
}

vector<PJsonNode*>
PJsonReader::parseIntArray( const string& innards )
{
	vector<PJsonNode*> data = vector<PJsonNode*>();

	istringstream iss( innards );
	string tok;
	char chars[] = "\"";
	while( getline( iss, tok, ',' ) ) {

		tok.erase( remove( tok.begin(), tok.end(), chars[0] ), tok.end() );
		char* pEnd;
		long int intVal = strtol( (tok.c_str()), &pEnd, 10 );
		cout << "parseIntArray parsed: " << intVal << endl;

		PJsonIntNode n = PJsonIntNode( intVal );
		data.push_back( &n );
	}
	return data;
}

PJsonArrayNode::ArrayType
PJsonReader::getArrayType( const char& c )
{
	switch( tolower( c ) ) {
		case '"':
			return PJsonArrayNode::STRING;
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			return PJsonArrayNode::INTEGER;
		case 't':
		case 'f':
			return PJsonArrayNode::BOOLEAN;
	}
}

void
PJsonReader::findNextDelimiter( const string& contents, int& index )
{
	for( int i=index; i<contents.length(); i++ ) {
		if( contents[i] == '"' || contents[i] == '}' ) {
			index = i;
			return;
		}
		//} else if( contents[i] == '}' ) {
		//	cout << "skipping a }" << endl;
		//	return i;
		//}
	}
}
