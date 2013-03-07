#ifndef CORE_PJSONNODE_H
#define CORE_PJSONNODE_H

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class PJsonNode
{
	public:
		PJsonNode( const string& node );
		virtual ~PJsonNode() { };
		string name;
};

class PJsonObjectNode : public PJsonNode
{
	public:
		PJsonObjectNode( const vector<PJsonNode*>& children );
		void addChild( const PJsonNode& node );

	private:
		vector<PJsonNode*> children;
};

class PJsonStringNode : public PJsonNode
{
	public:
		PJsonStringNode( const string& data );
		string getData();

	private:
		string data;
};

class PJsonIntNode : public PJsonNode
{
	public:
		PJsonIntNode( const int data );
		int getData();

	private:
		int data;
};

class PJsonArrayNode : public PJsonNode
{
	public:
		PJsonArrayNode( const vector<PJsonNode*>& data );
		enum ArrayType { STRING, INTEGER, BOOLEAN };

	private:
		vector<PJsonNode> data;
};

#endif
