#include "Constants.h"
#include "PlayerSprite.h"
#include <SDL2/SDL_ttf.h>
#include "System.h"
#include <SDL2/SDL_image.h>
#include "MovableSprite.h"

namespace cwing {

	PlayerSprite::PlayerSprite(Session* ses, std::string texturePath)
		: Component(startX, startY, playerWidth, playerHeight), ses(ses)
	{
		texture = IMG_LoadTexture(sys.get_ren(), (constants::gResPath + texturePath).c_str() );
		//(*this).ses = ses;
	}

	PlayerSprite::~PlayerSprite()
	{
		SDL_DestroyTexture(texture);
	}


    PlayerSprite* PlayerSprite::getInstance(Session* ses, std::string texturePath) {
		return new PlayerSprite(ses, texturePath);
	}

	void PlayerSprite::draw() const {
		// Code adjustment to handle the address to temporary object. 
		const SDL_Rect &rect = getRect();
		//SDL_RenderCopy(sys.ren, texture, NULL, &getRect());
		SDL_RenderCopy(sys.get_ren(), texture, NULL, &rect);
	}

	void PlayerSprite::mouseDown(const SDL_Event& eve) {
		//spawn a bullet
		MovableSprite* bullet = MovableSprite::getInstance((*this).getRect().x,(*this).getRect().y, ses);
		ses->add(bullet);
	}

	void PlayerSprite::keyDown(const SDL_Event& eve){
		switch(eve.key.keysym.sym){
			case SDLK_UP:
				if(this->getRect().y > 0){
					(*this).getRect().y -= 6;

				}	
				break;
			case SDLK_DOWN:
				if(this->getRect().y <= 400){
					(*this).getRect().y += 6;

				}	
				break;
				
		}

	}

}
