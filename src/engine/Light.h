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
	Light(DisplayObject* parent, string id, string color);
	virtual ~Light();

	virtual void update(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState);
	virtual void draw(AffineTransform &at);

	DisplayObject* parent;
  string id = "DEFAULT_LIGHT";
  string color;
private:

  SDL_Texture* texture;


};

#endif
