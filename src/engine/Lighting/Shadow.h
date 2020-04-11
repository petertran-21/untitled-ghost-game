#ifndef SHADOW_H
#define SHADOW_H

#include <vector>
#include "Game.h"
#include "DisplayObject.h"
#include "AffineTransform.h"
#include "Controller.h"
#include <string>
#include <fstream>

using namespace std;

class Shadow : public DisplayObject{

public:
  Shadow(string id, string color);
	virtual ~Shadow();

	virtual void update(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState);
	virtual void draw(AffineTransform &at);

  string id = "DEFAULT_SHADOW";
  string shape;
  int direction = 0;
private:

  SDL_Texture* texture;


};

#endif
