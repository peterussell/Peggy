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
		//PJsonNode* find( const string& name, const PJsonObjectNode& startNode );
		PJsonNode* find( const string& name,  PJsonObjectNode* startNode ) const;

	private:
		string path;
		PJsonObjectNode* rootNode;
		enum NodeType { OBJECT, STRING, INTEGER, ARRAY, BOOLEAN, NULLOBJ };
		PJsonObjectNode* currentParent;


		// Parsers
		string parseName( const string& contents, int& index );
		PJsonObjectNode* parseInternal( const string& contents, int& index );
		PJsonNode* parseNode( const string& contents, int& index );
		PJsonObjectNode* parseObject( const string& contents, int& index );
		PJsonStringNode* parseString( const string& contents, int& index );
		PJsonIntNode* parseInteger( const string& contents, int& index);
		PJsonArrayNode* parseArray( const string& contents, int& index);

		// Array helpers
		PJsonArrayNode::ArrayType getArrayType( const char& c );
		vector<PJsonNode*> parseStringArray( const string& contents );
		vector<PJsonNode*> parseIntArray( const string& contents );

		// Helpers
		void eatWhiteSpace( const string& contents, int& index );
		NodeType getNodeType( const char& nodeStart );
		void findNextDelimiter( const string& contents, int& index );
};
#endif
