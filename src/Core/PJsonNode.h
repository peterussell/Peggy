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
		//friend ostream& operator<<( ostream& os, const PJsonNode& n );

	private:
		virtual ostream& doPrint( ostream& ) const = 0;
};

class PJsonStringNode : public PJsonNode
{
	public:
		PJsonStringNode( const string& data );
		ostream& doPrint( ostream& os ) const;

	private:
		string data;
};

class PJsonObjectNode : public PJsonNode
{
	public:
		PJsonObjectNode();
		void addChild( PJsonNode* node );
		ostream& doPrint( ostream& os ) const;

	private:
		vector<PJsonNode*> children;
};


class PJsonIntNode : public PJsonNode
{
	public:
		PJsonIntNode( const int data );
		int getData();
		ostream& doPrint( ostream& os ) const;

	private:
		int data;
};

class PJsonArrayNode : public PJsonNode
{
	public:
		PJsonArrayNode( const vector<PJsonNode*>& data );
		enum ArrayType { STRING, INTEGER, BOOLEAN };
		ostream& doPrint( ostream& os ) const;

	private:
		vector<PJsonNode> data;
};

#endif
