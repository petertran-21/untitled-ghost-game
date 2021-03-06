#ifndef SCENE_H
#define SCENE_H

#include "DisplayObjectContainer.h"
#include "Controller.h"
#include "Sprite.h"
#include "AnimatedSprite.h"
#include "Camera.h"
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "json.hpp"
#include <iomanip>
#include <unordered_map>

using json = nlohmann::json;

using namespace std;

class Scene : public DisplayObjectContainer{

public:
	Scene();

	/* Load scene from a file */
	void loadScene(string sceneFilePath);
	void saveScene(string sceneFilePath);
	static vector<DisplayObject*>* getAllObjects(DisplayObject*);

	virtual void update( set<SDL_Scancode> pressedKeys, Controller::JoystickState currState, Mouse* mouse, SDL_Renderer* renderer );
	virtual void draw( AffineTransform &at, SDL_Renderer* renderer, Mouse* mouse );


private:

	bool noSpritesSelected = true;
    bool duplicatedLastFrame = true;

};

#endif