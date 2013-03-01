#ifndef CORE_PJSONREADER_H
#define CORE_PJSONREADER_H

#include "PJsonNode.h"
#include <string>

using namespace std;

class PJsonReader
{
	public:
		PJsonReader();
		virtual ~PJsonReader();

		void parse( const string& filePath );

	private:
		string path;
		enum NodeType { OBJECT, STRING, INTEGER, ARRAY, BOOLEAN, NULLOBJ };

		void parseInternal( const string& contents );
		void eatWhiteSpace( const string& contents, int& index );
		NodeType getNodeType( const char& nodeStart );
		string parseName( const string& contents, int& index );
		PJsonObjectNode* parseObject( const string& contents, int& index );
		PJsonStringNode* parseString( const string& contents, int& index );
		PJsonIntNode* parseInteger( const string& contents, int& index);
		int goToNextQuote( const string& contents, int& index );
};
#endif
