#ifndef CORE_PJSONWRITER_H
#define CORE_PJSONWRITER_H

#include <string>
#include <vector>
#include <map>

using namespace std;

class PJsonWriter
{
	public:
		PJsonWriter() { };
		~PJsonWriter() { };

		void openObject( const string& name );
		void closeObject();

		void writeNameValuePair( const string& name, const string& value );
		void writeNameValuePair( const string& name, const int& value );

		void writeArray( const vector<string>& values );
		void writeArray( const vector<int>& values );

		string getDocumentContents();
		int saveToFile( const string& fileName );


	private:
		string document;
		int openObjectCount;
};

#endif
