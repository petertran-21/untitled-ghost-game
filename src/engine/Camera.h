#ifndef CAMERA_H
#define CAMERA_H
#include "DisplayObjectContainer.h"
#include "Scene.h"
#include "Tween.h"
#include <vector>

class Camera : public DisplayObjectContainer{ 

public:
	Camera();
	~Camera();

	int x = 0;
	int y = 0;
	int viewportWidth = 500;
	int viewportHeight = 500;

	virtual void draw(AffineTransform &at);
	virtual void changeScene(Scene* old_scene, Scene* new_scene);
private:

	
};

#endif