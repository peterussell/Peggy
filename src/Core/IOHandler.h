#ifndef CORE_IOHANDLER_H
#define CORE_IOHANDLER_H

#include "PJsonReader.h"
#include "PJsonWriter.h"

#include <iostream>
using namespace std;

class IOHandler
{
	public:
		/* Initializer */
		IOHandler();

		/* Deconstructor */
		~IOHandler();

		/* Prints the game's welcome screen and initial instructions */
		void printWelcomeScreen();
		void printCommands();

		void loadWorld( const string filePath );
		void saveWorld();

	private:
		PJsonReader _jsonReader;
		PJsonWriter _jsonWriter;
};

#endif
