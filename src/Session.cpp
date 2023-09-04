#include "Session.h"
#include <SDL2/SDL.h>
#include "System.h"
#include "EnemySprite.h"
#include <string>

#include <iostream>

#define FPS 60

namespace cwing {

	Session::Session(int life, Label* healthCounter, Label* gameOverText){
		this->life = life;
		this->gameOvertext = gameOverText;
		lifeCounter = healthCounter;
		std::cout << "*** Session::Session()\n";
	}

	void Session::add(Component* component) {
		//comps.push_back(c);
		added.push_back(component);
	}

/*	 void Session::addEnemy(Component* enemy){
		enemies.push_back(enemy);	
	} */

	void Session::remove(Component* component){
		//std::cout << "*** removed()\n";
		removed.push_back(component);
	}

	/*void Session::removeEnemy(Component* component){
		//std::cout << "*** removed()\n";
		removedEnemies.push_back(component);
	}*/

	//removes a life
	void Session::takeDamage(){
		life --;
		lifeCounter->setText(std::to_string(life));
	}

	/*std::vector<Component*>* Session::getEnemies() {
		return &enemies;
	}*/

		std::vector<Component*>* Session::getComps() {
		return &comps;
	}

	void Session::clearEnemies(){
		for(Component* comp : *this->getComps()){
			if(EnemySprite* enemy = dynamic_cast<EnemySprite *>(comp) ){
					this->remove(enemy); // ta bort fiende sprite så den inte ritas ut, efter kollision
			}
		}
	}

	void Session::run() {
		//Initial values for the session -
		clearEnemies();
		bool quit = false;
		int spawnDelay = 0;
		life = 3;
		lifeCounter->setText(std::to_string(life));
		remove(gameOvertext);
		Uint32 tickInterval = 1000 / FPS;

		//loop while the session is still running
		while (!quit) {

			//spawn them with delay to stop overlapping
		    spawnDelay++;
				if( spawnDelay > 180){
					//randomize the spwn in y axis
					int nextY = rand() % 300 + 50;
					this->add(EnemySprite::getInstance(this, 550,nextY,100,50));
					spawnDelay = 0;
				}
			
			Uint32 nextTick = SDL_GetTicks() + tickInterval;

			//Input handling. 
			SDL_Event eve;
			while (SDL_PollEvent(&eve)) {
				switch (eve.type) {
				case SDL_QUIT: quit = true; break;
				case SDL_MOUSEBUTTONDOWN:
					for (Component* c : comps)
						c->mouseDown(eve);
					break;
				case SDL_MOUSEBUTTONUP:
					for (Component* c : comps)
						c->mouseUp(eve);
					break;
				case SDL_KEYDOWN:
					for (Component* c : comps)
						c->keyDown(eve);
					break;
				case SDL_KEYUP:
					for (Component* c : comps)
						c->keyUp(eve);
					break;

				} // switch
			} // inre while

			for (Component* c : comps) {
				c->tick();
			}

			//add objects to be drawn from buffer
			for (Component* c : added){
				comps.push_back(c);
			}
			added.clear();

			//Erase components corresponding from list of components so it is not redrawn
			Component* tbr;
			for (Component* c : removed){
				for (std::vector<Component*>::iterator i = comps.begin(); i != comps.end();) {
					if (*i == c) {
						i = comps.erase(i);
						 tbr = c;
					}
					else {
						i++;
					}
				}
			}
		
			removed.clear();

			//Draw sprites
			SDL_SetRenderDrawColor(sys.get_ren(), 255, 255, 255, 255);
			SDL_RenderClear(sys.get_ren());
			for (Component* c : comps)
				c->draw();
			SDL_RenderPresent(sys.get_ren());

			//wait the specified amount of time until next tick
			int delay = nextTick - SDL_GetTicks();	
			if (delay > 0)
				SDL_Delay(delay);

			if(life <= 0){
				quit = true;
			}

		} //yttre while

		//display game over text with an additonal draw call
		add(gameOvertext);
		gameOvertext->draw();
		SDL_RenderPresent(sys.get_ren());

	}

	Session::~Session()
	{
		delete lifeCounter;
		delete gameOvertext;
	}
}