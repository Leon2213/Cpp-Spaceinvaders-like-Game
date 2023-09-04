#ifndef ENEMYSPRITE_H
#define ENEMYSPRITE_H

#include "Component.h"
#include <SDL2/SDL.h>
#include "Session.h"


namespace cwing {
    class EnemySprite : public Component
    {
     public:
        static EnemySprite* getInstance(Session* ses, int x, int y, int w, int h);
		   void draw() const;
         void tick();
         void keyDown(const SDL_Event&){};
	      void mouseDown(const SDL_Event&){}; 
        ~EnemySprite();
     protected:
        EnemySprite(Session* ses, int x, int y, int w, int h);
     private:
      int enemyStopDistance = 0;
      Session* ses;
     	SDL_Texture* texture;
    };   

}
#endif