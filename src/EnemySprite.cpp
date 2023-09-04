#include "Constants.h"
#include <SDL2/SDL_ttf.h>
#include "System.h"
#include <SDL2/SDL_image.h>
#include "EnemySprite.h"

namespace cwing {

	EnemySprite::EnemySprite(Session* ses, int x, int y, int w, int h)
		: Component( x, y, w, h), ses(ses)
	{
		texture = IMG_LoadTexture(sys.get_ren(), (constants::gResPath + "images/rocket.png").c_str() );
		//texture = IMG_LoadTexture(sys.get_ren(), (constants::gResPath + "images/NerKnapp.png").c_str() );
	}

	EnemySprite::~EnemySprite()
	{
		SDL_DestroyTexture(texture);
	}


    EnemySprite* EnemySprite::getInstance(Session* ses, int x, int y, int w, int h) {
		return new EnemySprite(ses, x, y, w, h);
	}

	 void EnemySprite::tick(){
		if ((*this).getRect().x <= enemyStopDistance) {
			ses->takeDamage();
			ses->remove(this);
		}
			(*this).getRect().x--;
		}

	void EnemySprite::draw() const {
		// Code adjustment to handle the address to temporary object. 
		const SDL_Rect &rect = getRect();
		//SDL_RenderCopy(sys.ren, texture, NULL, &getRect());
		SDL_RenderCopy(sys.get_ren(), texture, NULL, &rect);
	}


}
