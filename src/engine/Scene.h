#ifndef SCENE_H
#define SCENE_H
#define SCENE_TRIGGER_SUBTYPE 108

#include "DisplayObjectContainer.h"
#include "Sprite.h"
#include "AnimatedSprite.h"
#include "Ghost.h"
#include "json.hpp"

using json = nlohmann::json;

class Scene : public DisplayObjectContainer{

public:
	Scene();
	~Scene();

	void loadScene(string sceneFilePath, DisplayObjectContainer* collisionContainer);

	virtual void update(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState);
	virtual void draw(AffineTransform &at);
	void SaveScene();
	string FilePath;

	/**
	 * Checked in Camera.h when drawing.
	 */
	bool isActive = false;
private:

	//Intermediate step used in giving Ghost to the Camera
	Ghost* ghost;
	bool isGhostSentToCamera;
};

#endif
