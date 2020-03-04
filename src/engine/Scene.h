#ifndef SCENE_H
#define SCENE_H

#include "DisplayObjectContainer.h"
#include "Sprite.h"
#include <string>
#include <vector>
#include <fstream>

class Scene : public DisplayObjectContainer{

public:
	Scene();

	/* Load scene from a file */
	void loadScene(string sceneFilePath);
	virtual void update(set<SDL_Scancode> pressedKeys);
	virtual void draw(AffineTransform &at);
	
	vector<DisplayObjectContainer*> background;
	vector<DisplayObjectContainer*> middleground;
	vector<DisplayObjectContainer*> foreground;

private:

};

#endif