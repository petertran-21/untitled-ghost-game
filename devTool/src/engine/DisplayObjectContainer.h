#ifndef DISPLAYOBJECTCONTAINER_H
#define DISPLAYOBJECTCONTAINER_H

#include "DisplayObject.h"
#include "AffineTransform.h"
#include "Controller.h"
#include <vector>
#include <string>
#include <fstream>

using namespace std;

class DisplayObjectContainer : public DisplayObject{

public:

	DisplayObjectContainer();
	DisplayObjectContainer(string id, string filepath);
	DisplayObjectContainer(string id, int red, int green, int blue);
	virtual ~DisplayObjectContainer();

	void addChild(DisplayObject* child);
	void removeImmediateChild(DisplayObject* child);
	void removeImmediateChild(string id);
	void removeChild(int index);
	void removeThis();

	virtual int numChildren();
	virtual DisplayObject* getChild(int index);
	virtual DisplayObject* getChild(string id);
	virtual DisplayObjectContainer* copy();

	virtual void update( set<SDL_Scancode> pressedKeys, Controller::JoystickState currState, Mouse* mouse, SDL_Renderer* renderer );
	virtual void draw( AffineTransform &at, SDL_Renderer* renderer, Mouse* mouse );

	//Node's children
	vector<DisplayObject*> children;

private:


};

#endif
