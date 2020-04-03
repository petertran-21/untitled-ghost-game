#ifndef SCENE_H
#define SCENE_H

#include "DisplayObjectContainer.h"
#include "Sprite.h"
#include <string>
#include <vector>
#include <fstream>
#include "Controller.h"

class Scene : public DisplayObjectContainer{

public:
	Scene();

	/* Load scene from a file */
	void loadScene(string sceneFilePath);

	virtual void update(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState);
	virtual void draw(AffineTransform &at);

	bool isActive = true;		// Checked in Camera.h when drawing.
private:
};

#endif
