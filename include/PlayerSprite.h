#ifndef PLAYERSPRITE_H
#define PLAYERSPRITE_H

#include "Component.h"
#include <SDL2/SDL.h>
#include "Session.h"


namespace cwing {
    class PlayerSprite : public Component
    {
     public:
        static PlayerSprite* getInstance(Session* ses, std::string texturePath);
		   void draw() const;
         void tick(){}
         void keyDown(const SDL_Event&);
	      void mouseDown(const SDL_Event&); 
        ~PlayerSprite();
     protected:
        PlayerSprite(Session* ses, std::string texturePath);
     private:
      Session* ses;
     	SDL_Texture* texture;
      static const int startX = 25;
      static const int startY = 140; 
      static const int playerWidth = 80;
      static const int playerHeight = 80;
    };   

}
#endif