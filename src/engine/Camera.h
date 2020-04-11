#ifndef CAMERA_H
#define CAMERA_H

#include "DisplayObjectContainer.h"
#include "Scene.h"
#include <vector>

using namespace std;

class Camera : public DisplayObjectContainer{ 

public:
	Camera();
	~Camera();

	virtual void draw(AffineTransform &at);
	virtual void changeScene(Scene* old_scene, Scene* new_scene);
private:
	
};

#endif