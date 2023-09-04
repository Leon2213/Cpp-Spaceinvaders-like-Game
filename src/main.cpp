

#include <SDL2/SDL.h>
#include "Label.h"
#include "Session.h"
#include "Button.h"
#include "PlayerSprite.h"
#include <string>
#include "EnemySprite.h"

#include <iostream>

/*
*   'gResPath' is a global constant defined in "Constants.h", 
*   representing the relative path to your resource folders as a string,
*   i.e. ' const std::string gResPath = "../../resources/" '
*   Use it through its namespace, 'constants::gResPath'.
*/

using namespace std;
using namespace cwing;


int main(int argc, char** argv) {
	std::cout << "*** main()\n";
	
	//Initial starting values
	Label* lifeCounter = Label::getInstance(25, 400, 50,50, "3");
	Label* gameOverLabel = Label::getInstance(200, 400, 300,50, "Game over. Press space to restart!");
	Session ses = Session(3, lifeCounter, gameOverLabel);
	Session* sesPointer = &ses;
	ses.add(lifeCounter);

	PlayerSprite* player = PlayerSprite::getInstance(sesPointer, "images/player.png");
	ses.add(player);

	// One enemy is created and added to the game at start. More enemies can be added here
	//  There is also a function in Session.run() for spawning enemies at random. 	
	EnemySprite* enemy1 = EnemySprite::getInstance(sesPointer, 450,200,100,50);
    ses.add(enemy1);

	SDL_Event eve;
	bool quit = false;
	bool running = true;

	//This loop controls restarting the game session.
	//In-game controll is handled by session
	while(!quit){
		if(running)
			ses.run();
		running = false;
		while(SDL_PollEvent(&eve)){
			if(eve.type == SDL_QUIT){
				quit = true;
				break;
			}
			if(eve.type == SDL_KEYDOWN && (eve.key.keysym.sym == SDLK_SPACE)){
				running = true;
				break;
			}
		}
	}
	
	return 0;
}