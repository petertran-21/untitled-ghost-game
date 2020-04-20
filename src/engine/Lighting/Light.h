#ifndef LIGHT_H
#define LIGHT_H

#include <vector>
#include "Game.h"
#include "DisplayObject.h"
#include "AffineTransform.h"
#include "Controller.h"
#include <string>
#include <fstream>

using namespace std;

class Light : public DisplayObject{

public:
  Light(string id, string color);
	virtual ~Light();

	virtual void update(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState);
	virtual void draw(AffineTransform &at);

  string id = "DEFAULT_LIGHT";
  string color;
  int direction = 0;
private:

  SDL_Texture* texture;


};

#endif
