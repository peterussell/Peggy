#include "PJsonWriter.h"

#include <iostream>

void
PJsonWriter::openObject( const string& name )
{
	document = document + name + " { ";
}

void
PJsonWriter::closeObject()
{
	document = document + " } ";
}

void
PJsonWriter::writeNameValuePair( const string& name, const string& value )
{
	// TODO
	cout << "Writing to name/value pair (string, string)..." << endl;
}

void
PJsonWriter::writeNameValuePair( const string& name, const int& value )
{
	// TODO
	cout << "Writing to name/value pair (string, int)..." << endl;
}

void
PJsonWriter::writeArray( const vector<string>& values )
{
	// TODO
	cout << "Writing to array (string)..." << endl;
}

void
PJsonWriter::writeArray( const vector<int>& values )
{
	// TODO
	cout << "Writing to array (int)..." << endl;
}

string
PJsonWriter::getDocumentContents()
{
	return document;
}

int
PJsonWriter::saveToFile( const string& fileName )
{
	// TODO
	cout << "Writing to file..." << endl;
}
