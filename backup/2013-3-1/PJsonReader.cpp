#include "PJsonReader.h"

#include <fstream>
#include <stack>

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

	parseInternal( contents );
	fs.close();
}

void
PJsonReader::parseInternal( const string& contents )
{
	stack<string> parts;

	int index = 0;
	string nodeName = parseName( contents, index );
	cout << "parseName completed, JSON object name: " + nodeName << endl;

	eatWhiteSpace( contents, index );

	cout << "NodeType: ";
	switch( getNodeType( contents[index] ) ) {
		case OBJECT:
		{
			PJsonObjectNode* objNode = parseObject( contents, index );
			break;
		}
		case STRING:
			cout << "string";
			break;
		case INTEGER:
			cout << "integer";
			break;
		case ARRAY:
			cout << "array";
			break;
		case BOOLEAN:
			cout << "bool";
			break;
		case NULLOBJ:
			cout << "null object";
			break;
	}

	cout << endl;

	//for( int i=1; i<contents.length(); i++ ) { // skip opening brace
	//	char ch = contents[i];

	//	// All JSON objects are name/value pairs.
	//	// The value can be a string, number, object, array, bool, null.
	//	// 1) read the name
	//	// 2) check the opening character of the value which will give us the type of value
	//	// 3) create the corresponding Node type, passing the Node content
	//	// 4) store the name and Node

	//	// 1) get the name
	//}

	//cout << endl;
}

/* Positions the index counter at the next non-whitespace character */
void
PJsonReader::eatWhiteSpace( const string& contents, int& index )
{
	while( isspace( contents[index] ) ) {
		index++;
	}

	// drop back one space
	//index--;
	// debugging
	cout << "Finished eating white space. Now at position " << index << ": ";
	for( int i=0; i<20; i++ ) {
		cout << contents[index+i];
	}
	cout << endl;
	// end debugging
}

PJsonReader::NodeType
PJsonReader::getNodeType( const char& nodeStart )
{
	switch( tolower( nodeStart ) ) {
		case '{':
			return OBJECT;
		case '\"':
			return STRING;
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

	index = goToNextQuote( contents, index );
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
	return name;

	//string name = "";
	//if( contents[index] != '"' ) {
	//	cout << "PJsonReader Error: object names must start with \" (at position " << index << "." << endl;
	//} else {
	//	index++;
	//}

	//while( contents[index] != '"' ) {
	//	name.append( 1, contents[index++] );
	//	if( index == contents.length() ) {
	//		cout << "PJsonReader Error: EOF while parsing object name. Started at " << startPos << "." << endl;
	//		return NULL;
	//	}
	//}
	//index++; // move past the closing quote
	//
	//eatWhiteSpace( contents, index );
	//if( contents[index] != ':' ) {
	//	cout << "PJsonReader Error: expected ':' after object name (at index " << index << "." << endl;
	//} else {
	//	index++;
	//	eatWhiteSpace( contents, index );
	//}
}

PJsonObjectNode*
PJsonReader::parseObject( const string& contents, int& index )
{
	cout << "Parsing object node, starting at [";
	for( int i=0; i<20; i++ ) {
		cout << contents[index+i];
	}
	cout << endl;

	return &PJsonObjectNode( vector<PJsonNode>() );
}

int
PJsonReader::goToNextQuote( const string& contents, int& index )
{
	for( int i = index; i < contents.length(); i++ ) {
		if( contents[i] == '"' ) {
			return i;
		}
	}
	return -1;
}
