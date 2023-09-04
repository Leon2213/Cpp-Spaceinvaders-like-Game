#include "Constants.h"
#include "MovableSprite.h"
#include <SDL2/SDL_ttf.h>
#include "System.h"
#include <SDL2/SDL_image.h>
#include "EnemySprite.h"

namespace cwing {

	MovableSprite::MovableSprite(int x, int y, Session* ses)
		: Component(x, y, bulletWidth, bulletHeight)
	{
		texture = IMG_LoadTexture(sys.get_ren(), (constants::gResPath + "images/bullet.png").c_str() );
		(*this).ses = ses;

	}

	MovableSprite::~MovableSprite()
	{	
		SDL_DestroyTexture(texture);
	}


    MovableSprite* MovableSprite::getInstance(int x, int y, Session* ses) {
		return new MovableSprite(x, y, ses);
	}

	void MovableSprite::draw() const {
		// Code adjustment to handle the address to temporary object. 
		const SDL_Rect &rect = getRect();
		//SDL_RenderCopy(sys.ren, texture, NULL, &getRect());
		SDL_RenderCopy(sys.get_ren(), texture, NULL, &rect);
	}

  

    void MovableSprite::tick(){

		if ((*this).getRect().x >= bulletStopDistance) {
			ses->remove(this);
		}

		for(Component* comp : *ses->getComps()){
			if(EnemySprite* enemy = dynamic_cast<EnemySprite *>(comp) ){
				if(collision(this, enemy)){
					ses->remove(enemy); // ta bort fiende sprite så den inte ritas ut, efter kollision
					ses->remove(this);	// ta bort kulan så den inte ritas ut längre, efter kollision
				};
			}
		}
		(*this).getRect().x += 8;
    }

	bool MovableSprite::collision(Component* bullet, Component* enemy){
					// om kulans högra kant är inom spannet för fiendens vänstra kant och kulans TAK är inom spannet för fiendens höjd 
			if(  (rightSideCollision(bullet, enemy)) &&  (topSideCollision(bullet, enemy)) && !(aboveEnemy(bullet, enemy))){
				return true;
				   // om kulans högra kant är inom spannet för fiendens vänstra kant och kulans GOLV är inom spannet för fiendens höjd 
			} if (  (rightSideCollision(bullet, enemy))  &&  (bottomSideCollision(bullet, enemy) && !(belowEnemy(bullet, enemy))) ){
				return true; 
			} else {
				  // annars paserar kulan
				return false; 
			}

		
			
		}

	bool MovableSprite::rightSideCollision(Component* bullet, Component* enemy){
		return (bullet->getRightSide() >= enemy->getLeftSide());
	}

	// Denna eller den undre är alltid sann. Så ska det inte vara
	bool MovableSprite::topSideCollision(Component* bullet, Component* enemy){
		return (bullet->getTopSide() <= enemy->getBottomSide());
	}

	// Denna eller den över är alltid sann. Så ska det inte vara
	bool MovableSprite::bottomSideCollision(Component* bullet, Component* enemy){
		return (bullet->getBottomSide() >= enemy->getTopSide());
	}

	bool MovableSprite::aboveEnemy(Component* bullet, Component* enemy){
		return bullet->getBottomSide() < enemy->getTopSide();
	}

	bool MovableSprite::belowEnemy(Component* bullet, Component* enemy){
		return bullet->getTopSide() > enemy->getBottomSide();
	}

	




}
