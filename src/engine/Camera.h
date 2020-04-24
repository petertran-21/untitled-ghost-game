#ifndef CAMERA_H
#define CAMERA_H

#include "DisplayObjectContainer.h"
#include "Scene.h"
#include "Ghost.h"

class Camera : public DisplayObjectContainer{ 

public:
	Camera();
	~Camera();

	virtual void draw(AffineTransform &at);
	virtual void update(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState);
	virtual void changeScene(Scene* old_scene, Scene* new_scene);

	//Allows the camera to track the Ghost
	void setGhost(Ghost* ghost);

private:
	Ghost* ghost;
	
};

#endif