#ifndef CAMERA_H
#define CAMERA_H
#include "DisplayObjectContainer.h"

class Camera : public DisplayObjectContainer{ 

public:
	Camera();
	~Camera();

	int x = 0;
	int y = 0;
	int viewportWidth = 500;
	int viewportHeight = 500;

private:

	
};

#endif