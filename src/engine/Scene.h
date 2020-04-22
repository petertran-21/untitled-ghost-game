#ifndef SCENE_H
#define SCENE_H
#define SCENE_TRIGGER_SUBTYPE 108

#include "DisplayObjectContainer.h"
#include "Sprite.h"
#include "AnimatedSprite.h"
#include "json.hpp"
#include <iomanip>

using json = nlohmann::json;

class Scene : public DisplayObjectContainer{

public:
	Scene();
	~Scene();

	void loadScene(string sceneFilePath, DisplayObjectContainer* collisionContainer);
	void SaveScene(string sceneFilePath);

	virtual void update(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState);
	virtual void draw(AffineTransform &at);

	/**
	 * Checked in Camera.h when drawing.
	 */
	bool isActive = false;
private:

};

#endif
