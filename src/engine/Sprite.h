#ifndef SPRITE_H
#define SPRITE_H
#define SPRITE_SUBTYPE 2

#include "DisplayObjectContainer.h"
#include "Controller.h"

using namespace std;

class Sprite : public DisplayObjectContainer{

public:
	Sprite();
	Sprite(string id, string filepath);
	Sprite(string id, int red, int green, int blue);

	virtual void update(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState);
	virtual void draw(AffineTransform &at);

private:

};

#endif
