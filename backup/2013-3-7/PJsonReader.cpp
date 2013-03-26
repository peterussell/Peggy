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
	PJsonObjectNode* root = parseObject( contents, index );
	fs.close();
}

PJsonObjectNode*
PJsonReader::parseObject( const string& contents, int& index )
{
	string nodeName = parseName( contents, index );
	cout << "parseName completed, JSON object name: " + nodeName << endl;

	eatWhiteSpace( contents, index );

	PJsonNode* node;
	NodeType type = getNodeType( contents[index] );
	cout << "Node type is " << type << endl;
	switch( getNodeType( contents[index] ) ) {
		case OBJECT:
		{
			node = parseObject( contents, index );
			break;
		}
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
	cout << "Created a new node, name = " << node->name << endl;
	cout << endl;

	// WORKING HERE: handle comma after objects
	parseObject( contents, index );
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
}

PJsonStringNode*
PJsonReader::parseString( const string& contents, int& index )
{
	while( contents[index++] != '"' ) { } // skip past opening quote

	string strVal = "";
	while( contents[index] != '"' ) {
		strVal += contents[index++];
	}

	while( contents[index++] != ',' ) { } // skip past trailing comma
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
		//int eatFrom = 0;
		//eatWhiteSpace( tok, eatFrom );

		tok.erase( remove( tok.begin(), tok.end(), chars[0] ), tok.end() );
		char* pEnd;
		long int intVal = strtol( (tok.c_str()), &pEnd, 10 );
		cout << "parseIntArray parsed: " << intVal << endl;
	}

	cout << "Size of int array created is " << data.size() << endl;
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
