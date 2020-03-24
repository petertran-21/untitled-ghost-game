#ifndef SPRITE_H
#define SPRITE_H

#include "DisplayObjectContainer.h"
#include "Controller.h"

using namespace std;

class Sprite : public DisplayObjectContainer{

public:

	Sprite();
	Sprite(string id, string filepath);
	Sprite(string id, int red, int green, int blue);
	virtual Sprite* copy();

	virtual void update( set<SDL_Scancode> pressedKeys, Controller::JoystickState currState, SDL_Renderer* renderer );
	virtual void draw( AffineTransform &at, SDL_Renderer* renderer );

private:

};

#endif
