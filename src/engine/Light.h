#ifndef LIGHT_H
#define LIGHT_H

#include <vector>
#include "DisplayObject.h"
#include "AffineTransform.h"
#include "Controller.h"
#include <string>
#include <fstream>

using namespace std;

class Light : public DisplayObject{

public:
	Light(DisplayObject* parent, string id, int red, int green, int blue);
	virtual ~Light();

  void loadRGBTexture(int red, int green, int blue);

	virtual void update(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState);
	virtual void draw(AffineTransform &at);

	DisplayObject* parent;
  string id = "DEFAULT_LIGHT";
private:


};

#endif
