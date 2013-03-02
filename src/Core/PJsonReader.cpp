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

	int index = 0;
	PJsonObjectNode* root = parseObject( contents, index );
	fs.close();
}

PJsonObjectNode*
PJsonReader::parseObject( const string& contents, int& index )
{
	stack<string> parts;

	string nodeName = parseName( contents, index );
	cout << "parseName completed, JSON object name: " + nodeName << endl;

	eatWhiteSpace( contents, index );

	PJsonNode* node;
	NodeType type = getNodeType( contents[index] );
	cout << "Node type is " << type << endl;
	switch( getNodeType( contents[index] ) ) {
		case OBJECT:
		{
			//PJsonObjectNode* objNode = parseObject( contents, index );
			//objNode->name = nodeName;
			//cout << "I've parsed a node, its name is " << objNode->name << endl;
			node = parseObject( contents, index );
			break;
		}
		case STRING:
			node = parseString( contents, index );
			cout << "Finished parsing a string node. Value is ";
			cout << ((PJsonStringNode*)node)->getData() << endl;
			break;

		case INTEGER:
			node = parseInteger( contents, index );
			cout << "Finished parsing an int node. Value is ";
			cout << ((PJsonIntNode*)node)->getData() << endl;
			break;

		case ARRAY:
			node = parseArray( contents, index );
			cout << "Finished parsing an array node. Value is ";
			break;

		case BOOLEAN:
			cout << "bool";
			break;

		case NULLOBJ:
			cout << "null object";
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

//PJsonObjectNode*
//PJsonReader::parseObject( const string& contents, int& index )
//{
//	cout << "Parsing object node, starting at ";
//	for( int i=0; i<20; i++ ) {
//		cout << contents[index+i];
//	}
//	cout << endl;
//
//	return new PJsonObjectNode( vector<PJsonNode>() );
//}

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
	// get the whole string
	char c;
	cout << "parsing an integer" << endl;
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
	while( contents[index++] != '[' ) { } // skip past opening bracket

	PJsonArrayNode* node;
	string strVal = "";
	char c;
	while( true ) {
		cout << "Character is " << contents[index];
		if( contents[index] == ']' || index == contents.length() ) {
			cout << "==], breaking" << endl;
			break;
		}
		if( isspace( contents[index] ) ) {
			cout << " is a space, skipping" << endl;
			index++;
		} else {
			cout << " is a valid char, appending" << endl;
			index++;
		}
	}
	index++; // skip past the closing bracket

	cout << "Array contents: " << strVal << endl;

	if( strVal != "" ) {
		PJsonArrayNode::ArrayType type = getArrayType( strVal[0] );
		switch( type ) {
			case PJsonArrayNode::INTEGER:
				cout << "Parsing an int array!" << endl;
				break;
			case PJsonArrayNode::BOOLEAN:
				cout << "Parsing a boolean array!" << endl;
				break;
			case PJsonArrayNode::STRING:
			default:
				cout << "Parsing a string array!" << endl;
				break;
		}
	}

	return node;
	//cout << "array contents: " << strVal << endl << endl << endl;
	//while( true ) {
	//	if( contents[index] == ']' ) {
	//		break;
	//	} else if( contents[index] == '[' ) {
	//		index++;
	//	} else if( isspace( contents[index] ) ) {
	//		eatWhiteSpace( contents, index );
	//	} else {
	//		PJsonArrayNode::ArrayType type = getArrayType( contents[index] );
	//		switch( type ) {
	//			case PJsonArrayNode::INTEGER:
	//				cout << "Parsing an int array!" << endl;
	//				break;
	//			case PJsonArrayNode::BOOLEAN:
	//				cout << "Parsing a bool array!" << endl;
	//				break;
	//			case PJsonArrayNode::STRING:
	//			default:
	//				vector<PJsonNode*> data = parseStringArray( contents, index );
	//				cout << ((PJsonStringNode*)data[0])->getData() << endl;
	//				break;
	//		}
	//		break;
	//	}
	//}
}

vector<PJsonNode*>
PJsonReader::parseStringArray( const string& contents, int& index )
{
	vector<PJsonNode*> data = vector<PJsonNode*>();
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
