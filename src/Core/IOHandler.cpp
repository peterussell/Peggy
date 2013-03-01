#include "IOHandler.h"

IOHandler::IOHandler()
{
	//todo: IOHandler initialization code goes here
}

IOHandler::~IOHandler()
{
	//todo: IO handler destruction code goes here
}

void
IOHandler::printWelcomeScreen()
{
	cout << "> = = = = = = = = = = = = = = = = = = = = = = = = = = = = <" << endl;
	cout << "|                                                         |" << endl;
	cout << "|                  * PEGGY'S ADVENTURES *                 |" << endl;
	cout << "|                  - Theme Park of Doom -                 |" << endl;
	cout << "|                                                         |" << endl;
	cout << "> = = = = = = = = = = = = = = = = = = = = = = = = = = = = <" << endl;
	cout << endl;

	cout << "Type 'start' to begin, or 'commands' to see available commands." << endl;
}

void
IOHandler::printCommands() {
	cout << "Commands (case insensitive):" << endl;
	cout << "> 'decrypt <clue>'" << endl;
	cout << "   Decrypts a clue using its associated key (which you must have)." << endl;
	cout << "> 'drop <item>'" << endl;
	cout << "   Removes an item from your inventory and leaves it in the ground." << endl;
	cout << "> 'go <direction'" << endl;
	cout << "   Moves in the specified direction." << endl;
	cout << "> 'inventory' or 'i'" << endl;
	cout << "   Prints a description of items in your inventory" << endl;
	cout << "> 'look' or 'l''" << endl;
	cout << "   Prints a description of your surroundings." << endl;
	cout << "> 'lookat <item>'" << endl;
	cout << "   Prints a description of an item." << endl;
	cout << "> 'search' <container>'" << endl;
	cout << "   Searches a container (eg. toolbox) and lists any items inside." << endl;
	cout << "> 'take <item>'" << endl;
	cout << "   Picks an item up and stores it in your inventory." << endl;
	cout << "> 'talk <player>'" << endl;
	cout << "   Talks to another player." << endl;
	cout << "> 'use <item>'" << endl;
	cout << "   Uses the item and prints the outcome of using it." << endl;
	cout << "> 'quit', 'q', or 'exit'" << endl;
	cout << "   Quit the game." << endl << endl;
}

void IOHandler::loadWorld( const string filePath )
{
	if( filePath == "" ) {
		cout << "Error loading world, no path specified." << endl;
		return;
	}

	if( &_jsonReader == NULL ) {
		_jsonReader = PJsonReader();
	}

	_jsonReader.parse( filePath );
}

void
IOHandler::saveWorld()
{
}
