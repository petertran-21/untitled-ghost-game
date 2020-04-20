#ifndef DISPLAYOBJECT_H
#define DISPLAYOBJECT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <set>
#include "AffineTransform.h"
#include "Controller.h"
#include "Mouse.h"

#define PI 3.14159265

using namespace std;

class DisplayObject{

public:
	string id = "DEFAULT_ID";
	string imgPath = "";
	string type = "DisplayObject";

	//Node's parent
	DisplayObject* parent = NULL;

	//Center?
	SDL_Point position = {0, 0};

	//Top-left?
	SDL_Point pivot = {0, 0};
	
	int width = 100;
	int height = 100;
	int alpha = 255;
	int red, green, blue;
	double scaleX = 1.0;
	double scaleY = 1.0;
	double rotation = 0.0; // in radians
	bool visible = true;
	bool isRGB = false;
	bool facingRight = true;
	bool selected = false;
	bool isBeingDragged = false;
	int subytpe;

	DisplayObject();
	DisplayObject(string id, string path);
	DisplayObject(string id, int red, int green, int blue);
	virtual ~DisplayObject();
	
	virtual void update( set<SDL_Scancode> pressedKeys, Controller::JoystickState currState, Mouse* mouse, SDL_Renderer* renderer );
	virtual void draw( AffineTransform &at, SDL_Renderer* renderer, Mouse* mouse );

	void loadTexture(string filepath);
	void loadRGBTexture(int red, int green, int blue);
	void setTexture(SDL_Texture* t);

	void applyTransformations(AffineTransform &at);
	void reverseTransformations(AffineTransform &at);
	virtual DisplayObject* copy();

	int getWidth();
	int getHeight();

private:
	double distance(SDL_Point &p1, SDL_Point &p2);
	double calculateRotation(SDL_Point &origin, SDL_Point &p);

	SDL_Texture* texture = NULL;
	SDL_Surface* image = NULL;
};

#endif
