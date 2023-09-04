#ifndef MOVABLESPRITE_H
#define MOVABLESPRITE_H

#include "Component.h"
#include <SDL2/SDL.h>
#include "Session.h"


namespace cwing {
    class MovableSprite : public Component
    {
     public:
        static MovableSprite* getInstance(int x, int y, Session* ses);
      int getRightSide();
      bool collision(Component* first, Component* other);
      bool rightSideCollision(Component* bullet, Component* enemy);
      bool topSideCollision(Component* bullet, Component* enemy);
      bool bottomSideCollision(Component* bullet, Component* enemy);
      bool aboveEnemy(Component* bullet, Component* enemy);
      bool belowEnemy(Component *bullet, Component* enemy);
		void draw() const;
        void tick();
        ~MovableSprite();
     protected:
        MovableSprite(int x, int y, Session* ses);
     private:
      static const int bulletWidth = 30;
      static const int bulletHeight = 20;
      const int bulletStopDistance = 550;
      Session* ses;
     	SDL_Texture* texture;
      //Session* ses;
    };   

}
#endif