#include "Component.h"

namespace cwing {

	Component::Component(int x, int y, int w, int h) :rect{ x,y,w,h }
	{
	}

	int Component::getRightSide() {
		return getRect().x + getRect().w;
	}

	int Component::getLeftSide() {
		return getRect().x;
	}

	int Component::getTopSide() {
		return getRect().y;
	}

	int Component::getBottomSide() {
		return getRect().y + getRect().h;
	}


	Component::~Component()
	{
	}
}