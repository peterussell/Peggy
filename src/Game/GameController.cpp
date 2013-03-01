#include "GameController.h"
#include "Location.h"
#include "../Core/StringHelpers.h"
#include "../Core/PJsonWriter.h"

#include <iostream>
#include "string.h"
using namespace std;

GameController::GameController()
{
	// world initialization
	//string worldFile = "data/default_world.json";
	string worldFile = "data/default_world.json";
	cout << "Loading world from file \"" << worldFile << "\"." << endl;

	ioh.loadWorld( worldFile );
	ioh = IOHandler();
	ioh.printWelcomeScreen();
}

GameController::~GameController()
{
	// todo: gamecontroller destruction code here
}

int
GameController::run()
{
	string cmd;
	int result = 1;
	while( result ) {
		// get input
		cout << "> ";
		if( !getline( cin, cmd ) ) {
			break;
		}
		StringHelpers::toUpper( cmd );
		result = doCommand( cmd );
	}
	return 0;
}

int
GameController::doCommand( const string& cmd ) {
	string cmdName, cmdParam;

	int splitAt = cmd.find( ' ' );
	if( splitAt != string::npos ) {
		cmdName = cmd.substr( 0, splitAt );
		cmdParam = cmd.substr( splitAt+1, cmd.length() );
	} else {
		cmdName = cmd;
	}

	// DEBUG:
	//cout << "Command Name: " << cmdName << ",\t Parameter:" << cmdParam << endl;

	// Command interpreter and dispatcher
	if( cmdName.compare( "COMMANDS" ) == 0 || cmdName.compare( "HELP" ) == 0 ) {
		ioh.printCommands();
	} else if( cmdName.compare( "DECRYPT" ) == 0 ) {
		cout << "Decrypting.." << endl; // TODO
	} else if( cmdName.compare( "DROP" ) == 0 ) {

		if( cmdParam.length() == 0 ) {
			cout << "Pick an item to drop from the inventory.." << endl;
			world.peggyPrintInventory();
			cout << endl;
		} else {
			world.peggyDrop( cmdParam );
		}

	} else if ( cmdName.compare( "GO" ) == 0 ) {

		if( cmdParam.length() == 0 ) {
			cout << "But, go where?" << endl;
		} else {
			world.peggyMove( cmdParam ); // move our Peggy
		}

	} else if( cmdName.compare( "INVENTORY" ) == 0 || cmdName.compare( "I" ) == 0 ) {
		// print Peggy's inventory
		world.peggyPrintInventory();
	} else if( cmdName.compare( "LOOK" ) == 0 || cmdName.compare( "L" ) == 0 ) {
		// print the list of items in the current Location
		world.peggyLook();
	} else if( cmdName.compare( "LOOKAT" ) == 0 ) {
		cout << "Looking at an item.." << endl;
	} else if( cmdName.compare( "SEARCH" ) == 0 ) {
		cout << "Searching a container.." << endl;
	} else if( cmdName.compare( "START" ) == 0 ) {
		if( gameStarted ) {
			cout << "You're already playing, ease up on the unicorn juice." << endl;
		} else {
			startGame();
			gameStarted = true;
		}
	} else if( cmdName.compare( "TAKE" ) == 0 ) {
		if( cmdParam.length() == 0 ) {
			cout << "Pick an item to take." << endl;
			world.peggyLook();
			cout << endl;
		} else {
			world.peggyTake( cmdParam );
		}
	} else if( cmdName.compare( "TALK" ) == 0 ) {
		cout << "Talking to another player.." << endl;
	} else if( cmdName.compare( "USE" ) == 0 ) {
		cout << "Using an item.." << endl;
	} else if( cmdName.compare( "QUIT" ) == 0 || 
							cmdName.compare( "Q" ) == 0  || 
							cmdName.compare( "EXIT" ) == 0 ) {
		return 0;
	}
	else {
		cout << "Sorry, I don't understand you." << endl;
	}
	return 1;
}

void
GameController::startGame() {
	cout << "Welcome to The Mutex, Peggy." << endl << endl;
	cout << "You find yourself peering into the entrance of a run-down, seemingly abandoned" << endl;
	cout << "amusement park. The dank smell of grease and elephant crap floods  your nostrils." << endl;
	cout << "You're not sure exactly why you're here. But Tommy G sent you, and Tommy G always" << endl;
	cout << "knows best." << endl << endl;

	cout << "What to do?" << endl;
}
