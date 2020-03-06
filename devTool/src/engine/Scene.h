#ifndef SCENE_H
#define SCENE_H

#include "DisplayObjectContainer.h"
#include "Controller.h"
#include "Sprite.h"
#include <string>
#include <vector>
#include <fstream>

class Scene : public DisplayObjectContainer{

public:
	Scene();

	/* Load scene from a file */
	void loadScene(string sceneFilePath);
	void saveScene(string sceneFilePath);
	static vector<DisplayObject*>* getAllObjects(DisplayObject*);

	virtual void update(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState);
	virtual void draw(AffineTransform &at);


private:

};

#endif