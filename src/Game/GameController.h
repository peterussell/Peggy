#ifndef GAME_GAMECONTROLLER_H
#define GAME_GAMECONTROLLER_H

#include "../Core/IOHandler.h"
#include "World.h"

class GameController {
	public:
		GameController();
		~GameController();

		int 			run();

	private:
		int 				doCommand( const string& );
		void 				startGame();
		
		IOHandler 	ioh;
		World 			world;
		bool 				gameStarted;
};

#endif
