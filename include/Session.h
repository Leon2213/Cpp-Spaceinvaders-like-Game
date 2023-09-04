#ifndef SESSION_H
#define SESSION_H

#include <vector>
#include "Component.h"
#include "Label.h"


namespace cwing {

	class Session
	{
	public:
		Session(int life, Label* lifeCounter, Label* GameOverText);
		void add(Component* c);
		std::vector<Component*>* getComps();
		void remove(Component* c);
		void takeDamage();
		void clearEnemies();
		void run();
		~Session();
	private:
		int life;
		Label* lifeCounter;
		Label* gameOvertext;

		std::vector<Component*> comps, removed, added;
	};
}
#endif